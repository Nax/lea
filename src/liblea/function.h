#ifndef LIBLEA_FUNCTION_H
#define LIBLEA_FUNCTION_H 1

#include <liblea/common.h>

typedef struct
{
    const void* cfunc;
    uint16_t    argCount;
    uint8_t     flags;
} LeaFunction;

#endif
