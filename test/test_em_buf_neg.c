/**
 *  @file   test_em_mem.c
 *  @brief  em_mem module unit tests for negative cases
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
 *  @brief Initialization: Null-pointer check
 */
void test_init_null (void)
{
    static em_buf_s buf;
    em_mem_iface_s mem_iface;
    bool ret = em_buf_init(NULL, &mem_iface);
    TEST_ASSERT_EQUAL(false, ret);

    ret = em_buf_init(&buf, NULL);
    TEST_ASSERT_EQUAL(false, ret);

    ret = em_buf_init(NULL, NULL);
    TEST_ASSERT_EQUAL(false, ret);
}

/**
 *  @brief Insert one line: Null-pointer check
 */
void test_line_insert_null (void)
{
    char * line = "coffee";
    bool ret  = em_buf_line_insert(NULL, line, 0);
    TEST_ASSERT_EQUAL(false, ret);

    ret  = em_buf_line_insert(&g_buf, NULL, 0);
    TEST_ASSERT_EQUAL(false, ret);

    ret  = em_buf_line_insert(NULL, NULL, 0);
    TEST_ASSERT_EQUAL(false, ret);

    TEST_ASSERT_EQUAL(0, em_buf_len(&g_buf));
}

/**
 *  @brief Peek line: Null-pointer check
 */
void test_line_peek_null (void)
{
    char * p_line_exp = "coffee";
    em_buf_line_insert(&g_buf, p_line_exp, 0);

    char * p_peeked = NULL;

    bool ret = em_buf_line_peek(NULL, &p_peeked, 0);
    TEST_ASSERT_EQUAL(false, ret);

    ret = em_buf_line_peek(&g_buf, NULL, 0);
    TEST_ASSERT_EQUAL(false, ret);

    ret = em_buf_line_peek(NULL, NULL, 0);
    TEST_ASSERT_EQUAL(false, ret);


    TEST_ASSERT_EQUAL(NULL, p_peeked);
}

/**
 *  @brief Get buffer length (lines count): Null-pointer check
 */
void test_len (void)
{
    TEST_ASSERT_EQUAL_UINT32(-1, em_buf_len(NULL));
}

/**
 *  @brief Try to remove line with invalid position
 */
void test_line_remove_neg (void)
{
    bool ret = em_buf_line_remove(&g_buf, 0);
    TEST_ASSERT_EQUAL(false, ret);

    char * p_line= "one";
    em_buf_line_insert(&g_buf, p_line, 0);

    ret = em_buf_line_remove(NULL, 0);
    TEST_ASSERT_EQUAL(false, ret);

    ret = em_buf_line_remove(&g_buf, 5);
    TEST_ASSERT_EQUAL(false, ret);
}
