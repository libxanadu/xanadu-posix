#ifndef			_XANADU_POSIX_PIPE_H_
#define			_XANADU_POSIX_PIPE_H_

#include <xanadu-posix/header.h>

XANADU_CXX_EXTERN_BEGIN



// X-Series type definition : x_pipe_t
#if defined(XANADU_SYSTEM_WINDOWS)
typedef				HANDLE 				x_pipe_t;
#else
typedef				int				x_pipe_t;
#endif



// Create a pair of anonymous pipes
_XPOSIXAPI_ int __xcall__ x_pipe_create(x_pipe_t* _Read, x_pipe_t* _Write);

// write data to pipe
_XPOSIXAPI_ int __xcall__ x_pipe_write(x_pipe_t _Handle, const void* _Bytes, x_size_t _Size);

// read data from pipe
_XPOSIXAPI_ int __xcall__ x_pipe_read(x_pipe_t _Handle, void* _Bytes, x_size_t _Size);

// close a fifo.
_XPOSIXAPI_ int __xcall__ x_pipe_close(x_pipe_t _Handle);



XANADU_CXX_EXTERN_END

#endif
