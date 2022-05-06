#include <xanadu-posix/system.h>
#include <xanadu-posix/filesystem.h>
#include <xanadu-posix/memory.h>
#include <xanadu-posix/process.h>
#include <xanadu-posix/string.h>
#include <xanadu-posix/stream.h>
#include <errno.h>
#if defined(XANADU_SYSTEM_WINDOWS)
#include <iphlpapi.h>
#include <WtsApi32.h>
#include <userenv.h>
#include <Shlobj.h>
#else
#include <dlfcn.h>
#include <sys/utsname.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#if !defined(XANADU_SYSTEM_ANDROID)
#include <sys/sysctl.h>
#endif
#endif




// posix : system
_XPOSIXAPI_ int __xcall__ x_posix_system(const char* _Command)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	wchar_t*	vCommandW = x_posix_strutow(_Command);
	int 		vStatus = EINVAL;

	if(vCommandW)
	{
		vStatus = _wsystem(vCommandW);
	}
	if(vCommandW)
	{
		x_posix_free(vCommandW);
	}
	return vStatus;
#else
	return system(_Command);
#endif
}





// posix : wsystem
_XPOSIXAPI_ int __xcall__ x_posix_wsystem(const wchar_t* _Command)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return _wsystem(_Command);
#else
	char*		vCommandU = x_posix_strwtou(_Command);
	int 		vStatus = EINVAL;

	if(vCommandU)
	{
		vStatus = system(vCommandU);
	}
	if(vCommandU)
	{
		x_posix_free(vCommandU);
	}
	return vStatus;
#endif
}





// posix : gethostid
_XPOSIXAPI_ long __xcall__ x_posix_gethostid(void)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	long			vHostID = 0U;
	unsigned long 		vLength = sizeof(IP_ADAPTER_ADDRESSES);
	IP_ADAPTER_ADDRESSES* 	vAddresses = (IP_ADAPTER_ADDRESSES*)x_posix_malloc(vLength);
	if(vAddresses)
	{
		// Make an initial call to GetAdaptersAddresses to get the required memory size
		if(GetAdaptersAddresses(AF_UNSPEC, 0, NULL, vAddresses, &vLength) == ERROR_BUFFER_OVERFLOW)
		{
			x_posix_free(vAddresses);
			vAddresses = (IP_ADAPTER_ADDRESSES*)x_posix_malloc(vLength);
			if(vAddresses)
			{
				if(GetAdaptersAddresses(AF_UNSPEC, 0, NULL, vAddresses, &vLength) == ERROR_SUCCESS)
				{
					// If successful, take out the first network card from the received data and convert it to HostID
					for(IP_ADAPTER_ADDRESSES* vIterator = vAddresses; vIterator && vHostID == 0ULL; vIterator = vIterator->Next)
					{
						// Ensure that the length of the MAC address is 00-00-00-00-00-00
						if(vIterator->PhysicalAddressLength == 6)
						{
							for(unsigned int vIndex = 0; vIndex < 6; ++vIndex)
							{
								vHostID = vHostID << 8;
								vHostID += vIterator->PhysicalAddress[vIndex];
							}
						}
					}
				}
				x_posix_free(vAddresses);
			}
		}
		else
		{
			x_posix_free(vAddresses);
		}
	}
	return vHostID;
#else
#if defined(XANADU_SYSTEM_ANDROID)
	long			vHostID = 0;
	char			vHostName[1024];
	struct hostent*		vHostEnt = NULL;
	char**			vAddress = NULL;
	struct in_addr		in;
	if (gethostname(vHostName, 1024) == 0)
	{
		if ((vHostEnt = gethostbyname(vHostName)) != NULL)
		{
			vAddress = vHostEnt->h_addr_list;
			if (vAddress && *vAddress)
			{
				memcpy(&in.s_addr, *vAddress, sizeof(in.s_addr));
				vHostID = (long)in.s_addr;
			}
		}
	}
	return vHostID;
#else
	return gethostid();
