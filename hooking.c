#include "hooking.h"

ZwQuerySystemInformationPrototype origSysInfo = 0;


int HookZwQuerySystemInformation(char* param2, char* param3)
{

	if(strIsEqual(param2, "set"))
	{
		if(!origSysInfo)
		{
			DbgPrint("Performing hook on ZwQuerySystemInformation.");
			(unsigned long)origSysInfo = ssdt_writeService((unsigned long)ZwQuerySystemInformation, (long)Hook_ZwQuerySystemInformation);
		}
		else
		{
			DbgPrint("Hook has already been applied.");
		}		
	}
	else
	{
		if(origSysInfo)
		{
			DbgPrint("Removing hook on ZwQuerySystemInformation.");
			ssdt_writeService((unsigned long)ZwQuerySystemInformation, (long)origSysInfo);

			origSysInfo = 0;
		}
		else
		{
			DbgPrint("No current hook has been applied.");
		}
	}

	return 1;
}



NTSTATUS Hook_ZwQuerySystemInformation(
		ULONG SystemInformationClass, 
		PVOID SystemInformation, 
		ULONG SystemInformationLength, 
		PULONG ReturnLength)
{
	DbgPrint("ZwQuerySystemInformation hook called. Redirecting to orignal method.");
	return origSysInfo(SystemInformationClass, SystemInformation, SystemInformationLength, ReturnLength);
}