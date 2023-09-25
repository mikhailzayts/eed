/**
 *  @file   test_em_mem.c
 *  @brief  em_mem module unit tests
 *
 *  @author Mikhail Zaytsev
 *  @date   20230924
 */

/** Includes */

#include "em_buf.h"
#include "em_mem.h"
#include "em_mem_mock.h"
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/** Definitions */

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

/**
 *  @brief Insert one line
 */
void test_line_insert (void)
{
    char * line = "coffee";
    bool   ret  = em_buf_line_insert(&g_buf, line, 0);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(1, em_buf_len(&g_buf));

    TEST_ASSERT_NOT_EQUAL(NULL, g_buf.p_head);
    TEST_ASSERT_EQUAL(g_buf.p_head->p_next, g_buf.p_head->p_prev);
}

/**
 *  @brief Peek line
 */
void test_line_peek (void)
{
    char * p_line_exp = "coffee";
    em_buf_line_insert(&g_buf, p_line_exp, 0);

    char * p_peeked = NULL;
    bool   ret      = em_buf_line_peek(&g_buf, &p_peeked, 0);

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
    bool   ret        = em_buf_line_insert(&g_buf, p_line_exp, 0);
    ret               = em_buf_line_insert(&g_buf, line2, 0);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(2, em_buf_len(&g_buf));

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

    bool ret = em_buf_line_insert(&g_buf, line, 0);
    ret      = em_buf_line_insert(&g_buf, line2, 0);
    ret      = em_buf_line_insert(&g_buf, line3, 0);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(3, em_buf_len(&g_buf));

    TEST_ASSERT_NOT_EQUAL(NULL, g_buf.p_head);
    TEST_ASSERT_NOT_EQUAL(g_buf.p_head, g_buf.p_head->p_next);
    TEST_ASSERT_EQUAL(g_buf.p_head, g_buf.p_head->p_next->p_prev);
    TEST_ASSERT_NOT_EQUAL(g_buf.p_head->p_next, g_buf.p_head->p_prev);
    TEST_ASSERT_EQUAL(g_buf.p_head->p_prev, g_buf.p_head->p_next->p_next);
}

/**
 *  @brief Get buffer length (lines count)
 */
void test_len (void)
{
    char * p_line = "coffee";

    uint32_t len_expected = 10;
    for (uint32_t idx = 0; idx < len_expected; idx++)
    {
        em_buf_line_insert(&g_buf, p_line, 0);
    }

    TEST_ASSERT_EQUAL_UINT32(len_expected, em_buf_len(&g_buf));
}

/**
 *  @brief Insert five lines and peek them
 */
void test_line_insert_and_peek5 (void)
{
    const char * p_lines_exp[] = {"one", "two", "three", "four", "five"};
    uint32_t     lines_count   = sizeof(p_lines_exp) / sizeof(p_lines_exp[0]);
    bool         ret           = false;

    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        ret = em_buf_line_insert(&g_buf, p_lines_exp[idx], 0);
        TEST_ASSERT_EQUAL(true, ret);
    }

    char * p_lines_peeked[lines_count];
    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        ret = em_buf_line_peek(&g_buf, &p_lines_peeked[idx], idx);
        TEST_ASSERT_EQUAL(true, ret);
    }

    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        TEST_ASSERT_EQUAL_STRING(p_lines_exp[idx],
                                 p_lines_peeked[lines_count - idx - 1]);
    }

    TEST_ASSERT_EQUAL(lines_count, em_buf_len(&g_buf));
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
        ret = em_buf_line_insert(&g_buf, p_lines[idx], 0);
        TEST_ASSERT_EQUAL(true, ret);
    }

    /** Insert line with non-zero position */
    ret = em_buf_line_insert(&g_buf, p_line_inserted, 2);

    char * p_lines_peeked[lines_count];
    for (uint32_t idx = 0; idx < em_buf_len(&g_buf); idx++)
    {
        ret = em_buf_line_peek(&g_buf, &p_lines_peeked[idx], idx);
        TEST_MESSAGE(p_lines_peeked[idx]);
        TEST_ASSERT_EQUAL(true, ret);
    }

    const char * p_lines_exp[]
        = {"five", "four", "three with half", "three", "two", "one"};
    for (uint32_t idx = 0; idx < em_buf_len(&g_buf); idx++)
    {
        TEST_ASSERT_EQUAL_STRING(p_lines_exp[idx], p_lines_peeked[idx]);
    }
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
        ret = em_buf_line_insert(&g_buf, p_lines_exp[idx], em_buf_len(&g_buf));
        TEST_ASSERT_EQUAL(true, ret);
    }

    TEST_ASSERT_EQUAL(lines_count, em_buf_len(&g_buf));

    const char * p_lines_peeked[lines_count];
    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        ret = em_buf_line_peek(&g_buf, (char **)&p_lines_peeked[idx], idx);
        TEST_MESSAGE(p_lines_peeked[idx]);
        TEST_ASSERT_EQUAL(true, ret);
    }

    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        TEST_ASSERT_EQUAL_STRING(p_lines_exp[idx], p_lines_peeked[idx]);
    }
}

