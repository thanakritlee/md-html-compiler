#include <stdio.h>
#include <string.h>

#include "../../source/tokeniser.h"
#include "../common.h"

void stringBasic() {
    printf("\tstring basic\n");

    char* source = "Hello\0";
    initTokeniser(source);

    Token token;
    token = getNextToken();
    
    assertWithMsg(token.type == TOKEN_STRING, "Expect TOKEN_STRING");
    assertWithMsg(token.length == 5, "Expect token length of 5");
    assertWithMsg(memcmp(token.start, "Hello", 5) == 0, "Expect token: 'Hello'");
}

void stringAlphanumberic1() {
    printf("\tstring alphanumeric 1\n");

    char* source = "Hello123\0";
    initTokeniser(source);

    Token token;
    token = getNextToken();

    assertWithMsg(token.type == TOKEN_STRING, "Expect TOKEN_STRING");
    assertWithMsg(token.length == 8, "Expect token length of 8");
    assertWithMsg(memcmp(token.start, "Hello123", 8) == 0, "Expect token: 'Hello123'");
}

void stringAlphanumberic2() {
    printf("\tstring alphanumeric 2\n");

    char* source = "123Hello\0";
    initTokeniser(source);

    Token token;
    token = getNextToken();

    assertWithMsg(token.type == TOKEN_STRING, "Expect TOKEN_STRING");
    assertWithMsg(token.length == 8, "Expect token length of 8");
    assertWithMsg(memcmp(token.start, "123Hello", 8) == 0, "Expect token: '123Hello'");
}

void stringAlphanumberic3() {
    printf("\tstring alphanumeric 3\n");

    char* source = "Hel123lo\0";
    initTokeniser(source);

    Token token;
    token = getNextToken();

    assertWithMsg(token.type == TOKEN_STRING, "Expect TOKEN_STRING");
    assertWithMsg(token.length == 8, "Expect token length of 8");
    assertWithMsg(memcmp(token.start, "Hel123lo", 8) == 0, "Expect token: 'Hel123lo'");
}

void stringSpecialChar1() {
    printf("\tstring special character 1\n");

    char* source = "Hello$^\0";
    initTokeniser(source);

    Token token;
    token = getNextToken();

    assertWithMsg(token.type == TOKEN_STRING, "Expect TOKEN_STRING");
    assertWithMsg(token.length == 7, "Expect token length of 7");
    assertWithMsg(memcmp(token.start, "Hello$^", 7) == 0, "Expect token: 'Hello$^'");
}

void stringSpecialChar2() {
    printf("\tstring special character 2\n");

    char* source = "&@Hello\0";
    initTokeniser(source);

    Token token;
    token = getNextToken();

    assertWithMsg(token.type == TOKEN_STRING, "Expect TOKEN_STRING");
    assertWithMsg(token.length == 7, "Expect token length of 7");
    assertWithMsg(memcmp(token.start, "&@Hello", 7) == 0, "Expect token: '&@Hello'");
}

/**
 * The reserved special character '-' splits the lexeme into
 * 3 tokens: STRING, MINUS, STRING, and (EOF)
 */
void stringSpecialChar3() {
    printf("\tstring special character 3\n");

    char* source = "H~el-l/o+\0";
    initTokeniser(source);

    Token token;
    token = getNextToken();

    assertWithMsg(token.type == TOKEN_STRING, "Expect TOKEN_STRING");
    assertWithMsg(token.length == 4, "Expect token length of 4");
    assertWithMsg(memcmp(token.start, "H~el", 4) == 0, "Expect token: 'H~el'");
}

void runStringTests() {
    stringBasic();
    stringAlphanumberic1();
    stringAlphanumberic2();
    stringAlphanumberic3();
    stringSpecialChar1();
    stringSpecialChar2();
    stringSpecialChar3();
}