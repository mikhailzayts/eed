/**
*  @file   eed_io_mock.c
*  @brief  IO module mock
*
*  @author Mikhail Zaytsev
*  @date   20230925
*/

/** Includes */

#include "eed_io_mock.h"
#include <stdint.h>

/** Definitions */


/** Structures and types */

typedef struct eed_io_mock_ctx_s
{
    char * p_buffer;
    size_t size;
    uint32_t cursor;
} eed_io_mock_ctx_s;

/** Private data */

static eed_io_mock_ctx_s g_input;
static eed_io_mock_ctx_s g_output;

/** Private function prototypes */

static void eed_io_mock_ctx_set (eed_io_mock_ctx_s * p_ctx, char * p_buffer,
                                 size_t size);

/** Public functions */

void eed_io_mock_init(void)
{
    eed_io_mock_ctx_set(&g_input, NULL, 0);
    eed_io_mock_ctx_set(&g_output, NULL, 0);
}

int32_t eed_io_mock_getchar(char * p_chr)
{
    if ((NULL == p_chr) || (g_input.cursor >= g_input.size))
    {
        return -1;
    }

    *p_chr = g_input.p_buffer[g_input.cursor];
    g_input.cursor++;
    return 0;
}

void eed_io_mock_getchar_buffer_set(const char * p_buffer, size_t size)
{
    eed_io_mock_ctx_set(&g_input, (char *)p_buffer, size);
}

int32_t eed_io_mock_putchar(char chr)
{
    if (g_output.cursor >= g_output.size)
    {
        return -1;
    }

    g_output.p_buffer[g_output.cursor] = chr;
    g_output.cursor++;
    return 0;
}

void eed_io_mock_putchar_buffer_set(char * p_buffer, size_t size)
{    
    eed_io_mock_ctx_set(&g_output, p_buffer, size);
}

/** Private functions */

static void eed_io_mock_ctx_set(eed_io_mock_ctx_s * p_ctx, char * p_buffer, size_t size)
{
    p_ctx->p_buffer = (char *)p_buffer;
    p_ctx->size = size;
    p_ctx->cursor = 0;
}
