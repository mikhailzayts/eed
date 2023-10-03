/**
*  @file   eed_io_mock.h
*  @brief  IO module mock
*
*  @author Mikhail Zaytsev
*  @date   20230925
*/

#ifndef __EED_IO_MOCK_H__
#define __EED_IO_MOCK_H__

/** Includes */

#include <stddef.h>
#include <stdint.h>

/** Definitions */


/** Structures and types */


/** Public function prototypes */

void eed_io_mock_init(void);

int32_t eed_io_mock_getchar(char * p_chr);
void eed_io_mock_getchar_buffer_set(const char * p_buffer, size_t size);

int32_t eed_io_mock_putchar(char chr);
void eed_io_mock_putchar_buffer_set(char * p_buffer, size_t size);

#endif /** __EED_IO_MOCK_H__ */
