
#include "entry.h"
const 	WCHAR deviceName[]  = L"\\Device\\MYDRIVER2";
const	WCHAR deviceSymbolicLink[] = L"\\DosDevices\\MYDRIVER2";

UNICODE_STRING unicodeDeviceNameBuffer;
UNICODE_STRING unicodeSymLinkBuffer;

PDEVICE_OBJECT g_pDeviceObject = 0;

NTSTATUS DriverEntry( IN PDRIVER_OBJECT driverObject, IN PUNICODE_STRING regPath)
{
	unsigned int i;

	driverObject->DriverUnload  = OnUnload;

	for(i=0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
		driverObject -> MajorFunction[i] = Io_Unsupported;

	driverObject->MajorFunction[IRP_MJ_CREATE]         = Create_DeviceIo;
	driverObject->MajorFunction[IRP_MJ_CLOSE]          = Close_DeviceIo;
	driverObject->MajorFunction[IRP_MJ_WRITE]           = Buffered_Write;

	if(!InitUnicodeStrings())
        	return STATUS_UNSUCCESSFUL; //report the driver could not be loaded.

	DbgPrint("ssdt inited with return code: %d", ssdt_init());

	SetupIoDevice(driverObject);

	DbgPrint("My Driver loaded.");
	
	return STATUS_SUCCESS;
}

int InitUnicodeStrings()
{
	RtlInitUnicodeString(&unicodeDeviceNameBuffer, deviceName);
	RtlInitUnicodeString(&unicodeSymLinkBuffer, deviceSymbolicLink);
	return 1;
}

int SetupIoDevice(PDRIVER_OBJECT pDriverObject)
{

	int ret;


	DbgPrint("Creating I\\O device under name: %ws", unicodeDeviceNameBuffer.Buffer);

	ret = IoCreateDevice(pDriverObject,
			0,
			&unicodeDeviceNameBuffer,
			FILE_DEVICE_UNKNOWN,
			FILE_DEVICE_SECURE_OPEN,
			FALSE,
			&g_pDeviceObject);

	g_pDeviceObject->Flags |= DO_BUFFERED_IO;

	g_pDeviceObject->Flags &= (~DO_DEVICE_INITIALIZING);

	if(ret != STATUS_SUCCESS)
	{
		DbgPrint("Error Creating Device");
		return -1;

	}

	DbgPrint("Device Created");

	ret = IoCreateSymbolicLink(&unicodeSymLinkBuffer, &unicodeDeviceNameBuffer);
	
	if(ret != STATUS_SUCCESS)
	{
		DbgPrint("error creating symbolic link to %ws, named: %ws", unicodeDeviceNameBuffer.Buffer, deviceSymbolicLink);
		return -1;
	}

	DbgPrint("Created symbolic link to %ws, named: %ws", unicodeDeviceNameBuffer.Buffer, unicodeSymLinkBuffer.Buffer);
	return 1;
}


VOID OnUnload(IN PDRIVER_OBJECT driverObject)
{
	if(g_pDeviceObject)
	{
        	IoDeleteDevice(g_pDeviceObject);
		IoDeleteSymbolicLink(&unicodeSymLinkBuffer);
		DbgPrint("Deleted IO Device and symbolic link.");
	}

	ssdt_deinit();

	DbgPrint("My Driver unloaded.");
}