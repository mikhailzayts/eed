/**
 *  @file   test_eed_mem.c
 *  @brief  eed_mem module unit tests for negative cases
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

/** Definitions */

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
 *  @brief Initialization: Null-pointer check
 */
void test_init_null (void)
{
    static eed_buf_s buf;
    eed_mem_iface_s mem_iface;
    bool ret = eed_buf_init(NULL, &mem_iface);
    TEST_ASSERT_EQUAL(false, ret);

    ret = eed_buf_init(&buf, NULL);
    TEST_ASSERT_EQUAL(false, ret);

    ret = eed_buf_init(NULL, NULL);
    TEST_ASSERT_EQUAL(false, ret);
}

/**
 *  @brief Deinitialization: Null-pointer check
 */
void test_deinit_null (void)
{
    bool ret = eed_buf_deinit(NULL);
    TEST_ASSERT_EQUAL(false, ret);
}

/**
 *  @brief Insert one line: Null-pointer check
 */
void test_line_insert_null (void)
{
    char * line = "coffee";
    bool ret  = eed_buf_line_insert(NULL, line, 0);
    TEST_ASSERT_EQUAL(false, ret);

    ret  = eed_buf_line_insert(&g_buf, NULL, 0);
    TEST_ASSERT_EQUAL(false, ret);

    ret  = eed_buf_line_insert(NULL, NULL, 0);
    TEST_ASSERT_EQUAL(false, ret);

    TEST_ASSERT_EQUAL(0, eed_buf_size(&g_buf));
}

/**
 *  @brief Peek line: Null-pointer check
 */
void test_line_peek_null (void)
{
    char * p_line_exp = "coffee";
    eed_buf_line_insert(&g_buf, p_line_exp, 0);

    char * p_peeked = NULL;

    bool ret = eed_buf_line_peek(NULL, &p_peeked, 0);
    TEST_ASSERT_EQUAL(false, ret);

    ret = eed_buf_line_peek(&g_buf, NULL, 0);
    TEST_ASSERT_EQUAL(false, ret);

    ret = eed_buf_line_peek(NULL, NULL, 0);
    TEST_ASSERT_EQUAL(false, ret);

    TEST_ASSERT_EQUAL(NULL, p_peeked);
}

/**
 *  @brief Get buffer length (lines count): Null-pointer check
 */
void test_size_null (void)
{
    TEST_ASSERT_EQUAL_UINT32(-1, eed_buf_size(NULL));
}

/**
 *  @brief Try to remove line with invalid position and Null-pointer
 */
void test_line_remove_neg (void)
{
    bool ret = eed_buf_line_remove(&g_buf, 0);
    TEST_ASSERT_EQUAL(false, ret);

    char * p_line= "one";
    eed_buf_line_insert(&g_buf, p_line, 0);

    ret = eed_buf_line_remove(NULL, 0);
    TEST_ASSERT_EQUAL(false, ret);

    ret = eed_buf_line_remove(&g_buf, 5);
    TEST_ASSERT_EQUAL(false, ret);
}

/**
 *  @brief Try to copy line with invalid position and Null-pointer
 */
void test_line_copy_neg (void)
{
    bool ret = eed_buf_line_copy(&g_buf, 0, 1);
    TEST_ASSERT_EQUAL(false, ret);

    char * p_line= "one";
    eed_buf_line_insert(&g_buf, p_line, 0);

    ret = eed_buf_line_copy(NULL, 0, 1);
    TEST_ASSERT_EQUAL(false, ret);

    ret = eed_buf_line_copy(&g_buf, 5, 1);
    TEST_ASSERT_EQUAL(false, ret);
}

/**
 *  @brief Try to move line with invalid position and Null-pointer
 */
void test_line_move_neg (void)
{
    bool ret = eed_buf_line_move(&g_buf, 0, 1);
    TEST_ASSERT_EQUAL(false, ret);

    char * p_line= "one";
    eed_buf_line_insert(&g_buf, p_line, 0);

    ret = eed_buf_line_move(NULL, 0, 1);
    TEST_ASSERT_EQUAL(false, ret);

    ret = eed_buf_line_move(&g_buf, 5, 1);
    TEST_ASSERT_EQUAL(false, ret);
}

/**
 *  @brief Try to get line len with NULL buffer pointer
 */
void test_line_len_neg (void)
{
    char * p_line= "one";
    eed_buf_line_insert(&g_buf, p_line, 0);

    int32_t ret = eed_buf_line_len(NULL, 0);
    TEST_ASSERT_EQUAL(-1, ret);

    ret = eed_buf_line_len(&g_buf, 1);
    TEST_ASSERT_EQUAL(-1, ret);
}
