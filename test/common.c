#include <stdio.h>
#include <stdbool.h>

void assert(bool assertion) {
    if (assertion) {
        printf("\t\tPASS\n");
    } else {
        printf("----------------FAIL\n");
    }
}

void assertWithMsg(bool assertion, char* failMsg) {
    if (assertion) {
        printf("\t\tPASS\n");
    } else {
        printf("----------------FAIL (%s)\n", failMsg);
    }
}