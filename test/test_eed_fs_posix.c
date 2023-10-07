/**
*  @file   test_eed_fs_posix.c
*  @brief  File system module POSIX implementation tests
*
*  @author Mikhail Zaytsev
*  @date   20231003
*/

/** Includes */

#include "eed_fs_posix.h"
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/** Definitions */


/** Private data */

static const char g_buffer_exp[] = {"hello world\n"};

/** Private function prototypes */


/** Public functions */

void setUp (void) 
{
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

/** TODO: 
 *          - Add negative tests for NULL pointers, incorrect file names, etc.
 */

void test_file_read (void)
{
    char buffer[32] = {0};

    int32_t ret = eed_fs_posix_file_read("read.txt", (uint8_t *)buffer, strlen(g_buffer_exp));
    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL_STRING(g_buffer_exp, buffer);
}

void test_file_read_not_exists (void)
{
    char buffer[32] = {0};

    int32_t ret = eed_fs_posix_file_read("not_exists.txt", (uint8_t *)buffer, strlen(g_buffer_exp));
    TEST_ASSERT_NOT_EQUAL(0, ret);
}

void test_file_read_null (void)
{
    char buffer[32] = {0};

    int32_t ret = eed_fs_posix_file_read("read.txt", NULL, strlen(g_buffer_exp));
    TEST_ASSERT_NOT_EQUAL(0, ret);
}

void test_file_read_null_name (void)
{
    char buffer[32] = {0};

    int32_t ret = eed_fs_posix_file_read(NULL, (uint8_t *)buffer, strlen(g_buffer_exp));
    TEST_ASSERT_NOT_EQUAL(0, ret);
}

void test_file_write (void)
{
    char buffer[32] = {0};

    int32_t ret = eed_fs_posix_file_write("write.txt", (uint8_t *)g_buffer_exp, strlen(g_buffer_exp));
    TEST_ASSERT_EQUAL(0, ret);

    eed_fs_posix_file_read("write.txt", (uint8_t *)buffer, strlen(g_buffer_exp));
    TEST_ASSERT_EQUAL_STRING(g_buffer_exp, buffer);
}

void test_file_write_null (void)
{
    int32_t ret = eed_fs_posix_file_write("write.txt", NULL, strlen(g_buffer_exp));
    TEST_ASSERT_NOT_EQUAL(0, ret);
}

void test_file_write_null_name (void)
{
    int32_t ret = eed_fs_posix_file_write(NULL, (uint8_t *)g_buffer_exp, strlen(g_buffer_exp));
    TEST_ASSERT_NOT_EQUAL(0, ret);
}

void test_file_size_get (void)
{
    int32_t ret = eed_fs_posix_file_size_get("read.txt");
    TEST_ASSERT_EQUAL(sizeof(g_buffer_exp), ret);
}

void test_file_size_get_null (void)
{
    int32_t ret = eed_fs_posix_file_size_get(NULL);
    TEST_ASSERT_EQUAL(true, 0 > ret);
}

void test_file_size_get_not_exists (void)
{
    int32_t ret = eed_fs_posix_file_size_get("not_exists.txt");
    TEST_ASSERT_EQUAL(true, 0 > ret);
}

void test_file_delete (void)
{
    int32_t ret = eed_fs_posix_file_write("write.txt", (uint8_t *)g_buffer_exp, strlen(g_buffer_exp));
    ret = eed_fs_posix_file_size_get("write.txt");
    TEST_ASSERT_EQUAL(strlen(g_buffer_exp), ret);

    ret = eed_fs_posix_file_delete("write.txt");
    TEST_ASSERT_EQUAL(0, ret);

    ret = eed_fs_posix_file_size_get("write.txt");
    TEST_ASSERT_EQUAL(true, 0 > ret);
}

void test_file_delete_null (void)
{
    int32_t ret = eed_fs_posix_file_delete(NULL);
    TEST_ASSERT_NOT_EQUAL(0, ret);
}

void test_file_delete_not_exists (void)
{
    int32_t ret = eed_fs_posix_file_delete("not_exists.txt");
    TEST_ASSERT_NOT_EQUAL(0, ret);
}
