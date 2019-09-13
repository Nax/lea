#include <stdlib.h>
#include <liblea/list.h>
#include <liblea/value.h>

LEA_API LeaError leaListCreate(LeaValue* value)
{
    *value = leaValueCreatePtr(LEA_TYPE_LIST, NULL);
    return LEA_OK;
}

LEA_API LeaError leaListPrepend(LeaValue* dst, LeaValue list, LeaValue element)
{
    LeaPair* p;

    p = malloc(sizeof(LeaPair));
    if (!p)
        return LEA_ERROR_OUT_OF_MEMORY;

    p->car = element;
    p->cdr = list;

    *dst = leaValueCreatePtr(LEA_TYPE_LIST, p);
    return LEA_OK;
}

LEA_API LeaError leaListReverse(LeaValue* dst, LeaValue list)
{
    LeaValue newList;
    LeaPair* p;

    leaListCreate(&newList);

    for (;;)
    {
        p = leaValueGetPtr(list);
        if (!p)
            break;
        leaListPrepend(&newList, newList, p->car);
        list = p->cdr;
    }

    *dst = newList;
    return LEA_OK;
}
