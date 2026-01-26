#include <stdbool.h>

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

/**
 * Check whether a token is a reserved HTML
 * character or not.
 * Reserved HTML characters are required to be
 * converted to HTML code e.g. &lt and &gt.
 */
bool isReservedHTMLCharacter(Token token) {
    if (token.type == TOKEN_LESS_THAN || 
        token.type == TOKEN_GREATER_THAN) {
            return true;
        }
    return false;
}

/**
 * Convert the reserved HTML character to HTML code
 * and write it to the buffer.
 */
void writeReservedHTMLCharacter(Token token) {
    switch (token.type) {
        case TOKEN_LESS_THAN:
            writeToBuffer("&lt", 3);
            break;
        case TOKEN_GREATER_THAN:
            writeToBuffer("&gt", 3);
            break;
    }
}

/**
 * Write the token to the buffer.
 * If the token is a reserved HTML character, then 
 * convert it to HTML code first then write it to
 * the buffer.
 * Otherwise, just write the token to the buffer.
 */
void writeTokenToBuffer(Token token) {
    if (isReservedHTMLCharacter(token)) {
        writeReservedHTMLCharacter(parser.currentToken);
    } else {
        writeToBuffer(token.start, token.length);
    }
}

/**
 * Restore both the parser and tokeniser to an earlier state.
 * 
 * The predictive parser does multiple lookahead of tokens to determine
 * which grammar rule to use. This function is use at the end after a grammar
 * rule has been determined to restore the parser and tokeniser back to the
 * state before doing the lookahead.
 */
void restoreParserAndTokeniser(Token previousToken, Token currentToken) {
    parser.previousToken = previousToken;
    parser.currentToken = currentToken;
    restoreTokeniser(currentToken.start + currentToken.length);
}

/**
 * Do multiple tokens lookahead to check whether the opening 
 * TOKEN_GRAVE_ACCENT has a closing TOKEN_GRAVE_ACCENT to fit 
 * into the inline code rule or not.
 * Inline code format: `...`
 */
bool isInlineCodeRule() {
    /**
     * Initial state:
     * - currentToken is the opening TOKEN_GRAVE_ACCENT.
     * End state:
     * - currentToken is the opening TOKEN_GRAVE_ACCENT.
     */

    Token originalPrevToken = parser.previousToken;
    Token originalCurrToken = parser.currentToken;

    advance();
    while (parser.currentToken.type != TOKEN_GRAVE_ACCENT && 
        parser.currentToken.type != TOKEN_NEWLINE &&
        parser.currentToken.type != TOKEN_EOF)
        {
            advance();
        }

    Token currToken = parser.currentToken;

    restoreParserAndTokeniser(originalPrevToken, originalCurrToken);

    if (currToken.type == TOKEN_GRAVE_ACCENT) {
        // Has a closing TOKEN_GRAVE_ACCENT.
        // Therefore, an inline code rule is valid.
        return true;
    }
    return false;
}

/**
 * Produce a HTML inline code:
 * <code> .... </code>
 */
void inlineCodeRule() {
    /**
     * Initial state:
     * - currentToken is the opening TOKEN_GRAVE_ACCENT.
     * Ending state:
     * - currentToken is the ending TOKEN_GRAVE_ACCENT.
     */

    writeToBuffer("<code>", 6);

    advance();
    while (parser.currentToken.type != TOKEN_GRAVE_ACCENT) {
        writeTokenToBuffer(parser.currentToken);
        advance();
    }

    writeToBuffer("</code>", 7);
}

/**
 * Do multiple tokens lookahead to determine whether it is
 * a link rule or not.
 * link rule format: [...](...)
 */
bool isLinkRule() {
    /**
     * Initial state:
     * - currentToken is the opening TOKEN_OPEN_SQUARE_BRACKET.
     * End state:
     * - currentToken is the opening TOKEN_OPEN_SQUARE_BRACKET.
     */

    Token originalPrevToken = parser.previousToken;
    Token originalCurrToken = parser.currentToken;

    advance();
    while (
        parser.currentToken.type != TOKEN_CLOSE_SQUARE_BRACKET &&
        parser.currentToken.type != TOKEN_NEWLINE &&
        parser.currentToken.type != TOKEN_EOF)
    {
        // Skip through the link description section.
        advance();
    }
    // If a closing square bracket hasn't been found, then
    // it's not a link rule.
    if (parser.currentToken.type != TOKEN_CLOSE_SQUARE_BRACKET) {
        restoreParserAndTokeniser(originalPrevToken, originalCurrToken);
        return false;
    }
    advance();
    // If a opening parenthesis hasn't been found, then
    // it's not a link rule.
    if (parser.currentToken.type != TOKEN_OPEN_PARENTHESIS) {
        restoreParserAndTokeniser(originalPrevToken, originalCurrToken);
        return false;
    }
    advance();
    while (
        parser.currentToken.type != TOKEN_CLOSE_PARENTHESIS &&
        parser.currentToken.type != TOKEN_NEWLINE &&
        parser.currentToken.type != TOKEN_EOF)
    {
        // Skip through the link URL section.
        advance();
    }
    
    if (parser.currentToken.type == TOKEN_CLOSE_PARENTHESIS) {
        // Has a closing parenthesis.
        // Therefore, a link rule is valid.
        restoreParserAndTokeniser(originalPrevToken, originalCurrToken);
        return true;
    }
    restoreParserAndTokeniser(originalPrevToken, originalCurrToken);
    return false;
}

