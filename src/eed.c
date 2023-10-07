/**
 *  @file   eed.c
 *  @brief  eed main module
 *
 *  @author Mikhail Zaytsev
 *  @date   20231007
 */

/** Includes */

#include "eed.h"
#include "eed_buf.h"
#include "eed_io.h"
#include "eed_mem.h"
#include "eed_parse.h"
#include "eed_cmd.h"

#include <string.h>

/** Definitions */

/** Structures and types */

/** Private data */

/** Private function prototypes */

static uint32_t _pos_to_line_idx (const eed_ctx_s *       p_ctx,
                           const eed_parse_pos_s * p_pos);

/** Public functions */

int32_t eed_init (eed_ctx_s * p_ctx, eed_iface_s * p_iface)
{
    p_ctx->p_iface = eed_mem_alloc(&p_iface->mem_iface, sizeof(eed_iface_s));
    *(p_ctx->p_iface) = *p_iface;

    p_ctx->p_buf = eed_mem_alloc(&p_iface->mem_iface, sizeof(eed_buf_s));
    eed_buf_init(p_ctx->p_buf, &p_iface->mem_iface);

    p_ctx->cursor = 1;
    return 0;
}

int32_t eed_deinit (eed_ctx_s * p_ctx)
{
    eed_buf_deinit(p_ctx->p_buf);
    eed_mem_iface_s * p_mem_iface = &p_ctx->p_iface->mem_iface;
    eed_mem_free(p_mem_iface, p_ctx->p_buf);
    eed_mem_free(p_mem_iface, p_ctx->p_iface);
    return 0;
}

int32_t eed_exec (eed_ctx_s * p_ctx, const char * p_command)
{
    if (true == p_ctx->mode)
    {
        if (('.' == p_command[0]) && (1 == strlen(p_command)))
        {
            p_ctx->mode = false;
        }
        else
        {
            eed_buf_line_insert(p_ctx->p_buf, p_command, p_ctx->cursor);
        }
        return 0;
    }

    eed_parse_s parsed = {0};
    int32_t     ret    = eed_parse(p_command, &parsed);

    uint32_t start_idx = _pos_to_line_idx(p_ctx, &parsed.start);
    uint32_t end_idx   = _pos_to_line_idx(p_ctx, &parsed.end);

    if (start_idx > end_idx)
    {
        uint32_t tmp_idx = start_idx;
        start_idx        = end_idx;
        end_idx          = tmp_idx;
    }

    switch (parsed.cmd)
    {
        case EED_PARSE_CMD_PRINT:
            ret = eed_cmd_print(p_ctx->p_iface, p_ctx->p_buf, start_idx, end_idx);
            /** TODO: check return value */
            break;

        case EED_PARSE_CMD_INSERT:
            p_ctx->mode = true;
            p_ctx->cursor = start_idx;
            break;

        default:
            return -1;
    }

    return 0;
}

/** Private functions */

static uint32_t _pos_to_line_idx (const eed_ctx_s *       p_ctx,
                           const eed_parse_pos_s * p_pos)
{
    if (NULL == p_pos)
    {
        return -1;
    }

    uint32_t idx = 0;
    switch (p_pos->whence)
    {
        case EED_PARSE_WHENCE_START:
            idx = 0;
            break;

        case EED_PARSE_WHENCE_CURR:
            idx = p_ctx->cursor;
            break;

        case EED_PARSE_WHENCE_END:
            idx = eed_buf_size(p_ctx->p_buf);
            break;

        default:
            return -1;
    }
    idx += p_pos->offset;
    idx--;

    return idx;
}
