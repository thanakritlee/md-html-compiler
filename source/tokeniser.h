#ifndef tokeniser_h
#define tokeniser_h

typedef enum {
    TOKEN_H1, TOKEN_H2, TOKEN_H3, TOKEN_H4, TOKEN_H5, TOKEN_H6,
    TOKEN_SPACE, TOKEN_TAB,
    TOKEN_EOF,
} TokenType;

typedef struct {
    TokenType type;
    const char* start;
    int length;
} Token;

void initTokeniser(const char* source);
Token getNextToken();

#endif