/**
 * Produce a HTML anchor hyperlink:
 * <a href=" ... "> ... </h1>
 * 
 * Markdown link and HTML anchor tag has their link URL and link description
 * positions inversed of each other.
 * This function skip through the Markdown description, grab the link URL and
 * write it to the buffer, then circle back to the description to write it to
 * the buffer.
 */
void linkRule() {
    /**
     * Initial state:
     * - currentToken is the opening TOKEN_OPEN_SQUARE_BRACKET.
     * End state:
     * - currentToken is the closing TOKEN_CLOSE_PARENTHESIS.
     */

    advance();
    Token descriptionPrevToken = parser.previousToken;
    Token descriptionCurrToken = parser.currentToken;

    writeToBuffer("<a href=\"", 9);

    // Skip through the link description section.
    while (parser.currentToken.type != TOKEN_CLOSE_SQUARE_BRACKET) {
        advance();
    }
    // 2 advance() to skip through the close square bracket and
    // open parenthesis token.
    advance();
    advance();
    while (parser.currentToken.type != TOKEN_CLOSE_PARENTHESIS) {        
        // Write link URL to buffer.
        writeTokenToBuffer(parser.currentToken);
        advance();
    }

    writeToBuffer("\">", 2);

    Token closingParenPrevToken = parser.previousToken;
    Token closingParenCurrToken = parser.currentToken;

    // Reset both tokeniser and parser back to the link
    // description section.
    restoreParserAndTokeniser(descriptionPrevToken, descriptionCurrToken);

    while (parser.currentToken.type != TOKEN_CLOSE_SQUARE_BRACKET) {
        // Write link description to buffer.
        writeTokenToBuffer(parser.currentToken);
        advance();
    }

    writeToBuffer("</a>", 4);

    // Set both tokeniser and parser to the state at the
    // end of the link rule, which is the closing parenthesis token.
    restoreParserAndTokeniser(closingParenPrevToken, closingParenCurrToken);
}

void contentRule() {
    while (parser.currentToken.type != TOKEN_NEWLINE &&
        parser.currentToken.type != TOKEN_EOF) {
            // TODO: Handle reserved special characters.

            if (parser.currentToken.type == TOKEN_GRAVE_ACCENT &&
                isInlineCodeRule()) {
                    inlineCodeRule();
                    advance();
                    continue;
            }

            if (parser.currentToken.type == TOKEN_OPEN_SQUARE_BRACKET &&
                isLinkRule()) {
                    linkRule();
                    advance();
                    continue;
            }

            writeTokenToBuffer(parser.currentToken);
            advance();
        }

    // Skip through all left over newlines after content, if any.
    while (parser.currentToken.type == TOKEN_NEWLINE) {
        advance();
    }
}

/**
 * A valid hearding rule is a heading token followed by
 * 1 or more spaces/tabs, then the content.
 */
bool isHeadingRule() {    
    if (
        !(
            parser.currentToken.type == TOKEN_H1 ||
            parser.currentToken.type == TOKEN_H2 ||
            parser.currentToken.type == TOKEN_H3 ||
            parser.currentToken.type == TOKEN_H4 ||
            parser.currentToken.type == TOKEN_H5 ||
            parser.currentToken.type == TOKEN_H6
        )) {
            // If the first token of the line isn't a 
            // heading token, then it's a not a valid
            // heading rule.
            return false;
        }

    Token originalPrevToken = parser.previousToken;
    Token originalCurrToken = parser.currentToken;

    advance();
    Token currToken = parser.currentToken;
    
    restoreParserAndTokeniser(originalPrevToken, originalCurrToken);

    // If a space or tab follows the heading token, then a
    // heading rule is valid.
    if (currToken.type == TOKEN_SPACE || 
        currToken.type == TOKEN_TAB) {
            return true;
        }
    return false;
}

/**
 * Produce a HTML heading:
 * <h1> ... </h1>
 */
void headingRule() {
    /**
     * Initial state:
     * - currentToken is a heading token.
     */

    TokenType headingType = parser.currentToken.type;
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
    
    advance();
    // Skip through all whitespace between '#' and content.
    while (parser.currentToken.type == TOKEN_SPACE ||
        parser.currentToken.type == TOKEN_TAB) {
            advance();
        }

    contentRule();

    writeToBuffer(closeHeadingStr, 6);
}

/**
 * Produce a HTML paragraph:
 * <p>
 * ...
 * </p>
 */
