/**
*  @file   eed_io_posix.c
*  @brief  IO module POSIX implementation
*
*  @author Mikhail Zaytsev
*  @date   20230925
*/

/** Includes */

#include "eed_io_posix.h"
#include <stdint.h>
#include <stdio.h>

/** Definitions */

/** Structures and types */

/** Private data */

/** Private function prototypes */

/** Public functions */

int32_t eed_io_posix_getchar(char * p_chr)
{
    if (NULL == p_chr)
    {
        return -1;
    }

    int32_t ret = getchar();
    if (0 > ret)
    {
        return -1;
    }

    *p_chr = ret;
    return 0;
}

int32_t eed_io_posix_putchar(char chr)
{
    return putchar(chr);
}

/** Private functions */
