#include <xanadu-posix/mutex.h>



// mutex init
_XPOSIXAPI_ void __xcall__ x_mutex_init(x_mutex_t* _Mutex)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	InitializeCriticalSection(_Mutex);
#else
	pthread_mutex_init(_Mutex, NULL);
#endif
}

// mutex destroy
_XPOSIXAPI_ void __xcall__ x_mutex_destroy(x_mutex_t* _Mutex)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	DeleteCriticalSection(_Mutex);
#else
	pthread_mutex_destroy(_Mutex);
#endif
}

// mutex lock
_XPOSIXAPI_ void __xcall__ x_mutex_lock(x_mutex_t* _Mutex)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	EnterCriticalSection(_Mutex);
#else
	pthread_mutex_lock(_Mutex);
#endif
}

// mutex trylock
_XPOSIXAPI_ int __xcall__ x_mutex_trylock(x_mutex_t* _Mutex)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	if(TryEnterCriticalSection(_Mutex))
	{
		return 0;
	}
	else
	{
		return (int)GetLastError();
	}
#else
	return pthread_mutex_trylock(_Mutex);
#endif
}

// mutex unlock
_XPOSIXAPI_ void __xcall__ x_mutex_unlock(x_mutex_t* _Mutex)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	LeaveCriticalSection(_Mutex);
#else
	pthread_mutex_unlock(_Mutex);
#endif
}