void paragraphRule() {
    writeToBuffer("<p>\n", 4);
    contentRule();
    writeToBuffer("\n", 1);
    writeToBuffer("</p>\n", 5);
}

/**
 * Do multiple tokens lookahead to determine whether it is
 * an image rule or not.
 * image rule format: ![...](...)
 */
bool isImageRule() {
    Token originalPrevToken = parser.previousToken;
    Token originalCurrToken = parser.currentToken;

    if (parser.currentToken.type != TOKEN_EXCLAMATION_MARK) {
        return false;
    }
    advance();
    if (parser.currentToken.type != TOKEN_OPEN_SQUARE_BRACKET) {
        restoreParserAndTokeniser(originalPrevToken, originalCurrToken);
        return false;
    }

    advance();
    while (
        parser.currentToken.type != TOKEN_CLOSE_SQUARE_BRACKET &&
        parser.currentToken.type != TOKEN_NEWLINE &&
        parser.currentToken.type != TOKEN_EOF
    ) {
        // Skip through image alt text section.
        advance();
    }
    // If a closing square bracket hasn't been found, then
    // it's not an image rule.
    if (parser.currentToken.type != TOKEN_CLOSE_SQUARE_BRACKET) {
        restoreParserAndTokeniser(originalPrevToken, originalCurrToken);
        return false;
    }
    advance();
    // If a opening parenthesis hasn't been found, then
    // it's not an image rule.
    if (parser.currentToken.type != TOKEN_OPEN_PARENTHESIS) {
        restoreParserAndTokeniser(originalPrevToken, originalCurrToken);
        return false;
    }
    advance();
    while (
        parser.currentToken.type != TOKEN_CLOSE_PARENTHESIS &&
        parser.currentToken.type != TOKEN_NEWLINE &&
        parser.currentToken.type != TOKEN_EOF
    ) {
        // Skip through the image link section.
        advance();
    }
    // If a closing parenthesis hasn't been found, then it's
    // not an image rule.
    if (parser.currentToken.type != TOKEN_CLOSE_PARENTHESIS) {
        restoreParserAndTokeniser(originalPrevToken, originalCurrToken);
        return false;
    }
    advance();
    if (
        parser.currentToken.type == TOKEN_NEWLINE ||
        parser.currentToken.type == TOKEN_EOF
    ) {
        // In the image rule, the closing parenthesis must be
        // followed by a newline or a EOF token.
        restoreParserAndTokeniser(originalPrevToken, originalCurrToken);
        return true;
    }
    restoreParserAndTokeniser(originalPrevToken, originalCurrToken);
    return false;
}

/**
 * Produce a HTML img:
 * <img src=" ... " alt=" ... ">
 * 
 * Similar to link rule, the image link and the image alt text are
 * in inversed position of each other in Markdown and HTML.
 * This function skip through the Markdown image alt text, grab the
 * image link and write it to the buffer, then circle back to the
 * alt text to write it to the buffer.
 */
void imageRule() {
    /**
     * Initial state:
     * - currentToken is TOKEN_EXCLAMATION_MARK.
     * End state:
     * - currentToken is the closing TOKEN_CLOSE_PARENTHESIS.
     */

    // 2 advance() to skip through the exclamation mark and open
    // square bracket.
    advance();
    advance();
    Token altTextPrevToken = parser.previousToken;
    Token altTextCurrToken = parser.currentToken;

    writeToBuffer("<img src=\"", 10);

    while (parser.currentToken.type != TOKEN_CLOSE_SQUARE_BRACKET) {
        advance();
    }
    // 2 advance() to skip through the close square bracket and
    // open parenthesis token.
    advance();
    advance();
    while (parser.currentToken.type != TOKEN_CLOSE_PARENTHESIS) {
        // Write image link to buffer.
        writeTokenToBuffer(parser.currentToken);
        advance();
    }

    writeToBuffer("\" alt=\"", 7);

    Token closingParenPrevToken = parser.previousToken;
    Token closingParenCurrToken = parser.currentToken;

    // Reset both tokeniser and parser back to the image
    // alt text section.
    restoreParserAndTokeniser(altTextPrevToken, altTextCurrToken);

    while (parser.currentToken.type != TOKEN_CLOSE_SQUARE_BRACKET) {
        // Write image alt text to buffer.
        writeTokenToBuffer(parser.currentToken);
        advance();
    }

    writeToBuffer("\">\n", 3);

    // Set both tokeniser and parser to the state at the end
    // of the image rule, which is the closing parenthesis token.
    restoreParserAndTokeniser(closingParenPrevToken, closingParenCurrToken);
    
    // Skip through all left over newlines after content, if any.
    advance();
    while (parser.currentToken.type == TOKEN_NEWLINE) {        
        advance();
    }
}

void sectionRule() {
    // TODO: if bullet list rule
    // TODO: if number list rule
    // TODO: if code rule
    if (isHeadingRule()) {
        headingRule();
    } else if (isImageRule()) {
        imageRule();
    } else {
        // A catch-all rule, when all other rules
        // are invalid.
        paragraphRule();
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