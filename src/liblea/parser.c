#include <liblea/parser.h>
#include <liblea/lexer.h>
#include <liblea/debug.h>

LeaError leaParse(LeaState* state, LeaValue* dst)
{
    LeaValue ast;

    leaListCreate(&ast);
    leaDebugPrint(ast);

    *dst = ast;
    return LEA_OK;
}
