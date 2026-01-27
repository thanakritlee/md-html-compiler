#include <stdio.h>
#include <string.h>

#include "../../source/tokeniser.h"
#include "../../source/buffer.h"
#include "../../source/parser.h"
#include "../common.h"

void codeAssembly() {
    printf("\tcode assembly\n");

    char* source =
    "```\n"
    "call ClearBuffer\n"
    "mov bl, [user_char_x_pos]\n"
    "mov al, [user_char_y_pos]\n"
    "mov cl, CHAR_AT\n"
    "call ModifyBuffer\n"
    "```\n\0";
    initTokeniser(source);
    initBuffer();

    parse();

    Buffer buffer = getBuffer();
    char expectedBuffer[] = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<pre>\n"
    "call ClearBuffer\n"
    "mov bl, [user_char_x_pos]\n"
    "mov al, [user_char_y_pos]\n"
    "mov cl, CHAR_AT\n"
    "call ModifyBuffer\n"
    "</pre>\n"
    "</html>\0";
    
    assertWithMsg(buffer.length == strlen(expectedBuffer), 
    "Unexpected buffer length");
    assertWithMsg(
        memcmp(buffer.mem, expectedBuffer, 
            strlen(expectedBuffer)) == 0, 
        "Unexpected buffer content");

    destroyBuffer();
}

void codeC() {
    printf("\tcode c\n");

    char* source =
    "```\n"
    "// Print the resulting hexadecimal.\n"
    "for (int i = 0; i < hexadecimalColumn + 1; i++) {\n"
    "    printf(\"\%c\", hexadecimal[i]);\n"
    "}\n"
    "printf(\"\n\")\n"
    "```\n\0";
    initTokeniser(source);
    initBuffer();

    parse();

    Buffer buffer = getBuffer();
    char expectedBuffer[] = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<pre>\n"
    "// Print the resulting hexadecimal.\n"
    "for (int i = 0; i &lt hexadecimalColumn + 1; i++) {\n"
    "    printf(\"\%c\", hexadecimal[i]);\n"
    "}\n"
    "printf(\"\n\")\n"
    "</pre>\n"
    "</html>\0";
    
    assertWithMsg(buffer.length == strlen(expectedBuffer), 
    "Unexpected buffer length");
    assertWithMsg(
        memcmp(buffer.mem, expectedBuffer, 
            strlen(expectedBuffer)) == 0, 
        "Unexpected buffer content");

    destroyBuffer();
}

void codeJave() {
    printf("\tcode java\n");

    char* source =
    "```\n"
    "public class Main {\n"
    "   public static void main(String[] args) {\n"
    "       System.out.println(\"Hello, world!\");\n"
    "   }\n"
    "}\n"
    "```\n\0";
    initTokeniser(source);
    initBuffer();

    parse();

    Buffer buffer = getBuffer();
    char expectedBuffer[] = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<pre>\n"
    "public class Main {\n"
    "   public static void main(String[] args) {\n"
    "       System.out.println(\"Hello, world!\");\n"
    "   }\n"
    "}\n"
    "</pre>\n"
    "</html>\0";
    
    assertWithMsg(buffer.length == strlen(expectedBuffer), 
    "Unexpected buffer length");
    assertWithMsg(
        memcmp(buffer.mem, expectedBuffer, 
            strlen(expectedBuffer)) == 0, 
        "Unexpected buffer content");

    destroyBuffer();
}

void runParserCodeTests() {
    codeAssembly();
    codeC();
    codeJave();
}