#endif
#endif
}

// posix : errno
_XPOSIXAPI_ int __xcall__ x_posix_errno()
{
	return errno;
}

// posix : seterrno
_XPOSIXAPI_ int __xcall__ x_posix_seterrno(int _Errno)
{
	errno = _Errno;
	return errno;
}

// posix : strerror
_XPOSIXAPI_ char* __xcall__ x_posix_strerror(int _Error)
{
	return strerror(_Error);
}

// posix : abort
_XPOSIXAPI_ void __xcall__ x_posix_abort(void)
{
	abort();
}

// posix : exit
_XPOSIXAPI_ void __xcall__ x_posix_exit(int _Status)
{
	exit(_Status);
}





// posix : getenv
_XPOSIXAPI_ char* __xcall__ x_posix_getenv(const char* _Name)
{
	return getenv(_Name);
}

// posix : setenv
_XPOSIXAPI_ int __xcall__ x_posix_setenv(const char* _Name, const char* _Value, int _Overwrite)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	char 		vEnvironmentVariable[MAX_PATH] = {0};
	if(_Overwrite)
	{
		if(SetEnvironmentVariableA(_Name, _Value))
		{
			return 0;
		}
		else
		{
			return (int)GetLastError();
		}
	}
	else
	{
		if(GetEnvironmentVariableA(_Name, vEnvironmentVariable, MAX_PATH) == 0)
		{
			if(GetLastError() == ERROR_ENVVAR_NOT_FOUND)
			{
				if(SetEnvironmentVariableA(_Name, _Value))
				{
					return 0;
				}
				else
				{
					return (int)GetLastError();
				}
			}
		}
		return 0;
	}
#else
	return setenv(_Name, _Value, _Overwrite);
#endif
}

// posix : putenv
_XPOSIXAPI_ int __xcall__ x_posix_putenv(char* _String)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return _putenv(_String);
#else
	return putenv(_String);
#endif
}

// posix : unsetenv
_XPOSIXAPI_ int __xcall__ x_posix_unsetenv(const char* _Name)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	if(SetEnvironmentVariableA(_Name, NULL))
	{
		return 0;
	}
	else
	{
		return (int)GetLastError();
	}
#else
	return unsetenv(_Name);
#endif
}





// posix : dlopen
_XPOSIXAPI_ void* __xcall__ x_posix_dlopen(const char* _Library, int _Mode)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	XANADU_UNUSED(_Mode);

	void*		vHandle = NULL;
	wchar_t*	vLocalLibrary = x_posix_strutow(_Library);
	if(vLocalLibrary)
	{
		vHandle = LoadLibraryW(vLocalLibrary);
		x_posix_free(vLocalLibrary);
	}
	return vHandle;
#else
	return dlopen(_Library, _Mode);
#endif
}

// posix : dlsym
_XPOSIXAPI_ void* __xcall__ x_posix_dlsym(void* _Handle, const char* _ProcName)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return (void*)GetProcAddress(_Handle, _ProcName);
#else
	return dlsym(_Handle, _ProcName);
#endif
}

// posix : dlclose
_XPOSIXAPI_ int __xcall__ x_posix_dlclose(void* _Handle)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return FreeLibrary(_Handle) ? 0 : 1;
#else
	return dlclose(_Handle);
#endif
}





#if defined(XANADU_SYSTEM_WINDOWS)
// windows: CpuCountSetBits
static DWORD CpuCountSetBits(ULONG_PTR bitMask)
{
	DWORD		LSHIFT = (sizeof(ULONG_PTR) * 8) - 1;
	DWORD		vBitSetCount = 0;
	ULONG_PTR	vBitTest = ((ULONG_PTR)1) << LSHIFT;
	DWORD		vIndex = 0;

	for (vIndex = 0; vIndex <= LSHIFT; ++vIndex)
	{
		vBitSetCount += ((bitMask & vBitTest) ? 1 : 0);
		vBitTest /= 2;
	}
	return vBitSetCount;
}

