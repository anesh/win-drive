#include "majorFunctions.h"

NTSTATUS Create_DeviceIo(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_SUCCESS;	

	DbgPrint("Handle to IO Device has been opened.");

	return NtStatus;
}


NTSTATUS Close_DeviceIo(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_SUCCESS;
	
	DbgPrint("Handle to IO Device has been closed.");

	return NtStatus;
}


NTSTATUS Buffered_Write(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_SUCCESS;
	
	PIO_STACK_LOCATION pIoStackIrp = NULL;

	PCHAR pInBuffer = NULL;


	DbgPrint("IO Device has been written to.");



	pIoStackIrp = IoGetCurrentIrpStackLocation(Irp);


	if(pIoStackIrp)
	{

		pInBuffer = (PCHAR)Irp->AssociatedIrp.SystemBuffer;

		if(pInBuffer)
		{
			forceNullTermination(pInBuffer, pIoStackIrp->Parameters.Write.Length);			
			DbgPrint("Processing Message: SZ:%u, STR:%s", pIoStackIrp->Parameters.Write.Length, pInBuffer);
			processMessage(pInBuffer);
		}
		else
		{
			DbgPrint("Write called with null buffer pointer.");
		}
	}
	else
	{
		DbgPrint("Invalid IRP stack pointer..");
	}

	return NtStatus;
}

NTSTATUS Io_Unsupported(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_SUCCESS;
	
	DbgPrint("Unsupported Majour Function Requested. Returning STATUS_SUCCESS");
	
	return NtStatus;
}