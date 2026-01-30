#include <string.h>
#include <stdlib.h>

#include "./buffer.h"

Buffer buffer;

void initBuffer() {
    buffer.capacity = 8;
    buffer.mem = (char*)malloc(8 * sizeof(char));
    buffer.length = 0;
}

void destroyBuffer() {
    free(buffer.mem);
    buffer.capacity = 0;
    buffer.length = 0;
}

Buffer getBuffer() {
    return buffer;
}

void expandBuffer() {
    // Increase the buffer capacity by multiplication of 2 each time it is expaned.
    int newCapacity = buffer.capacity << 1;
    char* result = (char*)realloc(buffer.mem , newCapacity * sizeof(char));
    // If C is unable to allocate anymore memory space,
    // then free the buffer memory and exit the program.
    if (result == NULL) {
        free(buffer.mem);
        exit(1);
    }
    
    buffer.mem = result;
    buffer.capacity = newCapacity;
}

void writeToBuffer(const char* mem, int length) {
    // If the buffer is already at max capacity,
    // then expand the buffer memory space.
    if (buffer.length + length > buffer.capacity) {
        expandBuffer();
    }

    for (int i = 0; i < length; i++) {
        buffer.mem[buffer.length] = mem[i];
        buffer.length++;        
    }
}