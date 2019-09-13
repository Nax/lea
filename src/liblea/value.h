#ifndef LIBLEA_VALUE_H
#define LIBLEA_VALUE_H 1

#include <liblea/common.h>

inline static LeaValue leaValueCreatePtr(LeaType type, void* ptr)
{
    LeaValue v;

    v = 0;
    v |= (((uint64_t)type & 0xff) << 1);
    v |= (((uintptr_t)ptr) << 9);

    return v;
}

inline static void* leaValueGetPtr(LeaValue v)
{
    return (void*)(v >> 9);
}

inline static LeaType leaValueGetType(LeaValue v)
{
    if (v & 1)
        return LEA_TYPE_INTEGER;
    else
        return (LeaType)((v >> 1) & 0xff);
}

#endif
