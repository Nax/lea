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
} LeaType;

typedef uint64_t LeaValue;

#define LEA_NIL     ((LeaValue)((LEA_TYPE_NIL  << 1) | (0x00 << 8)))
#define LEA_FALSE   ((LeaValue)((LEA_TYPE_BOOL << 1) | (0x00 << 8)))
#define LEA_TRUE    ((LeaValue)((LEA_TYPE_BOOL << 1) | (0x01 << 8)))

LEA_API LeaError leaListCreate(LeaValue* value);
LEA_API LeaError leaListPrepend(LeaValue* dst, LeaValue list, LeaValue element);
LEA_API LeaError leaListReverse(LeaValue* dst, LeaValue list);

#endif
