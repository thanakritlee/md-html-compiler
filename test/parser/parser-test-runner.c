#include <stdio.h>

#include "./heading.h"
#include "./paragraph.h"
#include "./combination.h"
#include "./image.h"
#include "./code.h"
#include "./list.h"

void runParserTests() {
    printf("=================================\n");
    printf("parser tests\n");
    printf("=================================\n\n");

    runParserHeadingTests();
    runParserParagraphTests();
    runParserCombinationTests();
    runParserImageTests();
    runParserCodeTests();
    runParserListTests();

    printf("\n");
}