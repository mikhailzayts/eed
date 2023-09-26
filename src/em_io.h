/**
*  @file   em_io.h
*  @brief  IO module dynamic interface
*
*  @author Mikhail Zaytsev
*  @date   20230925
*/

#ifndef __EM_IO_H__
#define __EM_IO_H__

/** Includes */

#include <stdint.h>
#include <stddef.h>

/** Definitions */


/** Structures and types */

typedef struct em_io_iface_s
{
    char * (* gets)(char * p_str, size_t size);
    int32_t (* puts)(const char * p_str);
} em_io_iface_s;

/** Public function prototypes */

char * em_io_gets(em_io_iface_s * p_iface, char * p_str, size_t size);
char * em_io_getline(em_io_iface_s * p_iface, char * p_str, size_t size);
int32_t em_io_puts(em_io_iface_s * p_iface, const char * p_str);

#endif /** __EM_IO_H__ */
