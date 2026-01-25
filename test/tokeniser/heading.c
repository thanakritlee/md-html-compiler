#include <stdio.h>

#include "../../source/tokeniser.h"
#include "../common.h"

void heading_1() {
    printf("\theading %d\n", 1);

    char* source = "# Title\0";
    initTokeniser(source);

    Token token = getNextToken();

    assertWithMsg(token.type == TOKEN_H1, "Expect TOKEN_H1");
}

void heading_2() {
    printf("\theading %d\n", 2);

    char* source = "## Title\0";
    initTokeniser(source);

    Token token = getNextToken();

    assertWithMsg(token.type == TOKEN_H2, "Expect TOKEN_H2");
}

void heading_3() {
    printf("\theading %d\n", 3);

    char* source = "### Title\0";
    initTokeniser(source);

    Token token = getNextToken();

    assertWithMsg(token.type == TOKEN_H3, "Expect TOKEN_H3");
}

void heading_4() {
    printf("\theading %d\n", 4);

    char* source = "#### Title\0";
    initTokeniser(source);

    Token token = getNextToken();

    assertWithMsg(token.type == TOKEN_H4, "Expect TOKEN_H4");
}

void heading_5() {
    printf("\theading %d\n", 5);

    char* source = "##### Title\0";
    initTokeniser(source);

    Token token = getNextToken();

    assertWithMsg(token.type == TOKEN_H5, "Expect TOKEN_H5");
}

void heading_6() {
    printf("\theading %d\n", 6);

    char* source = "###### Title\0";
    initTokeniser(source);
    
    Token token = getNextToken();

    assertWithMsg(token.type == TOKEN_H6, "Expect TOKEN_H6");
}

void heading_default() {
    printf("\theading default\n");

    char* source = "########## Title\0";
    initTokeniser(source);

    Token token = getNextToken();

    assertWithMsg(token.type == TOKEN_H6, "Expect TOKEN_H6");
}

void heading_concat_string() {
    printf("\theading concat string\n");

    char* source = "#Title\0";
    initTokeniser(source);

    Token token = getNextToken();
    assertWithMsg(token.type == TOKEN_H1, "Expect TOKEN_H1");
    token = getNextToken();
    assertWithMsg(token.type == TOKEN_STRING, "Expect TOKEN_STRING");
}

void runHeadingTests() {
    heading_1();
    heading_2();
    heading_3();
    heading_4();
    heading_5();
    heading_6();
    heading_default();
    heading_concat_string();
}