#include <stdio.h>
#include <string.h>

#include "../../source/tokeniser.h"
#include "../common.h"

void numberBasic1() {
    printf("\tnumber basic 1\n");

    char* source = "123\0";
    initTokeniser(source);

    Token token = getNextToken();

    assertWithMsg(token.type == TOKEN_NUMBER, "Expect TOKEN_NUMBER");
    assertWithMsg(token.length == 3, "Expect token length of 3");
    assertWithMsg(memcmp(token.start, "123", 3) == 0, "Expect token: '123'");
}

void numberBasic2() {
    printf("\tnumber basic 2\n");

    char* source = "1234567890\0";
    initTokeniser(source);

    Token token = getNextToken();

    assertWithMsg(token.type == TOKEN_NUMBER, "Expect TOKEN_NUMBER");
    assertWithMsg(token.length == 10, "Expect token length of 10");
    assertWithMsg(memcmp(token.start, "1234567890", 10) == 0, "Expect token: '1234567890'");
}

void numberBasic3() {
    printf("\tnumber basic 3\n");

    char* source = "0\0";
    initTokeniser(source);

    Token token = getNextToken();

    assertWithMsg(token.type == TOKEN_NUMBER, "Expect TOKEN_NUMBER");
    assertWithMsg(token.length == 1, "Expect token length of 1");
    assertWithMsg(memcmp(token.start, "0", 1) == 0, "Expect token: '0'");
}

void numberDot() {
    printf("\tnumber dot\n");

    char* source = "12345.67890\0";
    initTokeniser(source);

    Token token = getNextToken();

    assertWithMsg(token.type == TOKEN_NUMBER, "Expect TOKEN_NUMBER");
    assertWithMsg(token.length == 5, "Expect token length of 5");
    assertWithMsg(memcmp(token.start, "12345", 5) == 0, "Expect token: '12345'");
}

void runNumberTests() {
    numberBasic1();
    numberBasic2();
    numberBasic3();
    numberDot();
}