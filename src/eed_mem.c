/**
 *  @file   eed_mem.c
 *  @brief  Memory management dynamic interface
 *
 *  @author Mikhail Zaytsev
 *  @date   20230924
 */

/** Includes */

#include "eed_mem.h"

/** Definitions */

/** Structures and types */

/** Private data */

/** Private function prototypes */

/** Public functions */

void * eed_mem_alloc (const eed_mem_iface_s * p_iface, size_t size)
{
    return p_iface->alloc(size);
}

void eed_mem_free (const eed_mem_iface_s * p_iface, void * ptr)
{
    p_iface->free(ptr);
}

/** Private functions */
