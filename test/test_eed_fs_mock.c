/**
*  @file   test_eed_fs.c
*  @brief  File system dynamic interface tests
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
    char buffer_exp[] = {"hello world\n"};
    char buffer[32] = {0};

    int32_t ret = eed_fs_mock_file_read("read.txt", (uint8_t *)buffer, strlen(buffer_exp));
    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL_STRING(buffer_exp, buffer);
}

void test_file_write (void)
{
    char buffer_exp[] = {"hello world\n"};
    char buffer[32] = {0};

    int32_t ret = eed_fs_mock_file_write("write.txt", (uint8_t *)buffer_exp, strlen(buffer_exp));
    TEST_ASSERT_EQUAL(0, ret);

    eed_fs_mock_file_read("write.txt", (uint8_t *)buffer, strlen(buffer_exp));
    TEST_ASSERT_EQUAL_STRING(buffer_exp, buffer);
}

void test_file_size_get (void)
{
    char buffer_exp[] = {"hello world\n"};
    int32_t ret = eed_fs_mock_file_size_get("read.txt");
    TEST_ASSERT_EQUAL(strlen(buffer_exp), ret);
}

void test_file_delete (void)
{
    char buffer_exp[] = {"hello world\n"};
    int32_t ret = eed_fs_mock_file_write("write.txt", (uint8_t *)buffer_exp, strlen(buffer_exp));
    ret = eed_fs_mock_file_size_get("write.txt");
    TEST_ASSERT_EQUAL(strlen(buffer_exp), ret);

    ret = eed_fs_mock_file_delete("write.txt");
    TEST_ASSERT_EQUAL(0, ret);

    ret = eed_fs_mock_file_size_get("write.txt");
    TEST_ASSERT_EQUAL(true, 0 > ret);
}
