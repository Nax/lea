#include <string.h>
#include <liblea/common.h>
#include <liblea/value.h>

LEA_API LeaError leaSymbolCreate(LeaState* state, LeaValue* value, const char* str, size_t len)
{
    /* Dummy implementation */

    *value = leaValueCreatePtr(LEA_TYPE_SYMBOL, NULL);
    return LEA_OK;
}

LEA_API LeaError leaSymbolCreateC(LeaState* state, LeaValue* value, const char* str)
{
    return leaSymbolCreate(state, value, str, strlen(str));
}
