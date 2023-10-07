/**
 *  @file   eed_parse.h
 *  @brief  Command parsing module
 *
 *  @author Mikhail Zaytsev
 *  @date   20231007
 */

#ifndef __EED_PARSE_H__
#define __EED_PARSE_H__

/** Includes */

#include <stdbool.h>
#include <stdint.h>

/** Definitions */

/** Structures and types */

typedef enum eed_parse_whence_e
{
    EED_PARSE_WHENCE_INVALID = 0,
    EED_PARSE_WHENCE_START,
    EED_PARSE_WHENCE_CURR,
    EED_PARSE_WHENCE_END
} eed_parse_whence_e;

typedef enum eed_parse_cmd_e
{
    EED_PARSE_CMD_PRINT = 0,
    EED_PARSE_CMD_PRINTNUM,

    EED_PARSE_CMD_INSERT,
    EED_PARSE_CMD_APPEND,
    EED_PARSE_CMD_CHANGE,

    EED_PARSE_CMD_EDIT,
    EED_PARSE_CMD_FILE,

    EED_PARSE_CMD_WRITE,
    EED_PARSE_CMD_READ,
    EED_PARSE_CMD_MOVE,
    EED_PARSE_CMD_UNDO,
    EED_PARSE_CMD_COPY,

    EED_PARSE_CMD_QUIT,
} eed_parse_cmd_e;

typedef struct eed_parse_pos_s
{
    eed_parse_whence_e whence;
    int32_t offset;
} eed_parse_pos_s;
typedef struct eed_parse_s
{
    eed_parse_pos_s start;
    eed_parse_pos_s end;
    eed_parse_pos_s dest;

    eed_parse_cmd_e cmd;

    void * p_arg;
    void * p_regexp;
} eed_parse_s;

/** Public function prototypes */

int32_t eed_parse(const char * p_str, eed_parse_s * p_cmd);

#endif /** __EED_PARSE_H__ */
