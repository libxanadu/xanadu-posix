#ifndef			_XANADU_POSIX_PIPE_H_
#define			_XANADU_POSIX_PIPE_H_

#include <xanadu-posix/header.h>


XANADU_CXX_EXTERN_BEGIN



// X-Series type definition : x_pipe_t
#if defined(XANADU_SYSTEM_WINDOWS)
typedef				HANDLE 				x_pipe_handle;
#else
typedef				int				x_pipe_handle;
#endif



// Create a pair of anonymous pipes
_XPOSIXAPI_ int __xcall__ x_pipe_create(x_pipe_handle* _Read, x_pipe_handle* _Write);





// creates a new fifo file with name path.
_XPOSIXAPI_ x_pipe_handle __xcall__ x_fifo_create(const char* _Path, mode_t _Mode);

// connect to a named pipe that already exists
_XPOSIXAPI_ x_pipe_handle __xcall__ x_fifo_connect(const char* _Path, int _Flag);





// write data to pipe
_XPOSIXAPI_ int __xcall__ x_pipe_write(x_pipe_handle _Handle, const void* _Bytes, x_size_t _Size);

// read data from pipe
_XPOSIXAPI_ int __xcall__ x_pipe_read(x_pipe_handle _Handle, void* _Bytes, x_size_t _Size);

// close a fifo.
_XPOSIXAPI_ int __xcall__ x_pipe_close(x_pipe_handle _Handle);



XANADU_CXX_EXTERN_END

#endif
