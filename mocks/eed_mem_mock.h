/**
 *  @file   eed_mem_mock.h
 *  @brief  eed_mem module mock
 *
 *  @author Mikhail Zaytsev
 *  @date   20230924
 */

#ifndef __EED_MEM_SPY_H__
#define __EED_MEM_SPY_H__

/** Includes */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/** Definitions */

/** Structures and types */

/** Public function prototypes */

void   eed_mem_mock_init (void);
void * eed_mem_mock_alloc (size_t size);
void   eed_mem_mock_free (void * ptr);

uint32_t eed_mem_mock_alloc_call_count (void);
uint32_t eed_mem_mock_free_call_count (void);

#endif /** __EED_MEM_SPY_H__ */
