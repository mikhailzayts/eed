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
    char * (* gets)(char * p_str, size_t size);
    int32_t (* puts)(const char * p_str);
} eed_io_iface_s;

/** Public function prototypes */

char * eed_io_gets(eed_io_iface_s * p_iface, char * p_str, size_t size);
char * eed_io_getline(eed_io_iface_s * p_iface, char * p_str, size_t size);
int32_t eed_io_puts(eed_io_iface_s * p_iface, const char * p_str);

#endif /** __EED_IO_H__ */
