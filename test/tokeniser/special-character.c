#include <stdio.h>
#include <string.h>

#include "../../source/tokeniser.h"
#include "../common.h"


void lessThanToken() {
    printf("\tless than token '<'\n");

    char* source = "<\0";
    initTokeniser(source);

    Token token = getNextToken();

    assertWithMsg(token.type == TOKEN_LESS_THAN, "Expect TOKEN_LESS_THAN");
    assertWithMsg(token.length == 1, "Expect token length of 1");
}

void greaterThanToken() {
    printf("\tgreater than token '>'\n");

    char* source = ">\0";
    initTokeniser(source);

    Token token = getNextToken();

    assertWithMsg(token.type == TOKEN_GREATER_THAN, "Expect TOKEN_GREATER_THAN");
    assertWithMsg(token.length == 1, "Expect token length of 1");
}

void graveAccentToken() {
    printf("\tgrave accent token (`)\n");

    char* source = "`\0";
    initTokeniser(source);

    Token token = getNextToken();

    assertWithMsg(token.type == TOKEN_GRAVE_ACCENT, "Expect TOKEN_GRAVE_ACCENT");
    assertWithMsg(token.length == 1, "Expect token length of 1");
}

void openSquareBracket() {
    printf("\topen square bracket token '['\n");

    char* source = "[\0";
    initTokeniser(source);

    Token token = getNextToken();
    
    assertWithMsg(token.type == TOKEN_OPEN_SQUARE_BRACKET, "Expect TOKEN_OPEN_SQUARE_BRACKET");
    assertWithMsg(token.length == 1, "Expect token length of 1");
    assertWithMsg(memcmp(token.start, "[", 1) == 0, "Expect token: '['");
}

void closeSquareBracket() {
    printf("\tclose square bracket token ']'\n");

    char* source = "]\0";
    initTokeniser(source);

    Token token = getNextToken();
    
    assertWithMsg(token.type == TOKEN_CLOSE_SQUARE_BRACKET, "Expect TOKEN_CLOSE_SQUARE_BRACKET");
    assertWithMsg(token.length == 1, "Expect token length of 1");
    assertWithMsg(memcmp(token.start, "]", 1) == 0, "Expect token: ']'");
}

void openParenthesis() {
    printf("\topen parenthesis token '('\n");

    char* source = "(\0";
    initTokeniser(source);

    Token token = getNextToken();
    
    assertWithMsg(token.type == TOKEN_OPEN_PARENTHESIS, "Expect TOKEN_OPEN_PARENTHESIS");
    assertWithMsg(token.length == 1, "Expect token length of 1");
    assertWithMsg(memcmp(token.start, "(", 1) == 0, "Expect token: '('");
}

void closeParenthesis() {
    printf("\tclose parenthesis token ')'\n");

    char* source = ")\0";
    initTokeniser(source);

    Token token = getNextToken();
    
    assertWithMsg(token.type == TOKEN_CLOSE_PARENTHESIS, "Expect TOKEN_CLOSE_PARENTHESIS");
    assertWithMsg(token.length == 1, "Expect token length of 1");
    assertWithMsg(memcmp(token.start, ")", 1) == 0, "Expect token: ')'");
}

void period() {
    printf("\tperiod token '.'\n");

    char* source = ".\0";
    initTokeniser(source);

    Token token = getNextToken();
    
    assertWithMsg(token.type == TOKEN_PERIOD, "Expect TOKEN_PERIOD");
    assertWithMsg(token.length == 1, "Expect token length of 1");
    assertWithMsg(memcmp(token.start, ".", 1) == 0, "Expect token: '.'");
}

void runSpecialCharacterTests() {
    lessThanToken();
    greaterThanToken();
    graveAccentToken();
    openSquareBracket();
    closeSquareBracket();
    openParenthesis();
    closeParenthesis();
    period();
}