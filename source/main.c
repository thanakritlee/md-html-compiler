#include <stdio.h>
#include <stdlib.h>

#include "fileio.h"
#include "buffer.h"
#include "tokeniser.h"
#include "parser.h"

void compile(const char* markdownPath, const char* htmlPath) {
    char* source = readFile(markdownPath);
    
    initTokeniser(source);
    initBuffer();
    parse();
    
    Buffer outputBuffer = getBuffer();
    writeFile(htmlPath, outputBuffer.mem);
    
    destroyBuffer();
}

int main(int argc, const char* argv[]) {
    if (argc == 3) {
        compile(argv[1], argv[2]);
    } else {
        fprintf(stderr, "Usage: compiler [Markkdown file path] [HTML file path]\n");
        exit(-1);
    }

    return 0;
}