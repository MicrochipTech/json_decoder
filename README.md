# JSON Decoder

JSON Decoder aims to:

1. Be highly optimized for constrained embedded systems
2. Work on both PIC18 and AVR

## Example Usage

```
#define TEST_JSON "{\"main\":{\"key\" : 10,\"foo\":\"bar\"}, \"alt\":2}"

...

jsonNode_t *root, *objmain;
char foo[10], str[50];
int alt;

memcpy(str, TEST_JSON, sizeof(TEST_JSON));

JSON_DECODER_fromString(str)

JSON_DECODER_getRoot(&root);
JSON_DECODER_getObject(root, "main", &objmain);

JSON_DECODER_getNumber(root, "alt", &alt)
JSON_DECODER_getString(objmain, "foo", strlen(foo), foo)
```

## API

## `jsonDecoderStatus_t JSON_DECODER_fromString(char *str)`

###### Description

Parses a JSON string into a C representation. It supports string, number and object values.

###### Params

| Name | Type | Description                                                                                 |
| ---- | ---- | ------------------------------------------------------------------------------------------- |
| str  | IN   | A string representation of a JSON object. After parsing, the string will have been altered. |

###### Return

| Name                    | Description             |
| ----------------------- | ----------------------- |
| JSON_DECODER_OK         | Decoding was successful |
| JSON_DECODER_BAD_FORMAT | The input is invalid.   |

## `JSON_DECODER_getRoot(jsonNode_t **pNode)`

###### Description

The outermost object in a JSON is called the root.
This function must not be called before JSON_DECODER_fromString.

###### Params

| Name  | Type | Description                                                                                                             |
| ----- | ---- | ----------------------------------------------------------------------------------------------------------------------- |
| pNode | OUT  | Pointer to the root. When the function is called this parameter does not need to point to a valid `jsonNode_t` address. |

###### Return

| Name            | Description                  |
| --------------- | ---------------------------- |
| JSON_DECODER_OK | pNode now points to the root |

## `jsonDecoderStatus_t JSON_DECODER_getObject(jsonNode_t *current, char *key, jsonNode_t **pNode)`

###### Description

Finds a JSON object by key in another JOSN object.
This function must not be called before JSON_DECODER_fromString.

###### Params

| Name    | Type | Description                                                                                                                         |
| ------- | ---- | ----------------------------------------------------------------------------------------------------------------------------------- |
| current | IN   | The JSON object to search into                                                                                                      |
| key     | IN   | The key of the object to find                                                                                                       |
| pNode   | OUT  | Pointer to the object, if found. When the function is called this parameter does not need to point to a valid `jsonNode_t` address. |

###### Return

| Name                       | Description                                 |
| -------------------------- | ------------------------------------------- |
| JSON_DECODER_OK            | Object was found and pNode now points to in |
| JSON_DECODER_KEY_NOT_FOUND | The specified key does not exist            |

## `jsonDecoderStatus_t JSON_DECODER_getString(jsonNode_t *current, char *key, uint8_t size, char *pVal)`

###### Description

Finds a string by key in a JOSN object.
This function must not be called before JSON_DECODER_fromString.

###### Params

| Name    | Type | Description                                                                         |
| ------- | ---- | ----------------------------------------------------------------------------------- |
| current | IN   | The JSON object to search into                                                      |
| key     | IN   | The key of the string to find                                                       |
| size    | IN   | Maximum size of the string. Should not be bigger than the length of the pVal buffer |
| pVal    | OUT  | Pointer to the string, if found                                                     |

###### Return

| Name                       | Description                                |
| -------------------------- | ------------------------------------------ |
| JSON_DECODER_OK            | String was found and pVal now points to in |
| JSON_DECODER_KEY_NOT_FOUND | The specified key does not exist           |

## `jsonDecoderStatus_t JSON_DECODER_getNumber(jsonNode_t *current, char *key, int *pVal)`

###### Description

Finds a number by key in a JSON object.
This function must not be called before JSON_DECODER_fromString.

###### Params

| Name    | Type | Description                     |
| ------- | ---- | ------------------------------- |
| current | IN   | The JSON object to search into  |
| key     | IN   | The key of the string to find   |
| pVal    | OUT  | Pointer to the number, if found |

###### Return

| Name                       | Description                                |
| -------------------------- | ------------------------------------------ |
| JSON_DECODER_OK            | Number was found and pVal now points to in |
| JSON_DECODER_KEY_NOT_FOUND | The specified key does not exist           |