// windows: GetLogicalProcessorInformation
static int windows_GetLogicalProcessorInformation(SYSTEM_LOGICAL_PROCESSOR_INFORMATION** _CpuInfo, size_t* _Count)
{
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION*	vProcessInfo = NULL;
	DWORD					vReturnedLength = 0;

	GetLogicalProcessorInformation(NULL, &vReturnedLength);
	if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
	{
		return 0;
	}
	vProcessInfo = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION*) x_posix_malloc(vReturnedLength);
	if(vProcessInfo == NULL)
	{
		return 0;
	}
	if(GetLogicalProcessorInformation(vProcessInfo, &vReturnedLength))
	{
		*_CpuInfo = vProcessInfo;
		*_Count = vReturnedLength / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
		return 0;
	}
	x_posix_free(vProcessInfo);
	return -1;
}
#endif
#if defined(XANADU_SYSTEM_LINUX)
static size_t linux_system_output_buffer(const char* _System, char* _Buffer, size_t _Size)
{
	size_t		vSync = 0;
	FILE*		vHandle = x_posix_popen(_System, "rb");
	if(vHandle)
	{
		vSync = x_posix_fread(_Buffer, 1, _Size - 1, vHandle);
		x_posix_pclose(vHandle);
	}
	return vSync;
}
#endif



// Sets the last-error code for the calling thread.
_XPOSIXAPI_ void x_system_set_last_error(int _Error)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	SetLastError((DWORD)_Error);
#endif
	x_posix_seterrno(_Error);
}

// Gets the last-error code for the calling thread.
_XPOSIXAPI_ int x_system_get_last_error(void)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	DWORD		vError = GetLastError();
	if(vError != 0)
	{
		return (int)vError;
	}
#endif
	return x_posix_errno();
}





// Get operating system bits
_XPOSIXAPI_ size_t x_system_os_bits(void)
{
	static size_t 	_static_system_os_bits = 0;

	if(0 == _static_system_os_bits)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
#if defined(_WIN64)
		_static_system_os_bits = 64;
#else
		typedef BOOL(WINAPI* KERNEL_ISWOW64PROCESS)(HANDLE, PBOOL);
		BOOL			bIsWow64= FALSE;
		KERNEL_ISWOW64PROCESS	FunctionIsWow64Process = (KERNEL_ISWOW64PROCESS)GetProcAddress(GetModuleHandleW(L"kernel32"), "IsWow64Process");

		if (FunctionIsWow64Process)
		{
			if (FunctionIsWow64Process(GetCurrentProcess(), &bIsWow64))
			{
				_static_system_os_bits = bIsWow64 ? 64 : 32;
			}
			else
			{
				_static_system_os_bits = 32;
			}
		}
		else
		{
			_static_system_os_bits = 32;
		}
#endif
#else
		struct utsname		uts;
		if(0 == uname(&uts))
		{
			if(x_posix_stristr(uts.machine, "x86_64") || x_posix_stristr(uts.machine, "AMD64") || x_posix_strstr(uts.machine, "ARM64"))
			{
				_static_system_os_bits = 64;
			}
			else
			{
				_static_system_os_bits = 32;
			}
		}
#endif
	}

	return _static_system_os_bits;
}





// Get the number of CPU cores
_XPOSIXAPI_ size_t x_system_cpu_core_count(void)
{
	static size_t 	_static_system_cpu_core_count = 0;

	if(0 == _static_system_cpu_core_count)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		SYSTEM_INFO	vSystemInfo;
		GetSystemInfo(&vSystemInfo);
		_static_system_cpu_core_count = vSystemInfo.dwNumberOfProcessors;
#elif defined(XANADU_SYSTEM_DARWIN)
		int		vName[2];
		size_t		vLength = 4;
		uint32_t	vCpuCount = 0;

		vName[0] = CTL_HW;
		vName[1] = HW_AVAILCPU;
		sysctl(vName, 2, &vCpuCount, &vLength, NULL, 0);
		if(vCpuCount < 1)
		{
			vName[1] = HW_NCPU;
			sysctl(vName, 2, &vCpuCount, &vLength, NULL, 0);
			if(vCpuCount < 1)
			{
				vCpuCount = 1;
			}
		}
		_static_system_cpu_core_count = vCpuCount;
#elif defined(XANADU_SYSTEM_LINUX)
		_static_system_cpu_core_count = sysconf(_SC_NPROCESSORS_ONLN);
#else
#warning unrecognized platform
#endif
	}

	return _static_system_cpu_core_count;
}

