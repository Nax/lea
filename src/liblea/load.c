#include <liblea/liblea.h>

LEA_API LeaError leaLoadString(LeaState* state, const char* str, size_t len)
{
    LeaError err;

    err = leaLexerLoadString(state, str, len);
    if (err)
        return err;
    return LEA_OK;
}
