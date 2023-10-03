/**
 *  @file   test_eed_mem.c
 *  @brief  eed_mem module unit tests
 *
 *  @author Mikhail Zaytsev
 *  @date   20230924
 */

/** Includes */

#include "eed_mem.h"
#include "eed_mem_mock.h"
#include "unity.h"
#include <stdint.h>
#include <stdlib.h>

/** Definitions */

/** Structures and types */

/** Private data */

static eed_mem_iface_s g_iface;

/** Private function prototypes */

/** Public functions */

/**
 *  @brief  Set up operations for each test
 */
void setUp (void)
{
    g_iface.alloc = eed_mem_mock_alloc;
    g_iface.free  = eed_mem_mock_free;
    eed_mem_mock_init();
}

/**
 *  @brief  Tear down operations for each test
 */
void tearDown (void)
{
    /** Test teardown */
}

/**
 *  @brief  Check if eed_mem interface compatible with POSIX memory
 *          management functions
 */
void test_posix_iface (void)
{
    eed_mem_iface_s iface = {.alloc = malloc, .free = free};
}

/**
 *  @brief  Check if eed_mem interface compatible with mock functions
 */
void test_mock_iface (void)
{
    eed_mem_iface_s iface
        = {.alloc = eed_mem_mock_alloc, .free = eed_mem_mock_free};
}

/**
 *  @brief  Check alloc
 */
void test_mock_alloc (void)
{
    int32_t * p_number = (int32_t *)eed_mem_alloc(&g_iface, sizeof(int32_t));
    *p_number          = 5;

    TEST_ASSERT_EQUAL(1, eed_mem_mock_alloc_call_count());
    TEST_ASSERT_EQUAL_UINT32(5, *p_number);
}

/**
 *  @brief  Check free
 */
void test_mock_free (void)
{
    int32_t * p_number = (int32_t *)eed_mem_alloc(&g_iface, sizeof(int32_t));
    eed_mem_free(&g_iface, (void *)p_number);

    TEST_ASSERT_EQUAL(1, eed_mem_mock_free_call_count());
}

/** Private functions */
