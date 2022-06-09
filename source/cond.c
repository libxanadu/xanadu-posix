#include <xanadu-posix/cond.h>



// cond init
_XPOSIXAPI_ void __xcall__ x_cond_init(x_cond_t* _Cond)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_Cond == NULL)
	{
		return;
	}
#endif
#if defined(XANADU_SYSTEM_WINDOWS)
	*_Cond = CreateSemaphoreA(NULL, 0, 32767, NULL);
#else
	pthread_cond_init(_Cond, NULL);
#endif
}

// cond destroy
_XPOSIXAPI_ void __xcall__ x_cond_destroy(x_cond_t* _Cond)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_Cond == NULL)
	{
		return;
	}
#endif
#if defined(XANADU_SYSTEM_WINDOWS)
	CloseHandle(*_Cond);
#else
	pthread_cond_destroy(_Cond);
#endif
}

// cond signal
_XPOSIXAPI_ int __xcall__ x_cond_signal(x_cond_t* _Cond)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_Cond == NULL)
	{
		return -1;
	}
#endif
#if defined(XANADU_SYSTEM_WINDOWS)
	int result = 0;
	if (!ReleaseSemaphore(*_Cond, 1, NULL)) {
		result = -1;
	}
	return result;
#else
	return pthread_cond_signal(_Cond);
#endif
}

// cond wait
_XPOSIXAPI_ int __xcall__ x_cond_wait(x_cond_t* _Cond, x_mutex_t* _Mutex)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_Cond == NULL)
	{
		return -1;
	}
#endif
#if defined(XANADU_SYSTEM_WINDOWS)
	x_mutex_unlock(_Mutex);
	DWORD		res = WaitForSingleObject(*_Cond, INFINITE);
	switch (res)
	{
		case WAIT_OBJECT_0:
			return 0;
		default:
			return -1;
	}
#else
	return pthread_cond_wait(_Cond, _Mutex);
#endif
}

// cond wait timeout
_XPOSIXAPI_ int __xcall__ x_cond_wait_timeout(x_cond_t* _Cond, x_mutex_t* _Mutex, unsigned int _TimeoutMS)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_Cond == NULL)
	{
		return -1;
	}
#endif
#if defined(XANADU_SYSTEM_WINDOWS)
	x_mutex_unlock(_Mutex);
	DWORD res = WaitForSingleObject(*_Cond, _TimeoutMS);
	switch (res) {
		case WAIT_OBJECT_0:
		case WAIT_TIMEOUT:
			return 0;
		default:
			return -1;
	}
#else
	struct timespec		vTS;
	struct timeval		vNow;
	gettimeofday(&vNow, NULL);

	vTS.tv_sec = vNow.tv_sec + _TimeoutMS / 1000;
	vTS.tv_nsec = vNow.tv_usec * 1000 + 1000 * 1000 * (_TimeoutMS % 1000);
	vTS.tv_sec += vTS.tv_nsec / (1000 * 1000 * 1000);
	vTS.tv_nsec %= (1000 * 1000 * 1000);

	return pthread_cond_timedwait(_Cond, _Mutex, &vTS);
#endif
}
