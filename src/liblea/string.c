#include <string.h>
#include <stdlib.h>
#include <liblea/string.h>
#include <liblea/value.h>

LEA_API LeaError leaStringCreate(LeaState* state, LeaValue* value, const char* str, size_t len)
{
    LeaString* s;

    UNUSED(state);

    s = malloc(sizeof(LeaString) + len + 1);
    if (!s)
        return LEA_ERROR_OUT_OF_MEMORY;

    s->length = len;
    memcpy(s->data, str, len);
    s->data[len] = 0;

    *value = leaValueCreatePtr(LEA_TYPE_STRING, s);
    return LEA_OK;
}

LEA_API LeaError leaStringCreateC(LeaState* state, LeaValue* value, const char* str)
{
    return leaStringCreate(state, value, str, strlen(str));
}

LEA_API LeaError leaStringData(LeaState* state, const char** str, LeaValue v)
{
    LeaString* s;

    UNUSED(state);

    s = leaValueGetPtr(v);
    *str = s->data;
    return LEA_OK;
}

LEA_API LeaError leaStringLength(LeaState* state, size_t* len, LeaValue v)
{
    LeaString* s;

    UNUSED(state);

    s = leaValueGetPtr(v);
    *len = s->length;
    return LEA_OK;
}
