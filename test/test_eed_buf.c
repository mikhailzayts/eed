/**
 *  @file   test_em_mem.c
 *  @brief  eed_mem module unit tests
 *
 *  @author Mikhail Zaytsev
 *  @date   20230924
 */

/** Includes */

#include "eed_buf.h"
#include "eed_mem.h"
#include "eed_mem_mock.h"
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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
    TEST_ASSERT_EQUAL(0, buf.size);
    TEST_ASSERT_EQUAL(eed_mem_mock_alloc, buf.mem_iface.alloc);
    TEST_ASSERT_EQUAL(eed_mem_mock_free, buf.mem_iface.free);
}

/**
 *  @brief Insert one line
 */
void test_line_insert (void)
{
    char * line = "coffee";
    bool   ret  = eed_buf_line_insert(&g_buf, line, 0);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(1, eed_buf_size(&g_buf));

    TEST_ASSERT_NOT_EQUAL(NULL, g_buf.p_head);
    TEST_ASSERT_EQUAL(g_buf.p_head->p_next, g_buf.p_head->p_prev);
}

/**
 *  @brief Peek line
 */
void test_line_peek (void)
{
    char * p_line_exp = "coffee";
    eed_buf_line_insert(&g_buf, p_line_exp, 0);

    char * p_peeked = NULL;
    bool   ret      = eed_buf_line_peek(&g_buf, &p_peeked, 0);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL_STRING(p_line_exp, p_peeked);
}

/**
 *  @brief Insert two lines
 */
void test_line_insert2 (void)
{
    char * p_line_exp = "i love";
    char * line2      = "coffee";
    bool   ret        = eed_buf_line_insert(&g_buf, p_line_exp, 0);
    ret               = eed_buf_line_insert(&g_buf, line2, 0);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(2, eed_buf_size(&g_buf));

    TEST_ASSERT_NOT_EQUAL(NULL, g_buf.p_head);
    TEST_ASSERT_NOT_EQUAL(g_buf.p_head, g_buf.p_head->p_next);
    TEST_ASSERT_EQUAL(g_buf.p_head, g_buf.p_head->p_next->p_prev);
    TEST_ASSERT_EQUAL(g_buf.p_head->p_next, g_buf.p_head->p_prev);
    TEST_ASSERT_NOT_EQUAL(g_buf.p_head->p_prev, g_buf.p_head->p_next->p_next);
}

/**
 *  @brief Insert three lines
 */
void test_line_insert3 (void)
{
    char * line  = "i love";
    char * line2 = "coffee";
    char * line3 = "hello";

    bool ret = eed_buf_line_insert(&g_buf, line, 0);
    ret      = eed_buf_line_insert(&g_buf, line2, 0);
    ret      = eed_buf_line_insert(&g_buf, line3, 0);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(3, eed_buf_size(&g_buf));

    TEST_ASSERT_NOT_EQUAL(NULL, g_buf.p_head);
    TEST_ASSERT_NOT_EQUAL(g_buf.p_head, g_buf.p_head->p_next);
    TEST_ASSERT_EQUAL(g_buf.p_head, g_buf.p_head->p_next->p_prev);
    TEST_ASSERT_NOT_EQUAL(g_buf.p_head->p_next, g_buf.p_head->p_prev);
    TEST_ASSERT_EQUAL(g_buf.p_head->p_prev, g_buf.p_head->p_next->p_next);
}

/**
 *  @brief Get buffer length (lines count)
 */
void test_size (void)
{
    char * p_line = "coffee";

    uint32_t len_expected = 10;
    for (uint32_t idx = 0; idx < len_expected; idx++)
    {
        eed_buf_line_insert(&g_buf, p_line, 0);
    }

    TEST_ASSERT_EQUAL_UINT32(len_expected, eed_buf_size(&g_buf));
}

/**
 *  @brief Insert five lines and peek them
 */
