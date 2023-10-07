/**
 *  @file   eed_buf.h
 *  @brief  eed buffer module. Buffer implemented as ring double linked list
 * structure
 *
 *  @author Mikhail Zaytsev
 *  @date   20230925
 */

#ifndef __EED_BUF_H__
#define __EED_BUF_H__

/** Includes */

#include "eed_mem.h"
#include <stdbool.h>
#include <stdint.h>

/** Definitions */

/** Structures and types */

typedef struct eed_buf_line_s eed_buf_line_s;

struct eed_buf_line_s
{
    char * p_str;
    uint32_t len;

    eed_buf_line_s * p_next;
    eed_buf_line_s * p_prev;
};

typedef struct eed_buf_s
{
    eed_mem_iface_s mem_iface;

    eed_buf_line_s * p_head;

    uint32_t size;
} eed_buf_s;

/** Public function prototypes */

bool eed_buf_init (eed_buf_s * p_buf, const eed_mem_iface_s * p_mem_iface);
bool eed_buf_deinit (eed_buf_s * p_buf);

bool eed_buf_line_insert (eed_buf_s * p_buf, const char * p_line, uint32_t pos);
bool eed_buf_line_remove (eed_buf_s * p_buf, uint32_t pos);
bool eed_buf_line_copy (eed_buf_s * p_buf, uint32_t pos, uint32_t dest);
bool eed_buf_line_move (eed_buf_s * p_buf, uint32_t pos, uint32_t dest);

bool eed_buf_line_peek (eed_buf_s * p_buf, char ** pp_line, uint32_t pos);
int32_t eed_buf_line_len (eed_buf_s * p_buf, uint32_t pos);

int32_t eed_buf_size (eed_buf_s * p_buf);

#endif /** __EED_BUF_H__ */
