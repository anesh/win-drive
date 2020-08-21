#ifndef HOOKING_H_
#define HOOKING_H_
#include "ntddk.h"
#include "ssdt.h"
#include "stringTools.h"

typedef NTSTATUS (*ZwQuerySystemInformationPrototype)(ULONG SystemInformationCLass,PVOID SystemInformation, ULONG SystemInformationLength, PULONG ReturnLength);

NTSYSAPI NTSTATUS NTAPI ZwQuerySystemInformation(
           		ULONG  SystemInformationClass,
            		PVOID  SystemInformation,
                        ULONG  SystemInformationLength,
                        PULONG ReturnLength
			);



NTSTATUS Hook_ZwQuerySystemInformation(
		ULONG SystemInformationClass, 
		PVOID SystemInformation, 
		ULONG SystemInformationLength, 
		PULONG ReturnLength);

int HookZwQuerySystemInformation(char* param2, char* param3);



#endif