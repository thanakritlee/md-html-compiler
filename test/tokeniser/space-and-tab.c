#include <stdio.h>

#include "../../source/tokeniser.h"
#include "../common.h"

void space() {
    printf("\tspace\n");

    char* source = " \0";
    initTokeniser(source);

    Token token = getNextToken();

    assertWithMsg(token.type == TOKEN_SPACE, "Expect TOKEN_SPACE");
}

void tab() {
    printf("\ttab\n");

    char* source = "\t\0";
    initTokeniser(source);

    Token token = getNextToken();

    assertWithMsg(token.type == TOKEN_TAB, "Expect TOKEN_TAB");
}

void runSpaceAndTabTests() {
    space();
    tab();
}