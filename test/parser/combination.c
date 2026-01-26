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

void runParserCombinationTests() {
    combination1();
}