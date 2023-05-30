#pragma once
#include <ntddk.h>
#include <windef.h>
extern NTSTATUS CleanPiDDB();
extern BOOLEAN CleanUnloadedDrivers();