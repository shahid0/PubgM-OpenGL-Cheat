#include "Clean.h"

typedef struct _piddbcache
{
	LIST_ENTRY		List;
	UNICODE_STRING	DriverName;
	ULONG			TimeDateStamp;
	NTSTATUS		LoadStatus;
	char			_0x0028[16]; // data from the shim engine, or uninitialized memory for custom drivers
} _piddbcache, piddbcache;

typedef struct _RTL_PROCESS_MODULE_INFORMATION
{
	HANDLE Section;
	PVOID MappedBase;
	PVOID ImageBase;
	ULONG ImageSize;
	ULONG Flags;
	USHORT LoadOrderIndex;
	USHORT InitOrderIndex;
	USHORT LoadCount;
	USHORT OffsetToFileName;
	UCHAR  FullPathName[256];
} RTL_PROCESS_MODULE_INFORMATION, * PRTL_PROCESS_MODULE_INFORMATION;

typedef struct _RTL_PROCESS_MODULES
{
	ULONG NumberOfModules;
	RTL_PROCESS_MODULE_INFORMATION Modules[1];
} RTL_PROCESS_MODULES, * PRTL_PROCESS_MODULES;

typedef struct _SYSTEM_MODULE   // Information Class 11
{
	ULONG_PTR Reserved[2];
	PVOID Base;
	ULONG Size;
	ULONG Flags;
	USHORT Index;
	USHORT Unknown;
	USHORT LoadCount;
	USHORT ModuleNameOffset;
	CHAR ImageName[256];
} SYSTEM_MODULE, * PSYSTEM_MODULE;

typedef struct _SYSTEM_MODULE_INFORMATION   // Information Class 11
{
	ULONG_PTR ulModuleCount;
	SYSTEM_MODULE Modules[1];
} SYSTEM_MODULE_INFORMATION, * PSYSTEM_MODULE_INFORMATION;



