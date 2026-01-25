#include <stdio.h>

#include "./heading.h"
#include "./space-and-tab.h"
#include "./newline-and-eof.h"
#include "./string.h"
#include "./number.h"
#include "./special-character.h"

void runTokeniserTests() {
    printf("=================================\n");
    printf("tokeniser tests\n");
    printf("=================================\n\n");

    runHeadingTests();
    runSpaceAndTabTests();
    runNewlineAndEOFTests();
    runStringTests();
    runNumberTests();
    runSpecialCharacterTests();

    printf("\n");
}