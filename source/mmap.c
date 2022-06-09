#include <xanadu-posix/mmap.h>
#if defined(XANADU_COMPILER_MSVC)
#include <io.h>
#else
#include <sys/mman.h>
#endif


#if !defined(FILE_MAP_EXECUTE)
#define FILE_MAP_EXECUTE    0x0020
#endif

#if defined(XANADU_COMPILER_MSVC)
static int __xcall__ __map_mman_error(DWORD _Error)
{
	if(_Error == 0)
	{
		return 0;
	}
	return (int)_Error;
}

static DWORD __xcall__ __map_mmap_prot_page(const int _Prot)
{
	DWORD		vProtect = 0;
	if(_Prot == PROT_NONE)
	{
		return vProtect;
	}
	if((_Prot & PROT_EXEC) != 0)
	{
		vProtect = ((_Prot & PROT_WRITE) != 0) ? PAGE_EXECUTE_READWRITE : PAGE_EXECUTE_READ;
	}
	else
	{
		vProtect = ((_Prot & PROT_WRITE) != 0) ? PAGE_READWRITE : PAGE_READONLY;
	}
	return vProtect;
}

static DWORD __xcall__ __map_mmap_prot_file(const int _Prot)
{
	DWORD		vDesiredAccess = 0;
	if(_Prot == PROT_NONE)
	{
		return vDesiredAccess;
	}
	if((_Prot & PROT_READ) != 0)
	{
		vDesiredAccess |= FILE_MAP_READ;
	}
	if((_Prot & PROT_WRITE) != 0)
	{
		vDesiredAccess |= FILE_MAP_WRITE;
	}
	if((_Prot & PROT_EXEC) != 0)
	{
		vDesiredAccess |= FILE_MAP_EXECUTE;
	}
	return vDesiredAccess;
}
#endif

// creates  a  new  mapping  in the virtual address space of the calling process.
_XPOSIXAPI_ void* __xcall__ x_posix_mmap(void* _Addr, size_t _Length, int _Prot, int _Flags, int _Fildes, off_t _Off)
{
#if defined(XANADU_COMPILER_MSVC)
	UNREFERENCED_PARAMETER(_Addr);

	HANDLE		vFileMap = INVALID_HANDLE_VALUE;
	HANDLE		vHandle = INVALID_HANDLE_VALUE;
	void*		vMap = MAP_FAILED;
	DWORD		vFileOffsetLow = (DWORD)_Off;
	DWORD		vFileOffsetHigh = 0;
	DWORD		vProtect = __map_mmap_prot_page(_Prot);
	DWORD		vDesiredAccess = __map_mmap_prot_file(_Prot);
	off_t		vMaxSize = _Off + (off_t)_Length;
	DWORD		vMaxSizeLow = (DWORD)vMaxSize;
	DWORD		vMaxSizeHigh = 0;

	errno = 0;

	if(_Length == 0 || (_Flags & MAP_FIXED) != 0/* Unsupported flag combinations */ || _Prot == PROT_EXEC/* Usupported protection combinations */)
	{
		errno = EINVAL;
		return MAP_FAILED;
	}

	vHandle = ((_Flags & MAP_ANONYMOUS) == 0) ? (HANDLE)_get_osfhandle(_Fildes) : INVALID_HANDLE_VALUE;

	if((_Flags & MAP_ANONYMOUS) == 0 && vHandle == INVALID_HANDLE_VALUE)
	{
		errno = EBADF;
		return MAP_FAILED;
	}

	vFileMap = CreateFileMappingA(vHandle, NULL, vProtect, vMaxSizeHigh, vMaxSizeLow, NULL);

	if(vFileMap == NULL)
	{
		errno = __map_mman_error(GetLastError());
		return MAP_FAILED;
	}

	vMap = MapViewOfFile(vFileMap, vDesiredAccess, vFileOffsetHigh, vFileOffsetLow, _Length);

	CloseHandle(vFileMap);

	if(vMap == NULL)
	{
		errno = __map_mman_error(GetLastError());
		return MAP_FAILED;
	}
	return vMap;
#else
	return mmap(_Addr, _Length, _Prot, _Flags, _Fildes, _Off);
#endif
}

// deletes the mappings for the specified address range
_XPOSIXAPI_ int __xcall__ x_posix_munmap(void* _Addr, size_t _Length)
{
#if defined(XANADU_COMPILER_MSVC)
	UNREFERENCED_PARAMETER(_Length);

	if(UnmapViewOfFile(_Addr))
	{
		return 0;
	}
	errno = __map_mman_error(GetLastError());
	return -1;
#else
	return munmap(_Addr, _Length);
#endif
}

// changes  protection  for the calling process's memory page(s) containing any part of the address range in the interval [addr, addr+len-1].
_XPOSIXAPI_ int __xcall__ x_posix_mprotect(void* _Addr, size_t _Length, int _Prot)
{
#if defined(XANADU_COMPILER_MSVC)
	DWORD		vNewProtect = __map_mmap_prot_page(_Prot);
	DWORD		vOldProtect = 0;

	if(VirtualProtect(_Addr, _Length, vNewProtect, &vOldProtect))
	{
		return 0;
	}
	errno = __map_mman_error(GetLastError());
	return -1;
#else
	return mprotect(_Addr, _Length, _Prot);
#endif
}

// flushes changes made to the in-core copy of a file that was mapped into memory using mmap back to the filesystem.
_XPOSIXAPI_ int __xcall__ x_posix_msync(void* _Addr, size_t _Length, int _Flags)
{
#if defined(XANADU_COMPILER_MSVC)
	UNREFERENCED_PARAMETER(_Flags);

	if(FlushViewOfFile(_Addr, _Length))
	{
		return 0;
	}
	errno = __map_mman_error(GetLastError());
	return -1;
#else
	return msync(_Addr, _Length, _Flags);
#endif
}

// lock part or all of the calling process's virtual address space into RAM
_XPOSIXAPI_ int __xcall__ x_posix_mlock(const void* _Addr, size_t _Length)
{
#if defined(XANADU_COMPILER_MSVC)
	if(VirtualLock((LPVOID)_Addr, _Length))
	{
		return 0;
	}
	errno = __map_mman_error(GetLastError());
	return -1;
#else
	return mlock(_Addr, _Length);
#endif
}

// unlocking part  or  all  of  the  calling process's  virtual address space
_XPOSIXAPI_ int __xcall__ x_posix_munlock(const void* _Addr, size_t _Length)
{
#if defined(XANADU_COMPILER_MSVC)
	if(VirtualUnlock((LPVOID)_Addr, _Length))
	{
		return 0;
	}
	errno = __map_mman_error(GetLastError());
	return -1;
#else
	return munlock(_Addr, _Length);
#endif
}
