/**
*  @file   test_eed_fs_mock.c
*  @brief  File system mock tests
*
*  @author Mikhail Zaytsev
*  @date   20231003
*/

/** Includes */

#include "eed_fs_mock.h"
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/** Definitions */


/** Private data */

static char g_buffer_exp[] = {"hello world\n"};

/** Private function prototypes */


/** Public functions */

void setUp (void) 
{
}

void tearDown (void) 
{

}

/** TODO: 
 *          - Add negative tests for NULL pointers, incorrect file names, etc.
 */

void test_file_read (void)
{
    char buffer[32] = {0};

    int32_t ret = eed_fs_mock_file_read("read.txt", (uint8_t *)buffer, strlen(g_buffer_exp));
    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL_STRING(g_buffer_exp, buffer);
}

void test_file_write (void)
{
    char buffer[32] = {0};

    int32_t ret = eed_fs_mock_file_write("write.txt", (uint8_t *)g_buffer_exp, strlen(g_buffer_exp));
    TEST_ASSERT_EQUAL(0, ret);

    eed_fs_mock_file_read("write.txt", (uint8_t *)buffer, strlen(g_buffer_exp));
    TEST_ASSERT_EQUAL_STRING(g_buffer_exp, buffer);
}

void test_file_size_get (void)
{
    int32_t ret = eed_fs_mock_file_size_get("read.txt");
    TEST_ASSERT_EQUAL(strlen(g_buffer_exp), ret);
}

void test_file_delete (void)
{
    int32_t ret = eed_fs_mock_file_write("write.txt", (uint8_t *)g_buffer_exp, strlen(g_buffer_exp));
    ret = eed_fs_mock_file_size_get("write.txt");
    TEST_ASSERT_EQUAL(strlen(g_buffer_exp), ret);

    ret = eed_fs_mock_file_delete("write.txt");
    TEST_ASSERT_EQUAL(0, ret);

    ret = eed_fs_mock_file_size_get("write.txt");
    TEST_ASSERT_EQUAL(true, 0 > ret);
}
