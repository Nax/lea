#ifndef LIBLEA_PARSER_H
#define LIBLEA_PARSER_H

#include <lea/lea.h>

#define LEXER_TOKEN_MAX     2

typedef enum {
    TOKEN_NONE = 0,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_QUOTE,
    TOKEN_HASH,
    TOKEN_SYMBOL,
    TOKEN_STRING,
    TOKEN_EOF,
    TOKEN_INVALID
} LeaTokenType;

typedef struct {
    LeaTokenType    type;
    char*           str;
} LeaToken;

typedef struct {
    char*       buffer;
    size_t      bufferSize;
    size_t      cursor;
    LeaToken    tokens[LEXER_TOKEN_MAX];
    size_t      tokenCursor;
} LeaLexer;

LeaError    leaLexerLoadString(LeaState* state, const char* str, size_t size);
void        leaLexerNextToken(LeaState* state);
LeaToken*   leaLexerPeekToken(LeaState* state);

#endif
