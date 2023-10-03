/**
*  @file   eed_fs.c
*  @brief  File system dynamic interface module
*
*  @author Mikhail Zaytsev
*  @date   20231003
*/

/** Includes */

#include "eed_fs.h"
#include <stddef.h>

/** Definitions */


/** Structures and types */


/** Private data */


/** Private function prototypes */


/** Public functions */

int32_t eed_fs_file_write(const eed_fs_iface_s * p_iface, const char * p_file_name, const uint8_t * p_content, uint32_t size)
{
    if (NULL == p_iface)
    {
        return -1;
    }

    p_iface->file_write(p_file_name, p_content, size);
    return 0;
}

int32_t eed_fs_file_read(const eed_fs_iface_s * p_iface, const char * p_file_name, uint8_t * p_content, uint32_t size)
{
    if (NULL == p_iface)
    {
        return -1;
    }

    p_iface->file_read(p_file_name, p_content, size);
    return 0;
}

int32_t eed_fs_file_size_get(const eed_fs_iface_s * p_iface, const char * p_file_name)
{
    if (NULL == p_iface)
    {
        return -1;
    }

    return p_iface->file_size_get(p_file_name);
}

int32_t eed_fs_file_delete(const eed_fs_iface_s * p_iface, const char * p_file_name)
{
    if (NULL == p_iface)
    {
        return -1;
    }

    return p_iface->file_delete(p_file_name);
}

/** Private functions */


