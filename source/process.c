#include <xanadu-posix/process.h>
#include <xanadu-posix/system.h>
#include <xanadu-posix/memory.h>
#include <xanadu-posix/string.h>
#include <signal.h>
#include <source/os/ntdll.h>
#if defined(XANADU_SYSTEM_WINDOWS)
#include <tlhelp32.h>
#include <Psapi.h>
#else
#include <errno.h>
#endif
#if defined(XANADU_SYSTEM_LINUX)
#include <xanadu-posix/filesystem.h>
#endif
#if defined(XANADU_SYSTEM_DARWIN)
#include <libproc.h>
#endif


#if defined(XANADU_SYSTEM_DARWIN)
// private : data of process find
typedef struct _private_process_find_data
{
	pid_t*				array;
	int 				count;
	int				index;
}private_process_find_data;
#endif



// X-Series macro definition : signal
#if !defined(SIGQUIT)
#define SIGQUIT				3
#endif
#if !defined(SIGKILL)
#define SIGKILL				9
#endif
#if !defined(SIGSTOP)
#define SIGSTOP				17
#endif
#if !defined(SIGTSTP)
#define SIGTSTP				18
#endif
#if !defined(SIGCONT)
#define SIGCONT				19
#endif





// posix : chdir
_XPOSIXAPI_ int __xcall__ x_posix_chdir(const char* _Directory)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	int 		vSync = 0;
	wchar_t* 	vDirectoryW = x_posix_strutow(_Directory);
	if(vDirectoryW)
	{
		if(SetCurrentDirectoryW(vDirectoryW))
		{
			vSync = 0;
		}
		else
		{
			vSync = (int)GetLastError();
		}
		x_posix_free(vDirectoryW);
		return vSync;
	}
	return vSync;
#else
	return chdir(_Directory);
#endif
}

// posix : getcwd
_XPOSIXAPI_ char* __xcall__ x_posix_getcwd(char* _Directory, size_t _Size)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	wchar_t 	vDirectoryW[XANADU_PATH_MAX] = {0};
	char*		vDirectoryU = NULL;
	if(GetCurrentDirectoryW(XANADU_PATH_MAX, vDirectoryW))
	{
		vDirectoryU = x_posix_strwtou(vDirectoryW);
		if(vDirectoryU)
		{
			x_posix_strncpy(_Directory, vDirectoryU, _Size);
			x_posix_free(vDirectoryU);
			return _Directory;
		}
	}
	return NULL;
#else
	return getcwd(_Directory, _Size);
#endif
}

// posix : popen
_XPOSIXAPI_ FILE* __xcall__ x_posix_popen(const char* _Command, const char* _Mode)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	wchar_t*	vCommandW = x_posix_strutow(_Command);
	wchar_t*	vModeW = x_posix_strutow(_Mode);
	FILE*		vHandle = NULL;

	if(vCommandW && vModeW)
	{
		vHandle = _wpopen(vCommandW, vModeW);
	}
	if(vCommandW)
	{
		x_posix_free(vCommandW);
	}
	if(vModeW)
	{
		x_posix_free(vModeW);
	}
	return vHandle;
#else
	return popen(_Command, _Mode);
#endif
}

// posix : pclose
_XPOSIXAPI_ int __xcall__ x_posix_pclose(FILE* _Stream)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return _pclose(_Stream);
#else
	return pclose(_Stream);
#endif
}

// posix : perror
_XPOSIXAPI_ void __xcall__ x_posix_perror(const char* _ErrorMessage)
{
	perror(_ErrorMessage);
}

// posix : getpid
_XPOSIXAPI_ pid_t __xcall__ x_posix_getpid(void)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return (pid_t)GetCurrentProcessId();
#else
	return getpid();
#endif
}

// posix : getppid
_XPOSIXAPI_ pid_t __xcall__ x_posix_getppid(void)
{
#if defined(XANADU_SYSTEM_WINDOWS)

	DWORD 				vCurrentID = GetCurrentProcessId();
	OS_PROCESS_BASIC_INFORMATION	vProcessBasicInfo;
	HANDLE            		vProcessHandle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, vCurrentID);
	DWORD				vParentProcessId = (DWORD)-1;
	LONG 				vStatus = 0;

	if(vProcessHandle != INVALID_HANDLE_VALUE)
	{
		vStatus = ntdll_NtQueryInformationProcess(vProcessHandle, OS_ProcessBasicInformation, (PVOID)&vProcessBasicInfo, sizeof(OS_PROCESS_BASIC_INFORMATION), NULL);
		if (vStatus == 0)
		{
			vParentProcessId = vProcessBasicInfo.InheritedFromUniqueProcessId;
		}
		CloseHandle(vProcessHandle);
	}

	return (pid_t)vParentProcessId;
