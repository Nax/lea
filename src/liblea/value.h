#ifndef LIBLEA_VALUE_H
#define LIBLEA_VALUE_H 1

#include <liblea/common.h>

inline static LeaValue leaValueCreatePtr(LeaType type, void* ptr)
{
    LeaValue v;

    v = 0;
    v |= (type << 1);
    v |= (((uintptr_t)ptr) << 8);

    return v;
}

inline static void* leaValueGetPtr(LeaValue v)
{
    return (void*)(v >> 9);
}

#endif
