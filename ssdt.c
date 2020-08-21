#include "ssdt.h"


unsigned long* g_pMappedSCT;
MDL*  g_pMdlSCT;

int g_iInitStatus;


ULONGLONG GetKeSeviceDescriptorTable64()
{
    /*
                 The idea is to read the value of 0xC0000082, which is the address of the KiSystemCall64 function, and then search through the signature.
                 The ssdt signature is 0x4c8d15 and then the offset of the address value of ssdt, and then through the formula:
                 Real address = current address + current instruction length + offset Get ssdt address
                 Looking for a shadow ssdt address is similar

    */
    PUCHAR startSearchAddress = (PUCHAR)__readmsr(0xC0000082);
    PUCHAR endSearchAddress = startSearchAddress + 0x500;
    PUCHAR i = 0;
    UCHAR b1 = 0, b2 = 0, b3 = 0;
    ULONG temp = 0;
    ULONGLONG addr = 0;
    for (i = startSearchAddress; i < endSearchAddress; i++)
    {
        if (MmIsAddressValid(i) && MmIsAddressValid(i + 1) && MmIsAddressValid(i + 2))
        {
            b1 = *i;
            b2 = *(i + 1);
            b3 = *(i + 2);
            if (b1 == 0x4c && b2 == 0x8d && b3 == 0x15)
            {
                memcpy(&temp, i + 3, 4);
                addr = (ULONGLONG)temp + (ULONGLONG)i + 7;//Plus instruction length
                KdPrint(("find ssdt is %p\n", addr));
                return addr;
            }
        }
    }
    KdPrint(("find ssdt error\n"));
    return 0;
}

//__declspec(dllimport) SSDT KeServiceDescriptorTable;
//SSDT KeServiceDescriptorTable;



/*int getNumberOfServices()
{
	return KeServiceDescriptorTable.NumberOfServices;
}*/
PSYSTEM_SERVICE_TABLE KeServiceDescriptorTable = NULL;

int ssdt_init()
{
    KeServiceDescriptorTable = (PSYSTEM_SERVICE_TABLE)GetKeSeviceDescriptorTable64();
	g_pMdlSCT = MmCreateMdl(0,KeServiceDescriptorTable->ServiceTableBase, 
					KeServiceDescriptorTable->NumberOfServices * 4);

	if(!g_pMdlSCT)
	{
		g_iInitStatus = -1;
		return -1;
	}

	MmBuildMdlForNonPagedPool(g_pMdlSCT);

	g_pMdlSCT->MdlFlags |= MDL_MAPPED_TO_SYSTEM_VA;

	g_pMappedSCT = MmMapLockedPages(g_pMdlSCT, KernelMode);

	g_iInitStatus = 1;

	return g_iInitStatus;
	
}

int ssdt_deinit()
{
	if(g_iInitStatus)
	{
		MmUnmapLockedPages(g_pMappedSCT, g_pMdlSCT);
		IoFreeMdl(g_pMdlSCT);
	}

	return 1;
}

unsigned long ssdt_writeService(unsigned long sysServiceFunction, unsigned long hookAddr)
{
	unsigned long ret;

	if(!g_iInitStatus)
		return 0;

	ret = (unsigned long)InterlockedExchange((PULONG)&g_pMappedSCT[SYSCALL_INDEX(sysServiceFunction)], (long)hookAddr);

	return ret;
}
