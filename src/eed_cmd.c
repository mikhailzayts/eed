/**
*  @file   eed_cmd.c
*  @brief  eed command implementation functions
*
*  @author Mikhail Zaytsev
*  @date   20231007
*/

/** Includes */

#include "eed_cmd.h"
#include "eed_buf.h"
#include <string.h>

/** Definitions */

#define EED_CMD_NUL '\0' /**< Null symbol */
#define EED_CMD_LF  '\n' /**< Line feed symbol (new line) */

/** Structures and types */


/** Private data */


/** Private function prototypes */


/** Public functions */

int32_t eed_cmd_read (const eed_iface_s * p_iface, const char * p_file_name, eed_buf_s * p_buf)
{
    int32_t ret = eed_fs_file_size_get(&(p_iface->fs_iface), p_file_name);
    if (0 > ret) goto error;

    uint32_t size = (uint32_t)ret;
    char * p_content = (char *)eed_mem_alloc(&(p_iface->mem_iface), size + sizeof(EED_CMD_NUL));
    ret = eed_fs_file_read(&(p_iface->fs_iface), p_file_name, (uint8_t *)p_content, size);
    p_content[size] = EED_CMD_NUL;

    char * p_str = p_content;
    for (uint32_t idx = 0; idx < size; idx++)
    {
        if (EED_CMD_LF != p_content[idx])
        {
            continue;
        }

        if ((idx - sizeof(char)) != size)
        {
            p_content[idx] = EED_CMD_NUL;
        }

        ret = eed_buf_line_insert(p_buf, p_str, eed_buf_size(p_buf));
        if (0 > ret) goto free_err;

        p_str = &p_content[idx];
        p_str++;
    }
    
    eed_mem_free(&(p_iface->mem_iface), p_content);
    return 0;

free_err:
    eed_mem_free(&(p_iface->mem_iface), p_content);
error:
    return -1;
}

int32_t eed_cmd_write (const eed_iface_s * p_iface, const char * p_file_name, eed_buf_s * p_buf)
{
    int32_t ret = eed_buf_size(p_buf);
    if (0 > ret) goto error;

    uint32_t buf_len = (uint32_t)ret;
    uint32_t size = 0;
    for (uint32_t idx = 0; idx < buf_len; idx++)
    {
        ret = eed_buf_line_len(p_buf, idx);
        if (0 > ret) goto error;

        size += ret;
    }
    size += buf_len;

    char * p_content = (char *)eed_mem_alloc(&(p_iface->mem_iface), size + sizeof(EED_CMD_NUL));
    uint32_t cursor = 0;
    for (uint32_t idx = 0; idx < buf_len; idx++)
    {
        char * p_str = NULL;
        ret = eed_buf_line_peek(p_buf, &p_str, idx);
        if (0 > ret) goto free_err;

        ret = eed_buf_line_len(p_buf, idx);
        if (0 > ret) goto free_err;

        memcpy(&p_content[cursor], p_str, ret);
        cursor += ret;
        p_content[cursor] = EED_CMD_LF;
        cursor++;
    }
    p_content[size] = EED_CMD_NUL;

    ret = eed_fs_file_write(&(p_iface->fs_iface), p_file_name, (uint8_t *)p_content, size);
    if (0 > ret) goto free_err;

    eed_mem_free(&(p_iface->mem_iface), p_content);
    return 0;

free_err:
    eed_mem_free(&(p_iface->mem_iface), p_content);
error:
    return -1;
}

int32_t eed_cmd_print (const eed_iface_s * p_iface, const eed_buf_s * p_buf,
                       uint32_t start_idx, uint32_t end_idx)
{
    if ((NULL == p_iface) || (NULL == p_buf))
    {
        return -1;
    }

    int32_t ret = 0;
    for (uint32_t idx = start_idx; idx <= end_idx; idx++)
    {
        char *  p_str = NULL;
        bool    is_ok = eed_buf_line_peek((eed_buf_s *)p_buf, &p_str, idx);
        int32_t line_len = eed_buf_line_len((eed_buf_s *)p_buf, idx);
        if (0 > line_len)
        {
            return -1;
        }
        for (uint32_t idx = 0; idx < line_len; idx++)
        {
            ret = eed_io_putchar(&(p_iface->io_iface), p_str[idx]);
            if (0 > ret)
            {
                return -1;
            }
        }
    }

    return 0;
}

/** Private functions */

