#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "stringTools.h"
#include "memory.h"

#define MSG_PARAM_SPLIT_CHAR '\\'

typedef struct Msg MSG;

struct Msg
{
	char command[80];
	char param1[80];
	char param2[80];
	char param3[80];
}Msg;

int GetStructFromChar(char* input, MSG* msgOut);

#endif