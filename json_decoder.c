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

#include <string.h>
#include <stdint.h>
#include "json_decoder.h"
#include "mem_model.h"
#include "lexer.h"
#include "parser.h"

jsonDecoderStatus_t JSON_DECODER_getRoot(jsonNode_t **pNode)
{
    *pNode = theJson;
    return JSON_DECODER_OK;
}

jsonDecoderStatus_t JSON_DECODER_getObject(jsonNode_t *current, char *key, jsonNode_t **pNode)
{
    do
    {
        if (strcmp(current->key, key) == 0)
        {
            if (current->type == OBJECT && current->v != NULL)
            {
                *pNode = current->v;
                return JSON_DECODER_OK;
            }
            return JSON_DECODER_KEY_NOT_FOUND;
        }
        current = current->h;
    } while (current != NULL);

    return JSON_DECODER_KEY_NOT_FOUND;
}

jsonDecoderStatus_t JSON_DECODER_getString(jsonNode_t *current, char *key, uint8_t size, char *pVal)
{
    do
    {
        if (strcmp(current->key, key) == 0)
        {
            strncpy(pVal, current->value.str, size);
            return JSON_DECODER_OK;
        }
        current = current->h;
    } while (current != NULL);

    return JSON_DECODER_KEY_NOT_FOUND;
}

jsonDecoderStatus_t JSON_DECODER_getNumber(jsonNode_t *current, char *key, int *pVal)
{
    do
    {
        if (strcmp(current->key, key) == 0)
        {
            *pVal = current->value.num;
            return JSON_DECODER_OK;
        }
        current = current->h;
    } while (current != NULL);

    return JSON_DECODER_KEY_NOT_FOUND;
}

jsonDecoderStatus_t JSON_DECODER_fromString(char *str)
{
    MEM_MODEL_init();
    LEXER_init(str);

    if (PARSER_OK != PARSER_parseTokens())
    {
        return JSON_DECODER_BAD_FORMAT;
    }

    return JSON_DECODER_OK;
}