/**
 *  @file   test_em_mem_mock.c
 *  @brief  em_mem mock unit tests
 *
 *  @author Mikhail Zaytsev
 *  @date   20230924
 */

/** Includes */

#include "em_mem_mock.h"
#include "unity.h"
#include <stdint.h>
#include <stdlib.h>

/** Definitions */

/** Structures and types */

/** Private data */

/** Private function prototypes */

/** Public functions */

void setUp (void)
{
    em_mem_mock_init();
}

void tearDown (void)
{
    /** Test teardown */
}

void test_alloc (void)
{
    uint32_t * p_number = (uint32_t *)em_mem_mock_alloc(sizeof(uint32_t));
    *p_number           = 5;

    TEST_ASSERT_EQUAL(1, em_mem_mock_alloc_call_count());
    TEST_ASSERT_EQUAL_UINT32(5, *p_number);
    em_mem_mock_free(p_number);
}

void test_init (void)
{
    uint32_t * p_number = (uint32_t *)em_mem_mock_alloc(sizeof(uint32_t));
    em_mem_mock_free(p_number);
    em_mem_mock_init();

    TEST_ASSERT_EQUAL(0, em_mem_mock_alloc_call_count());
    TEST_ASSERT_EQUAL(0, em_mem_mock_free_call_count());
}

void test_free (void)
{
    uint32_t * p_number = (uint32_t *)em_mem_mock_alloc(sizeof(uint32_t));
    em_mem_mock_free(p_number);

    TEST_ASSERT_EQUAL(1, em_mem_mock_free_call_count());
}

void test_alloc_call_count (void)
{
    uint32_t * p_number = (uint32_t *)em_mem_mock_alloc(sizeof(uint32_t));
    em_mem_mock_free(p_number);
    p_number = (uint32_t *)em_mem_mock_alloc(sizeof(uint32_t));
    em_mem_mock_free(p_number);

    TEST_ASSERT_EQUAL(2, em_mem_mock_alloc_call_count());
}

void test_free_call_count (void)
{
    uint32_t * p_number = (uint32_t *)em_mem_mock_alloc(sizeof(uint32_t));
    em_mem_mock_free(p_number);
    p_number = (uint32_t *)em_mem_mock_alloc(sizeof(uint32_t));
    em_mem_mock_free(p_number);

    TEST_ASSERT_EQUAL(2, em_mem_mock_free_call_count());
}
/** Private functions */
