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

#ifndef MEM_MODEL_H_
#define MEM_MODEL_H_

#define JSON_MAX_KEYS 10

typedef struct jsonNode {
    char *key;

    enum {
        LEAF,
        OBJECT,
    } type;

    union {
        char *str;
        int num;
    } value;
    struct jsonNode *h;
    struct jsonNode *v;
} jsonNode_t;

typedef enum {
    NONE,
    STRING,
    NUMBER,
    LEFT_BRACE,
    RIGHT_BRACE,
    COLON,
    COMMA,
} tokenType_t;

typedef struct {
    tokenType_t type;

    union {
        char *str;
        int num;
    } value;
} jsonToken_t;

jsonNode_t theJson[JSON_MAX_KEYS];

jsonNode_t* MEM_MODEL_allocNode(void);
void MEM_MODEL_init(void);

#endif /* MEM_MODEL_H_ */