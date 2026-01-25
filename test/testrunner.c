#include "tokeniser/tokeniser-test-runner.h"
#include "parser/parser-test-runner.h"
#include "buffer/buffer-test-runner.h"

int main () {
    runTokeniserTests();
    runParserTests();
    runBufferTests();
    return 0;
}