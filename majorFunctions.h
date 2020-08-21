#ifndef MAJORFUNCTIONS_H_
#define MAJORFUNCTIONS_H_

#include "ntddk.h"
#include "stringTools.h"
#include "messageProcessor.h"

NTSTATUS Buffered_Write(PDEVICE_OBJECT DeviceObject, PIRP Irp);

NTSTATUS Io_Unsupported(PDEVICE_OBJECT DeviceObject, PIRP Irp);

NTSTATUS Create_DeviceIo(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS Close_DeviceIo(PDEVICE_OBJECT DeviceObject, PIRP Irp);

#endif