#else
	return getppid();
#endif
}

// posix : kill
_XPOSIXAPI_ int __xcall__ x_posix_kill(pid_t _Pid, int _Sig)
{
	return x_process_kill_id(_Pid, _Sig);
}





// This function returns the process identifier of the calling process.
_XPOSIXAPI_ x_process_id_t __xcall__ x_process_get_id()
{
	return (x_process_id_t)x_posix_getpid();
}

// Enable process privilege (Windows only)
_XPOSIXAPI_ int __xcall__ x_process_enable_privilege()
{
	int 		vStatus = -1;
#if defined(XANADU_SYSTEM_WINDOWS)
	HANDLE		vProcessToken = INVALID_HANDLE_VALUE;
	if(OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &vProcessToken))
	{
		LUID 		vLocallyUniqueID;
		if (LookupPrivilegeValueA(NULL, SE_DEBUG_NAME, &vLocallyUniqueID))
		{
			TOKEN_PRIVILEGES	vTokenPrivileges;
			vTokenPrivileges.PrivilegeCount = 1;
			vTokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			vTokenPrivileges.Privileges[0].Luid = vLocallyUniqueID;
			vStatus = AdjustTokenPrivileges(vProcessToken, FALSE, &vTokenPrivileges, 0, NULL, NULL) ? 0 : -1;
		}
		CloseHandle(vProcessToken);
	}
#endif
	return vStatus;
}

// Kill the process with the specified process ID
_XPOSIXAPI_ int __xcall__ x_process_kill_id(x_process_id_t _ProcessID, int _Signal)
{
	int		vSync = 0;
#if defined(XANADU_SYSTEM_WINDOWS)
	UNREFERENCED_PARAMETER(_Signal);
	HANDLE		vProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, _ProcessID);
	if(vProcess == NULL)
	{
		switch (GetLastError())
		{
			case ERROR_INVALID_PARAMETER:
				return x_posix_seterrno(EINVAL);
			case ERROR_ACCESS_DENIED:
				return x_posix_seterrno(EPERM);
			default:
				return x_posix_seterrno(EFAULT);
		}
	}

	switch (_Signal)
	{
		case SIGSTOP:
		case SIGTSTP:
			vSync = (int)ntdll_NtSuspendProcess(vProcess);
			break;
		case SIGCONT:
			vSync = (int)ntdll_NtResumeProcess(vProcess);
			break;
		case SIGTERM:
		case SIGQUIT:
		case SIGINT:
		case SIGKILL:
			vSync = TerminateProcess(vProcess, 0) == TRUE ? 0 : ((int)GetLastError());
			break;
		default:
			vSync = x_posix_seterrno(ENOSYS);
			break;
	}
	CloseHandle(vProcess);
#else
	vSync = kill(_ProcessID, _Signal);
#endif
	return vSync;
}

// Kill the process with the specified process name
_XPOSIXAPI_ int __xcall__ x_process_kill_name(const char* _ProcessName, int _Signal)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_ProcessName == NULL)
	{
		return EINVAL;
	}
#endif

	int 				vKillStatus = ENOEXEC;
	x_process_data_t		vProcessData;
	x_process_stream_t		vStream = x_process_find_first(&vProcessData);
	if(vStream)
	{
		do
		{
			if(0 == x_posix_strcmp(vProcessData.name, _ProcessName))
			{
				vKillStatus = x_process_kill_id(vProcessData.id, _Signal);
			}
		}while(x_process_find_next(vStream, &vProcessData) == 0);
		x_process_find_close(vStream);
	}
	return vKillStatus;
}

// Get data according to process ID
_XPOSIXAPI_ int __xcall__ x_process_get_data_by_id(x_process_id_t _ProcessID, x_process_data_t* _ProcessData)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_ProcessData == NULL)
	{
		return EINVAL;
	}