typedef enum _SYSTEM_INFORMATION_CLASS
{
	SystemBasicInformation = 0x0,
	SystemProcessorInformation = 0x1,
	SystemPerformanceInformation = 0x2,
	SystemTimeOfDayInformation = 0x3,
	SystemPathInformation = 0x4,
	SystemProcessInformation = 0x5,
	SystemCallCountInformation = 0x6,
	SystemDeviceInformation = 0x7,
	SystemProcessorPerformanceInformation = 0x8,
	SystemFlagsInformation = 0x9,
	SystemCallTimeInformation = 0xa,
	SystemModuleInformation = 0xb,
	SystemLocksInformation = 0xc,
	SystemStackTraceInformation = 0xd,
	SystemPagedPoolInformation = 0xe,
	SystemNonPagedPoolInformation = 0xf,
	SystemHandleInformation = 0x10,
	SystemObjectInformation = 0x11,
	SystemPageFileInformation = 0x12,
	SystemVdmInstemulInformation = 0x13,
	SystemVdmBopInformation = 0x14,
	SystemFileCacheInformation = 0x15,
	SystemPoolTagInformation = 0x16,
	SystemInterruptInformation = 0x17,
	SystemDpcBehaviorInformation = 0x18,
	SystemFullMemoryInformation = 0x19,
	SystemLoadGdiDriverInformation = 0x1a,
	SystemUnloadGdiDriverInformation = 0x1b,
	SystemTimeAdjustmentInformation = 0x1c,
	SystemSummaryMemoryInformation = 0x1d,
	SystemMirrorMemoryInformation = 0x1e,
	SystemPerformanceTraceInformation = 0x1f,
	SystemObsolete0 = 0x20,
	SystemExceptionInformation = 0x21,
	SystemCrashDumpStateInformation = 0x22,
	SystemKernelDebuggerInformation = 0x23,
	SystemContextSwitchInformation = 0x24,
	SystemRegistryQuotaInformation = 0x25,
	SystemExtendServiceTableInformation = 0x26,
	SystemPrioritySeperation = 0x27,
	SystemVerifierAddDriverInformation = 0x28,
	SystemVerifierRemoveDriverInformation = 0x29,
	SystemProcessorIdleInformation = 0x2a,
	SystemLegacyDriverInformation = 0x2b,
	SystemCurrentTimeZoneInformation = 0x2c,
	SystemLookasideInformation = 0x2d,
	SystemTimeSlipNotification = 0x2e,
	SystemSessionCreate = 0x2f,
	SystemSessionDetach = 0x30,
	SystemSessionInformation = 0x31,
	SystemRangeStartInformation = 0x32,
	SystemVerifierInformation = 0x33,
	SystemVerifierThunkExtend = 0x34,
	SystemSessionProcessInformation = 0x35,
	SystemLoadGdiDriverInSystemSpace = 0x36,
	SystemNumaProcessorMap = 0x37,
	SystemPrefetcherInformation = 0x38,
	SystemExtendedProcessInformation = 0x39,
	SystemRecommendedSharedDataAlignment = 0x3a,
	SystemComPlusPackage = 0x3b,
	SystemNumaAvailableMemory = 0x3c,
	SystemProcessorPowerInformation = 0x3d,
	SystemEmulationBasicInformation = 0x3e,
	SystemEmulationProcessorInformation = 0x3f,
	SystemExtendedHandleInformation = 0x40,
	SystemLostDelayedWriteInformation = 0x41,
	SystemBigPoolInformation = 0x42,
	SystemSessionPoolTagInformation = 0x43,
	SystemSessionMappedViewInformation = 0x44,
	SystemHotpatchInformation = 0x45,
	SystemObjectSecurityMode = 0x46,
	SystemWatchdogTimerHandler = 0x47,
	SystemWatchdogTimerInformation = 0x48,
	SystemLogicalProcessorInformation = 0x49,
	SystemWow64SharedInformationObsolete = 0x4a,
	SystemRegisterFirmwareTableInformationHandler = 0x4b,
	SystemFirmwareTableInformation = 0x4c,
	SystemModuleInformationEx = 0x4d,
	SystemVerifierTriageInformation = 0x4e,
	SystemSuperfetchInformation = 0x4f,
	SystemMemoryListInformation = 0x50,
	SystemFileCacheInformationEx = 0x51,
	SystemThreadPriorityClientIdInformation = 0x52,
	SystemProcessorIdleCycleTimeInformation = 0x53,
	SystemVerifierCancellationInformation = 0x54,
	SystemProcessorPowerInformationEx = 0x55,
	SystemRefTraceInformation = 0x56,
	SystemSpecialPoolInformation = 0x57,
	SystemProcessIdInformation = 0x58,
	SystemErrorPortInformation = 0x59,
	SystemBootEnvironmentInformation = 0x5a,
	SystemHypervisorInformation = 0x5b,
	SystemVerifierInformationEx = 0x5c,
	SystemTimeZoneInformation = 0x5d,
	SystemImageFileExecutionOptionsInformation = 0x5e,
	SystemCoverageInformation = 0x5f,
	SystemPrefetchPatchInformation = 0x60,
	SystemVerifierFaultsInformation = 0x61,
	SystemSystemPartitionInformation = 0x62,
	SystemSystemDiskInformation = 0x63,
	SystemProcessorPerformanceDistribution = 0x64,
	SystemNumaProximityNodeInformation = 0x65,
	SystemDynamicTimeZoneInformation = 0x66,
	SystemCodeIntegrityInformation = 0x67,
	SystemProcessorMicrocodeUpdateInformation = 0x68,
	SystemProcessorBrandString = 0x69,
	SystemVirtualAddressInformation = 0x6a,
	SystemLogicalProcessorAndGroupInformation = 0x6b,
	SystemProcessorCycleTimeInformation = 0x6c,
	SystemStoreInformation = 0x6d,
	SystemRegistryAppendString = 0x6e,
	SystemAitSamplingValue = 0x6f,
	SystemVhdBootInformation = 0x70,
	SystemCpuQuotaInformation = 0x71,
	SystemNativeBasicInformation = 0x72,
	SystemErrorPortTimeouts = 0x73,
	SystemLowPriorityIoInformation = 0x74,
	SystemBootEntropyInformation = 0x75,
	SystemVerifierCountersInformation = 0x76,
	SystemPagedPoolInformationEx = 0x77,
	SystemSystemPtesInformationEx = 0x78,
	SystemNodeDistanceInformation = 0x79,
	SystemAcpiAuditInformation = 0x7a,
	SystemBasicPerformanceInformation = 0x7b,
	SystemQueryPerformanceCounterInformation = 0x7c,
	SystemSessionBigPoolInformation = 0x7d,
	SystemBootGraphicsInformation = 0x7e,
	SystemScrubPhysicalMemoryInformation = 0x7f,
	SystemBadPageInformation = 0x80,
	SystemProcessorProfileControlArea = 0x81,
	SystemCombinePhysicalMemoryInformation = 0x82,
	SystemEntropyInterruptTimingInformation = 0x83,
	SystemConsoleInformation = 0x84,
	SystemPlatformBinaryInformation = 0x85,
	SystemThrottleNotificationInformation = 0x86,
	SystemHypervisorProcessorCountInformation = 0x87,
	SystemDeviceDataInformation = 0x88,
	SystemDeviceDataEnumerationInformation = 0x89,
	SystemMemoryTopologyInformation = 0x8a,
	SystemMemoryChannelInformation = 0x8b,
	SystemBootLogoInformation = 0x8c,
	SystemProcessorPerformanceInformationEx = 0x8d,
	SystemSpare0 = 0x8e,
	SystemSecureBootPolicyInformation = 0x8f,
	SystemPageFileInformationEx = 0x90,
	SystemSecureBootInformation = 0x91,
	SystemEntropyInterruptTimingRawInformation = 0x92,
	SystemPortableWorkspaceEfiLauncherInformation = 0x93,
	SystemFullProcessInformation = 0x94,
	SystemKernelDebuggerInformationEx = 0x95,
	SystemBootMetadataInformation = 0x96,
	SystemSoftRebootInformation = 0x97,
	SystemElamCertificateInformation = 0x98,
	SystemOfflineDumpConfigInformation = 0x99,
	SystemProcessorFeaturesInformation = 0x9a,
	SystemRegistryReconciliationInformation = 0x9b,
	MaxSystemInfoClass = 0x9c,
} SYSTEM_INFORMATION_CLASS;
NTSTATUS
NTAPI
ZwQuerySystemInformation(
	IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
	OUT PVOID SystemInformation,
	IN ULONG SystemInformationLength,
	OUT PULONG ReturnLength OPTIONAL
);
static uintptr_t get_kernel_address(const char* name, size_t* size)
{
	NTSTATUS status = STATUS_SUCCESS;
	ULONG neededSize = 0;

	ZwQuerySystemInformation(
		SystemModuleInformation,
		&neededSize,
		0,
		&neededSize
	);

	PSYSTEM_MODULE_INFORMATION pModuleList;

	pModuleList = (PSYSTEM_MODULE_INFORMATION)ExAllocatePool(NonPagedPool, neededSize);

	if (!pModuleList)
	{
		log("ExAllocatePoolWithTag failed(kernel addr)\n");
		return 0;
	}

	status = ZwQuerySystemInformation(SystemModuleInformation,
		pModuleList,
		neededSize,
		0
	);

	ULONG i = 0;
	uintptr_t address = 0;

	for (i = 0; i < pModuleList->ulModuleCount; i++)
	{
		SYSTEM_MODULE mod = pModuleList->Modules[i];

		address = (uintptr_t)(pModuleList->Modules[i].Base);
		*size = (uintptr_t)(pModuleList->Modules[i].Size);
		if (strstr(mod.ImageName, name) != NULL)
			break;
	}

	ExFreePool(pModuleList);

	return address;
}


