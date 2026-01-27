#include <stdio.h>
#include <string.h>

#include "../../source/tokeniser.h"
#include "../../source/buffer.h"
#include "../../source/parser.h"
#include "../common.h"

void bulletList() {
    printf("\tbullet list\n");

    char* source =
    "- First item\n"
    "- Second item\n"
    "- Third item\n"
    "-Not an item\n\0";
    initTokeniser(source);
    initBuffer();

    parse();

    Buffer buffer = getBuffer();
    char expectedBuffer[] = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<ul>\n"
    "<li>First item</li>\n"
    "<li>Second item</li>\n"
    "<li>Third item</li>\n"
    "</ul>\n"
    "<p>\n"
    "-Not an item\n"
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

void numberList() {
    printf("\tnumber list\n");

    char* source =
    "1. First item\n"
    "2. Second item\n"
    "3. Third item\n"
    "4.Not an item\n\0";
    initTokeniser(source);
    initBuffer();

    parse();

    Buffer buffer = getBuffer();
    char expectedBuffer[] = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<ol type=\"1\">\n"
    "<li>First item</li>\n"
    "<li>Second item</li>\n"
    "<li>Third item</li>\n"
    "</ol>\n"
    "<p>\n"
    "4.Not an item\n"
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

void bulletAndNumberList() {
    printf("\tbullet and number list\n");

    char* source =
    "- First item\n"
    "- Second item\n"
    "1. First item\n"
    "2. Second item\n"
    "3. Third item\n\0";
    initTokeniser(source);
    initBuffer();

    parse();

    Buffer buffer = getBuffer();
    char expectedBuffer[] = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<ul>\n"
    "<li>First item</li>\n"
    "<li>Second item</li>\n"
    "</ul>\n"
    "<ol type=\"1\">\n"
    "<li>First item</li>\n"
    "<li>Second item</li>\n"
    "<li>Third item</li>\n"
    "</ol>\n"
    "</html>\0";
    
    assertWithMsg(buffer.length == strlen(expectedBuffer), 
    "Unexpected buffer length");
    assertWithMsg(
        memcmp(buffer.mem, expectedBuffer, 
            strlen(expectedBuffer)) == 0, 
        "Unexpected buffer content");

    destroyBuffer();
}

void runParserListTests() {
    bulletList();
    numberList();
    bulletAndNumberList();
}