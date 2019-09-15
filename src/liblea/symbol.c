#include <string.h>
#include <liblea/liblea.h>

LeaError leaSymbolPoolInit(LeaState* state)
{
    LeaSymbolPool* pool = &state->symPool;

    pool->slotCount = 16;
    pool->slotUsage = 0;
    pool->slots = zalloc(pool->slotCount * sizeof(*pool->slots));

    return LEA_OK;
}

static int leaSymbolPoolLookup(LeaSymbolPoolEntry** dst, LeaSymbolPool* pool, const char* str, size_t len, uint32_t hash)
{
    LeaSymbolPoolEntry* e;
    size_t i;

    i = hash & (pool->slotCount - 1);

    for (;;)
    {
        e = pool->slots + i;
        if (!e->str)
        {
            *dst = e;
            return 0;
        }
        if (e->hash == hash && e->size == len && memcmp(str, e->str, len) == 0)
        {
            *dst = e;
            return 1;
        }
        i = (i + 1) & (pool->slotCount - 1);
    }
}

static void leaSymbolPoolExpand(LeaSymbolPool* pool)
{
    LeaSymbolPool newPool;
    LeaSymbolPoolEntry* eOld;
    LeaSymbolPoolEntry* eNew;

    newPool.slotCount = pool->slotCount * 2;
    newPool.slotUsage = pool->slotUsage;
    newPool.slots = zalloc(newPool.slotCount * sizeof(*newPool.slots));

    for (size_t i = 0; i < pool->slotCount; ++i)
    {
        eOld = pool->slots + i;
        if (!eOld->str)
            continue;
        leaSymbolPoolLookup(&eNew, &newPool, eOld->str, eOld->size, eOld->hash);
        eNew->str = eOld->str;
        eNew->size = eOld->size;
        eNew->hash = eOld->hash;
    }

    free(pool->slots);

    pool->slotCount = newPool.slotCount;
    pool->slots = newPool.slots;
}

LEA_API LeaError leaSymbolCreate(LeaState* state, LeaValue* value, const char* str, size_t len)
{
    LeaSymbolPool* pool;
    LeaSymbolPoolEntry* e;
    uint32_t hash;
    char* tmp;
    char* addr;

    pool = &state->symPool;
    hash = leaHashStr32(str, len);
    if (leaSymbolPoolLookup(&e, pool, str, len, hash))
    {
        addr = e->str;
    }
    else
    {
        tmp = malloc(len + 1);
        memcpy(tmp, str, len);
        tmp[len] = 0;

        e->hash = hash;
        e->str = tmp;
        e->size = len;

        addr = tmp;

        pool->slotUsage++;
        if (pool->slotUsage > pool->slotCount / 2)
            leaSymbolPoolExpand(pool);
    }

    *value = leaValueCreatePtr(LEA_TYPE_SYMBOL, addr);
    return LEA_OK;
}

LEA_API LeaError leaSymbolCreateC(LeaState* state, LeaValue* value, const char* str)
{
    return leaSymbolCreate(state, value, str, strlen(str));
}
