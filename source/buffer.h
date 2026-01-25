#ifndef buffer_h
#define buffer_h

typedef struct {
    char* mem;          // Buffer memory address.
    int capacity;       // Capacity of the buffer.
                        // Use for determining when to expand
                        // the buffer.
    int length;         // Occupied space in the buffer.
} Buffer;

// Initialise the buffer.
void initBuffer();
/**
 * Free the buffer memory and set capacity and length to 0.
 */
void destroyBuffer();
// Return the buffer.
Buffer getBuffer();
// Write a string to buffer.
void writeToBuffer(const char* mem, int length);

#endif