#include <stdio.h>
#include <string.h>

#include "../../source/tokeniser.h"
#include "../../source/buffer.h"
#include "../../source/parser.h"
#include "../common.h"


void paragraph1() {
    printf("\tparagraph %d\n", 1);

    char* source = "This is a simple basic paragraph.\0";
    initTokeniser(source);
    initBuffer();

    parse();

    Buffer buffer = getBuffer();
    char expectedBuffer[] = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<p>\n"
    "This is a simple basic paragraph.\n"
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

void multipleParagraphs() {
    printf("\tmultiple paragraphs\n");

    char* source = 
    "This is the first paragraph.\n"
    "This is the second paragraph.\n\n"
    "This is the third paragraph.\n\0";
    initTokeniser(source);
    initBuffer();

    parse();

    Buffer buffer = getBuffer();
    char expectedBuffer[] = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<p>\n"
    "This is the first paragraph.\n"
    "</p>\n"
    "<p>\n"
    "This is the second paragraph.\n"
    "</p>\n"
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

void paragraphsWithLinkAndInlineCode() {
    printf("\tparagraphs with link and inline code\n");

    char* source = 
    "Here's some code: `mov ah, 1Bh`\n"
    "And this is a link to [my site](www.site.com)\n\n"
    "In conclusion, this is pretty neat.\n\0";
    initTokeniser(source);
    initBuffer();

    parse();

    Buffer buffer = getBuffer();
    char expectedBuffer[] = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<p>\n"
    "Here's some code: <code>mov ah, 1Bh</code>\n"
    "</p>\n"
    "<p>\n"
    "And this is a link to <a href=\"www.site.com\">my site</a>\n"
    "</p>\n"
    "<p>\n"
    "In conclusion, this is pretty neat.\n"
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

void runParserParagraphTests() {
    paragraph1();
    multipleParagraphs();
    paragraphsWithLinkAndInlineCode();
}