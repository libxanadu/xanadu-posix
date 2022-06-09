#ifndef			_SRCXANADU_OS_NTDLL_H_
#define			_SRCXANADU_OS_NTDLL_H_

#include <xanadu-posix/header.h>


XANADU_CXX_EXTERN_BEGIN



// ntdll : PROCESSINFOCLASS
typedef enum _OS_PROCESSINFOCLASS
{
	OS_ProcessBasicInformation			 = 0,
	OS_ProcessDebugPort				 = 7,
	OS_ProcessWow64Information			 = 26,
	OS_ProcessImageFileName				 = 27,
	OS_ProcessBreakOnTermination			 = 29,
	OS_ProcessSubsystemInformation			 = 75
}OS_PROCESSINFOCLASS;



// ntdll
typedef struct _OS_PROCESS_BASIC_INFORMATION
{
	DWORD ExitStatus;
	DWORD PebBaseAddress;
	DWORD AffinityMask;
	DWORD BasePriority;
	ULONG UniqueProcessId;
	ULONG InheritedFromUniqueProcessId;
}OS_PROCESS_BASIC_INFORMATION;



// ntdll : handle
_XPOSIXAPI_ void* __xcall__ ntdll_handle(void);

// ntdll : find address
_XPOSIXAPI_ void* __xcall__ ntdll_find_address(const char* _FuncName);



// ntdll : NtQueryInformationProcess
_XPOSIXAPI_ NTSTATUS __xcall__ ntdll_NtQueryInformationProcess(HANDLE ProcessHandle, OS_PROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength);



// ntdll : NtSuspendProcess
_XPOSIXAPI_ DWORD __xcall__ ntdll_NtSuspendProcess(HANDLE _ProcessHandle);

// ntdll : NtResumeProcess
_XPOSIXAPI_ DWORD __xcall__ ntdll_NtResumeProcess(HANDLE _ProcessHandle);



XANADU_CXX_EXTERN_END


#endif
