#include <stdio.h>

#include "../../source/tokeniser.h"
#include "./heading.h"
#include "./space-and-tab.h"
#include "./newline-and-eof.h"
#include "./string.h"
#include "./number.h"

void run_tokeniser_tests() {
    printf("=================================\n");
    printf("tokeniser tests\n");
    printf("=================================\n\n");

    runHeadingTests();
    runSpaceAndTabTests();
    runNewlineAndEOFTests();
    runStringTests();
    runNumberTests();

    printf("\n");
}