#endif

	x_posix_memset(_ProcessData, 0, sizeof(x_process_data_t));
	_ProcessData->id = _ProcessID;
#if defined(XANADU_SYSTEM_WINDOWS)

	HANDLE		vHandle = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, _ProcessID);
	if(vHandle == NULL || vHandle == INVALID_HANDLE_VALUE)
	{
		switch (GetLastError())
		{
			case ERROR_INVALID_PARAMETER:
				return x_posix_seterrno(EINVAL);
			case ERROR_ACCESS_DENIED:
				return x_posix_seterrno(EPERM);
			default:
				return x_posix_seterrno(EFAULT);
		}
	}

	// The first module under the process is the address of its own process
	DWORD		vReturnLength = GetModuleFileNameExA(vHandle, NULL, _ProcessData->path, _X_PROCESS_MAX_PATH);
	if(vReturnLength == 0)
	{
		return x_posix_seterrno(EFAULT);
	}
	x_string_replace_char(_ProcessData->path, '\\', '/');
	const char*	vFileName = x_posix_strrchr(_ProcessData->path, '/');
	if(vFileName)
	{
		x_posix_strcpy(_ProcessData->name, vFileName + 1);
	}
	return 0;
#endif
#if defined(XANADU_SYSTEM_LINUX)
	char		vProcessFind[_X_PROCESS_MAX_PATH];
	sprintf(vProcessFind, "/proc/%lld", (long long)_ProcessID);
	strcat(vProcessFind, "/exe");

	int		vCount = readlink(vProcessFind, _ProcessData->path, _X_PROCESS_MAX_PATH);
	if(0 <= vCount || vCount <= _X_PROCESS_MAX_PATH)
	{
		if(strlen(_ProcessData->path))
		{
			const char*	vName = strrchr(_ProcessData->path, '/') + 1;
			if(vName && strlen(vName))
			{
				strcpy(_ProcessData->name, vName);
				return 0;
			}
		}
	}
	return x_posix_errno();
#endif
#if defined(XANADU_SYSTEM_DARWIN)
	int		vStatusName = proc_name(_ProcessID, _ProcessData->name, _X_PROCESS_MAX_NAME);
	int		vStatusPath = proc_pidpath(_ProcessID, _ProcessData->path, _X_PROCESS_MAX_PATH);
	return vStatusName == 0 &&  vStatusPath == 0;
#endif
}



// Process lookup start
_XPOSIXAPI_ x_process_stream_t __xcall__ x_process_find_first(x_process_data_t* _ProcessData)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_ProcessData == NULL)
	{
		return NULL;
	}
#endif
#if defined(XANADU_SYSTEM_WINDOWS)
	PROCESSENTRY32		vProcessEntry32;
	vProcessEntry32.dwSize = sizeof(vProcessEntry32);
	HANDLE			vHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(vHandle == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}
	BOOL		vMore = Process32First(vHandle, &vProcessEntry32);
	if(vMore == FALSE)
	{
		return NULL;
	};
	x_process_get_data_by_id(vProcessEntry32.th32ProcessID, _ProcessData);
	x_posix_strcpy(_ProcessData->name, vProcessEntry32.szExeFile);
	return vHandle;
#endif
#if defined(XANADU_SYSTEM_LINUX)
	bool			vProcessFind = false;
	x_file_data_t		vFileData;
	x_dir_stream_t		vHandle = x_filesystem_find_first("/proc", &vFileData);
	if(vHandle == NULL)
	{
		return NULL;
	}
	do
	{
		if(x_filesystem_is_directory(vFileData.mode) && strcmp(vFileData.name, ".") != 0 && x_posix_strcmp(vFileData.name, "..") != 0)
		{
			uint64_t	vProcessID = strtoull(vFileData.name, NULL, 10);
			if(vProcessID)
			{
				vProcessFind = true;
				x_process_get_data_by_id(vProcessID, _ProcessData);
				break;
			}
		}
	}while(x_filesystem_find_next(vHandle, &vFileData) == 0);
	if(vProcessFind == false)
	{
		x_filesystem_find_close(vHandle);
		return NULL;
	}
	return vHandle;
