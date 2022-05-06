#ifndef			_XANADU_POSIX_TIME_H_
#define			_XANADU_POSIX_TIME_H_

#include <xanadu-posix/header.h>


#if defined(__cplusplus)
extern "C" {
#endif



// posix : srand
_XPOSIXAPI_ void __xcall__ x_posix_srand(unsigned int _Seed);

// posix : rand
_XPOSIXAPI_ int __xcall__ x_posix_rand(void);

// posix : time
_XPOSIXAPI_ time_t __xcall__ x_posix_time(time_t* _Seconds);

// posix : sleep
_XPOSIXAPI_ unsigned int __xcall__ x_posix_sleep(unsigned int _Seconds);

// posix : msleep
_XPOSIXAPI_ unsigned int __xcall__ x_posix_msleep(unsigned int _Milliseconds);

// posix : usleep
_XPOSIXAPI_ unsigned int __xcall__ x_posix_usleep(unsigned int _Microseconds);





// Gets the total number of second of the current system time
_XPOSIXAPI_ int64_t x_time_system_second();

// Gets the total number of millisecond of the current system time
_XPOSIXAPI_ int64_t x_time_system_millisecond();

// Gets the total number of microsecond of the current system time
_XPOSIXAPI_ int64_t x_time_system_microsecond();


#if defined(__cplusplus)
}
#endif


#endif
