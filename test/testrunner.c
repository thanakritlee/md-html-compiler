#include "../source/tokeniser.h"
#include "stdio.h"

int main () {
    int ret;
    ret = scanToken(12);
    if (ret == 12) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }

    return 0;
}