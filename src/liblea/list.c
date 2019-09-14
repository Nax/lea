#include <stdlib.h>
#include <stdio.h>
#include <liblea/list.h>
#include <liblea/value.h>

LEA_API LeaError leaListCreate(LeaState* state, LeaValue* value)
{
    UNUSED(state);

    *value = leaValueCreatePtr(LEA_TYPE_LIST, NULL);
    return LEA_OK;
}

LEA_API LeaError leaListPrepend(LeaState* state, LeaValue* dst, LeaValue list, LeaValue element)
{
    LeaPair* p;

    UNUSED(state);

    p = malloc(sizeof(LeaPair));
    if (!p)
        return LEA_ERROR_OUT_OF_MEMORY;

    p->car = element;
    p->cdr = list;

    *dst = leaValueCreatePtr(LEA_TYPE_LIST, p);
    return LEA_OK;
}

LEA_API LeaError leaListReverse(LeaState* state, LeaValue* dst, LeaValue list)
{
    LeaValue newList;
    LeaPair* p;

    UNUSED(state);

    leaListCreate(state, &newList);

    for (;;)
    {
        p = leaValueGetPtr(list);
        if (!p)
            break;
        leaListPrepend(state, &newList, newList, p->car);
        list = p->cdr;
    }

    *dst = newList;
    return LEA_OK;
}

LEA_API LeaError leaListCar(LeaState* state, LeaValue* dst, LeaValue list)
{
    LeaPair* p;

    UNUSED(state);

    p = leaValueGetPtr(list);
    if (!p)
        *dst = LEA_NIL;
    else
        *dst = p->car;
    return LEA_OK;
}

LEA_API LeaError leaListCdr(LeaState* state, LeaValue* dst, LeaValue list)
{
    LeaPair* p;

    UNUSED(state);

    p = leaValueGetPtr(list);
    if (!p)
        *dst = LEA_NIL;
    else
        *dst = p->cdr;
    return LEA_OK;
}
