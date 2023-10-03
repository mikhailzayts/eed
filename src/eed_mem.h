/**
 *  @file   eed_mem.h
 *  @brief  Memory management dynamic interface
 *
 *  @author Mikhail Zaytsev
 *  @date   20230924
 */

#ifndef __EED_MEM_H__
#define __EED_MEM_H__

/** Includes */

#include <stddef.h>

/** Definitions */

/** Structures and types */

typedef struct eed_mem_iface_s
{
    void * (*alloc)(size_t size);
    void   (*free)(void * ptr);
} eed_mem_iface_s;

/** Public function prototypes */

void * eed_mem_alloc (const eed_mem_iface_s * p_iface, size_t size);
void   eed_mem_free (const eed_mem_iface_s * p_iface, void * ptr);

#endif /** __EED_MEM_H__ */
