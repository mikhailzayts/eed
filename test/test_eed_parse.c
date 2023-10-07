/**
 *  @file   test_eed_parse.c
 *  @brief  eed_parse module unit tests
 *
 *  @author Mikhail Zaytsev
 *  @date   20231007
 */

/** Includes */

#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "eed_parse.h"

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

/**
 *  @brief  Parse print command
 */
void test_parse_print (void)
{
    char * p_str = "p";
    eed_parse_s cmd = {0};
    int32_t ret = eed_parse(p_str, &cmd);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(EED_PARSE_CMD_PRINT, cmd.cmd);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_CURR, cmd.start.whence);
    TEST_ASSERT_EQUAL(0, cmd.start.offset);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_CURR, cmd.end.whence);
    TEST_ASSERT_EQUAL(0, cmd.end.offset);
}

/**
 *  @brief  Parse command with line position
 */
void test_parse_pos (void)
{
    char * p_str = "1p";
    eed_parse_s cmd = {0};
    int32_t ret = eed_parse(p_str, &cmd);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(EED_PARSE_CMD_PRINT, cmd.cmd);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_START, cmd.start.whence);
    TEST_ASSERT_EQUAL(1, cmd.start.offset);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_START, cmd.end.whence);
    TEST_ASSERT_EQUAL(1, cmd.end.offset);
}

/**
 *  @brief  Parse command with line position 2
 */
void test_parse_pos2 (void)
{
    char * p_str = "2p";
    eed_parse_s cmd = {0};
    int32_t ret = eed_parse(p_str, &cmd);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(EED_PARSE_CMD_PRINT, cmd.cmd);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_START, cmd.start.whence);
    TEST_ASSERT_EQUAL(2, cmd.start.offset);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_START, cmd.end.whence);
    TEST_ASSERT_EQUAL(2, cmd.end.offset);
}

/**
 *  @brief  Parse command with current line position
 */
void test_parse_pos_dot (void)
{
    char * p_str = ".p";
    eed_parse_s cmd = {0};
    int32_t ret = eed_parse(p_str, &cmd);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(EED_PARSE_CMD_PRINT, cmd.cmd);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_CURR, cmd.start.whence);
    TEST_ASSERT_EQUAL(0, cmd.start.offset);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_CURR, cmd.end.whence);
    TEST_ASSERT_EQUAL(0, cmd.end.offset);
}

/**
 *  @brief  Parse command with last line position
 */
void test_parse_pos_end (void)
{
    char * p_str = "$p";
    eed_parse_s cmd = {0};
    int32_t ret = eed_parse(p_str, &cmd);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(EED_PARSE_CMD_PRINT, cmd.cmd);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_END, cmd.start.whence);
    TEST_ASSERT_EQUAL(0, cmd.start.offset);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_END, cmd.end.whence);
    TEST_ASSERT_EQUAL(0, cmd.end.offset);
}

/**
 *  @brief  Parse command with multidigit line position
 */
void test_parse_pos_multidigit (void)
{
    char * p_str = "123p";
    eed_parse_s cmd = {0};
    int32_t ret = eed_parse(p_str, &cmd);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(EED_PARSE_CMD_PRINT, cmd.cmd);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_START, cmd.start.whence);
    TEST_ASSERT_EQUAL(123, cmd.start.offset);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_START, cmd.end.whence);
    TEST_ASSERT_EQUAL(123, cmd.end.offset);
}

/**
 *  @brief  Parse quit command
 */
void test_parse_quit (void)
{
    char * p_str = "q";
    eed_parse_s cmd = {0};
    int32_t ret = eed_parse(p_str, &cmd);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(EED_PARSE_CMD_QUIT, cmd.cmd);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_CURR, cmd.start.whence);
    TEST_ASSERT_EQUAL(0, cmd.start.offset);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_CURR, cmd.end.whence);
    TEST_ASSERT_EQUAL(0, cmd.end.offset);
}

/**
 *  @brief  Parse plus command position
 */
void test_parse_pos_plus (void)
{
    char * p_str = "++q";
    eed_parse_s cmd = {0};
    int32_t ret = eed_parse(p_str, &cmd);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(EED_PARSE_CMD_QUIT, cmd.cmd);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_CURR, cmd.start.whence);
    TEST_ASSERT_EQUAL(2, cmd.start.offset);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_CURR, cmd.end.whence);
    TEST_ASSERT_EQUAL(2, cmd.end.offset);
}

/**
 *  @brief  Parse minus command position
 */
void test_parse_pos_minus (void)
{
    char * p_str = "---q";
    eed_parse_s cmd = {0};
    int32_t ret = eed_parse(p_str, &cmd);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(EED_PARSE_CMD_QUIT, cmd.cmd);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_CURR, cmd.start.whence);
    TEST_ASSERT_EQUAL(-3, cmd.start.offset);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_CURR, cmd.end.whence);
    TEST_ASSERT_EQUAL(-3, cmd.end.offset);
}

/**
 *  @brief  Parse num with minus command position
 */
void test_parse_pos_num_minus (void)
{
    char * p_str = "10--q";
    eed_parse_s cmd = {0};
    int32_t ret = eed_parse(p_str, &cmd);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(EED_PARSE_CMD_QUIT, cmd.cmd);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_START, cmd.start.whence);
    TEST_ASSERT_EQUAL(8, cmd.start.offset);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_START, cmd.end.whence);
    TEST_ASSERT_EQUAL(8, cmd.end.offset);
}

/**
 *  @brief  Parse plus with num command position
 */
void test_parse_pos_plus_num (void)
{
    char * p_str = "++10q";
    eed_parse_s cmd = {0};
    int32_t ret = eed_parse(p_str, &cmd);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(EED_PARSE_CMD_QUIT, cmd.cmd);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_CURR, cmd.start.whence);
    TEST_ASSERT_EQUAL(11, cmd.start.offset);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_CURR, cmd.end.whence);
    TEST_ASSERT_EQUAL(11, cmd.end.offset);
}

/**
 *  @brief  Parse plus with num with plus command position
 */
void test_parse_pos_plus_num_plus (void)
{
    char * p_str = "+++5+++q";
    eed_parse_s cmd = {0};
    int32_t ret = eed_parse(p_str, &cmd);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(EED_PARSE_CMD_QUIT, cmd.cmd);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_CURR, cmd.start.whence);
    TEST_ASSERT_EQUAL(10, cmd.start.offset);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_CURR, cmd.end.whence);
    TEST_ASSERT_EQUAL(10, cmd.end.offset);
}

/**
 *  @brief  Parse command with third position from the end
 */
void test_parse_pos_end_with_minus (void)
{
    char * p_str = "$--3q";
    eed_parse_s cmd = {0};
    int32_t ret = eed_parse(p_str, &cmd);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(EED_PARSE_CMD_QUIT, cmd.cmd);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_END, cmd.start.whence);
    TEST_ASSERT_EQUAL(-4, cmd.start.offset);
    TEST_ASSERT_EQUAL(EED_PARSE_WHENCE_END, cmd.end.whence);
    TEST_ASSERT_EQUAL(-4, cmd.end.offset);
}
