/**
 *  @file   test_em_io_mock.c
 *  @brief  em_io mock unit tests
 *
 *  @author Mikhail Zaytsev
 *  @date   20230924
 */

/** Includes */

#include "em_io_mock.h"
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
}

/**
 *  @brief  Tear down operations for each test
 */
void tearDown (void)
{
}

void test_iface (void)
{

}

void test_init (void)
{
    char buffer[16];
    memset(buffer, 0, sizeof(buffer));
    em_io_mock_init();
    char * p_ret = em_io_mock_gets(buffer, sizeof(buffer) / sizeof(buffer[0]));

    TEST_ASSERT_EQUAL(NULL, p_ret);
    //char * input[] = {"Hello world\n"};
    //em_io_mock_input_set(input);

}
