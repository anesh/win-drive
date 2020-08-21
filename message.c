#include "message.h"

int GetStructFromChar(char* input, MSG* msgOut)
{
	zeroMemory((void*)msgOut, sizeof(MSG));
	getParam(input, msgOut->command, 80, 0, MSG_PARAM_SPLIT_CHAR);
	getParam(input, msgOut->param1 , 80, 1, MSG_PARAM_SPLIT_CHAR);
	getParam(input, msgOut->param2 , 80, 2, MSG_PARAM_SPLIT_CHAR);
	getParam(input, msgOut->param3 , 80, 3, MSG_PARAM_SPLIT_CHAR);

	return 1;
}