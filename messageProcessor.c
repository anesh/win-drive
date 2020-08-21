#include "messageProcessor.h"

int processMessage(char* msg)
{
	MSG msgBuffer;
	GetStructFromChar(msg, &msgBuffer);
   
	if(strIsEqual(msgBuffer.command, "hook.ssdt.ss"))
		if(strIsEqual(msgBuffer.param1, "ZwQuerySystemInformation"))
			HookZwQuerySystemInformation(msgBuffer.param2, msgBuffer.param3);
		else
			DbgPrint("Driver does not know how to hook this method.");
    		else
			DbgPrint("Unknow command requested from console");

	return 1;
}