/**
 *  @file   eed_parse.c
 *  @brief  Command parsing module
 *
 *  @author Mikhail Zaytsev
 *  @date   20231007
 */

/** Includes */

#include "eed_parse.h"
#include <string.h>

/** Definitions */

/** Structures and types */

/** Private data */

/** Private function prototypes */

static bool _is_letter (char chr);
static bool _is_digit (char chr);
static uint8_t _letter_to_digit (char chr);
static eed_parse_cmd_e _parse_cmd (char chr);
static void _whence_def (eed_parse_pos_s * p_pos, eed_parse_whence_e whence);
static void _digit_process (eed_parse_pos_s * p_pos, int32_t * p_tmp_offset, char chr);
static void _symbol_process (eed_parse_pos_s * p_pos, int32_t * p_tmp_offset, int32_t * p_sign_offset, char chr);

/** Public functions */

int32_t eed_parse (const char * p_str, eed_parse_s * p_cmd)
{
    p_cmd->start.whence = EED_PARSE_WHENCE_INVALID;
    eed_parse_pos_s * p_pos = &(p_cmd->start);

    bool is_positive = true;
    int32_t tmp_offset = 0;
    int32_t sign_offset = 0;
    uint32_t len = strlen(p_str);

    for (uint32_t idx = 0; idx < len; idx++)
    {
        if (true == _is_letter(p_str[idx]))
        {
            p_cmd->cmd = _parse_cmd(p_str[idx]);
            _whence_def(p_pos, EED_PARSE_WHENCE_CURR);

            p_pos->offset += sign_offset + tmp_offset;
            sign_offset = 0;
            tmp_offset = 0;
            if (p_pos == &(p_cmd->start))
            {
                p_cmd->end = p_cmd->start;
            }

            p_pos = &(p_cmd->dest);
        }

        _symbol_process (p_pos, &tmp_offset, &sign_offset, p_str[idx]);

        if (true == _is_digit(p_str[idx]))
        {
            _whence_def(p_pos, EED_PARSE_WHENCE_START);
            _digit_process(p_pos, &tmp_offset, p_str[idx]);
        }

        if (',' == p_str[idx])
        {
            p_pos->offset += sign_offset + tmp_offset;
            sign_offset = 0;
            tmp_offset = 0;
            p_pos = &(p_cmd->end);
        }
    }
    p_pos->offset += sign_offset + tmp_offset;

    if (p_pos == &(p_cmd->start))
    {
        p_cmd->end = p_cmd->start;
    }

    return 0;
}

/** Private functions */

static bool _is_letter (char chr)
{
    return ('A' <= chr) && ('z' >= chr);
}

static bool _is_digit (char chr)
{
    return ('0' <= chr) && ('9' >= chr);
}

static eed_parse_cmd_e _parse_cmd (char chr)
{
    switch (chr)
    {
        case 'p':
            return EED_PARSE_CMD_PRINT;
        break;

        case 'i':
            return EED_PARSE_CMD_INSERT;
        break;

        case 'a':
            return EED_PARSE_CMD_APPEND;
        break;

        case 'c':
            return EED_PARSE_CMD_CHANGE;
        break;

        case 'd':
            return EED_PARSE_CMD_DELETE;
        break;

        case 'm':
            return EED_PARSE_CMD_MOVE;
        break;

        case 'j':
            return EED_PARSE_CMD_JOIN;
        break;

        case 'q':
            return EED_PARSE_CMD_QUIT;
        break;

        default:
            return EED_PARSE_CMD_PRINT;
        break;
    }
}

static void _whence_def (eed_parse_pos_s * p_pos, eed_parse_whence_e whence)
{
    if (NULL == p_pos)
    {
        return;
    }

    if (EED_PARSE_WHENCE_INVALID == p_pos->whence)
    {
        p_pos->whence = whence;
    }
}

static uint8_t _letter_to_digit (char chr)
{
    return chr - 48;
}

static void _digit_process (eed_parse_pos_s * p_pos, int32_t * p_tmp_offset, char chr)
{
    if (0 == *p_tmp_offset)
    {
        p_pos->offset *= 10;
        if (0 <= p_pos->offset)
        {
            p_pos->offset += _letter_to_digit(chr);
        }
        else
        {
            p_pos->offset -= _letter_to_digit(chr);
        }
    }
    else if (0 < *p_tmp_offset)
    {
        p_pos->offset += _letter_to_digit(chr);
    }
    else
    {
        p_pos->offset -= _letter_to_digit(chr);
    }

    *p_tmp_offset = 0;
}

static void _symbol_process (eed_parse_pos_s * p_pos, int32_t * p_tmp_offset, int32_t * p_sign_offset, char chr)
{
        switch (chr)
        {
            case '.':
                _whence_def(p_pos, EED_PARSE_WHENCE_CURR);
            break;

            case '$':
                _whence_def(p_pos, EED_PARSE_WHENCE_END);
            break;

            case '+':
                *p_sign_offset += *p_tmp_offset;
                *p_tmp_offset = 0;
                (*p_tmp_offset)++;
                _whence_def(p_pos, EED_PARSE_WHENCE_CURR);
            break;

            case '-':
                *p_sign_offset += *p_tmp_offset;
                *p_tmp_offset = 0;
                (*p_tmp_offset)--;
                _whence_def(p_pos, EED_PARSE_WHENCE_CURR);
            break;
        }
}
