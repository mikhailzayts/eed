/**
 *  @file   em_buf.h
 *  @brief  em buffer module. Buffer implemented as ring double linked list
 * structure
 *
 *  @author Mikhail Zaytsev
 *  @date   20230925
 */

#ifndef __EM_BUF_H__
#define __EM_BUF_H__

/** Includes */

#include "em_mem.h"
#include <stdbool.h>
#include <stdint.h>

/** Definitions */

/** Structures and types */

typedef struct em_buf_line_s em_buf_line_s;

struct em_buf_line_s
{
    char * p_str;

    em_buf_line_s * p_next;
    em_buf_line_s * p_prev;
};

typedef struct em_buf_s
{
    em_mem_iface_s mem_iface;

    em_buf_line_s * p_head;

    uint32_t len;
} em_buf_s;

/** Public function prototypes */

bool em_buf_init (em_buf_s * p_buf, const em_mem_iface_s * p_mem_iface);

bool em_buf_line_insert (em_buf_s * p_buf, const char * p_line, uint32_t pos);

bool em_buf_line_peek (em_buf_s * p_buf, char ** pp_line, uint32_t pos);

int32_t em_buf_len (em_buf_s * p_buf);

#endif /** __EM_BUF_H__ */
