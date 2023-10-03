/**
*  @file    eed_fs_mock.c
*  @brief   File system mock
*
*  @author  Mikhail Zaytsev
*  @date    20231003
*/

/** Includes */

#include "eed_fs_mock.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/** Definitions */


/** Structures and types */


/** Private data */


/** Private functions prototypes */


/** Public functions */

int32_t eed_fs_mock_file_write(const char * p_file_name, const uint8_t * p_content, uint32_t size)
{
    FILE * p_desc = fopen(p_file_name, "w");
    size_t writed_size = fwrite(p_content, sizeof(uint8_t), size, p_desc);
    int32_t ret = fclose(p_desc);
    return ret;
}

int32_t eed_fs_mock_file_read(const char * p_file_name, uint8_t * p_content, uint32_t size)
{
    FILE * p_desc = fopen(p_file_name, "r");
    size_t readed_size = fread(p_content, sizeof(uint8_t), size, p_desc);
    int32_t ret = fclose(p_desc);
    return ret;
}

int32_t eed_fs_mock_file_size_get(const char * p_file_name)
{
    FILE * p_desc = fopen(p_file_name, "r");
    if (NULL == p_desc)
    {
        return -1;
    }

    int32_t ret = fseek(p_desc, 0, SEEK_END);
    ret = ftell(p_desc);
    fclose(p_desc);
    return ret;
}

int32_t eed_fs_mock_file_delete(const char * p_file_name)
{
    return remove(p_file_name);
}

/** Private functions */


