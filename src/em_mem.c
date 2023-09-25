/**
 *  @file   em_mem.c
 *  @brief  Memory management dynamic interface
 *
 *  @author Mikhail Zaytsev
 *  @date   20230924
 */

/** Includes */

#include "em_mem.h"

/** Definitions */

/** Structures and types */

/** Private data */

/** Private function prototypes */

/** Public functions */

void * em_mem_alloc (const em_mem_iface_s * p_iface, size_t size)
{
    return p_iface->alloc(size);
}

void em_mem_free (const em_mem_iface_s * p_iface, void * ptr)
{
    p_iface->free(ptr);
}

/** Private functions */