// Get the number of CPU threads
_XPOSIXAPI_ size_t x_system_cpu_thread_count(void)
{
	static size_t 	_static_system_cpu_thread_count = 0;

	if(0 == _static_system_cpu_thread_count)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		size_t 					vCpuCoreCount = 0;
		size_t 					vCpuThreadCount = 0;
		size_t 					vProcessIndex = 0;
		size_t 					vProcessCount = 0;
		SYSTEM_LOGICAL_PROCESSOR_INFORMATION*	vProcessInfo = NULL;
		windows_GetLogicalProcessorInformation(&vProcessInfo, &vProcessCount);

		if(vProcessInfo && vProcessCount > 0)
		{
			for(vProcessIndex = 0; vProcessIndex < vProcessCount; ++vProcessIndex)
			{
				if (vProcessInfo[vProcessIndex].Relationship == RelationProcessorCore)
				{
					vCpuCoreCount++;
					vCpuThreadCount += CpuCountSetBits(vProcessInfo[vProcessIndex].ProcessorMask);
				}
			}
			x_posix_free(vProcessInfo);
		}
		_static_system_cpu_thread_count = vCpuThreadCount;
#elif defined(XANADU_SYSTEM_LINUX)
#define 	X_CPU_THREAD_BUFFER	(1024)
		char			vProcessBuffer[X_CPU_THREAD_BUFFER] = {0};
		unsigned int		vThreadCount = 0;
		if(0 != linux_system_output_buffer("grep \'processor\' /proc/cpuinfo | sort -u | wc -l", vProcessBuffer, X_CPU_THREAD_BUFFER))
		{
			x_posix_sscanf(vProcessBuffer, "%u", &vThreadCount);
		}
		_static_system_cpu_thread_count = vThreadCount;
#elif defined(XANADU_SYSTEM_DARWIN)
		size_t			vThreadCount = 0;
		size_t			vSizeofThreadCount = sizeof(vThreadCount);
		sysctlbyname("machdep.cpu.thread_count", &vThreadCount, &vSizeofThreadCount, 0, 0);
		_static_system_cpu_thread_count = vThreadCount;
#else
#warning unrecognized platform
#endif
	}

	return _static_system_cpu_thread_count;
}

// Get the size of cpu cache line
_XPOSIXAPI_ size_t x_system_cpu_cache_line_size(void)
{
	static size_t 	_static_system_cpu_cache_line_size = 0;

	if(0 == _static_system_cpu_cache_line_size)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		size_t 					vProcessIndex = 0;
		size_t 					vProcessCount = 0;
		SYSTEM_LOGICAL_PROCESSOR_INFORMATION*	vProcessInfo = NULL;
		windows_GetLogicalProcessorInformation(&vProcessInfo, &vProcessCount);
		if(vProcessInfo && vProcessCount > 0)
		{
			for(vProcessIndex = 0; vProcessIndex < vProcessCount; ++vProcessIndex)
			{
				if (vProcessInfo[vProcessIndex].Relationship == RelationCache && vProcessInfo[vProcessIndex].Cache.Level == 1)
				{
					_static_system_cpu_cache_line_size = vProcessInfo[vProcessIndex].Cache.LineSize;
					break;
				}
			}
			x_posix_free(vProcessInfo);
		}
#elif defined(XANADU_SYSTEM_LINUX)
#define 	X_CPU_CACHE_BUFFER	(1024)
		char			vProcessBuffer[X_CPU_CACHE_BUFFER] = {0};
		unsigned int		vLineSize = 0;
		FILE*			vHandle = x_posix_fopen("/sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size", "r");
		if (vHandle)
		{
			x_posix_fscanf(vHandle, "%u", &vLineSize);
			x_posix_fclose(vHandle);
		}
		else
		{
			if(0 != linux_system_output_buffer("getconf LEVEL1_ICACHE_LINESIZE", vProcessBuffer, X_CPU_CACHE_BUFFER))
			{
				x_posix_sscanf(vProcessBuffer, "%u", &vLineSize);
			}
		}
		_static_system_cpu_cache_line_size = vLineSize;
#elif defined(XANADU_SYSTEM_DARWIN)
		size_t			vLineSize = 0;
		size_t			vSizeofLineSize = sizeof(vLineSize);
		sysctlbyname("hw.cachelinesize", &vLineSize, &vSizeofLineSize, 0, 0);
		_static_system_cpu_cache_line_size = vLineSize;
#else
#warning unrecognized platform
#endif
	}

	return _static_system_cpu_cache_line_size;
}





