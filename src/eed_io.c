/**
*  @file   eed_io.c
*  @brief  IO module dynamic interface
*
*  @author Mikhail Zaytsev
*  @date   20231003
*/

/** Includes */


#include "eed_io.h"


/** Definitions */


/** Structures and types */


/** Private data */


/** Private function prototypes */


/** Public functions */

int32_t eed_io_getchar(const eed_io_iface_s * p_iface, char * p_chr)
{
    if (NULL == p_iface)
    {
        return -1;
    }

    p_iface->getchar(p_chr);

    return 0;
}

int32_t eed_io_putchar(const eed_io_iface_s * p_iface, char chr)
{
    if (NULL == p_iface)
    {
        return -1;
    }

    p_iface->putchar(chr);

    return 0;
}

/** Private functions */


