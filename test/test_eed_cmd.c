/**
 *  @file   test_eed_cmd.c
 *  @brief  eed_cmd module unit tests
 *
 *  @author Mikhail Zaytsev
 *  @date   20231007
 */

/** Includes */

#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "eed_mem.h"
#include "eed_fs.h"
#include "eed_io.h"
#include "eed_buf.h"
#include "eed_iface.h"

#include "eed_io_mock.h"
#include "eed_fs_posix.h"
#include "eed_mem_mock.h"
#include "eed_cmd.h"

/** Definitions */

#define TEST_FIRST_STR  "first"
#define TEST_SECOND_STR  "second"
#define TEST_THIRD_STR  "third"

/** Structures and types */

/** Private data */

static eed_buf_s g_buf;
static eed_iface_s g_iface;
static const char g_content[] = 
{
    TEST_FIRST_STR "\n"
    TEST_SECOND_STR "\n"
    TEST_THIRD_STR "\n"
};

/** Private function prototypes */

/** Public functions */

/**
 *  @brief  Set up operations for each test
 */
void setUp (void)
{
    g_iface.io_iface.getchar = eed_io_mock_getchar,
    g_iface.io_iface.putchar = eed_io_mock_putchar,
    g_iface.fs_iface.file_read = eed_fs_posix_file_read,
    g_iface.fs_iface.file_write = eed_fs_posix_file_write,
    g_iface.fs_iface.file_size_get = eed_fs_posix_file_size_get,
    g_iface.fs_iface.file_delete = eed_fs_posix_file_delete,
    g_iface.mem_iface.alloc = eed_mem_mock_alloc,
    g_iface.mem_iface.free = eed_mem_mock_free,

    eed_mem_mock_init();
    bool ret = eed_buf_init(&g_buf, &(g_iface.mem_iface));
}

/**
 *  @brief  Tear down operations for each test
 */
void tearDown (void)
{
}

/**
 *  @brief  Read command (r <filename>)
 */
void test_cmd_read (void)
{
    eed_fs_posix_file_write("edit.txt", (uint8_t *)g_content, sizeof(g_content));
    int32_t ret = 0;
    ret = eed_cmd_read(&g_iface, "edit.txt", &g_buf);

    TEST_ASSERT_EQUAL(0, ret);

    char * p_str = NULL;
    eed_buf_line_peek(&g_buf, &p_str, 0);
    TEST_ASSERT_EQUAL_STRING_LEN(TEST_FIRST_STR, p_str, strlen(p_str));
    eed_buf_line_peek(&g_buf, &p_str, 1);
    TEST_ASSERT_EQUAL_STRING_LEN(TEST_SECOND_STR, p_str, strlen(p_str));
    eed_buf_line_peek(&g_buf, &p_str, 2);
    TEST_ASSERT_EQUAL_STRING_LEN(TEST_THIRD_STR, p_str, strlen(p_str));

    eed_buf_deinit(&g_buf);
    TEST_ASSERT_EQUAL(eed_mem_mock_alloc_call_count(), eed_mem_mock_free_call_count());
}

/**
 *  @brief  Write command (w <filename>)
 */
void test_cmd_write (void)
{
    eed_buf_line_insert(&g_buf, TEST_FIRST_STR, eed_buf_size(&g_buf));
    eed_buf_line_insert(&g_buf, TEST_SECOND_STR, eed_buf_size(&g_buf));
    eed_buf_line_insert(&g_buf, TEST_THIRD_STR, eed_buf_size(&g_buf));
    int32_t ret = 0;
    ret = eed_cmd_write(&g_iface, "write.txt", &g_buf);

    TEST_ASSERT_EQUAL(0, ret);

    uint32_t size = (uint32_t)eed_fs_file_size_get(&(g_iface.fs_iface), "write.txt");
    char * p_written = (char *)eed_mem_alloc(&(g_iface.mem_iface), size);
    eed_fs_posix_file_read("write.txt", (uint8_t *)p_written, size);
    TEST_ASSERT_EQUAL_STRING_LEN(g_content, p_written, sizeof(g_content));
    eed_mem_free(&(g_iface.mem_iface), p_written);

    eed_buf_deinit(&g_buf);
    TEST_ASSERT_EQUAL(eed_mem_mock_alloc_call_count(), eed_mem_mock_free_call_count());
}

/**
 *  @brief  Print command (p)
 */
void test_cmd_print (void)
{
    TEST_IGNORE_MESSAGE("TODO");
}

/** TODO: add negative tests */