void test_line_insert_and_peek5 (void)
{
    const char * p_lines[] = {"one", "two", "three", "four", "five"};
    uint32_t     lines_count   = TEST_ARRAY_SIZE(p_lines);
    bool         ret           = false;

    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        ret = eed_buf_line_insert(&g_buf, p_lines[idx], 0);
        TEST_ASSERT_EQUAL(true, ret);
    }

    const char * p_lines_exp[] = {"five", "four", "three", "two", "one"};
    TEST_PEAK_AND_CHECK(p_lines_exp, TEST_ARRAY_SIZE(p_lines_exp));
}

/**
 *  @brief Insert with non-zero position
 */
void test_line_insert_with_pos (void)
{
    const char * p_lines[]       = {"one", "two", "three", "four", "five"};
    uint32_t     lines_count     = sizeof(p_lines) / sizeof(p_lines[0]);
    bool         ret             = false;
    const char * p_line_inserted = "three with half";

    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        ret = eed_buf_line_insert(&g_buf, p_lines[idx], 0);
        TEST_ASSERT_EQUAL(true, ret);
    }

    /** Insert line with non-zero position */
    ret = eed_buf_line_insert(&g_buf, p_line_inserted, 2);

    const char * p_lines_exp[]
        = {"five", "four", "three with half", "three", "two", "one"};
    TEST_PEAK_AND_CHECK(p_lines_exp, TEST_ARRAY_SIZE(p_lines_exp));
}

/**
 *  @brief Insert at the end
 */
void test_line_insert_end (void)
{
    const char * p_lines_exp[] = {"one", "two", "three", "four", "five"};
    uint32_t     lines_count   = sizeof(p_lines_exp) / sizeof(p_lines_exp[0]);
    bool         ret           = false;
    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        ret = eed_buf_line_insert(&g_buf, p_lines_exp[idx], eed_buf_size(&g_buf));
        TEST_ASSERT_EQUAL(true, ret);
    }

    TEST_ASSERT_EQUAL(lines_count, eed_buf_size(&g_buf));

    TEST_PEAK_AND_CHECK(p_lines_exp, lines_count);
}

/**
 *  @brief Check if line is copied
 */
void test_line_insert_copy (void)
{
    char * p_line_exp = "one";
    eed_buf_line_insert(&g_buf, p_line_exp, 0);

    p_line_exp = "two";

    char * p_line_peeked = NULL;
    eed_buf_line_peek(&g_buf, &p_line_peeked, 0);

    TEST_ASSERT_EQUAL_STRING("one", p_line_peeked);
}

/**
 *  @brief Insert empty line
 */
void test_line_insert_empty (void)
{
    char * p_line= "";

    bool ret = eed_buf_line_insert(&g_buf, p_line, 0);
    TEST_ASSERT_EQUAL(true, ret);
    ret = eed_buf_line_insert(&g_buf, p_line, 0);
    TEST_ASSERT_EQUAL(true, ret);
    ret = eed_buf_line_insert(&g_buf, p_line, 0);
    TEST_ASSERT_EQUAL(true, ret);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(3, eed_buf_size(&g_buf));

    const char * p_lines_exp[] = {"", "", ""};
    TEST_PEAK_AND_CHECK(p_lines_exp, TEST_ARRAY_SIZE(p_lines_exp));
}

/**
 *  @brief Remove line
 */
void test_line_remove (void)
{
    char * p_line= "one";
    eed_buf_line_insert(&g_buf, p_line, 0);

    bool ret = eed_buf_line_remove(&g_buf, 0);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(0, eed_buf_size(&g_buf));

    TEST_ASSERT_NOT_EQUAL(0, eed_mem_mock_free_call_count());
    TEST_ASSERT_EQUAL(eed_mem_mock_alloc_call_count(), eed_mem_mock_free_call_count());
}

/**
 *  @brief Remove head line
 */
