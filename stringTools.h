#ifndef STRINGTOOLS_H_
#define STRINGTOOLS_H_

#include "memory.h"

         int forceNullTermination(char* string, unsigned int len);

         int getParam(char* source, char* out, unsigned int outSize, unsigned int param, char clipChar);
unsigned int getStrLen(char* str, int includeTerminator, unsigned int maxLen);
         int strIsEqual(char* source, char* source2);

#endif