unsigned __int64 dereference(unsigned __int64 address, unsigned int offset)
{
	if (address == 0)
		return 0;

	return address + (int)((*(int*)(address + offset) + offset) + sizeof(int));
}

unsigned __int64 find_pattern(void* start, size_t length, const char* pattern, const char* mask)
{
	const char* data = (const char*)start;
	const auto pattern_length = strlen(mask);

	for (size_t i = 0; i <= length - pattern_length; i++)
	{
		BOOLEAN accumulative_found = TRUE;

		for (size_t j = 0; j < pattern_length; j++)
		{
			if (!MmIsAddressValid((void*)((unsigned __int64)data + i + j)))
			{
				accumulative_found = FALSE;
				break;
			}

			if (data[i + j] != pattern[j] && mask[j] != '?')
			{
				accumulative_found = FALSE;
				break;
			}
		}

		if (accumulative_found)
		{
			return (unsigned __int64)((unsigned __int64)data + i);
		}
	}

	return NULL;
}


BOOLEAN CleanUnloadedDrivers()
{
	ULONG bytes = 0;
	NTSTATUS status = ZwQuerySystemInformation(SystemModuleInformation, 0, bytes, &bytes);

	if (!bytes)
	{
		return FALSE;
	}

	PRTL_PROCESS_MODULES modules = (PRTL_PROCESS_MODULES)ExAllocatePoolWithTag(NonPagedPool, bytes, 'g53a');

	status = ZwQuerySystemInformation(SystemModuleInformation, modules, bytes, &bytes);

	if (!NT_SUCCESS(status))
	{
		return FALSE;
	}

	PRTL_PROCESS_MODULE_INFORMATION module = modules->Modules;
	UINT64 ntoskrnlBase = 0, ntoskrnlSize = 0;

	for (ULONG i = 0; i < modules->NumberOfModules; i++)
	{
		if (!strcmp((char*)module[i].FullPathName, "\\SystemRoot\\system32\\ntoskrnl.exe"))
		{
			ntoskrnlBase = (UINT64)module[i].ImageBase;
			ntoskrnlSize = (UINT64)module[i].ImageSize;
			break;
		}
	}

	if (modules)
		ExFreePoolWithTag(modules, 0);

	if (ntoskrnlBase <= 0)
	{
		return FALSE;
	}

	// NOTE: 4C 8B ? ? ? ? ? 4C 8B C9 4D 85 ? 74 + 3] + current signature address = MmUnloadedDrivers
	UINT64 mmUnloadedDriversPtr = find_pattern((UINT64)ntoskrnlBase, (UINT64)ntoskrnlSize, (BYTE*)"\x4C\x8B\x00\x00\x00\x00\x00\x4C\x8B\xC9\x4D\x85\x00\x74", "xx?????xxxxx?x");

	if (!mmUnloadedDriversPtr)
	{
		return FALSE;
	}

	UINT64 mmUnloadedDrivers = (UINT64)((PUCHAR)mmUnloadedDriversPtr + *(PULONG)((PUCHAR)mmUnloadedDriversPtr + 3) + 7);
	UINT64 bufferPtr = *(UINT64*)mmUnloadedDrivers;

	// NOTE: 0x7D0 is the size of the MmUnloadedDrivers array for win 7 and above
	PVOID newBuffer = ExAllocatePoolWithTag(NonPagedPoolNx, 0x7D0, 'g53a');

	if (!newBuffer)
		return FALSE;

	memset(newBuffer, 0, 0x7D0);

	// NOTE: replace MmUnloadedDrivers
	*(UINT64*)mmUnloadedDrivers = (UINT64)newBuffer;

	// NOTE: clean the old buffer
	ExFreePoolWithTag((PVOID)bufferPtr, 'g53a'); // 'MmDT'

	return TRUE;
}

