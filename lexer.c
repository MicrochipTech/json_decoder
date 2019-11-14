/*
   (c) 2019 Microchip Technology Inc. and its subsidiaries.

   Subject to your compliance with these terms, you may use Microchip software and any
   derivatives exclusively with Microchip products. It is your responsibility to comply with third party
   license terms applicable to your use of third party software (including open source software) that
   may accompany Microchip software.

   THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
   EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
   IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
   FOR A PARTICULAR PURPOSE.

   IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
   INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
   WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
   HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
   THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
   CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
   OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
   SOFTWARE.
 */
 
#define JSON_SYNTAX "{:,}"
#define NUMBER_CHARACTERS "0123456789"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "mem_model.h"
#include "lexer.h"

static char *current_possition;

typedef enum {
    FOUND,
    NOT_FOUND,
} partialLexStatus_t;

static partialLexStatus_t lex_string(jsonToken_t *token)
{
    if (*current_possition == '"')
    {
        current_possition = current_possition + 1;
    }
    else
    {
        return NOT_FOUND;
    }

    for (uint8_t i = 0; i < strlen(current_possition); i++)
    {
        if (current_possition[i] == '"')
        {
            token->type = STRING;
            token->value.str = current_possition;

            current_possition[i] = 0;
            current_possition = current_possition + i + 1;
            return LEXER_OK;
        }
    }

    return NOT_FOUND;
}

static partialLexStatus_t lex_number(jsonToken_t *token)
{
    char *numEnd = current_possition;
    char temp;

    for (uint8_t i = 0; i < strlen(current_possition); i++)
    {
        if (!strchr(NUMBER_CHARACTERS, current_possition[i]))
        {
            break;
        }
        numEnd = numEnd + 1;
    }

    // Only decimal numbers allowed

    if (numEnd - current_possition >= 1)
    {
        temp = *numEnd;
        *numEnd = 0;

        token->type = NUMBER;
        token->value.num = atoi(current_possition);

        *numEnd = temp;
        current_possition = numEnd;

        return LEXER_OK;
    }

    return NOT_FOUND;
}

static lexStatus_t lex_core(jsonToken_t *token)
{
    partialLexStatus_t ret;

    if (strlen(current_possition))
    {
        ret = lex_string(token);
        if (FOUND == ret)
        {
            return LEXER_OK;
        }
        else if (ret != NOT_FOUND)
        {
            return LEXER_BAD_FORMAT;
        }

        ret = lex_number(token);
        if (FOUND == ret)
        {
            return LEXER_OK;
        }
        else if (ret != NOT_FOUND)
        {
            return LEXER_BAD_FORMAT;
        }

        switch (current_possition[0])
        {
            case ' ': // intended fall through
            case '\\':
                current_possition = current_possition + 1;
                return LEXER_SKIP;

                break;

            case '{':
                token->type = LEFT_BRACE;
                break;

            case '}':
                token->type = RIGHT_BRACE;
                break;

            case ',':
                token->type = COMMA;
                break;

            case ':':
                token->type = COLON;
                break;

            default:
                return LEXER_BAD_FORMAT;
        }

        current_possition = current_possition + 1;

        return LEXER_OK;
    }

    return LEXER_NO_MORE_TOKENS;
}

lexStatus_t LEXER_nextToken(jsonToken_t *token)
{
    lexStatus_t ret;
    ret = lex_core(token);

    while (LEXER_SKIP == ret)
    {
        ret = lex_core(token);
    }

    return ret;
}

void LEXER_init(char *str)
{
    current_possition = str;
}
