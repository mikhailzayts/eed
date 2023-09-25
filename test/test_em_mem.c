/**
 *  @file   test_em_mem.c
 *  @brief  em_mem module unit tests
 *
 *  @author Mikhail Zaytsev
 *  @date   20230924
 */

/** Includes */

#include "em_mem.h"
#include "em_mem_mock.h"
#include "unity.h"
#include <stdint.h>
#include <stdlib.h>

/** Definitions */

/** Structures and types */

/** Private data */

static em_mem_iface_s g_iface;

/** Private function prototypes */

/** Public functions */

/**
 *  @brief  Set up operations for each test
 */
void setUp (void)
{
    g_iface.alloc = em_mem_mock_alloc;
    g_iface.free  = em_mem_mock_free;
    em_mem_mock_init();
}

/**
 *  @brief  Tear down operations for each test
 */
void tearDown (void)
{
    /** Test teardown */
}

/**
 *  @brief  Check if em_mem interface compatible with POSIX memory
 *          management functions
 */
void test_posix_iface (void)
{
    em_mem_iface_s iface = {.alloc = malloc, .free = free};
}

/**
 *  @brief  Check if em_mem interface compatible with mock functions
 */
void test_mock_iface (void)
{
    em_mem_iface_s iface
        = {.alloc = em_mem_mock_alloc, .free = em_mem_mock_free};
}

/**
 *  @brief  Check alloc
 */
void test_mock_alloc (void)
{
    int32_t * p_number = (int32_t *)em_mem_alloc(&g_iface, sizeof(int32_t));
    *p_number          = 5;

    TEST_ASSERT_EQUAL(1, em_mem_mock_alloc_call_count());
    TEST_ASSERT_EQUAL_UINT32(5, *p_number);
}

/**
 *  @brief  Check free
 */
void test_mock_free (void)
{
    int32_t * p_number = (int32_t *)em_mem_alloc(&g_iface, sizeof(int32_t));
    em_mem_free(&g_iface, (void *)p_number);

    TEST_ASSERT_EQUAL(1, em_mem_mock_free_call_count());
}

/** Private functions */
