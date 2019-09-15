#include <liblea/common.h>

/*
 * This is the FNV-1a hashing algorithm, in it's 32 bit variant.
 */
uint32_t leaHashStr32(const char* str, size_t size)
{
    static const uint32_t prime = 16777619;
    static const uint32_t offset = 2166136261;

    uint8_t tmp;
    uint32_t hash;

    hash = offset;
    for (size_t i = 0; i < size; ++i)
    {
        tmp = (uint8_t)str[i];
        hash ^= tmp;
        hash *= prime;
    }

    return hash;
}
