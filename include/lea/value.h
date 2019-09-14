#ifndef LEA_VALUE_H
#define LEA_VALUE_H 1

#include <stdint.h>
#include <lea/common.h>

typedef enum {
    LEA_TYPE_NIL        = 0,
    LEA_TYPE_BOOL       = 1,
    LEA_TYPE_SYMBOL     = 2,
    LEA_TYPE_INTEGER    = 3,
    LEA_TYPE_FLOAT      = 4,
    LEA_TYPE_STRING     = 5,
    LEA_TYPE_LIST       = 6,
    LEA_TYPE_HASHMAP    = 7,
    LEA_TYPE_FUNCTION   = 8,
} LeaType;

typedef uint64_t LeaValue;

#define LEA_NIL     ((LeaValue)((LEA_TYPE_NIL  << 1) | (0x00 << 8)))
#define LEA_FALSE   ((LeaValue)((LEA_TYPE_BOOL << 1) | (0x00 << 8)))
#define LEA_TRUE    ((LeaValue)((LEA_TYPE_BOOL << 1) | (0x01 << 8)))

#define LEA_FUNCTION_MACRO      0x01
#define ELA_FUNCTION_VARIADIC   0x02

/* List */
LEA_API LeaError leaListCreate(LeaState* state, LeaValue* value);
LEA_API LeaError leaListPrepend(LeaState* state, LeaValue* dst, LeaValue list, LeaValue element);
LEA_API LeaError leaListReverse(LeaState* state, LeaValue* dst, LeaValue list);
LEA_API LeaError leaListCar(LeaState* state, LeaValue* dst, LeaValue list);
LEA_API LeaError leaListCdr(LeaState* state, LeaValue* dst, LeaValue list);

/* String */
LEA_API LeaError leaStringCreate(LeaState* state, LeaValue* value, const char* str, size_t len);
LEA_API LeaError leaStringCreateC(LeaState* state, LeaValue* value, const char* str);
LEA_API LeaError leaStringData(LeaState* state, const char** str, LeaValue v);
LEA_API LeaError leaStringLength(LeaState* state, size_t* len, LeaValue v);

/* Symbol */
LEA_API LeaError leaSymbolCreate(LeaState* state, LeaValue* value, const char* str, size_t len);
LEA_API LeaError leaSymbolCreateC(LeaState* state, LeaValue* value, const char* str);

/* Function */
LEA_API LeaError leaFunctionCreateC(LeaState* state, LeaValue* value, const void* cfunc, uint16_t argCount, uint8_t flags);
LEA_API LeaError leaFunctionCall(LeaState* state, LeaValue* out, LeaValue func, LeaValue args);

#endif
