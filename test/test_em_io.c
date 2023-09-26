/**
 *  @file   test_em_io.c
 *  @brief  em_io module unit tests
 *
 *  @author Mikhail Zaytsev
 *  @date   20230924
 */

/** Includes */

#include "em_io.h"
#include "em_io_mock.h"
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

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

void test_init (void)
{
    em_io_iface_s io_iface =
    {
        .gets = em_io_mock_gets,
        .puts = em_io_mock_puts
    };

}
