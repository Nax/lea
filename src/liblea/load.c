#include <liblea/lexer.h>
#include <liblea/parser.h>

LEA_API LeaError leaLoadString(LeaState* state, const char* str, size_t len)
{
    LeaError err;
    LeaValue ast;

    err = leaLexerLoadString(state, str, len);
    if (err)
        return err;
    leaParse(state, &ast);
    return LEA_OK;
}
