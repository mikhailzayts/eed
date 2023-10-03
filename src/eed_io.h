/**
*  @file   eed_io.h
*  @brief  IO module dynamic interface
*
*  @author Mikhail Zaytsev
*  @date   20230925
*/

#ifndef __EED_IO_H__
#define __EED_IO_H__

/** Includes */

#include <stdint.h>
#include <stddef.h>

/** Definitions */


/** Structures and types */

typedef struct eed_io_iface_s
{
    int32_t (* getchar)(char * p_chr);
    int32_t (* putchar)(char chr);
} eed_io_iface_s;

/** Public function prototypes */

int32_t eed_io_getchar(const eed_io_iface_s * p_iface, char * p_chr);
int32_t eed_io_putchar(const eed_io_iface_s * p_iface, char chr);

#endif /** __EED_IO_H__ */
