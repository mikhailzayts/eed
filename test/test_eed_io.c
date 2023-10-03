/**
 *  @file   test_eed_io.c
 *  @brief  eed_io module unit tests
 *
 *  @author Mikhail Zaytsev
 *  @date   20230924
 */

/** Includes */

#include "eed_io.h"
#include "eed_io_mock.h"
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** Definitions */

/** Structures and types */

/** Private data */

static eed_io_iface_s g_io_iface;

/** Private function prototypes */

/** Public functions */

/**
 *  @brief  Set up operations for each test
 */
void setUp (void)
{
    g_io_iface.getchar = eed_io_mock_getchar;
    g_io_iface.putchar = eed_io_mock_putchar;
    eed_io_mock_init();
}

/**
 *  @brief  Tear down operations for each test
 */
void tearDown (void)
{
}

void test_iface (void)
{
    eed_io_iface_s io_iface =
    {
        .getchar = eed_io_mock_getchar,
        .putchar = eed_io_mock_putchar
    };
}

void test_getchar (void)
{
    char buffer[] = {"hello"};
    uint32_t buffer_size = sizeof(buffer);
    eed_io_mock_getchar_buffer_set(buffer, buffer_size);

    char chr = 0;
    for (uint32_t idx = 0; idx < buffer_size; idx++)
    {
        TEST_ASSERT_EQUAL(0, eed_io_getchar(&g_io_iface, &chr));
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
        TEST_ASSERT_EQUAL(0, eed_io_putchar(&g_io_iface, buffer_exp[idx]));
        TEST_ASSERT_EQUAL(buffer_exp[idx], buffer[idx]);
    }
}

void test_getchar_null (void)
{
    char chr = 0;
    int32_t ret = eed_io_getchar(NULL, &chr);

    TEST_ASSERT_NOT_EQUAL(0, ret);
}

void test_putchar_null (void)
{
    int32_t ret = eed_io_putchar(NULL, 'A');

    TEST_ASSERT_NOT_EQUAL(0, ret);
}