// The name of the user who is now logged in
_XPOSIXAPI_ const char* x_system_current_user(void)
{
	static char 	_static_system_current_user[X_FILESYSTEM_MAX_PATH] = {0};
	if(0 == x_posix_strlen(_static_system_current_user))
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		wchar_t		vUserProfileDirectory[X_FILESYSTEM_MAX_PATH] = {0};
		HANDLE		vProcess = GetCurrentProcess();
		HANDLE		vToken = NULL;
		BOOL		vSync = OpenProcessToken(vProcess, TOKEN_QUERY, &vToken);
		if (vSync)
		{
			DWORD		vWTS_Length = 0;
			wchar_t*	vWTS_Data = NULL;
			// First call, to determine size of the strings (with '\0').
			vSync = GetUserProfileDirectoryW(vToken, NULL, &vWTS_Length);
			if (!vSync && vWTS_Length != 0)
			{
				vWTS_Data = x_posix_malloc((vWTS_Length + 1) * sizeof(wchar_t));
				if(vWTS_Data)
				{
					vSync = GetUserProfileDirectoryW(vToken, vWTS_Data, &vWTS_Length);
					if (vSync)
					{
						x_string_replace_wchar_t(vWTS_Data, L'\\', L'/');
						wcscpy(vUserProfileDirectory, vWTS_Data);
					}
					x_posix_free(vWTS_Data);
				}
			}
			CloseHandle(vToken);
		}

		if(0 == wcslen(vUserProfileDirectory))
		{
			LPWSTR		vInfoBuffer = NULL;
			DWORD		vInfoLength = 0;
			BOOL		vQuery = WTSQuerySessionInformationW(WTS_CURRENT_SERVER_HANDLE, WTS_CURRENT_SESSION, WTSUserName, &vInfoBuffer, &vInfoLength);
			if (vQuery && vInfoBuffer && vInfoLength)
			{
				wcsncpy(vUserProfileDirectory, vInfoBuffer, vInfoLength);
			}
			else
			{
				DWORD		vUserLength = X_FILESYSTEM_MAX_PATH - 1;
				GetUserNameW(vUserProfileDirectory, &vUserLength);
			}
			if(vInfoBuffer)
			{
				WTSFreeMemory(vInfoBuffer);
			}
		}
		if(0 < wcslen(vUserProfileDirectory))
		{
			char*		vDirectoryU = x_posix_strwtou(vUserProfileDirectory);
			if(vDirectoryU)
			{
				x_posix_strcpy(_static_system_current_user, vDirectoryU);
				x_posix_free(vDirectoryU);
			}
		}
#else
		x_posix_strcpy(_static_system_current_user, getenv("USER"));
#endif
	}
	return _static_system_current_user;
}

