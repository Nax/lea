#include <stdio.h>
#include <liblea/debug.h>
#include <liblea/value.h>

static void leaDebugPrintAny(LeaValue v);

static void leaDebugPrintRaw(LeaValue v)
{
    printf("#<%02X:%p>", leaValueGetType(v), leaValueGetPtr(v));
}

static void leaDebugPrintSymbol(LeaValue v)
{
    (void)v;
    printf(":SYMBOL");
}

static void leaDebugPrintList(LeaValue v)
{
    int first;
    LeaValue car;

    printf("(");
    first = 1;
    for (;;)
    {
        leaListCar(&car, v);
        if (car == LEA_NIL)
            break;
        if (!first)
            printf(" ");
        else
            first = 0;
        leaDebugPrintAny(car);
        leaListCdr(&v, v);
    }
    printf(")");
}

static void leaDebugPrintAny(LeaValue v)
{
    switch (leaValueGetType(v))
    {
    case LEA_TYPE_NIL:
        printf("nil");
        break;
    case LEA_TYPE_SYMBOL:
        leaDebugPrintSymbol(v);
        break;
    case LEA_TYPE_LIST:
        leaDebugPrintList(v);
        break;
    default:
        leaDebugPrintRaw(v);
        break;
    }
}

void leaDebugPrint(LeaValue v)
{
    leaDebugPrintAny(v);
    printf("\n");
    fflush(stdout);
}
