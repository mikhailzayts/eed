/**
*  @file   test_eed_fs.c
*  @brief  File system dynamic interface tests
*
*  @author Mikhail Zaytsev
*  @date   20231003
*/

/** Includes */

#include "unity.h"
#include <stdbool.h>
#include <string.h>

#include "eed_fs_posix.h"
#include "eed_fs.h"

/** Definitions */


/** Private data */

static eed_fs_iface_s g_fs_iface;
static char g_buffer_exp[] = {"hello world\n"};

/** Private function prototypes */


/** Public functions */

void setUp(void) 
{
    g_fs_iface.file_read = eed_fs_posix_file_read;
    g_fs_iface.file_write = eed_fs_posix_file_write;
    g_fs_iface.file_size_get = eed_fs_posix_file_size_get;
    g_fs_iface.file_delete = eed_fs_posix_file_delete;

    FILE * p_desc = fopen("read.txt", "w");
    fwrite(g_buffer_exp, sizeof(uint8_t), sizeof(g_buffer_exp), p_desc);
    fclose(p_desc);
    remove("write.txt");
}

void tearDown (void) 
{
    remove("read.txt");
    remove("write.txt");
}

void test_iface(void)
{
    eed_fs_iface_s fs_iface =
    {
        .file_read = eed_fs_posix_file_read,
        .file_write = eed_fs_posix_file_write,
        .file_size_get = eed_fs_posix_file_size_get,
        .file_delete = eed_fs_posix_file_delete,
    };
}

void test_file_read (void)
{
    char buffer[32] = {0};

    int32_t ret = eed_fs_file_read(&g_fs_iface, "read.txt", (uint8_t *)buffer, strlen(g_buffer_exp));
    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL_STRING(g_buffer_exp, buffer);
}

void test_file_read_null (void)
{
    char buffer[32] = {0};

    int32_t ret = eed_fs_file_read(NULL, "read.txt", (uint8_t *)buffer, strlen(g_buffer_exp));
    TEST_ASSERT_NOT_EQUAL(0, ret);
}

void test_file_write (void)
{
    char buffer[32] = {0};

    int32_t ret = eed_fs_file_write(&g_fs_iface, "write.txt", (uint8_t *)g_buffer_exp, strlen(g_buffer_exp));
    TEST_ASSERT_EQUAL(0, ret);

    eed_fs_file_read(&g_fs_iface, "write.txt", (uint8_t *)buffer, strlen(g_buffer_exp));
    TEST_ASSERT_EQUAL_STRING(g_buffer_exp, buffer);
}

void test_file_write_null (void)
{
    int32_t ret = eed_fs_file_write(NULL, "write.txt", (uint8_t *)g_buffer_exp, strlen(g_buffer_exp));
    TEST_ASSERT_NOT_EQUAL(0, ret);
}

void test_file_size_get (void)
{
    int32_t ret = eed_fs_file_size_get(&g_fs_iface, "read.txt");
    TEST_ASSERT_EQUAL(sizeof(g_buffer_exp), ret);
}

void test_file_size_get_null (void)
{
    int32_t ret = eed_fs_file_size_get(NULL, "read.txt");
    TEST_ASSERT_EQUAL(true, 0 > ret);
}

void test_file_delete (void)
{
    int32_t ret = eed_fs_file_write(&g_fs_iface, "write.txt", (uint8_t *)g_buffer_exp, strlen(g_buffer_exp));
    ret = eed_fs_file_size_get(&g_fs_iface, "write.txt");
    TEST_ASSERT_EQUAL(strlen(g_buffer_exp), ret);

    ret = eed_fs_file_delete(&g_fs_iface, "write.txt");
    TEST_ASSERT_EQUAL(0, ret);

    ret = eed_fs_file_size_get(&g_fs_iface, "write.txt");
    TEST_ASSERT_EQUAL(true, 0 > ret);
}

void test_file_delete_null (void)
{
    int32_t ret = eed_fs_file_delete(NULL, "read.txt");
    TEST_ASSERT_NOT_EQUAL(0, ret);
}
