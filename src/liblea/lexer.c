#include <string.h>
#include <stdlib.h>
#include <liblea/liblea.h>

typedef struct
{
    const char*     str;
    LeaTokenType    type;
} LeaLexerSimpleMatcher;

static void leaLexerFreeToken(LeaToken* tok)
{
    switch (tok->type)
    {
    default:
        break;
    case TOKEN_SYMBOL:
    case TOKEN_STRING:
        free(tok->str);
        break;
    }
}

static void leaLexerSkipWS(LeaLexer* lex)
{
    char c;

    for (;;)
    {
        c = lex->buffer[lex->cursor];
        if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f')
            lex->cursor++;
        else
            break;
    }
}

static int leaLexerTokenSimple(LeaLexer* lex, LeaToken* tok)
{
    static const LeaLexerSimpleMatcher matchers[] = {
        {"(", TOKEN_LPAREN},
        {")", TOKEN_RPAREN},
        {"#", TOKEN_HASH},
        {"'", TOKEN_QUOTE},
    };

    for (size_t i = 0; i < sizeof(matchers) / sizeof(*matchers); ++i)
    {
        if (memcmp(lex->buffer + lex->cursor, matchers[i].str, strlen(matchers[i].str)) == 0)
        {
            tok->type = matchers[i].type;
            lex->cursor += strlen(matchers[i].str);
            return 1;
        }
    }

    return 0;
}

static int leaLexerTokenString(LeaLexer* lex, LeaToken* tok)
{
    char c;
    size_t len;

    if (lex->buffer[lex->cursor] != '"')
        return 0;
    lex->cursor++;
    len = 0;
    for (;;)
    {
        c = lex->buffer[lex->cursor + len];
        if (c == 0 || c == '"')
            break;
        len++;
    }
    tok->type = TOKEN_STRING;
    tok->strLength = len;
    tok->str = malloc(len);
    memcpy(tok->str, lex->buffer + lex->cursor, len);
    lex->cursor += len;
    lex->cursor++;
    return 1;
}

static void leaLexerLexToken(LeaLexer* lex, LeaToken* tok)
{
    leaLexerSkipWS(lex);

    if (leaLexerTokenSimple(lex, tok))
        return;
    if (leaLexerTokenString(lex, tok))
        return;

    if (lex->cursor == lex->bufferSize)
        tok->type = TOKEN_EOF;
    else
        tok->type = TOKEN_INVALID;
}

LeaError leaLexerLoadString(LeaState* state, const char* str, size_t size)
{
    LeaLexer* lex = &state->lexer;

    /* We over-allocate by one NUL byte to make EOF checking easier */
    lex->buffer = malloc(size + 1);
    if (!lex->buffer)
        return LEA_ERROR_OUT_OF_MEMORY;

    memcpy(lex->buffer, str, size);
    lex->buffer[size] = 0;
    lex->bufferSize = size;

    lex->cursor = 0;
    lex->tokenCursor = LEXER_TOKEN_MAX - 1;
    memset(lex->tokens, 0, sizeof(LeaToken) * LEXER_TOKEN_MAX);

    return LEA_OK;
}

void leaLexerNextToken(LeaState* state)
{
    LeaLexer* lex = &state->lexer;
    LeaToken* tok;

    lex->tokenCursor = (lex->tokenCursor + 1) % LEXER_TOKEN_MAX;
    tok = &lex->tokens[lex->tokenCursor];

    leaLexerFreeToken(tok);
    leaLexerLexToken(lex, tok);
}

LeaToken* leaLexerPeekToken(LeaState* state)
{
    LeaLexer* lex = &state->lexer;

    return &lex->tokens[lex->tokenCursor];
}
