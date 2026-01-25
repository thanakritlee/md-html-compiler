#include <stdio.h>
#include <string.h>

#include "../../source/buffer.h"
#include "../common.h"

void testInitBuffer() {
    printf("\tinit buffer\n");

    initBuffer();
    Buffer buffer = getBuffer();

    assertWithMsg(buffer.length == 0, "Expect buffer to have length of 0");
    assertWithMsg(buffer.capacity == 8, "Expect buffer to have initial capacity of 8");

    destroyBuffer();
}

void testDestroyBuffer() {
    printf("\tdestroy buffer\n");

    initBuffer();
    destroyBuffer();
    Buffer buffer = getBuffer();

    assertWithMsg(buffer.length == 0, "Expect buffer to have length of 0");
    assertWithMsg(buffer.capacity == 0, "Expect buffer to have 0 capacity");
}

void testWriteToBuffer() {
    printf("\twrite to buffer\n");

    initBuffer();

    writeToBuffer("Hello, world!", 13);

    Buffer buffer = getBuffer();

    assertWithMsg(buffer.length == 13, "Expect buffer length of 13");
    assertWithMsg(memcmp(buffer.mem, "Hello, world!", 13) == 0, 
        "Expect buffer to contain 'Hello, world!'");

    destroyBuffer();
}

void testWriteToBufferLengthControl() {
    printf("\twrite to buffer length control\n");

    initBuffer();

    writeToBuffer("Hello, world!", 5);

    Buffer buffer = getBuffer();

    assertWithMsg(buffer.length == 5, "Expect buffer length of 5");
    assertWithMsg(memcmp(buffer.mem, "Hello", 5) == 0, 
        "Expect buffer to contain 'Hello'");
    assertWithMsg(memcmp(&buffer.mem[5], ", world!", 8) != 0, 
        "Expect buffer to not contain anything else after the first 5 bytes");

    destroyBuffer();
}

void runAllBufferTests() {
    testInitBuffer();
    testDestroyBuffer();
    testWriteToBuffer();
    testWriteToBufferLengthControl();
}