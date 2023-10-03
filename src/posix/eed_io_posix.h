/**
*  @file   eed_io_posix.h
*  @brief  IO module POSIX implementation
*
*  @author Mikhail Zaytsev
*  @date   20230925
*/

#ifndef __EED_IO_POSIX_H__
#define __EED_IO_POSIX_H__

/** Includes */

#include <stddef.h>
#include <stdint.h>

/** Definitions */


/** Structures and types */


/** Public function prototypes */

int32_t eed_io_posix_getchar(char * p_chr);
int32_t eed_io_posix_putchar(char chr);

#endif /** __EED_IO_POSIX_H__ */
