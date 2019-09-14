#include <stdlib.h>
#include <liblea/function.h>
#include <liblea/value.h>

extern LeaValue leaFunctionCallTrampoline(LeaState* state, const void* cfunc, const LeaValue* args, uint16_t argCount);

LEA_API LeaError leaFunctionCreateC(LeaState* state, LeaValue* value, const void* cfunc, uint16_t argCount, uint8_t flags)
{
    UNUSED(state);

    LeaFunction* f;

    f = malloc(sizeof(*f));
    if (!f)
        return LEA_ERROR_OUT_OF_MEMORY;

    f->cfunc = cfunc;
    f->argCount = argCount;
    f->flags = flags;

    *value = leaValueCreatePtr(LEA_TYPE_FUNCTION, f);
    return LEA_OK;
}

static LeaError leaFunctionCallNative(LeaState* state, LeaValue* out, const void* cfunc, LeaValue args)
{
    LeaValue argBuffer[256];
    uint16_t i;

    for (i = 0; i < 256; ++i)
    {
        if (leaValueGetPtr(args) == NULL)
            break;
        leaListCar(state, argBuffer + i, args);
        leaListCdr(state, &args, args);
    }

    *out = leaFunctionCallTrampoline(state, cfunc, argBuffer, i);
    return LEA_OK;
}

LEA_API LeaError leaFunctionCall(LeaState* state, LeaValue* out, LeaValue func, LeaValue args)
{
    UNUSED(state);

    LeaValue tmp;
    LeaValue evaluatedArgs;
    LeaFunction* f;

    f = leaValueGetPtr(func);
    if (!(f->flags & LEA_FUNCTION_MACRO))
    {
        leaListCreate(state, &evaluatedArgs);
        for (;;)
        {
            if (leaValueGetPtr(args) == NULL)
                break;
            leaListCar(state, &tmp, args);
            leaEval(state, &tmp, tmp);
            leaListPrepend(state, &evaluatedArgs, evaluatedArgs, tmp);
            leaListCdr(state, &args, args);
        }
        leaListReverse(state, &args, evaluatedArgs);
    }
    return leaFunctionCallNative(state, out, f->cfunc, args);
}
