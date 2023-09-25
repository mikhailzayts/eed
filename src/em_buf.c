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
void            _line_insert (em_buf_s * p_buf, em_buf_line_s * p_line,
                             em_buf_line_s * p_dest);
void            _line_remove (em_buf_s * p_buf, em_buf_line_s * p_line);
em_buf_line_s * _mem_alloc (em_buf_s * p_buf, const char * p_str);
void            _mem_free (em_buf_s * p_buf, em_buf_line_s * p_line);

/** Public functions */

bool em_buf_init (em_buf_s * p_buf, const em_mem_iface_s * p_mem_iface)
{
    if ((NULL == p_buf) || (NULL == p_mem_iface))
    {
        return false;
    }

    memset(p_buf, 0, sizeof(em_buf_s));
    p_buf->mem_iface.alloc = p_mem_iface->alloc;
    p_buf->mem_iface.free  = p_mem_iface->free;
    return true;
}

bool em_buf_deinit (em_buf_s * p_buf)
{
    if (NULL == p_buf)
    {
        return false;
    }

    uint32_t len = p_buf->len;
    for (uint32_t idx = 0; idx < len; idx++)
    {
        em_buf_line_remove(p_buf, 0);
    }
    return true;
}

bool em_buf_line_insert (em_buf_s * p_buf, const char * p_line, uint32_t pos)
{
    if ((NULL == p_buf) || (NULL == p_line))
    {
        return false;
    }

    em_buf_line_s * p_new = _mem_alloc(p_buf, p_line);

    if (0 == p_buf->len)
    {
        p_buf->p_head = p_new;
        p_new->p_next = p_new;
        p_new->p_prev = p_new;
    }
    else
    {
        em_buf_line_s * p_dest = p_buf->p_head;
        if (p_buf->len != pos)
        {
            p_dest = em_buf_line_get_by_idx(p_buf, pos);
        }
        _line_insert(p_buf, p_new, p_dest);
        if (0 == pos) p_buf->p_head = p_new;
    }

    p_buf->len++;

    return true;
}

bool em_buf_line_remove (em_buf_s * p_buf, uint32_t pos)
{
    if ((NULL == p_buf) || (pos >= p_buf->len) || (0 == p_buf->len))
    {
        return false;
    }

    em_buf_line_s * p_removed = em_buf_line_get_by_idx(p_buf, pos);

    _line_remove(p_buf, p_removed);
    _mem_free(p_buf, p_removed);
    p_removed = NULL;
    p_buf->len--;

    return true;
}

bool em_buf_line_copy (em_buf_s * p_buf, uint32_t pos, uint32_t dest)
{
    if ((NULL == p_buf) || (pos >= p_buf->len) || (0 == p_buf->len))
    {
        return false;
    }

    em_buf_line_s * p_copied = em_buf_line_get_by_idx(p_buf, pos);
    return em_buf_line_insert(p_buf, p_copied->p_str, dest);
}

bool em_buf_line_move (em_buf_s * p_buf, uint32_t pos, uint32_t dest)
{
    if ((NULL == p_buf) || (pos >= p_buf->len) || (0 == p_buf->len))
    {
        return false;
    }

    em_buf_line_s * p_moved = em_buf_line_get_by_idx(p_buf, pos);
    _line_remove(p_buf, p_moved);

    em_buf_line_s * p_dest = em_buf_line_get_by_idx(p_buf, dest);
    _line_insert(p_buf, p_moved, p_dest);
    if (0 == dest) p_buf->p_head = p_moved;
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

void _line_insert (em_buf_s * p_buf, em_buf_line_s * p_line,
                  em_buf_line_s * p_dest)
{
    if ((NULL == p_buf) || (NULL == p_line) || (NULL == p_dest))
    {
        return;
    }
    em_buf_line_s * p_next = p_dest;
    em_buf_line_s * p_prev = p_next->p_prev;

    p_line->p_prev = p_prev;
    p_line->p_next = p_next;

    p_prev->p_next = p_line;
    p_next->p_prev = p_line;
}

void _line_remove (em_buf_s * p_buf, em_buf_line_s * p_line)
{
    if ((NULL == p_buf) || (NULL == p_line))
    {
        return;
    }

    em_buf_line_s * p_next = p_line->p_next;
    em_buf_line_s * p_prev = p_line->p_prev;

    p_prev->p_next = p_next;
    p_next->p_prev = p_prev;

    if (p_buf->p_head == p_line) p_buf->p_head = p_next;
}

em_buf_line_s * _mem_alloc (em_buf_s * p_buf, const char * p_str)
{
    if ((NULL == p_buf) || (NULL == p_str))
    {
        return NULL;
    }

    em_buf_line_s * p_new
        = em_mem_alloc(&(p_buf->mem_iface), sizeof(em_buf_line_s));

    uint32_t line_len = strlen(p_str) + sizeof('\0');
    p_new->p_str      = (char *)em_mem_alloc(&(p_buf->mem_iface), line_len);
    memcpy(p_new->p_str, p_str, line_len);
    return p_new;
}

void _mem_free (em_buf_s * p_buf, em_buf_line_s * p_line)
{
    if ((NULL == p_buf) || (NULL == p_line))
    {
        return;
    }

    em_mem_free(&(p_buf->mem_iface), p_line->p_str);
    em_mem_free(&(p_buf->mem_iface), p_line);
}
