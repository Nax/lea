#ifndef LIBLEA_COMMON_H
#define LIBLEA_COMMON_H 1

#include <stdlib.h>
#include <lea/lea.h>

#define UNUSED(x)   ((void)(x))
#define zalloc(x)   calloc(1, (x))

uint32_t leaHashStr32(const char* str, size_t size);

#endif
