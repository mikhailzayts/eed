/**
*  @file   eed_iface.h
*  @brief  eed hardware and OS level interface
*
*  @author Mikhail Zaytsev
*  @date   20231004
*/

#ifndef __EED_IFACE_H__
#define __EED_IFACE_H__

/** Includes */

#include "eed_io.h"
#include "eed_fs.h"
#include "eed_mem.h"

/** Definitions */


/** Structures and types */

typedef struct eed_iface_s
{
    eed_io_iface_s io_iface;
    eed_fs_iface_s fs_iface;
    eed_mem_iface_s mem_iface;
} eed_iface_s;

/** Public function prototypes */


#endif /** __EED_IFACE_H__ */
