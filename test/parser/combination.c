#include <stdio.h>
#include <string.h>

#include "../../source/tokeniser.h"
#include "../../source/buffer.h"
#include "../../source/parser.h"
#include "../common.h"

void combination1() {
    printf("\tcombination 1\n");

    char* source = 
    "# Some Title\n\n"
    "## Subject 1\n"
    "This is the first paragraph.\n\n"
    "## Subject 2\n"
    "This is the second paragraph.\n\n"
    "## Subject 3\n"
    "This is the third paragraph.\0";
    initTokeniser(source);
    initBuffer();

    parse();

    Buffer buffer = getBuffer();
    char expectedBuffer[] = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<h1>Some Title</h1>\n"
    "<h2>Subject 1</h2>\n"
    "<p>\n"
    "This is the first paragraph.\n"
    "</p>\n"
    "<h2>Subject 2</h2>\n"
    "<p>\n"
    "This is the second paragraph.\n"
    "</p>\n"
    "<h2>Subject 3</h2>\n"
    "<p>\n"
    "This is the third paragraph.\n"
    "</p>\n"
    "</html>\0";
    
    assertWithMsg(buffer.length == strlen(expectedBuffer), 
    "Unexpected buffer length");
    assertWithMsg(
        memcmp(buffer.mem, expectedBuffer, 
            strlen(expectedBuffer)) == 0, 
        "Unexpected buffer content");

    destroyBuffer();
}

void combination2() {
    printf("\tcombination 2\n");

    char* source = 
    "# Some Title\n\n"
    "## Subject 1\n"
    "This is the first paragraph.\n\n"
    "![Binary Tree](/image/binary-tree.png)\0";
    initTokeniser(source);
    initBuffer();

    parse();

    Buffer buffer = getBuffer();
    char expectedBuffer[] = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<h1>Some Title</h1>\n"
    "<h2>Subject 1</h2>\n"
    "<p>\n"
    "This is the first paragraph.\n"
    "</p>\n"
    "<img src=\"/image/binary-tree.png\" alt=\"Binary Tree\">\n"
    "</html>\0";

    assertWithMsg(buffer.length == strlen(expectedBuffer), 
    "Unexpected buffer length");
    assertWithMsg(
        memcmp(buffer.mem, expectedBuffer, 
            strlen(expectedBuffer)) == 0, 
        "Unexpected buffer content");

    destroyBuffer();
}

void combinationSpecialCharacters() {
    printf("\tcombination special characters\n");

    char* source = 
    "# Some Brackets: ( { [ ] } )\n"
    "## Some Dots: , . !\n"
    "Some reserved HTML characters: < >\n\n"
    "Some more special characters? + - * / # $ @ &\n\0";
    initTokeniser(source);
    initBuffer();

    parse();

    Buffer buffer = getBuffer();
    char expectedBuffer[] = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<h1>Some Brackets: ( { [ ] } )</h1>\n"
    "<h2>Some Dots: , . !</h2>\n"
    "<p>\n"
    "Some reserved HTML characters: &lt &gt\n"
    "</p>\n"
    "<p>\n"
    "Some more special characters? + - * / # $ @ &\n"
    "</p>\n"
    "</html>\0";
    
    assertWithMsg(buffer.length == strlen(expectedBuffer), 
    "Unexpected buffer length");
    assertWithMsg(
        memcmp(buffer.mem, expectedBuffer, 
            strlen(expectedBuffer)) == 0, 
        "Unexpected buffer content");

    destroyBuffer();
}

void combinationAll() {
    printf("\tcombination all\n");

    char* source = 
    "# Some Title\n\n"
    "## Subject 1\n"
    "This is the first paragraph.\n\n"
    "![Binary Tree](/image/binary-tree.png)\n\n"
    "## Some `mov` code example\n"
    "This is some x64 assembly code:\n"
    "```\n"
    "call ClearBuffer\n"
    "mov bl, [user_char_x_pos]\n"
    "mov al, [user_char_y_pos]\n"
    "mov cl, CHAR_AT\n"
    "call ModifyBuffer\n"
    "```\n"
    "# Contact at [site](www.site.com)\n"
    "For more detail, have a look at my site: [site](www.site.com)\0";
    initTokeniser(source);
    initBuffer();

    parse();

    Buffer buffer = getBuffer();
    char expectedBuffer[] = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<h1>Some Title</h1>\n"
    "<h2>Subject 1</h2>\n"
    "<p>\n"
    "This is the first paragraph.\n"
    "</p>\n"
    "<img src=\"/image/binary-tree.png\" alt=\"Binary Tree\">\n"
    "<h2>Some <code>mov</code> code example</h2>\n"
    "<p>\n"
    "This is some x64 assembly code:\n"
    "</p>\n"
    "<pre>\n"
    "call ClearBuffer\n"
    "mov bl, [user_char_x_pos]\n"
    "mov al, [user_char_y_pos]\n"
    "mov cl, CHAR_AT\n"
    "call ModifyBuffer\n"
    "</pre>\n"
    "<h1>Contact at <a href=\"www.site.com\">site</a></h1>\n"
    "<p>\n"
    "For more detail, have a look at my site: <a href=\"www.site.com\">site</a>\n"
    "</p>\n"
    "</html>\0";

    assertWithMsg(buffer.length == strlen(expectedBuffer), 
    "Unexpected buffer length");
    assertWithMsg(
        memcmp(buffer.mem, expectedBuffer, 
            strlen(expectedBuffer)) == 0, 
        "Unexpected buffer content");

    destroyBuffer();
}

void runParserCombinationTests() {
    combination1();
    combination2();
    combinationSpecialCharacters();
    combinationAll();
}