#include <xanadu-posix/thread.h>
#include <sys/types.h>
#if !defined(XANADU_SYSTEM_WINDOWS)
#include <unistd.h>
#include <sys/syscall.h>
#include <signal.h>
#include <errno.h>
#endif



// posix : gettid
_XPOSIXAPI_ pid_t __xcall__ x_posix_gettid(void)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return (pid_t)GetCurrentThreadId();
#endif
#if defined(XANADU_SYSTEM_LINUX)
	// return gettid();
	return (pid_t)syscall(SYS_gettid);
#endif
#if defined(XANADU_SYSTEM_DARWIN)
	uint64_t	vThreadID = 0;
	pthread_threadid_np(NULL, &vThreadID);
	return (pid_t)vThreadID;
#endif
}





/// Create a thread
_XPOSIXAPI_ x_thread_t __xcall__ x_thread_create(x_thread_function_t _Address, void* _Param)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)_Address, _Param, 0, 0);
#else
	typedef void*(*LPTHREAD_START_ROUTINE)(void*);
	pthread_t	vHandle = 0;
	pthread_create(&vHandle, NULL, (LPTHREAD_START_ROUTINE)_Address, _Param);
	return vHandle;
#endif
}

/// Thread detach
_XPOSIXAPI_ void __xcall__ x_thread_detach(x_thread_t _Thread)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_Thread == X_THREAD_INVALID_HANDLE)
	{
		return;
	}
#endif
#if defined(XANADU_SYSTEM_WINDOWS)
	CloseHandle(_Thread);
#else
	pthread_detach(_Thread);
#endif
}

/// Gets the ID of the thread itself.
_XPOSIXAPI_ x_thread_t __xcall__ x_thread_self()
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return GetCurrentThread();
#else
	return pthread_self();
#endif
}

/// Wait for the end of a thread
_XPOSIXAPI_ int __xcall__ x_thread_join(x_thread_t _Thread)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_Thread == X_THREAD_INVALID_HANDLE)
	{
		return EINVAL;
	}
#endif
#if defined(XANADU_SYSTEM_WINDOWS)
	return (int)WaitForSingleObject(_Thread, INFINITE);
#else
	return pthread_join(_Thread, NULL);
#endif
}

/// Check whether the thread is alive
_XPOSIXAPI_ int __xcall__ x_thread_alive(x_thread_t _Thread)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_Thread == X_THREAD_INVALID_HANDLE)
	{
		return EINVAL;
	}
#endif
#if defined(XANADU_SYSTEM_WINDOWS)
	if(WaitForSingleObject(_Thread, 0) == WAIT_TIMEOUT)
	{
		return 0;
	}
	else
	{
		return (int)GetLastError();
	}
#else
	return pthread_kill(_Thread, 0);
#endif
}

/// Kill the specified thread
_XPOSIXAPI_ int __xcall__ x_thread_kill(x_thread_t _Thread)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_Thread == X_THREAD_INVALID_HANDLE)
	{
		return EINVAL;
	}
#endif
#if defined(XANADU_SYSTEM_WINDOWS)
	if(TerminateThread(_Thread, 0))
	{
		return 0;
	}
	else
	{
		return (int)GetLastError();
	}
#else
	return pthread_kill(_Thread, 9);
#endif
}
