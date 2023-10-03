/**
 *  @file   test_eed_cmd.c
 *  @brief  eed_cmd module unit tests
 *
 *  @author Mikhail Zaytsev
 *  @date   20230924
 */

/** Includes */

#include "eed_cmd.h"
#include "eed_buf.h"
#include "eed_mem.h"
#include "eed_mem_mock.h"
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/** Definitions */

#define TEST_PEAK_AND_CHECK(p_lines_exp, lines_count) \
    do \
    { \
        char * p_lines_peeked[lines_count]; \
        for (uint32_t idx = 0; idx < lines_count; idx++) \
        { \
            ret = eed_buf_line_peek(&g_buf, &p_lines_peeked[idx], idx); \
            TEST_MESSAGE(p_lines_peeked[idx]); \
            TEST_ASSERT_EQUAL(true, ret); \
        } \
        for (uint32_t idx = 0; idx < lines_count; idx++) \
        { \
            TEST_ASSERT_EQUAL_STRING(p_lines_exp[idx], p_lines_peeked[idx]); \
        } \
    } while (0)

#define TEST_ARRAY_SIZE(arr)    (sizeof(arr) / sizeof(arr[0]))

/** Structures and types */

/** Private data */

static eed_buf_s g_buf;

/** Private function prototypes */

/** Public functions */

/**
 *  @brief  Set up operations for each test
 */
void setUp (void)
{
    eed_mem_mock_init();
    eed_mem_iface_s mem_iface = {
        .alloc = eed_mem_mock_alloc,
        .free  = eed_mem_mock_free,
    };
    bool ret = eed_buf_init(&g_buf, &mem_iface);
}

/**
 *  @brief  Tear down operations for each test
 */
void tearDown (void)
{
}

/**
 *  @brief  Check if eed_mem interface compatible with POSIX memory
 *          management functions
 */
void test_init (void)
{
    eed_buf_s       buf;
    eed_mem_iface_s mem_iface = {
        .alloc = eed_mem_mock_alloc,
        .free  = eed_mem_mock_free,
    };
    bool ret = eed_buf_init(&buf, &mem_iface);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(NULL, buf.p_head);
    TEST_ASSERT_EQUAL(0, buf.len);
    TEST_ASSERT_EQUAL(eed_mem_mock_alloc, buf.mem_iface.alloc);
    TEST_ASSERT_EQUAL(eed_mem_mock_free, buf.mem_iface.free);
}