NTSTATUS CleanPiDDB() {
	//DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "\nCleanPiDDB started!");

	PCWSTR pDrivNam = L"Ae714312.sys";
	UNICODE_STRING DrivNam;
	RtlInitUnicodeString(&DrivNam, pDrivNam);

	size_t ntoskrnlSize;
	uintptr_t ntoskrnlBase = get_kernel_address("ntoskrnl.exe", &ntoskrnlSize);


	PRTL_AVL_TABLE PiDDBCacheTable;

	PiDDBCacheTable = (PRTL_AVL_TABLE)dereference(find_pattern((void*)ntoskrnlBase, ntoskrnlSize, "\x48\x8D\x0D\x00\x00\x00\x00\x4C\x89\x35\x00\x00\x00\x00\x49\x8B\xE9", "xxx????xxx????xxx"), 3);
	if (!PiDDBCacheTable)
		PiDDBCacheTable = (PRTL_AVL_TABLE)dereference(find_pattern((void*)ntoskrnlBase, ntoskrnlSize, "\x48\x8D\x0D\x00\x00\x00\x00\x4C\x89\x35\x00\x00\x00\x00\xBB\x00\x00\x00\x00", "xxx????xxx????x????"), 3);
	if (!PiDDBCacheTable)
		PiDDBCacheTable = (PRTL_AVL_TABLE)dereference(find_pattern((void*)ntoskrnlBase, ntoskrnlSize, "\x48\x8d\x0d\x00\x00\x00\x00\xe8\x00\x00\x00\x00\x3d\x00\x00\x00\x00\x0f\x83", "xxx????x????x????xx"), 3);

	if (PiDDBCacheTable) {

		uintptr_t entry_address = (uintptr_t)(PiDDBCacheTable->BalancedRoot.RightChild) + sizeof(RTL_BALANCED_LINKS);
		piddbcache* entry = (piddbcache*)(entry_address);

		/*capcom.sys(drvmap) : 0x57CD1415 iqvw64e.sys(kdmapper) : 0x5284EAC3*/
		if (entry->TimeDateStamp == 0x57CD1415 || entry->TimeDateStamp == 0x5284EAC3)
		{
			entry->TimeDateStamp = 0xff197d; //change timestamp
			entry->DriverName = DrivNam; //change driver name
		}

		ULONG count = 0;

		for (PLIST_ENTRY link = entry->List.Flink; link != entry->List.Blink; link = link->Flink, count++)
		{
			piddbcache* cache_entry = (piddbcache*)(link);

			if (cache_entry->TimeDateStamp == 0x57CD1415 || cache_entry->TimeDateStamp == 0x5284EAC3)
			{
				cache_entry->TimeDateStamp = 0xff197d + count;
				cache_entry->DriverName = DrivNam;
			}
			//DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "cache_entry count: %lu name: %wZ \t\t stamp: %x\n", count, cache_entry->DriverName, cache_entry->TimeDateStamp);
		}
	}

}
