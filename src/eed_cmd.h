/**
 *  @file   eed_cmd.h
 *  @brief  eed commands implementation
 *
 *  @author Mikhail Zaytsev
 *  @date   20231007
 */

#ifndef __EED_CMD_H__
#define __EED_CMD_H__

/** Includes */

#include "eed_buf.h"
#include "eed_fs.h"
#include "eed_iface.h"
#include "eed_mem.h"

/** Definitions */

/** Structures and types */

/** Public function prototypes */

int32_t eed_cmd_read (const eed_iface_s * p_iface, const char * p_file_name,
                      eed_buf_s * p_buf);
int32_t eed_cmd_write (const eed_iface_s * p_iface, const char * p_file_name,
                       eed_buf_s * p_buf);
int32_t eed_cmd_print (const eed_iface_s * p_iface, const eed_buf_s * p_buf,
                       uint32_t start_idx, uint32_t end_idx);

#endif /** __EED_CMD_H__ */
