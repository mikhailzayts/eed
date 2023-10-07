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

bool _is_letter (char chr);
bool _is_digit (char chr);
uint8_t _letter_to_digit (char chr);
eed_parse_cmd_e _parse_cmd (char chr);
void _whence_def (eed_parse_pos_s * p_pos, eed_parse_whence_e whence);

/** Public functions */

int32_t eed_parse (const char * p_str, eed_parse_s * p_cmd)
{
    p_cmd->start.whence = EED_PARSE_WHENCE_INVALID;

    bool is_num = false;
    bool is_plus = false;
    bool is_minus = false;
    bool is_positive = true;
    int32_t temp_offset = 0;
    uint32_t len = strlen(p_str);
    for (uint32_t idx = 0; idx < len; idx++)
    {
        if (true == _is_letter(p_str[idx]))
        {
            p_cmd->cmd = _parse_cmd(p_str[idx]);
            _whence_def(&(p_cmd->start), EED_PARSE_WHENCE_CURR);
        }

        switch (p_str[idx])
        {
            case '.':
                is_num = false;
                is_plus = false;
                is_minus = false;
                _whence_def(&(p_cmd->start), EED_PARSE_WHENCE_CURR);
            break;

            case '$':
                is_num = false;
                is_plus = false;
                is_minus = false;
                _whence_def(&(p_cmd->start), EED_PARSE_WHENCE_END);
            break;

            case '+':
                is_num = false;
                is_minus = false;
                temp_offset++;
                is_plus = true;
                _whence_def(&(p_cmd->start), EED_PARSE_WHENCE_CURR);
            break;

            case '-':
                is_num = false;
                is_plus = false;
                temp_offset--;
                is_minus = true;
                _whence_def(&(p_cmd->start), EED_PARSE_WHENCE_CURR);
            break;
        }

        if (true == _is_digit(p_str[idx]))
        {
            if (true == is_plus)
            {
                is_positive = true;
                temp_offset--;
                is_plus = false;
            }

            if (true == is_minus)
            {
                is_positive = false;
                temp_offset++;
                is_minus = false;
            }

            _whence_def(&(p_cmd->start), EED_PARSE_WHENCE_START);
            if (true == is_num)
            {
                p_cmd->start.offset *= 10;
            }

            if (true == is_positive)
            {
                p_cmd->start.offset += _letter_to_digit(p_str[idx]);
            }
            else
            {
                p_cmd->start.offset -= _letter_to_digit(p_str[idx]);
            }

            is_num = true;
        }
    }
    p_cmd->start.offset += temp_offset;

    p_cmd->end = p_cmd->start;

    return 0;
}

/** Private functions */

bool _is_letter (char chr)
{
    return ('A' <= chr) && ('z' >= chr);
}

bool _is_digit (char chr)
{
    return ('0' <= chr) && ('9' >= chr);
}

eed_parse_cmd_e _parse_cmd (char chr)
{
    switch (chr)
    {
        case 'p':
            return EED_PARSE_CMD_PRINT;
        break;

        case 'q':
            return EED_PARSE_CMD_QUIT;
        break;

        default:
            return EED_PARSE_CMD_PRINT;
        break;
    }
}

void _whence_def (eed_parse_pos_s * p_pos, eed_parse_whence_e whence)
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

uint8_t _letter_to_digit (char chr)
{
    return chr - 48;
}
