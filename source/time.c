#include <xanadu-posix/time.h>
#if !defined(XANADU_SYSTEM_ANDROID)
#include <sys/timeb.h>
#endif
#if !defined(XANADU_SYSTEM_WINDOWS)
#include <sys/time.h>
#include <time.h>
#endif



// posix : srand
_XPOSIXAPI_ void __xcall__ x_posix_srand(unsigned int _Seed)
{
	srand(_Seed);
}

// posix : rand
_XPOSIXAPI_ int __xcall__ x_posix_rand(void)
{
	return rand();
}

// posix : time
_XPOSIXAPI_ time_t __xcall__ x_posix_time(time_t* _Seconds)
{
	return time(_Seconds);
}

// posix : sleep
_XPOSIXAPI_ unsigned int __xcall__ x_posix_sleep(unsigned int _Seconds)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return x_posix_msleep(_Seconds * 1000);
#else
	return sleep(_Seconds);
#endif
}

// posix : msleep
_XPOSIXAPI_ unsigned int __xcall__ x_posix_msleep(unsigned int _Milliseconds)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	Sleep(_Milliseconds);
	return 0;
#else
	return usleep(_Milliseconds * 1000) / 1000;
#endif
}

// posix : usleep
_XPOSIXAPI_ unsigned int __xcall__ x_posix_usleep(unsigned int _Microseconds)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	LARGE_INTEGER	vInterval;
	vInterval.QuadPart = -(10 * (int64_t)(_Microseconds));

	HANDLE 		vTimer = CreateWaitableTimerA(NULL, TRUE, NULL);
	SetWaitableTimer(vTimer, &vInterval, 0, NULL, NULL, 0);
	WaitForSingleObject(vTimer, INFINITE);
	CloseHandle(vTimer);
	return 0;
#else
	return usleep(_Microseconds);
#endif
}





// Gets the total number of second of the current system time
_XPOSIXAPI_ x_time_type __xcall__ x_time_system_second()
{
	x_time_type		vSecond = 0;
#if defined(XANADU_SYSTEM_WINDOWS)
	struct timeb		vRawtime;
	ftime(&vRawtime);
	vSecond = vRawtime.time;
#else
	struct timespec		vTimeSpec;
	clock_gettime(CLOCK_REALTIME, &vTimeSpec);
	vSecond = vTimeSpec.tv_sec;
#endif
	return vSecond;
}

// Gets the total number of millisecond of the current system time
_XPOSIXAPI_ x_time_type __xcall__ x_time_system_millisecond()
{
	x_time_type		vMillisecond = 0;
#if defined(XANADU_SYSTEM_WINDOWS)
	struct timeb		vRawtime;
	ftime(&vRawtime);
	vMillisecond = vRawtime.time * 1000LL + vRawtime.millitm;
#else
	struct timespec		vTimeSpec;
	clock_gettime(CLOCK_REALTIME, &vTimeSpec);
	vMillisecond = vTimeSpec.tv_sec * 1000;
	vMillisecond += (vTimeSpec.tv_nsec / 1000000);
#endif
	return vMillisecond;
}

// Gets the total number of microsecond of the current system time
_XPOSIXAPI_ x_time_type __xcall__ x_time_system_microsecond()
{
	x_time_type		vMicrosecond = 0;
#if defined(XANADU_SYSTEM_WINDOWS)
	// Time from 0:0:0:000 on January 1, 1601 to 0:0:0:000 on January 1, 1970 (unit: 100ns)
#define			TIME_OFFSET_1601_TO_1970   (116444736000000000LL)

	FILETIME		vFileTime;
	LARGE_INTEGER		vLarge;
	GetSystemTimeAsFileTime(&vFileTime);
	vLarge.LowPart = vFileTime.dwLowDateTime;
	vLarge.HighPart = (LONG)vFileTime.dwHighDateTime;
	// Microseconds from 0:0:0:000 on January 1, 1970 (UTC time)
	vMicrosecond = (vLarge.QuadPart - TIME_OFFSET_1601_TO_1970) / 10;
#else
	struct timespec		vTimeSpec;
	clock_gettime(CLOCK_REALTIME, &vTimeSpec);
	vMicrosecond = vTimeSpec.tv_sec * 1000000;
	vMicrosecond += (vTimeSpec.tv_nsec / 1000);
#endif
	return vMicrosecond;
}
