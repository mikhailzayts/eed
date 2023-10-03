/**
*  @file   eed_fs.h
*  @brief  File system dynamic interface module
*
*  @author Mikhail Zaytsev
*  @date   20231003
*/

#ifndef __EED_FS_H__
#define __EED_FS_H__

/** Includes */

#include <stdint.h>

/** Definitions */

/** Structures and types */

typedef struct eed_fs_iface_s
{
    int32_t (* file_write)(const char * p_file_name, const uint8_t * p_content, uint32_t size);
    int32_t (* file_read)(const char * p_file_name, uint8_t * p_content, uint32_t size);

    int32_t (* file_size_get)(const char * p_file_name);
    int32_t (* file_delete)(const char * p_file_name);
} eed_fs_iface_s;

/** Public function prototypes */

int32_t eed_fs_file_write(const eed_fs_iface_s * p_iface, const char * p_file_name, const uint8_t * p_content, uint32_t size);
int32_t eed_fs_file_read(const eed_fs_iface_s * p_iface, const char * p_file_name, uint8_t * p_content, uint32_t size);

int32_t eed_fs_file_size_get(const eed_fs_iface_s * p_iface, const char * p_file_name);
int32_t eed_fs_file_delete(const eed_fs_iface_s * p_iface, const char * p_file_name);

#endif /** __EED_FS_H__ */
