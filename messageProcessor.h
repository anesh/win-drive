#ifndef MESSAGEPROCESSOR_H_
#define MESSAGEPROCESSOR_H_

#include "ntddk.h"
#include "message.h"
#include "stringTools.h"
#include "hooking.h"

int processMessage(char* msg);

#endif