/**
*  @file   em_io_mock.h
*  @brief  IO module mock
*
*  @author Mikhail Zaytsev
*  @date   20230925
*/

#ifndef __EM_IO_MOCK_H__
#define __EM_IO_MOCK_H__

/** Includes */

#include <stddef.h>
#include <stdint.h>

/** Definitions */


/** Structures and types */


/** Public function prototypes */

void em_io_mock_init(void);

char * em_io_mock_gets(char * p_str, size_t size);
int32_t em_io_mock_puts(const char * p_str);

#endif /** __EM_IO_MOCK_H__ */
