/**
*  @file   eed.h
*  @brief  eed main module
*
*  @author Mikhail Zaytsev
*  @date   20231007
*/

#ifndef __EED_H__
#define __EED_H__

/** Includes */

#include <stdint.h>
#include "eed_iface.h"
#include "eed_buf.h"

/** Definitions */


/** Structures and types */

typedef struct eed_ctx_s
{
    uint32_t cursor;
    char * p_filename;
    eed_iface_s * p_iface;
    eed_buf_s * p_buf;
} eed_ctx_s;

/** Public function prototypes */

int32_t eed_init (eed_ctx_s * p_ctx, eed_iface_s * p_iface);
int32_t eed_deinit (eed_ctx_s * p_ctx);
int32_t eed_exec (eed_ctx_s * p_ctx, const char * p_command);

#endif /** __EED_H__ */
