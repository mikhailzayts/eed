/**
 *  @file   em_mem_mock.h
 *  @brief  em_mem module mock
 *
 *  @author Mikhail Zaytsev
 *  @date   20230924
 */

#ifndef __EM_MEM_SPY_H__
#define __EM_MEM_SPY_H__

/** Includes */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/** Definitions */

/** Structures and types */

/** Public function prototypes */

void   em_mem_mock_init (void);
void * em_mem_mock_alloc (size_t size);
void   em_mem_mock_free (void * ptr);

uint32_t em_mem_mock_alloc_call_count (void);
uint32_t em_mem_mock_free_call_count (void);

#endif /** __EM_MEM_SPY_H__ */
