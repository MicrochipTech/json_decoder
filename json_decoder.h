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

#ifndef JSON_DECODER_H_
#define JSON_DECODER_H_

#include "mem_model.h"

typedef enum {
    JSON_DECODER_OK,
    JSON_DECODER_BAD_FORMAT,
    JSON_DECODER_KEY_NOT_FOUND,
} jsonDecoderStatus_t;

/**
 * \brief Parses a JSON string into a C representation.
 *
 * It supports string, number and object values.
 *
 * \param[in] str A string representation of a JSON object. After parsing, the string will have been altered.
 *
 * \return Decoder status.
 * \retval JSON_DECODER_OK Decoding is successful.
 * \retval JSON_DECODER_BAD_FORMAT There input is invalid.
 */
jsonDecoderStatus_t JSON_DECODER_fromString(char *str);

/**
 * \brief The outermost object in a JSON is called the root.
 *
 * This function must not be called before JSON_DECODER_fromString.
 *
 * \param[out] pNode Pointer to a jsonNode_t.
 *
 * \return Decoder status.
 * \retval JSON_DECODER_OK pNode now points to the root.
 */
jsonDecoderStatus_t JSON_DECODER_getRoot(jsonNode_t **pNode);

/**
 * \brief Finds a JSON object by key in another JOSN object.
 *
 * This function must not be called before JSON_DECODER_fromString.
 *
 * \param[in] current The JSON object to search into.
 * \param[in] key The key of the object to find.
 * \param[out] pNode Pointer to the object, if found.
 *
 * \return Decoder status.
 * \retval JSON_DECODER_OK Object was found and pNode now points to in.
 * \retval JSON_DECODER_KEY_NOT_FOUND The specified key does not exist.
 */
jsonDecoderStatus_t JSON_DECODER_getObject(jsonNode_t *current, char *key, jsonNode_t **pNode);

/**
 * \brief Finds a string by key in a JOSN object.
 *
 * This function must not be called before JSON_DECODER_fromString.
 *
 * \param[in] current The JSON object to search into.
 * \param[in] key The key of the string to find.
 * \param[in] size Maximum size of the string. Should not be bigger than the length of the pVal buffer.
 * \param[out] pVal Pointer to the string, if found.
 *
 * \return Decoder status.
 * \retval JSON_DECODER_OK String was found and pVal now points to in.
 * \retval JSON_DECODER_KEY_NOT_FOUND The specified key does not exist.
 */
jsonDecoderStatus_t JSON_DECODER_getString(jsonNode_t *current, char *key, uint8_t size, char *pVal);

/**
 * \brief Finds a number by key in a JSON object.
 *
 * This function must not be called before JSON_DECODER_fromString.
 *
 * \param[in] current The JSON object to search into.
 * \param[in] key The key of the string to find.
 * \param[out] pVal Pointer to the number, if found.
 *
 * \return Decoder status.
 * \retval JSON_DECODER_OK Number was found and pVal now points to in.
 * \retval JSON_DECODER_KEY_NOT_FOUND The specified key does not exist.
 */
jsonDecoderStatus_t JSON_DECODER_getNumber(jsonNode_t *current, char *key, int *pVal);

#endif /* JSON_DECODER_H_ */
