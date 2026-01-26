#include <stdio.h>

#include "./heading.h"
#include "./paragraph.h"
#include "./combination.h"

void runParserTests() {
    printf("=================================\n");
    printf("parser tests\n");
    printf("=================================\n\n");

    runParserHeadingTests();
    runParserParagraphTests();
    runParserCombinationTests();

    printf("\n");
}