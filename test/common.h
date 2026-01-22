#include <stdbool.h>

#ifndef test_common_h
#define test_common_h

void assert(bool assertion);
void assertWithMsg(bool assertion, char* failMsg);

#endif