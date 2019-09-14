#include <stdio.h>
#include <liblea/debug.h>
#include <liblea/value.h>

static void leaDebugPrintAny(LeaState* state, LeaValue v);

static void leaDebugPrintRaw(LeaState* state, LeaValue v)
{
    printf("#<%02X:%p>", leaValueGetType(v), leaValueGetPtr(v));
}

static void leaDebugPrintSymbol(LeaState* state, LeaValue v)
{
    (void)v;
    printf(":SYMBOL");
}

static void leaDebugPrintList(LeaState* state, LeaValue v)
{
    int first;
    LeaValue car;

    printf("(");
    first = 1;
    for (;;)
    {
        leaListCar(state, &car, v);
        if (car == LEA_NIL)
            break;
        if (!first)
            printf(" ");
        else
            first = 0;
        leaDebugPrintAny(state, car);
        leaListCdr(state, &v, v);
    }
    printf(")");
}

static void leaDebugPrintAny(LeaState* state, LeaValue v)
{
    switch (leaValueGetType(v))
    {
    case LEA_TYPE_NIL:
        printf("nil");
        break;
    case LEA_TYPE_SYMBOL:
        leaDebugPrintSymbol(state, v);
        break;
    case LEA_TYPE_LIST:
        leaDebugPrintList(state, v);
        break;
    default:
        leaDebugPrintRaw(state, v);
        break;
    }
}

void leaDebugPrint(LeaState* state, LeaValue v)
{
    leaDebugPrintAny(state, v);
    printf("\n");
    fflush(stdout);
}
