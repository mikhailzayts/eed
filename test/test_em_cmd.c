/**
 *  @file   test_em_cmd.c
 *  @brief  em_cmd module unit tests
 *
 *  @author Mikhail Zaytsev
 *  @date   20230924
 */

/** Includes */

#include "em_cmd.h"
#include "em_buf.h"
#include "em_mem.h"
#include "em_mem_mock.h"
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
            ret = em_buf_line_peek(&g_buf, &p_lines_peeked[idx], idx); \
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

static em_buf_s g_buf;

/** Private function prototypes */

/** Public functions */

/**
 *  @brief  Set up operations for each test
 */
void setUp (void)
{
    em_mem_mock_init();
    em_mem_iface_s mem_iface = {
        .alloc = em_mem_mock_alloc,
        .free  = em_mem_mock_free,
    };
    bool ret = em_buf_init(&g_buf, &mem_iface);
}

/**
 *  @brief  Tear down operations for each test
 */
void tearDown (void)
{
}

/**
 *  @brief  Check if em_mem interface compatible with POSIX memory
 *          management functions
 */
void test_init (void)
{
    em_buf_s       buf;
    em_mem_iface_s mem_iface = {
        .alloc = em_mem_mock_alloc,
        .free  = em_mem_mock_free,
    };
    bool ret = em_buf_init(&buf, &mem_iface);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(NULL, buf.p_head);
    TEST_ASSERT_EQUAL(0, buf.len);
    TEST_ASSERT_EQUAL(em_mem_mock_alloc, buf.mem_iface.alloc);
    TEST_ASSERT_EQUAL(em_mem_mock_free, buf.mem_iface.free);
}
