/**
 *  @file   test_eed_io_mock.c
 *  @brief  eed_io mock unit tests
 *
 *  @author Mikhail Zaytsev
 *  @date   20230924
 */

/** Includes */

#include "eed_io_mock.h"
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/** Definitions */

/** Structures and types */

/** Private data */

/** Private function prototypes */

/** Public functions */

/**
 *  @brief  Set up operations for each test
 */
void setUp (void)
{
    eed_io_mock_init();
}

/**
 *  @brief  Tear down operations for each test
 */
void tearDown (void)
{
}

void test_init (void)
{
    eed_io_mock_init();
}

void test_getchar (void)
{
    char buffer[] = {"hello"};
    uint32_t buffer_size = sizeof(buffer);
    eed_io_mock_getchar_buffer_set(buffer, buffer_size);

    char chr = 0;
    for (uint32_t idx = 0; idx < buffer_size; idx++)
    {
        TEST_ASSERT_EQUAL(0, eed_io_mock_getchar(&chr));
        TEST_ASSERT_EQUAL(buffer[idx], chr);
    }
}

void test_putchar (void)
{
    char buffer[32] = {0};
    memset(buffer, 0, sizeof(buffer));
    uint32_t buffer_size = sizeof(buffer);
    eed_io_mock_putchar_buffer_set(buffer, buffer_size);

    char buffer_exp[] = {"hello"};
    for (uint32_t idx = 0; idx < buffer_size; idx++)
    {
        TEST_ASSERT_EQUAL(0, eed_io_mock_putchar(buffer_exp[idx]));
        TEST_ASSERT_EQUAL(buffer_exp[idx], buffer[idx]);
    }
}

void test_getchar_neg (void)
{
    char chr = 0;
    int32_t ret = eed_io_mock_getchar(&chr);

    TEST_ASSERT_NOT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(0, chr);
}

void test_getchar_null (void)
{
    char buffer[] = {"hello"};
    uint32_t buffer_size = sizeof(buffer);
    eed_io_mock_getchar_buffer_set(buffer, buffer_size);

    int32_t ret = eed_io_mock_getchar(NULL);

    TEST_ASSERT_NOT_EQUAL(0, ret);
}

void test_putchar_neg (void)
{
    int32_t ret = eed_io_mock_putchar('A');

    TEST_ASSERT_NOT_EQUAL(0, ret);
}
