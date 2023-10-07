/**
*  @file    eed_fs_posix.c
*  @brief   File system module POSIX implementation
*
*  @author  Mikhail Zaytsev
*  @date    20231003
*/

/** Includes */

#include "eed_fs_posix.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/** Definitions */


/** Structures and types */


/** Private data */


/** Private functions prototypes */


/** Public functions */

int32_t eed_fs_posix_file_write(const char * p_file_name, const uint8_t * p_content, uint32_t size)
{
    if ((NULL == p_file_name) || (NULL == p_content))
    {
        return -1;
    }

    FILE * p_desc = fopen(p_file_name, "w");
    if (NULL == p_desc)
    {
        return -1;
    }

    size_t writed_size = fwrite(p_content, sizeof(uint8_t), size, p_desc);
    int32_t ret = fclose(p_desc);
    return ret;
}

int32_t eed_fs_posix_file_read(const char * p_file_name, uint8_t * p_content, uint32_t size)
{
    if ((NULL == p_file_name) || (NULL == p_content))
    {
        return -1;
    }

    FILE * p_desc = fopen(p_file_name, "r");
    if (NULL == p_desc)
    {
        return -1;
    }

    size_t readed_size = fread(p_content, sizeof(uint8_t), size, p_desc);
    int32_t ret = fclose(p_desc);
    return ret;
}

int32_t eed_fs_posix_file_size_get(const char * p_file_name)
{
    if (NULL == p_file_name)
    {
        return -1;
    }

    FILE * p_desc = fopen(p_file_name, "r");
    if (NULL == p_desc)
    {
        return -1;
    }

    int32_t ret = fseek(p_desc, 0, SEEK_END);
    int32_t pos = ftell(p_desc);
    ret = fclose(p_desc);
    return pos;
}

int32_t eed_fs_posix_file_delete(const char * p_file_name)
{
    if (NULL == p_file_name)
    {
        return -1;
    }

    return remove(p_file_name);
}

/** Private functions */


