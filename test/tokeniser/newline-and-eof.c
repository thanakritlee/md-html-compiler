#include <stdio.h>
#include <stdbool.h>

#include "../../source/tokeniser.h"
#include "../common.h"

void newline() {
    printf("\tnewline\n");

    char* source = "\n\0";
    initTokeniser(source);

    Token token;
    token = getNextToken();
    assert(token.type == TOKEN_NEWLINE);
}

void newlines() {
    printf("\tnewlines\n");

    char* source = "\n\n\0";
    initTokeniser(source);

    Token firstToken = getNextToken();
    Token secondToken = getNextToken();
    assert(
        firstToken.type == TOKEN_NEWLINE && 
        secondToken.type == TOKEN_NEWLINE);
}

void eof() {
    printf("\teof\n");

    char* source = "\0";
    initTokeniser(source);

    Token token = getNextToken();
    assert(token.type == TOKEN_EOF);
}

void runNewlineAndEOFTests() {
    newline();
    newlines();
    eof();
}