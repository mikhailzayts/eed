/**
 *  @file   em_buf.c
 *  @brief  em buffer module. Buffer implemented as ring double linked list
 * structure
 *
 *  @author Mikhail Zaytsev
 *  @date   20230925
 */

/** Includes */

#include "em_buf.h"
#include <stddef.h>
#include <string.h>

/** Definitions */

/** Structures and types */

/** Private data */

/** Private function prototypes */

em_buf_line_s * em_buf_line_get_by_idx (em_buf_s * p_buf, uint32_t idx);

/** Public functions */

bool em_buf_init (em_buf_s * p_buf, const em_mem_iface_s * p_mem_iface)
{
    if (NULL == p_buf)
    {
        return false;
    }

    memset(p_buf, 0, sizeof(em_buf_s));
    p_buf->mem_iface.alloc = p_mem_iface->alloc;
    p_buf->mem_iface.free  = p_mem_iface->free;
    return true;
}

bool em_buf_line_insert (em_buf_s * p_buf, const char * p_line, uint32_t pos)
{
    if ((NULL == p_buf) || (NULL == p_line))
    {
        return false;
    }

    em_buf_line_s * p_new
        = em_mem_alloc(&(p_buf->mem_iface), sizeof(em_buf_line_s));

    uint32_t line_len = strlen(p_line) + sizeof('\0');
    p_new->p_str = (char *)em_mem_alloc(&(p_buf->mem_iface), line_len);
    memcpy(p_new->p_str, p_line, line_len);

    if (0 == p_buf->len)
    {
        p_buf->p_head = p_new;
        p_new->p_next = p_new;
        p_new->p_prev = p_new;
    }
    else
    {
        em_buf_line_s * p_next = p_buf->p_head;
        em_buf_line_s * p_prev = p_buf->p_head->p_prev;
        if (p_buf->len != pos)
        {
            p_next = em_buf_line_get_by_idx(p_buf, pos);
            p_prev = p_next->p_prev;
        }

        p_new->p_prev = p_prev;
        p_new->p_next = p_next;

        p_prev->p_next = p_new;
        p_next->p_prev = p_new;

        if (0 == pos) p_buf->p_head = p_new;
    }

    p_buf->len++;

    return true;
}

bool em_buf_line_peek (em_buf_s * p_buf, char ** pp_line, uint32_t pos)
{
    if ((NULL == p_buf) || (NULL == pp_line))
    {
        return false;
    }

    em_buf_line_s * p_curr = em_buf_line_get_by_idx(p_buf, pos);
    *pp_line               = p_curr->p_str;
    return true;
}

int32_t em_buf_len (em_buf_s * p_buf)
{
    if (NULL == p_buf)
    {
        return -1;
    }

    return p_buf->len;
}

/** Private functions */

em_buf_line_s * em_buf_line_get_by_idx (em_buf_s * p_buf, uint32_t idx)
{
    if ((NULL == p_buf) || (idx >= p_buf->len))
    {
        return NULL;
    }

    em_buf_line_s * p_cursor = p_buf->p_head;
    for (uint32_t tmp = 0; tmp < idx; tmp++)
    {
        p_cursor = p_cursor->p_next;
    }

    return p_cursor;
}
