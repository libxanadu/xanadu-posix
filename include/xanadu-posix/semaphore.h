#ifndef			_XANADU_POSIX_SEMAPHORE_H_
#define			_XANADU_POSIX_SEMAPHORE_H_

#include <xanadu-posix/header.h>
#include <xanadu-posix/mutex.h>
#if !defined(XANADU_SYSTEM_WINDOWS)
#include <semaphore.h>
#endif


#if defined(__cplusplus)
extern "C" {
#endif


// X-Series type definition : x_semaphore_t
#if defined(XANADU_SYSTEM_WINDOWS)
typedef				HANDLE				x_semaphore_t;
#else
typedef				sem_t				x_semaphore_t;
#endif


// semaphore open
_XPOSIXAPI_ x_semaphore_t* __xcall__ x_semaphore_open(const char* _Name, int _Flag, mode_t _Mode, unsigned int _Value);

// semaphore init
_XPOSIXAPI_ int __xcall__ x_semaphore_init(x_semaphore_t* _Handle, int _PShared, unsigned int _Value);

// semaphore getvalue
_XPOSIXAPI_ int __xcall__ x_semaphore_getvalue(x_semaphore_t* _Handle, int* _Value);

// semaphore post
_XPOSIXAPI_ int __xcall__ x_semaphore_post(x_semaphore_t* _Handle);

// semaphore wait
_XPOSIXAPI_ int __xcall__ x_semaphore_wait(x_semaphore_t* _Handle);

// semaphore trywait
_XPOSIXAPI_ int __xcall__ x_semaphore_trywait(x_semaphore_t* _Handle);

// semaphore wait_timeout
_XPOSIXAPI_ int __xcall__ x_semaphore_wait_timeout(x_semaphore_t* _Handle, unsigned int _TimeoutMS);

// semaphore unlink
_XPOSIXAPI_ int __xcall__ x_semaphore_unlink(const char* _Name);

// semaphore destroy
_XPOSIXAPI_ int __xcall__ x_semaphore_destroy(x_semaphore_t* _Handle);

// semaphore close
_XPOSIXAPI_ int __xcall__ x_semaphore_close(x_semaphore_t* _Handle);


#if defined(__cplusplus)
}
#endif


#endif
