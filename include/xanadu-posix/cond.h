#ifndef			_XANADU_POSIX_COND_H_
#define			_XANADU_POSIX_COND_H_

#include <xanadu-posix/header.h>
#include <xanadu-posix/mutex.h>
#if !defined(XANADU_SYSTEM_WINDOWS)
#include <signal.h>
#include <sys/time.h>
#endif


#if defined(__cplusplus)
extern "C" {
#endif


// xanadu系列类型定义 : x_cond_t
#if defined(XANADU_SYSTEM_WINDOWS)
typedef				HANDLE				x_cond_t;
#else
typedef				pthread_cond_t			x_cond_t;
#endif


// cond init
_XPOSIXAPI_ void x_cond_init(x_cond_t* _Cond);

// cond destroy
_XPOSIXAPI_ void x_cond_destroy(x_cond_t* _Cond);

// cond signal
_XPOSIXAPI_ int x_cond_signal(x_cond_t* _Cond);

// cond wait
_XPOSIXAPI_ int x_cond_wait(x_cond_t* _Cond, x_mutex_t* _Mutex);

// cond wait timeout
_XPOSIXAPI_ int x_cond_wait_timeout(x_cond_t* _Cond, x_mutex_t* _Mutex, unsigned int _TimeoutMS);


#if defined(__cplusplus)
}
#endif


#endif
