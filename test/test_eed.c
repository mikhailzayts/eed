/**
 *  @file   test_eed.c
 *  @brief  eed module unit tests
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
#include "eed_io.h"
#include "eed_fs.h"
#include "eed_buf.h"
#include "eed_iface.h"

#include "eed_io_mock.h"
#include "eed_fs_posix.h"
#include "eed_mem_mock.h"
#include "eed_cmd.h"
#include "eed_parse.h"

#include "eed.h"

/** Definitions */

#define TEST_STR    "Hello, World!"
#define TEST_STR2   "Some another string"
#define TEST_STR3   "Coffee"
#define TEST_STR4   "ed is standard text editor"
#define TEST_STR5   "C programming language"

/** Structures and types */

/** Private data */

static eed_ctx_s g_ctx;
static eed_buf_s g_buf;
static eed_iface_s g_iface;
static char g_output_buf[512];
static char g_buffer_content[] = 
{
    TEST_STR 
    TEST_STR2
    TEST_STR3
    TEST_STR4
    TEST_STR5
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

    eed_io_mock_init();
    eed_io_mock_putchar_buffer_set(g_output_buf, sizeof(g_output_buf));
    eed_mem_mock_init();
    eed_buf_init(&g_buf, &(g_iface.mem_iface));
    eed_buf_line_insert(&g_buf, TEST_STR, eed_buf_size(&g_buf));
    eed_buf_line_insert(&g_buf, TEST_STR2, eed_buf_size(&g_buf));
    eed_buf_line_insert(&g_buf, TEST_STR3, eed_buf_size(&g_buf));
    eed_buf_line_insert(&g_buf, TEST_STR4, eed_buf_size(&g_buf));
    eed_buf_line_insert(&g_buf, TEST_STR5, eed_buf_size(&g_buf));

    g_ctx.cursor = 1;
    g_ctx.p_iface = &g_iface;
    g_ctx.p_buf = &g_buf;
}

/**
 *  @brief  Tear down operations for each test
 */
void tearDown (void)
{
}

/**
 *  @brief  Initialization
 */
void test_init (void)
{
    eed_ctx_s ctx = {0};
    int32_t ret = eed_init(&ctx, &g_iface);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(1, ctx.cursor);
    TEST_ASSERT_NOT_EQUAL(NULL, ctx.p_iface);
    TEST_ASSERT_NOT_EQUAL(NULL, ctx.p_buf);

    TEST_ASSERT_NOT_EQUAL(0, eed_mem_mock_alloc_call_count());
}

/**
 *  @brief  Deinitialization
 */
void test_deinit (void)
{
    eed_mem_mock_init();
    eed_ctx_s ctx = {0};
    eed_init(&ctx, &g_iface);

    int32_t ret = eed_deinit(&ctx);
    TEST_ASSERT_EQUAL(0, ret);

    TEST_ASSERT_EQUAL(eed_mem_mock_alloc_call_count(), eed_mem_mock_free_call_count());
}

/**
 *  @brief  Execute command
 */
void test_exec (void)
{
    int32_t ret = eed_exec(&g_ctx, "p");

    TEST_ASSERT_EQUAL(0, ret);
    TEST_MESSAGE(g_output_buf);
    TEST_ASSERT_EQUAL_STRING(TEST_STR, g_output_buf);
}

/**
 *  @brief  Print last line
 */
void test_print_last_line (void)
{
    int32_t ret = eed_exec(&g_ctx, "$p");

    TEST_ASSERT_EQUAL(0, ret);
    TEST_MESSAGE(g_output_buf);
    TEST_ASSERT_EQUAL_STRING(TEST_STR5, g_output_buf);
}

/**
 *  @brief  Print mid
 */
void test_print_mid (void)
{
    int32_t ret = eed_exec(&g_ctx, "4p");

    TEST_ASSERT_EQUAL(0, ret);
    TEST_MESSAGE(g_output_buf);
    TEST_ASSERT_EQUAL_STRING(TEST_STR4, g_output_buf);
}

/**
 *  @brief  Print range
 */
void test_print_range (void)
{
    char content[] = 
    {
        TEST_STR2
        TEST_STR3
        TEST_STR4
    };
    int32_t ret = eed_exec(&g_ctx, "2,4p");

    TEST_ASSERT_EQUAL(0, ret);
    TEST_MESSAGE(g_output_buf);
    TEST_ASSERT_EQUAL_STRING(content, g_output_buf);
}


