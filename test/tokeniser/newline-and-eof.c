#include <stdio.h>
#include <stdbool.h>

#include "../../source/tokeniser.h"
#include "../common.h"

void newline() {
    printf("\tnewline\n");

    char* source = "\n\0";
    initTokeniser(source);

    Token token = getNextToken();
    assertWithMsg(token.type == TOKEN_NEWLINE, "Expect TOKEN_NEWLINE");
}

void newlines() {
    printf("\tnewlines\n");

    char* source = "\n\n\0";
    initTokeniser(source);

    Token token = getNextToken();
    assertWithMsg(token.type == TOKEN_NEWLINE, "Expect first TOKEN_NEWLINE");
    token = getNextToken();
    assertWithMsg(token.type == TOKEN_NEWLINE, "Expect second TOKEN_NEWLINE");
}

void eof() {
    printf("\teof\n");

    char* source = "\0";
    initTokeniser(source);

    Token token = getNextToken();
    assertWithMsg(token.type == TOKEN_EOF, "Expect TOKEN_EOF");
}

void runNewlineAndEOFTests() {
    newline();
    newlines();
    eof();
}