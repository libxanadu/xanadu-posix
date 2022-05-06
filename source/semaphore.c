#include <xanadu-posix/semaphore.h>
#include <xanadu-posix/memory.h>
#include <xanadu-posix/string.h>
#include <xanadu-posix/system.h>
#include <xanadu-posix/time.h>
#include <fcntl.h>


// semaphore open
_XPOSIXAPI_ x_semaphore_t* __xcall__ x_semaphore_open(const char* _Name, int _Flag, mode_t _Mode, unsigned int _Value)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	const size_t 	vNameMaxSize = 512;
	size_t 		vNameLength = x_posix_strlen(_Name);
	char		buffer[512] = {0};
	x_semaphore_t	vHandle = NULL;

	XANADU_UNUSED(_Mode);

	if (vNameLength > vNameMaxSize - 8 || vNameLength == 0)
	{
		errno = EINVAL;
		return NULL;
	}

	x_posix_memmove(buffer, "Global\\", 7);
	x_posix_memmove(buffer + 7, _Name, vNameLength);

	vHandle = CreateSemaphoreA(NULL, (LONG)_Value, 0x7FFFFFFF, buffer);
	if (vHandle == NULL)
	{
		switch (GetLastError())
		{
			case ERROR_ACCESS_DENIED:
				x_posix_seterrno(EACCES);
				break;
			case ERROR_INVALID_HANDLE:
				x_posix_seterrno(ENOENT);
				break;
			default:
				x_posix_seterrno(ENOSPC);
				break;
		}
		return NULL;
	}
	else
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			if ((_Flag & O_CREAT) && (_Flag & O_EXCL)) {
				CloseHandle(vHandle);
				x_posix_seterrno(EEXIST);
				return NULL;
			}
			return vHandle;
		}
		else
		{
			if (!(_Flag & O_CREAT))
			{
				x_posix_seterrno(ENOENT);
				return NULL;
			}
		}
	}
	return vHandle;
#else
	return sem_open(_Name, _Flag, _Mode, _Value);
#endif
}

// semaphore init
_XPOSIXAPI_ int __xcall__ x_semaphore_init(x_semaphore_t* _Handle, int _PShared, unsigned int _Value)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	XANADU_UNUSED(_PShared);
	HANDLE 		vSemaphore = CreateSemaphoreA(NULL, (long)_Value, 0x7FFFFFFF, NULL);
	if(vSemaphore)
	{
		*_Handle = vSemaphore;
		return 0;
	}
	return (int)GetLastError();
#else
#if defined(XANADU_SYSTEM_DARWIN)
	XANADU_UNUSED(_PShared);
	char 		vName[512] = {0};
	sprintf(vName, "xanadu_semaphore_%p", (void*)vName);
	x_semaphore_t*	vHandle = x_semaphore_open(vName, O_CREAT, S_IRUSR | S_IWUSR, _Value);
	if(vHandle)
	{
		x_posix_memcpy(_Handle, vHandle, sizeof(x_semaphore_t));
		return 0;
	}
	return x_posix_errno();
#else
	return sem_init(_Handle, _PShared, _Value);
#endif
#endif
}

// semaphore getvalue
_XPOSIXAPI_ int __xcall__ x_semaphore_getvalue(x_semaphore_t* _Handle, int* _Value)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	LONG		vPrevious = 0;
	switch (WaitForSingleObject(_Handle, 0))
	{
		case WAIT_OBJECT_0:
			if (ReleaseSemaphore(_Handle, 1, &vPrevious) == FALSE)
			{
				*_Value = vPrevious + 1;
				return 0;
			}
			return (int)GetLastError();
		case WAIT_TIMEOUT:
			*_Value = 0;
			return 0;

		default:
			return (int)GetLastError();
	}
#else
#if defined(XANADU_SYSTEM_DARWIN)
	// Untested, compiled only
	*_Value = *_Handle;
	return 0;
#else
	return sem_getvalue(_Handle, _Value);
#endif
#endif
}

// semaphore post
_XPOSIXAPI_ int __xcall__ x_semaphore_post(x_semaphore_t* _Handle)
{

#if defined(XANADU_SYSTEM_WINDOWS)
	DWORD		vStatus = ReleaseSemaphore(_Handle, 1, NULL);
	if(vStatus)
	{
		return 0;
	}
	return (int)GetLastError();
#else
	return sem_post(_Handle);
#endif
}

// semaphore wait
_XPOSIXAPI_ int __xcall__ x_semaphore_wait(x_semaphore_t* _Handle)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	DWORD		vStatus = WaitForSingleObject(_Handle, INFINITE);
	if(WAIT_OBJECT_0 == vStatus)
	{
		return 0;
	}
	return (int)GetLastError();
#else
	return sem_wait(_Handle);
#endif
}

// semaphore trywait
_XPOSIXAPI_ int __xcall__ x_semaphore_trywait(x_semaphore_t* _Handle)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	DWORD		vStatus = WaitForSingleObject(_Handle, 0);
	if(WAIT_OBJECT_0 == vStatus)
	{
		return 0;
	}
	return (int)GetLastError();
#else
	return sem_trywait(_Handle);
#endif
}

// semaphore wait_timeout
_XPOSIXAPI_ int __xcall__ x_semaphore_wait_timeout(x_semaphore_t* _Handle, unsigned int _TimeoutMS)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	DWORD		vStatus = WaitForSingleObject(_Handle, _TimeoutMS);
	if(WAIT_OBJECT_0 == vStatus)
	{
		return 0;
	}
	return (int)GetLastError();
#else
#if defined(XANADU_SYSTEM_DARWIN)
	unsigned int		vSleepMS = 0;
	while(vSleepMS < _TimeoutMS)
	{
		if(0 == sem_trywait(_Handle))
		{
			return 0;
		}
		x_posix_msleep(100);
		vSleepMS += 100;
	}
	return x_posix_errno();
#else
	struct timespec		vTimeSpec;
	clock_gettime(CLOCK_REALTIME, &vTimeSpec);
	vTimeSpec.tv_sec += (_TimeoutMS / 1000);
	vTimeSpec.tv_nsec += ((long)_TimeoutMS) * 1000 * 1000;
	return sem_timedwait(_Handle, &vTimeSpec);
#endif
#endif
}

// semaphore unlink
_XPOSIXAPI_ int __xcall__ x_semaphore_unlink(const char* _Name)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	XANADU_UNUSED(_Name);
	return 0;
#else
	return sem_unlink(_Name);
#endif
}

// semaphore destroy
_XPOSIXAPI_ int __xcall__ x_semaphore_destroy(x_semaphore_t* _Handle)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	if (CloseHandle(_Handle) == 0)
	{
		return (int)GetLastError();
	}
	return 0;
#else
#if defined(XANADU_SYSTEM_DARWIN)
	return sem_close(_Handle);
#else
	return sem_destroy(_Handle);
#endif
#endif
}

// semaphore close
_XPOSIXAPI_ int __xcall__ x_semaphore_close(x_semaphore_t* _Handle)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return x_semaphore_destroy(_Handle);
#else
	return sem_close(_Handle);
#endif
}
