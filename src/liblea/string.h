#ifndef LIBLEA_STRING_H
#define LIBLEA_STRING_H 1

#include <liblea/common.h>

typedef struct
{
    size_t  length;
    char    data[];
} LeaString;

#endif
