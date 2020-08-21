#ifndef ENTRY_H_
#define ENTRY_H_

#include "ntddk.h"
#include "majorFunctions.h"
#include "ssdt.h"

void OnUnload(IN PDRIVER_OBJECT driverObject);
int InitUnicodeStrings();
int SetupIoDevice();
#endif