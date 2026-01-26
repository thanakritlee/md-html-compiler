#ifndef tokeniser_h
#define tokeniser_h

typedef enum {
    TOKEN_H1, TOKEN_H2, TOKEN_H3, TOKEN_H4, TOKEN_H5, TOKEN_H6,
    TOKEN_SPACE, TOKEN_TAB,
    TOKEN_NEWLINE,
    TOKEN_EOF,
    TOKEN_STRING, TOKEN_NUMBER,
    TOKEN_LESS_THAN, TOKEN_GREATER_THAN, TOKEN_GRAVE_ACCENT,
    TOKEN_OPEN_SQUARE_BRACKET, TOKEN_CLOSE_SQUARE_BRACKET,
    TOKEN_OPEN_PARENTHESIS, TOKEN_CLOSE_PARENTHESIS,
    TOKEN_PERIOD, TOKEN_EXCLAMATION_MARK, TOKEN_MINUS, TOKEN_ASTERISK,
} TokenType;

typedef struct {
    TokenType type;
    const char* start;
    int length;
} Token;

void initTokeniser(const char* source);
/**
 * Restore the Tokeniser to an earlier state by
 * resetting the current character memory pointer.
 */
void restoreTokeniser(const char* current);
Token getNextToken();

#endif