#endif
#if defined(XANADU_SYSTEM_DARWIN)
	bool		vProcessFind = false;
	int		vProcessCount = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0) * 2;
	if(vProcessCount <= 0)
	{
		return NULL;
	}
	pid_t*		vProcessArray = (pid_t*)x_posix_malloc(sizeof(pid_t) * vProcessCount);
	if(vProcessArray == NULL)
	{
		return NULL;
	}
	vProcessCount = proc_listpids(PROC_ALL_PIDS, 0, vProcessArray, sizeof(pid_t) * vProcessCount);
	if(vProcessCount <= 0)
	{
		free(vProcessArray);
		return NULL;
	}
	private_process_find_data*	vHandle = (private_process_find_data*)x_posix_malloc(sizeof(private_process_find_data));
	if(vHandle == NULL)
	{
		free(vProcessArray);
		return NULL;
	}

	vHandle->array = vProcessArray;
	vHandle->count = vProcessCount;
	vHandle->index = 0;

	for(int vIndex = 0; vIndex < vHandle->count; ++vIndex)
	{
		pid_t           vProcessID = vHandle->array[vIndex];
		if(vProcessID == 0)
		{
			continue;
		}
		vProcessFind = true;
		vHandle->index = vIndex;

		x_process_get_data_by_id(vProcessID, _ProcessData);
		break;
	}
	if(vProcessFind == false)
	{
		x_posix_free(vHandle->array);
		x_posix_free(vHandle);
		return NULL;
	}

	return (x_process_stream_t)vHandle;
#endif
}

// Find the next process. If successful returns 0, Failure returned - 1.
_XPOSIXAPI_ int __xcall__ x_process_find_next(x_process_stream_t _Handle, x_process_data_t* _ProcessData)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_Handle == NULL || _ProcessData == NULL)
	{
		return EINVAL;
	}
#endif
#if defined(XANADU_SYSTEM_WINDOWS)
	PROCESSENTRY32		vProcessEntry32;
	vProcessEntry32.dwSize = sizeof(vProcessEntry32);
	BOOL		vMore = Process32Next(_Handle, &vProcessEntry32);
	if(vMore == FALSE)
	{
		return EEXIST;
	};

	x_process_get_data_by_id(vProcessEntry32.th32ProcessID, _ProcessData);
	x_posix_strcpy(_ProcessData->name, vProcessEntry32.szExeFile);
	return 0;
#endif
#if defined(XANADU_SYSTEM_LINUX)
	bool			vProcessFind = false;
	x_file_data_t	vFileData;
	while(x_filesystem_find_next(_Handle, &vFileData) == 0)
	{
		if(x_filesystem_is_directory(vFileData.mode) && strcmp(vFileData.name, ".") != 0 && x_posix_strcmp(vFileData.name, "..") != 0)
		{
			uint64_t	vProcessID = strtoull(vFileData.name, NULL, 10);
			if(vProcessID)
			{
				vProcessFind = true;
				x_process_get_data_by_id(vProcessID, _ProcessData);
				break;
			}
			break;
		}
	};
	if(vProcessFind == false)
	{
		return EEXIST;
	}
	return 0;
#endif
#if defined(XANADU_SYSTEM_DARWIN)
	bool				vProcessFind = false;
	private_process_find_data*	vHandle = (private_process_find_data*)_Handle;

	for(int vIndex = vHandle->index; vIndex < vHandle->count; ++vIndex)
	{
		pid_t           vProcessID = vHandle->array[vIndex];
		if(vProcessID == 0)
		{
			continue;
		}
		vProcessFind = true;
		vHandle->index = vIndex;

		x_process_get_data_by_id(vProcessID, _ProcessData);
		break;
	}
	if(vProcessFind == false)
	{
		return EEXIST;
	}
	return 0;
#endif
}

// This function closes the specified search handle. If successful returns 0, Failure returned - 1.
_XPOSIXAPI_ int __xcall__ x_process_find_close(x_process_stream_t _Handle)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_Handle == NULL)
	{
		return EINVAL;
	}
#endif
#if defined(XANADU_SYSTEM_WINDOWS)
	return CloseHandle(_Handle) == TRUE ? 0 : EFAULT;
#endif
#if defined(XANADU_SYSTEM_LINUX)
	return x_filesystem_find_close(_Handle);
#endif
#if defined(XANADU_SYSTEM_DARWIN)
	private_process_find_data*	vHandle = (private_process_find_data*)_Handle;
	x_posix_free(vHandle->array);
	x_posix_free(vHandle);
	return 0;
#endif
}
