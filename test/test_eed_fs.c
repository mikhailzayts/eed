/**
*  @file   test_eed_fs.c
*  @brief  File system dynamic interface tests
*
*  @author Mikhail Zaytsev
*  @date   20231003
*/

/** Includes */

#include "unity.h"
#include <stdbool.h>
#include <string.h>
#include "eed_fs.h"
#include "eed_fs_mock.h"

/** Definitions */


/** Private data */


/** Private function prototypes */


/** Public functions */

void setUp(void) 
{
}

void tearDown(void) 
{
}

void test_iface(void)
{
    eed_fs_iface_s fs_iface =
    {
        .file_read = eed_fs_mock_file_read,
        .file_write = eed_fs_mock_file_write,
        .file_size_get = eed_fs_mock_file_size_get,
        .file_delete = eed_fs_mock_file_delete,
    };
}
