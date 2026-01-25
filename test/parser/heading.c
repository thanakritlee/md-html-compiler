#include <stdio.h>
#include <string.h>

#include "../../source/tokeniser.h"
#include "../../source/buffer.h"
#include "../../source/parser.h"
#include "../common.h"

void heading1() {
    printf("\theading %d\n", 1);

    char* source = "# Title\0";
    initTokeniser(source);
    initBuffer();

    parse();

    Buffer buffer = getBuffer();
    char expectedBuffer[] = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<h1>Title</h1>\n"
    "</html>\0";
    
    assertWithMsg(buffer.length == strlen(expectedBuffer), 
    "Unexpected buffer length");
    assertWithMsg(
        memcmp(buffer.mem, expectedBuffer, 
            strlen(expectedBuffer)) == 0, 
        "Unexpected buffer content");

    destroyBuffer();
}

void heading2() {
    printf("\theading %d\n", 2);

    char* source = "# This is my 2nd title 123\0";
    initTokeniser(source);
    initBuffer();

    parse();

    Buffer buffer = getBuffer();
    char expectedBuffer[] = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<h1>This is my 2nd title 123</h1>\n"
    "</html>\0";
    
    assertWithMsg(buffer.length == strlen(expectedBuffer), 
    "Unexpected buffer length");
    assertWithMsg(
        memcmp(buffer.mem, expectedBuffer, 
            strlen(expectedBuffer)) == 0, 
        "Unexpected buffer content");

    destroyBuffer();
}

void runParserHeadingTests() {
    heading1();
    heading2();
}