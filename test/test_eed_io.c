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
    eed_io_iface_s io_iface =
    {
        .gets = eed_io_mock_gets,
        .puts = eed_io_mock_puts
    };

}
