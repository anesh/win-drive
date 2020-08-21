#ifndef SSDT_H_
#define SSDT_H_
#include "ntddk.h"

#define SYSCALL_INDEX(_Function) *(PULONG)((PUCHAR)_Function+1)

typedef struct SystemServiceDescriptorTable {
        void*                 ServiceTableBase;
        void*                 ServiceCounterTableBase;
        unsigned int          NumberOfServices;
        unsigned char*        ParamTableBase;
} SSDT,*PSYSTEM_SERVICE_TABLE;

extern PSYSTEM_SERVICE_TABLE KeServiceDescriptorTable;





int ssdt_init();
int ssdt_deinit();

unsigned long ssdt_writeService(unsigned long sysServiceFunction, unsigned long hookAddr);
#endif