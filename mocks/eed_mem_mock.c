/**
 *  @file   eed_mem_mock.c
 *  @brief  eed_mem module mock
 *
 *  @author Mikhail Zaytsev
 *  @date   20230924
 */

/** Includes */

#include "eed_mem_mock.h"
#include <stdlib.h>

/** Definitions */

/** Structures and types */

/** Private data */

static uint32_t g_alloc_call_count;
static uint32_t g_free_call_count;

/** Private function prototypes */

/** Public functions */

void eed_mem_mock_init (void)
{
    g_alloc_call_count = 0;
    g_free_call_count  = 0;
}

void * eed_mem_mock_alloc (size_t size)
{
    g_alloc_call_count++;
    return malloc(size);
}

void eed_mem_mock_free (void * ptr)
{
    g_free_call_count++;
    free(ptr);
}

uint32_t eed_mem_mock_alloc_call_count (void)
{
    return g_alloc_call_count;
}

uint32_t eed_mem_mock_free_call_count (void)
{
    return g_free_call_count;
}

/** Private functions */
