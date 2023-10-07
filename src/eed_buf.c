/**
 *  @file   eed_buf.c
 *  @brief  eed buffer module. Buffer implemented as ring double linked list
 * structure
 *
 *  @author Mikhail Zaytsev
 *  @date   20230925
 */

/** Includes */

#include "eed_buf.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

/** Definitions */

/** Structures and types */

/** Private data */

/** Private function prototypes */

eed_buf_line_s * _line_get_by_idx (eed_buf_s * p_buf, uint32_t idx);
void             _line_insert (eed_buf_s * p_buf, eed_buf_line_s * p_line,
                               eed_buf_line_s * p_dest);
void             _line_remove (eed_buf_s * p_buf, eed_buf_line_s * p_line);
eed_buf_line_s * _mem_alloc (eed_buf_s * p_buf, const char * p_str);
void             _mem_free (eed_buf_s * p_buf, eed_buf_line_s * p_line);

/** Public functions */

bool eed_buf_init (eed_buf_s * p_buf, const eed_mem_iface_s * p_mem_iface)
{
    if ((NULL == p_buf) || (NULL == p_mem_iface))
    {
        return false;
    }

    memset(p_buf, 0, sizeof(eed_buf_s));
    p_buf->mem_iface.alloc = p_mem_iface->alloc;
    p_buf->mem_iface.free  = p_mem_iface->free;
    return true;
}

bool eed_buf_deinit (eed_buf_s * p_buf)
{
    if (NULL == p_buf)
    {
        return false;
    }

    uint32_t len = p_buf->size;
    for (uint32_t idx = 0; idx < len; idx++)
    {
        eed_buf_line_remove(p_buf, 0);
    }
    return true;
}

bool eed_buf_line_insert (eed_buf_s * p_buf, const char * p_line, uint32_t pos)
{
    if ((NULL == p_buf) || (NULL == p_line))
    {
        return false;
    }

    eed_buf_line_s * p_new = _mem_alloc(p_buf, p_line);

    if (0 == p_buf->size)
    {
        p_buf->p_head = p_new;
        p_new->p_next = p_new;
        p_new->p_prev = p_new;
    }
    else
    {
        eed_buf_line_s * p_dest = p_buf->p_head;
        if (p_buf->size != pos)
        {
            p_dest = _line_get_by_idx(p_buf, pos);
        }
        _line_insert(p_buf, p_new, p_dest);
        if (0 == pos) p_buf->p_head = p_new;
    }

    p_buf->size++;

    return true;
}

bool eed_buf_line_remove (eed_buf_s * p_buf, uint32_t pos)
{
    if ((NULL == p_buf) || (pos >= p_buf->size) || (0 == p_buf->size))
    {
        return false;
    }

    eed_buf_line_s * p_removed = _line_get_by_idx(p_buf, pos);

    _line_remove(p_buf, p_removed);
    _mem_free(p_buf, p_removed);
    p_removed = NULL;
    p_buf->size--;

    return true;
}

bool eed_buf_line_copy (eed_buf_s * p_buf, uint32_t pos, uint32_t dest)
{
    if ((NULL == p_buf) || (pos >= p_buf->size) || (0 == p_buf->size))
    {
        return false;
    }

    eed_buf_line_s * p_copied = _line_get_by_idx(p_buf, pos);
    return eed_buf_line_insert(p_buf, p_copied->p_str, dest);
}

bool eed_buf_line_move (eed_buf_s * p_buf, uint32_t pos, uint32_t dest)
{
    if ((NULL == p_buf) || (pos >= p_buf->size) || (0 == p_buf->size))
    {
        return false;
    }

    eed_buf_line_s * p_moved = _line_get_by_idx(p_buf, pos);
    _line_remove(p_buf, p_moved);

    eed_buf_line_s * p_dest = _line_get_by_idx(p_buf, dest);
    _line_insert(p_buf, p_moved, p_dest);
    if (0 == dest) p_buf->p_head = p_moved;
    return true;
}

bool eed_buf_line_peek (eed_buf_s * p_buf, char ** pp_line, uint32_t pos)
{
    if ((NULL == p_buf) || (NULL == pp_line))
    {
        return false;
    }

    eed_buf_line_s * p_curr = _line_get_by_idx(p_buf, pos);
    *pp_line                = p_curr->p_str;
    return true;
}

int32_t eed_buf_line_len (eed_buf_s * p_buf, uint32_t pos)
{
    if ((NULL == p_buf) || (pos >= p_buf->size))
    {
        return -1;
    }

    eed_buf_line_s * p_curr = _line_get_by_idx(p_buf, pos);
    return p_curr->len;
}

int32_t eed_buf_size (eed_buf_s * p_buf)
{
    if (NULL == p_buf)
    {
        return -1;
    }

    return p_buf->size;
}

/** Private functions */

eed_buf_line_s * _line_get_by_idx (eed_buf_s * p_buf, uint32_t idx)
{
    if ((NULL == p_buf) || (idx >= p_buf->size))
    {
        return NULL;
    }

    eed_buf_line_s * p_cursor = p_buf->p_head;
    for (uint32_t tmp = 0; tmp < idx; tmp++)
    {
        p_cursor = p_cursor->p_next;
    }

    return p_cursor;
}

void _line_insert (eed_buf_s * p_buf, eed_buf_line_s * p_line,
                   eed_buf_line_s * p_dest)
{
    if ((NULL == p_buf) || (NULL == p_line) || (NULL == p_dest))
    {
        return;
    }
    eed_buf_line_s * p_next = p_dest;
    eed_buf_line_s * p_prev = p_next->p_prev;

    p_line->p_prev = p_prev;
    p_line->p_next = p_next;

    p_prev->p_next = p_line;
    p_next->p_prev = p_line;
}

void _line_remove (eed_buf_s * p_buf, eed_buf_line_s * p_line)
{
    if ((NULL == p_buf) || (NULL == p_line))
    {
        return;
    }

    eed_buf_line_s * p_next = p_line->p_next;
    eed_buf_line_s * p_prev = p_line->p_prev;

    p_prev->p_next = p_next;
    p_next->p_prev = p_prev;

    if (p_buf->p_head == p_line) p_buf->p_head = p_next;
}

eed_buf_line_s * _mem_alloc (eed_buf_s * p_buf, const char * p_str)
{
    if ((NULL == p_buf) || (NULL == p_str))
    {
        return NULL;
    }

    eed_buf_line_s * p_new
        = eed_mem_alloc(&(p_buf->mem_iface), sizeof(eed_buf_line_s));

    uint32_t line_len = strlen(p_str);
    p_new->p_str      = (char *)eed_mem_alloc(&(p_buf->mem_iface), line_len + sizeof(char));
    /** TODO: check null */
    memcpy(p_new->p_str, p_str, line_len);
    p_new->len = line_len;
    return p_new;
}

void _mem_free (eed_buf_s * p_buf, eed_buf_line_s * p_line)
{
    if ((NULL == p_buf) || (NULL == p_line))
    {
        return;
    }

    eed_mem_free(&(p_buf->mem_iface), p_line->p_str);
    eed_mem_free(&(p_buf->mem_iface), p_line);
}