void test_line_remove_head (void)
{
    const char * p_lines[] = {"one", "two", "three", "four", "five"};
    uint32_t     lines_count   = sizeof(p_lines) / sizeof(p_lines[0]);
    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        eed_buf_line_insert(&g_buf, p_lines[idx], eed_buf_size(&g_buf));
    }

    bool ret = eed_buf_line_remove(&g_buf, 0);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(lines_count - 1, eed_buf_size(&g_buf));

    TEST_ASSERT_NOT_EQUAL(0, eed_mem_mock_free_call_count());

    const char * p_lines_exp[] = {"two", "three", "four", "five"};
    TEST_PEAK_AND_CHECK(p_lines_exp, TEST_ARRAY_SIZE(p_lines_exp));
}

/**
 *  @brief Remove tail line
 */
void test_line_remove_tail (void)
{
    const char * p_lines[] = {"one", "two", "three", "four", "five"};
    uint32_t     lines_count   = sizeof(p_lines) / sizeof(p_lines[0]);
    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        eed_buf_line_insert(&g_buf, p_lines[idx], eed_buf_size(&g_buf));
    }

    bool ret = eed_buf_line_remove(&g_buf, eed_buf_size(&g_buf) - 1);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(lines_count - 1, eed_buf_size(&g_buf));

    TEST_ASSERT_NOT_EQUAL(0, eed_mem_mock_free_call_count());

    const char * p_lines_exp[] = {"one", "two", "three", "four"};
    TEST_PEAK_AND_CHECK(p_lines_exp, TEST_ARRAY_SIZE(p_lines_exp));
}

/**
 *  @brief Remove middle line
 */
void test_line_remove_middle (void)
{
    const char * p_lines[] = {"one", "two", "three", "four", "five"};
    uint32_t     lines_count   = sizeof(p_lines) / sizeof(p_lines[0]);
    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        eed_buf_line_insert(&g_buf, p_lines[idx], eed_buf_size(&g_buf));
    }

    bool ret = eed_buf_line_remove(&g_buf, 2);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(lines_count - 1, eed_buf_size(&g_buf));

    TEST_ASSERT_NOT_EQUAL(0, eed_mem_mock_free_call_count());

    const char * p_lines_exp[] = {"one", "two", "four", "five"};
    TEST_PEAK_AND_CHECK(p_lines_exp, TEST_ARRAY_SIZE(p_lines_exp));
}

/**
 *  @brief Copy line
 */
void test_line_copy (void)
{
    char * p_line= "one";
    eed_buf_line_insert(&g_buf, p_line, 0);

    bool ret = eed_buf_line_copy(&g_buf, 0, 1);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(2, eed_buf_size(&g_buf));

    const char * p_lines_exp[] = {"one", "one"};
    TEST_PEAK_AND_CHECK(p_lines_exp, TEST_ARRAY_SIZE(p_lines_exp));
}

void test_line_copy_tail_to_head (void)
{
    const char * p_lines[] = {"one", "two", "three", "four", "tail"};
    uint32_t     lines_count   = sizeof(p_lines) / sizeof(p_lines[0]);
    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        eed_buf_line_insert(&g_buf, p_lines[idx], eed_buf_size(&g_buf));
    }

    bool ret = eed_buf_line_copy(&g_buf, 4, 0);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(lines_count + 1, eed_buf_size(&g_buf));

    const char * p_lines_exp[] = {"tail", "one", "two", "three", "four", "tail"};
    TEST_PEAK_AND_CHECK(p_lines_exp, TEST_ARRAY_SIZE(p_lines_exp));
}

void test_line_copy_head_to_tail (void)
{
    const char * p_lines[] = {"head", "one", "two", "three", "four"};
    uint32_t     lines_count   = sizeof(p_lines) / sizeof(p_lines[0]);
    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        eed_buf_line_insert(&g_buf, p_lines[idx], eed_buf_size(&g_buf));
    }

    bool ret = eed_buf_line_copy(&g_buf, 0, 5);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(lines_count + 1, eed_buf_size(&g_buf));

    const char * p_lines_exp[] = {"head", "one", "two", "three", "four", "head"};
    TEST_PEAK_AND_CHECK(p_lines_exp, TEST_ARRAY_SIZE(p_lines_exp));
}

