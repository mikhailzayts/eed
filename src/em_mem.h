/**
 *  @file   em_mem.h
 *  @brief  Memory management dynamic interface
 *
 *  @author Mikhail Zaytsev
 *  @date   20230924
 */

#ifndef __EM_MEM_H__
#define __EM_MEM_H__

/** Includes */

#include <stddef.h>

/** Definitions */

/** Structures and types */

typedef struct em_mem_iface_s
{
    void * (*alloc)(size_t size);
    void   (*free)(void * ptr);
} em_mem_iface_s;

/** Public function prototypes */

void * em_mem_alloc (const em_mem_iface_s * p_iface, size_t size);
void   em_mem_free (const em_mem_iface_s * p_iface, void * ptr);

#endif /** __EM_MEM_H__ */
