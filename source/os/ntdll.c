#include <source/os/ntdll.h>
#include <xanadu-posix/system.h>



// X-Series type definition : ntdll
typedef NTSTATUS (WINAPI *OS_NtQueryInformationProcess)(HANDLE ProcessHandle, OS_PROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength);
typedef DWORD (WINAPI *OS_NtSuspendProcess)(HANDLE _ProcessHandle);
typedef DWORD (WINAPI *OS_NtResumeProcess)(HANDLE _ProcessHandle);



#if !defined(ENOSYS)
#define ENOSYS				40
#endif



// ntdll : handle
_XPOSIXAPI_ void* __xcall__ ntdll_handle(void)
{
	static void*		_static_ntdll_handle = NULL;
	if(_static_ntdll_handle == NULL)
	{
		_static_ntdll_handle = x_posix_dlopen("ntdll.dll", 0);
	}
	return _static_ntdll_handle;
}

// ntdll : find address
_XPOSIXAPI_ void* __xcall__ ntdll_find_address(const char* _FuncName)
{
	return x_posix_dlsym(ntdll_handle(), _FuncName);
}



// ntdll : NtQueryInformationProcess
_XPOSIXAPI_ NTSTATUS __xcall__ ntdll_NtQueryInformationProcess(HANDLE ProcessHandle, OS_PROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength)
{
	OS_NtQueryInformationProcess		_Function = (OS_NtQueryInformationProcess)ntdll_find_address("NtQueryInformationProcess");
	if(_Function)
	{
		return _Function(ProcessHandle, ProcessInformationClass, ProcessInformation, ProcessInformationLength, ReturnLength);
	}
	return x_posix_seterrno(ENOSYS);
}



// ntdll : NtSuspendProcess
_XPOSIXAPI_ DWORD __xcall__ ntdll_NtSuspendProcess(HANDLE _ProcessHandle)
{
	OS_NtSuspendProcess		_Function = (OS_NtSuspendProcess)ntdll_find_address("NtSuspendProcess");
	if(_Function)
	{
		return _Function(_ProcessHandle);
	}
	return x_posix_seterrno(ENOSYS);
}

// ntdll : NtResumeProcess
_XPOSIXAPI_ DWORD __xcall__ ntdll_NtResumeProcess(HANDLE _ProcessHandle)
{
	OS_NtResumeProcess		_Function = (OS_NtResumeProcess)ntdll_find_address("NtResumeProcess");
	if(_Function)
	{
		return _Function(_ProcessHandle);
	}
	return x_posix_seterrno(ENOSYS);
}