void test_line_copy_middle (void)
{
    const char * p_lines[] = {"one", "two", "three", "four"};
    uint32_t     lines_count   = sizeof(p_lines) / sizeof(p_lines[0]);
    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        eed_buf_line_insert(&g_buf, p_lines[idx], eed_buf_size(&g_buf));
    }

    bool ret = eed_buf_line_copy(&g_buf, 1, 3);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(lines_count + 1, eed_buf_size(&g_buf));

    const char * p_lines_exp[] = {"one", "two", "three", "two", "four"};
    TEST_PEAK_AND_CHECK(p_lines_exp, TEST_ARRAY_SIZE(p_lines_exp));
}

void test_line_move (void)
{
    const char * p_lines[] = {"one", "two", "three", "four"};
    uint32_t     lines_count   = sizeof(p_lines) / sizeof(p_lines[0]);
    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        eed_buf_line_insert(&g_buf, p_lines[idx], eed_buf_size(&g_buf));
    }

    bool ret = eed_buf_line_move(&g_buf, 1, 2);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(lines_count, eed_buf_size(&g_buf));


    const char * p_lines_exp[] = {"one", "three", "two", "four"};
    TEST_PEAK_AND_CHECK(p_lines_exp, TEST_ARRAY_SIZE(p_lines_exp));
}

void test_line_move_head_to_tail (void)
{
    const char * p_lines[] = {"one", "two", "three", "four"};
    uint32_t     lines_count   = sizeof(p_lines) / sizeof(p_lines[0]);
    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        eed_buf_line_insert(&g_buf, p_lines[idx], eed_buf_size(&g_buf));
    }

    bool ret = eed_buf_line_move(&g_buf, 0, 3);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(lines_count, eed_buf_size(&g_buf));

    const char * p_lines_exp[] = {"two", "three", "four", "one"};
    TEST_PEAK_AND_CHECK(p_lines_exp, TEST_ARRAY_SIZE(p_lines_exp));
}

void test_line_move_tail_to_head (void)
{
    const char * p_lines[] = {"one", "two", "three", "four"};
    uint32_t     lines_count   = sizeof(p_lines) / sizeof(p_lines[0]);
    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        eed_buf_line_insert(&g_buf, p_lines[idx], eed_buf_size(&g_buf));
    }

    bool ret = eed_buf_line_move(&g_buf, 3, 0);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(lines_count, eed_buf_size(&g_buf));

    const char * p_lines_exp[] = {"four", "one", "two", "three"};
    TEST_PEAK_AND_CHECK(p_lines_exp, TEST_ARRAY_SIZE(p_lines_exp));
}

void test_deinit (void)
{
    const char * p_lines[] = {"one", "two", "three", "four", "five"};
    uint32_t     lines_count   = sizeof(p_lines) / sizeof(p_lines[0]);
    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        eed_buf_line_insert(&g_buf, p_lines[idx], eed_buf_size(&g_buf));
    }

    bool ret = eed_buf_deinit(&g_buf);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(0, eed_buf_size(&g_buf));
    TEST_ASSERT_NOT_EQUAL(0, eed_mem_mock_free_call_count());
    TEST_ASSERT_EQUAL(eed_mem_mock_alloc_call_count(), eed_mem_mock_free_call_count());
}

void test_line_len (void)
{
    const char * p_lines[] = {"one", "two", "three", "four", "five"};
    uint32_t     lines_count   = sizeof(p_lines) / sizeof(p_lines[0]);
    TEST_MESSAGE("line len");
    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        eed_buf_line_insert(&g_buf, p_lines[idx], eed_buf_size(&g_buf));
    }

    int32_t len = 0;
    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        len = eed_buf_line_len(&g_buf, idx);
        TEST_ASSERT_EQUAL_MESSAGE(strlen(p_lines[idx]), len, p_lines[idx]);
    }

    bool ret = eed_buf_deinit(&g_buf);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(0, eed_buf_size(&g_buf));
    TEST_ASSERT_NOT_EQUAL(0, eed_mem_mock_free_call_count());
    TEST_ASSERT_EQUAL(eed_mem_mock_alloc_call_count(), eed_mem_mock_free_call_count());

}
