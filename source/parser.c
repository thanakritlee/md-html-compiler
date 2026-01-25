#include "./buffer.h"
#include "./tokeniser.h"

typedef struct {
    Token previousToken;
    Token currentToken;
} Parser;

Parser parser;

// Get the next token.
void advance() {
    parser.previousToken = parser.currentToken;

    parser.currentToken = getNextToken();
}

void contentRule() {
    while (parser.currentToken.type != TOKEN_NEWLINE &&
        parser.currentToken.type != TOKEN_EOF) {
            // TODO: Handle inline-code and link rules.
            // TODO: Handle reserved special characters.            
            writeToBuffer(parser.currentToken.start, parser.currentToken.length);
            advance();
        }

    // Skip through all left over newlines after content, if any.
    while (parser.currentToken.type == TOKEN_NEWLINE) {
        advance();
    }
}

void headingRule() {
    /**
     * Initial state:
     * - previousToken is a heading token.
     * - currentToken is a space or tab token.
     */

    TokenType headingType = parser.previousToken.type;
    char headingNumber = '1';
    switch (headingType)
    {
        case TOKEN_H1:
            headingNumber = '1';
            break;
        case TOKEN_H2:
            headingNumber = '2';
            break;
        case TOKEN_H3:
            headingNumber = '3';
            break;
        case TOKEN_H4:
            headingNumber = '4';
            break;
        case TOKEN_H5:
            headingNumber = '5';
            break;
        case TOKEN_H6:
            headingNumber = '6';
            break;
    }
    char openHeadingStr[] = "<h?>";
    openHeadingStr[2] = headingNumber;
    char closeHeadingStr[] = "</h?>\n";
    closeHeadingStr[3] = headingNumber;

    writeToBuffer(openHeadingStr, 4);

    // Skip through all whitespace between '#' and content.
    while (parser.currentToken.type == TOKEN_SPACE ||
        parser.currentToken.type == TOKEN_TAB) {
            advance();
        }

    contentRule();

    writeToBuffer(closeHeadingStr, 6);
}

void paragraphRule() {
    writeToBuffer("<p>\n", 4);

    // TODO: Add paragraph rule.
    // ...

    writeToBuffer("</p>\n", 5);
}

void sectionRule() {
    if (
        parser.currentToken.type == TOKEN_H1 ||
        parser.currentToken.type == TOKEN_H2 ||
        parser.currentToken.type == TOKEN_H3 ||
        parser.currentToken.type == TOKEN_H4 ||
        parser.currentToken.type == TOKEN_H5 ||
        parser.currentToken.type == TOKEN_H6
    ) {
        advance();
        // Determine whether to follow the heading or paragraph
        // production rule.
        if (parser.currentToken.type == TOKEN_SPACE || 
            parser.currentToken.type == TOKEN_TAB) {
                // Follow the heading rule.
                headingRule();
            } else {
                // Follow the paragraph rule.
                paragraphRule();
            }
    }
}

void parse() {
    writeToBuffer("<!DOCTYPE html>\n", 16);
    writeToBuffer("<html>\n", 7);

    advance();
    while (parser.currentToken.type != TOKEN_EOF) {
        sectionRule();
    }

    writeToBuffer("</html>\0", 7);
}