#ifndef			_XANADU_POSIX_MUTEX_H_
#define			_XANADU_POSIX_MUTEX_H_

#include <xanadu-posix/header.h>
#if !defined(XANADU_SYSTEM_WINDOWS)
#include <pthread.h>
#endif


XANADU_CXX_EXTERN_BEGIN


// X-Series type definition : x_mutex_t
#if defined(XANADU_SYSTEM_WINDOWS)
typedef				CRITICAL_SECTION		x_mutex_t;
#else
typedef				pthread_mutex_t			x_mutex_t;
#endif


// mutex init
_XPOSIXAPI_ void __xcall__ x_mutex_init(x_mutex_t* _Mutex);

// mutex destroy
_XPOSIXAPI_ void __xcall__ x_mutex_destroy(x_mutex_t* _Mutex);

// mutex lock
_XPOSIXAPI_ void __xcall__ x_mutex_lock(x_mutex_t* _Mutex);

// mutex trylock
_XPOSIXAPI_ int __xcall__ x_mutex_trylock(x_mutex_t* _Mutex);

// mutex unlock
_XPOSIXAPI_ void __xcall__ x_mutex_unlock(x_mutex_t* _Mutex);


XANADU_CXX_EXTERN_END


#endif
