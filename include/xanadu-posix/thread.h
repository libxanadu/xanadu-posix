#ifndef			_XANADU_POSIX_THREAD_H_
#define			_XANADU_POSIX_THREAD_H_

#include <xanadu-posix/header.h>
#if !defined(XANADU_SYSTEM_WINDOWS)
#include <pthread.h>
#endif


#if defined(__cplusplus)
extern "C" {
#endif


// X-Series type definition : x_thread_t
#if defined(XANADU_SYSTEM_WINDOWS)
typedef				HANDLE				x_thread_t;
#else
typedef				pthread_t			x_thread_t;
#endif
#if defined(XANADU_SYSTEM_LINUX)
#define _X_THREAD_INVALID_HANDLE				((x_thread_t)(0))
#else
#define _X_THREAD_INVALID_HANDLE				((x_thread_t)(NULL))
#endif
typedef void(*x_thread_function_t)(void* _Param);



// posix : gettid
_XPOSIXAPI_ pid_t __xcall__ x_posix_gettid(void);





/// Create a thread
/// \param _Address : A pointer to the application-defined function to be executed by the thread. This pointer represents the starting address of the thread.
/// \param _Param : A pointer to a variable to be passed to the thread.
/// \return : If the function succeeds, the return value is a handle to the new thread.
/// \return : If the function fails, the return value is NULL.
_XPOSIXAPI_ x_thread_t x_thread_create(x_thread_function_t _Address, void* _Param);

/// It is separated from the thread. After the thread ends, the resources are automatically recycled.
/// \param _Thread : Thread handle to detach
_XPOSIXAPI_ void x_thread_detach(x_thread_t _Thread);

/// Gets the ID of the thread itself.
/// \return : Thread ID
_XPOSIXAPI_ x_thread_t x_thread_self();

/// Wait for the end of a thread
/// \param _Thread : Thread ID
/// \return : 0 represents success. If it fails, the error number is returned.
_XPOSIXAPI_ int x_thread_join(x_thread_t _Thread);

/// Check whether the thread is alive
/// \param _Thread : Thread ID
/// \return : 0 means survival. If it fails, the error number is returned.
_XPOSIXAPI_ int x_thread_alive(x_thread_t _Thread);

/// Kill the specified thread
/// \param _Thread : Thread ID
/// \return : 0 represents success. If it fails, the error number is returned.
_XPOSIXAPI_ int x_thread_kill(x_thread_t _Thread);


#if defined(__cplusplus)
}
#endif


#endif
