/**
*  @fs      eed_fs_mock.h
*  @brief   File system mock
*
*  @author  Mikhail Zaytsev
*  @date    20231003
*/

#ifndef __EED_FS_H__
#define __EED_FS_H__

/** Includes */

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

/** Structures and types */


/** Public functions prototypes */

int32_t eed_fs_mock_file_write(const char * p_file_name, const uint8_t * p_content, uint32_t size);
int32_t eed_fs_mock_file_read(const char * p_file_name, uint8_t * p_content, uint32_t size);

int32_t eed_fs_mock_file_size_get(const char * p_file_name);
int32_t eed_fs_mock_file_delete(const char * p_file_name);

#endif /** __EED_FS_H__ */
