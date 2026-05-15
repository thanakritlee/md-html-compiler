#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readFile(const char* path) {
    // Read the Markdown file as a binary file into a file stream.
    // Mode: r = read, b = binary file.
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Could not open file '%s'.\n", path);
        exit(-1);
    }

    // Move the "file pointer" to the end of the file stream.
    fseek(file, 0L, SEEK_END);
    // ftell() returns how many bytes there are from the start of the file
    // to where the file pointer is (i.e. at the end of the file).
    // Therefore, the expression below will return how many bytes the whole file is.
    size_t fileSize = ftell(file);
    // Move the file pointer back to the start of the file stream.
    rewind(file);

    // Allocate a string of a size of the file (+ 1 byte).
    char* buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory to read '%s'.\n", path);
        exit(-1);
    }
    // Read the whole file in a single batch into buffer string variable.
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    if (bytesRead < fileSize) {
        fprintf(stderr, "Could not read file '%s'.\n", path);        
        free(buffer);
        fclose(file);
        exit(-1);
    }
    // Set the (+ 1 byte) of the string buffer to '\0' to indicate end of file.
    // The 'null' byte.
    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;
}

void writeFile(const char* path, const char* contentMemAddr) {
    // Open a file in writing mode
    FILE* fptr = fopen(path, "w");

    // Write buffer to file.
    fprintf(fptr, "%s", contentMemAddr);

    // Close the file
    fclose(fptr);
}
