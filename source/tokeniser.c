#include <stdbool.h>

#include "tokeniser.h"

typedef struct {
    // The starting mem addr of the current lexeme.
    const char* start;
    // The current mem addr of the current lexeme that
    // the tokeniser is running through.
    const char* current;
} Tokeniser;

Tokeniser tokeniser;

void initTokeniser(const char* source) {
    tokeniser.start = source;
    tokeniser.current = source;
}

static Token makeToken(TokenType type) {
    Token token;
    token.type = type;
    token.start = tokeniser.start;
    token.length = (int)(tokeniser.current - tokeniser.start);
    return token;
}

/**
 * Check if encounter NULL string terminator.
 */
static bool isAtEOF() {
    return *tokeniser.current == '\0';
}

/**
 * Return current character in the lexeme
 * and advance the lexeme character pointer
 * by 1 position.
 */
static char advance() {
    tokeniser.current++;
    return tokeniser.current[-1];
}

/**
 * Advance by multiple positions.
 */
static char advanceByPos(int positions) {
    if (positions == 0) {
        return tokeniser.current[0];
    }

    tokeniser.current = &tokeniser.current[positions];
    return tokeniser.current[-1];
}

/**
 * Return a lookahead character from the source
 * code without advancing.
 * 
 * The `positions` argument is how many positions
 * to look into the source code.
 * A `positions` of `1` will return the character
 * in the current position.
 * Expect `positions` to be >= 1.
 */
static char peek(int positions) {
    int p = 0;
    char currentChar;
    do {
        currentChar = tokeniser.current[p];
        
        // If at any point in source we encounter
        // a null terminator, then we'll break
        // the loop and return.
        if (currentChar == '\0') {
            return '\0';
        }

        p++;
    } while (p <= positions - 1);
    return currentChar;
}

/**
 * Identify complete lexeme and return the correct
 * heading token.
 */
Token getHeadingToken() {
    // Keep on peeking into the source until we
    // find a character that is not '#'.
    // Once found, advance by the positions
    // that the '#' character occupies.
    int peekPosition = 1;
    while (peek(peekPosition) == '#')
    {
        peekPosition++;
    }
    advanceByPos(peekPosition - 1);
    
    /**
     * Identify what token the lexeme represents.
     */
    switch (peekPosition)
    {
        case 1:
            return makeToken(TOKEN_H1);
        case 2:
            return makeToken(TOKEN_H2);
        case 3:
            return makeToken(TOKEN_H3);
        case 4:
            return makeToken(TOKEN_H4);
        case 5:
            return makeToken(TOKEN_H5);
        default:
            // 6 or more #'s is considered
            // a H6 token.
            return makeToken(TOKEN_H6);
    }
}

/**
 * Check whether a character is a reserved special character or not.
 * These characters are lexemes to other tokens.
 */
bool isReservedSpecialCharacter(char c) {
    if (c == '-'  || 
        c == '*'  || 
        c == '!'  || 
        c == '('  || 
        c == ')'  || 
        c == '['  || 
        c == ']'  || 
        c == '<'  || 
        c == '>'  || 
        c == '.'  ||
        c == '#'  ||
        c == '`'  ||
        c == ' '  ||
        c == '\t' ||
        c == '\n' ||
        c == '\0') 
    {
        return true;
    }
    return false;
}

bool isDigit(char c) {
    if (c >= '0' && c <= '9') {
        return true;
    }
    return false;
}

bool isAlphaOrSpecialChar(char c) {
    if (!isReservedSpecialCharacter(c) &&
        !isDigit(c)) {
            return true;
        }
    return false;
}

/**
 * A STRING token can consist of alphabets, numbers, and any
 * non-reserved special characters.
 */
Token getStringToken() {
    while (!isReservedSpecialCharacter(peek(1))) {
        advance();
    }
    return makeToken(TOKEN_STRING);
}

/**
 * Return a NUMBER token.
 * Doesn't look for anymore digits for the NUMBER token lexeme
 * , because all digits in the lexeme has already been identified.
 */
Token getNumberToken() {
    return makeToken(TOKEN_NUMBER);
}

/**
 * Identify whether the iteral token is a STRING or a NUMBER token.
 * A NUMBER token is a sequence of digits not concatenated with 
 * any alphabets or non-reserved special characters.
 * A STRING token is a sequence of alphanumeric and non-reserved
 * special characters concatenated together.
 */
Token getLiteralToken(char currentChar) {    
    // If first character is an alphabet or a non-reserved
    // special character, then it's not a digit.
    if (isAlphaOrSpecialChar(currentChar)) {
        return getStringToken();
    }

    // Look ahead through sequence of digits, until encounter
    // a non-digit character.
    while (isDigit(peek(1))) {
        advance();
    }
    // If the non-digit character is an alphabet, or a 
    // non-reserved special character, then it's a STRING token.
    if (isAlphaOrSpecialChar(peek(1))) {
        return getStringToken();
    } else {
        // Otherwise, it's a NUMBER token.
        // This is because this lookahead character could, for example
        // , be a newline, or a space etc. (i.e. a reserved special character)
        return getNumberToken();
    }
}

Token getNextToken() {
    tokeniser.start = tokeniser.current;

    if (isAtEOF()) {
        return makeToken(TOKEN_EOF);
    }

    char currentChar = advance();

    if (isAlphaOrSpecialChar(currentChar) | isDigit(currentChar)) {
        return getLiteralToken(currentChar);
    }

    switch (currentChar) {
        case '#':
            return getHeadingToken();
        case ' ':
            return makeToken(TOKEN_SPACE);
        case '\t':
            return makeToken(TOKEN_TAB);
        case '\n':
            return makeToken(TOKEN_NEWLINE);
    }
}