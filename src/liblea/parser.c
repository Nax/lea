#include <liblea/parser.h>
#include <liblea/lexer.h>
#include <liblea/debug.h>

static int leaParseValue(LeaState* state, LeaValue* dst);

static LeaToken* accept(LeaState* state, LeaTokenType type)
{
    LeaToken* tok;

    tok = leaLexerPeekToken(state);
    if (tok->type == type)
    {
        leaLexerNextToken(state);
        return tok;
    }
    return NULL;
}

static int leaParseEOF(LeaState* state)
{
    if (accept(state, TOKEN_EOF))
        return 1;
    return 0;
}

static int leaParseString(LeaState* state, LeaValue* dst)
{
    LeaToken* tok;

    tok = accept(state, TOKEN_STRING);
    if (!tok)
        return 0;

    leaStringCreate(state, dst, tok->str, tok->strLength);
    return 1;
}

static int leaParseSymbol(LeaState* state, LeaValue* dst)
{
    LeaToken* tok;

    tok = accept(state, TOKEN_SYMBOL);
    if (!tok)
        return 0;

    leaSymbolCreate(state, dst, tok->str, tok->strLength);
    return 1;
}

static int leaParseList(LeaState* state, LeaValue* dst)
{
    LeaValue list;
    LeaValue v;

    if (!(accept(state, TOKEN_LPAREN)))
        return 0;

    leaListCreate(state, &list);
    for (;;)
    {
        if (!leaParseValue(state, &v))
            break;
        leaListPrepend(state, &list, list, v);
    }
    accept(state, TOKEN_RPAREN);
    leaListReverse(state, &list, list);
    *dst = list;
    return 1;
}

static int leaParseQuoteExpr(LeaState* state, LeaValue* dst)
{
    LeaValue list;
    LeaValue v;

    if (!(accept(state, TOKEN_QUOTE)))
        return 0;

    leaListCreate(state, &list);
    leaParseValue(state, &v);
    leaListPrepend(state, &list, list, v);
    leaSymbolCreateC(state, &v, "quote");
    leaListPrepend(state, &list, list, v);

    *dst = list;
    return 1;
}

static int leaParseValue(LeaState* state, LeaValue* dst)
{
    if (leaParseQuoteExpr(state, dst))
        return 1;
    if (leaParseString(state, dst))
        return 1;
    if (leaParseSymbol(state, dst))
        return 1;
    if (leaParseList(state, dst))
        return 1;
    return 0;
}

LeaError leaParse(LeaState* state, LeaValue* dst)
{
    LeaValue ast;
    LeaValue v;

    leaListCreate(state, &ast);
    for (;;)
    {
        if (leaParseEOF(state))
            break;
        if (leaParseValue(state, &v))
            leaListPrepend(state, &ast, ast, v);
    }
    leaListReverse(state, &ast, ast);
    leaDebugPrint(state, ast);

    *dst = ast;
    return LEA_OK;
}