/**
 *  @brief Check if line is copied
 */
void test_line_insert_copy (void)
{
    char * p_line_exp = "one";
    em_buf_line_insert(&g_buf, p_line_exp, 0);

    p_line_exp = "two";

    char * p_line_peeked = NULL;
    em_buf_line_peek(&g_buf, &p_line_peeked, 0);

    TEST_ASSERT_EQUAL_STRING("one", p_line_peeked);
}

/**
 *  @brief Remove line
 */
void test_line_remove (void)
{
    char * p_line= "one";
    em_buf_line_insert(&g_buf, p_line, 0);

    bool ret = em_buf_line_remove(&g_buf, 0);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(0, em_buf_len(&g_buf));

    TEST_ASSERT_NOT_EQUAL(0, em_mem_mock_free_call_count());
    TEST_ASSERT_EQUAL(em_mem_mock_alloc_call_count(), em_mem_mock_free_call_count());
}

/**
 *  @brief Remove head line
 */
void test_line_remove_head (void)
{
    const char * p_lines[] = {"one", "two", "three", "four", "five"};
    uint32_t     lines_count   = sizeof(p_lines) / sizeof(p_lines[0]);
    const char * p_lines_exp[] = {"two", "three", "four", "five"};
    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        em_buf_line_insert(&g_buf, p_lines[idx], em_buf_len(&g_buf));
    }

    bool ret = em_buf_line_remove(&g_buf, 0);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(lines_count - 1, em_buf_len(&g_buf));

    TEST_ASSERT_NOT_EQUAL(0, em_mem_mock_free_call_count());

    const char * p_lines_peeked[lines_count - 1];
    for (uint32_t idx = 0; idx < (lines_count - 1); idx++)
    {
        ret = em_buf_line_peek(&g_buf, (char **)&p_lines_peeked[idx], idx);
        TEST_MESSAGE(p_lines_peeked[idx]);
        TEST_ASSERT_EQUAL(true, ret);
    }

    for (uint32_t idx = 0; idx < (lines_count - 1); idx++)
    {
        TEST_ASSERT_EQUAL_STRING(p_lines_exp[idx], p_lines_peeked[idx]);
    }
}

/**
 *  @brief Remove tail line
 */
void test_line_remove_tail (void)
{
    const char * p_lines[] = {"one", "two", "three", "four", "five"};
    uint32_t     lines_count   = sizeof(p_lines) / sizeof(p_lines[0]);
    const char * p_lines_exp[] = {"one", "two", "three", "four"};
    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        em_buf_line_insert(&g_buf, p_lines[idx], em_buf_len(&g_buf));
    }

    bool ret = em_buf_line_remove(&g_buf, em_buf_len(&g_buf) - 1);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(lines_count - 1, em_buf_len(&g_buf));

    TEST_ASSERT_NOT_EQUAL(0, em_mem_mock_free_call_count());

    const char * p_lines_peeked[lines_count - 1];
    for (uint32_t idx = 0; idx < (lines_count - 1); idx++)
    {
        ret = em_buf_line_peek(&g_buf, (char **)&p_lines_peeked[idx], idx);
        TEST_MESSAGE(p_lines_peeked[idx]);
        TEST_ASSERT_EQUAL(true, ret);
    }

    for (uint32_t idx = 0; idx < (lines_count - 1); idx++)
    {
        TEST_ASSERT_EQUAL_STRING(p_lines_exp[idx], p_lines_peeked[idx]);
    }
}

/**
 *  @brief Remove middle line
 */
void test_line_remove_middle (void)
{
    const char * p_lines[] = {"one", "two", "three", "four", "five"};
    uint32_t     lines_count   = sizeof(p_lines) / sizeof(p_lines[0]);
    const char * p_lines_exp[] = {"one", "two", "four", "five"};
    for (uint32_t idx = 0; idx < lines_count; idx++)
    {
        em_buf_line_insert(&g_buf, p_lines[idx], em_buf_len(&g_buf));
    }

    bool ret = em_buf_line_remove(&g_buf, 2);

    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(lines_count - 1, em_buf_len(&g_buf));

    TEST_ASSERT_NOT_EQUAL(0, em_mem_mock_free_call_count());

    const char * p_lines_peeked[lines_count - 1];
    for (uint32_t idx = 0; idx < (lines_count - 1); idx++)
    {
        ret = em_buf_line_peek(&g_buf, (char **)&p_lines_peeked[idx], idx);
        TEST_MESSAGE(p_lines_peeked[idx]);
        TEST_ASSERT_EQUAL(true, ret);
    }

    for (uint32_t idx = 0; idx < (lines_count - 1); idx++)
    {
        TEST_ASSERT_EQUAL_STRING(p_lines_exp[idx], p_lines_peeked[idx]);
    }
}

