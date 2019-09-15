#ifndef LIBLEA_SYMBOL_H
#define LIBLEA_SYMBOL_H 1

#include <liblea/common.h>

typedef struct
{
    char*       str;
    size_t      size;
    uint32_t    hash;
} LeaSymbolPoolEntry;

typedef struct
{
    LeaSymbolPoolEntry*     slots;
    size_t                  slotCount;
    size_t                  slotUsage;
} LeaSymbolPool;

LeaError leaSymbolPoolInit(LeaState* state);

#endif