// Computer name
_XPOSIXAPI_ const char* x_system_host_name(void)
{
	static char	_static_system_host_name[_X_FILESYSTEM_MAX_NAME] = { 0 };
#if defined(XANADU_SYSTEM_WINDOWS)
	wchar_t		vHostName[_X_FILESYSTEM_MAX_NAME] = { 0 };
	DWORD		vLength = _X_FILESYSTEM_MAX_NAME;
	if(GetComputerNameW(vHostName, &vLength))
	{
		char*		vHostNameU = x_posix_strwtou(vHostName);
		if(vHostNameU)
		{
			x_posix_strcpy(_static_system_host_name, vHostNameU);
			x_posix_free(vHostNameU);
		}
	}
#else
	gethostname(_static_system_host_name, _X_FILESYSTEM_MAX_NAME);
#endif
	return _static_system_host_name;
}

// Gets the directory for the current user
_XPOSIXAPI_ const char* x_system_user_home(void)
{
	static char 	_static_system_user_home[X_FILESYSTEM_MAX_PATH] = {0};
	if(0 == x_posix_strlen(_static_system_user_home))
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		x_posix_strcpy(_static_system_user_home, "C:/Users/");
#endif
#if defined(XANADU_SYSTEM_LINUX)
		x_posix_strcpy(_static_system_user_home, "/home/");
#endif
#if defined(XANADU_SYSTEM_DARWIN)
		x_posix_strcpy(_static_system_user_home, "/Users/");
#endif
		x_posix_strcat(_static_system_user_home, x_system_current_user());
	}
	return _static_system_user_home;
}

// Get system cache directory
_XPOSIXAPI_ const char* x_system_cache_directory(void)
{
	static char	_staticCacheDirectory[X_FILESYSTEM_MAX_PATH] = {0};
	if(0 == x_posix_strlen(_staticCacheDirectory))
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		char*		vUtfDirectory = NULL;
		wchar_t 	vLongDirectory[X_FILESYSTEM_MAX_PATH] = { 0 };
		wchar_t		vTempDirectory[X_FILESYSTEM_MAX_PATH] = { 0 };
		if(GetTempPathW(X_FILESYSTEM_MAX_PATH, vTempDirectory))
		{
			GetLongPathNameW(vTempDirectory, vLongDirectory, X_FILESYSTEM_MAX_PATH);
			vUtfDirectory = x_posix_strwtou(vLongDirectory);
			if(vUtfDirectory)
			{
				x_posix_strcpy(_staticCacheDirectory, vUtfDirectory);
				x_posix_free(vUtfDirectory);
			}
		}
#else
		x_posix_strcpy(_staticCacheDirectory, "/tmp");
#endif
	}
	return _staticCacheDirectory;
}

// Get system config directory
_XPOSIXAPI_ const char* x_system_config_directory(void)
{
	static char	_static_system_config_directory[X_FILESYSTEM_MAX_PATH] = {0};
	if(0 == x_posix_strlen(_static_system_config_directory))
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		wchar_t		vLocalDirectory[X_FILESYSTEM_MAX_PATH] = { 0 };
		if(SHGetSpecialFolderPathW(GetDesktopWindow(), vLocalDirectory, CSIDL_LOCAL_APPDATA, FALSE))
		{
			x_string_replace_wchar_t(vLocalDirectory, L'\\', L'/');
			char*		vLocalDirectoryU = x_posix_strwtou(vLocalDirectory);
			if(vLocalDirectoryU)
			{
				x_posix_strcpy(_static_system_config_directory, vLocalDirectoryU);
				x_posix_free(vLocalDirectoryU);
			}
		}
		else
		{
			x_posix_strcpy(_static_system_config_directory, x_system_user_home());
			x_posix_strcat(_static_system_config_directory, "/AppData/Local");
		}
#else
		x_posix_strcpy(_static_system_config_directory, x_system_user_home());
		x_posix_strcat(_static_system_config_directory, "/.config");
		x_posix_mkdir(_static_system_config_directory, 0777);
#endif
	}
	return _static_system_config_directory;
}
