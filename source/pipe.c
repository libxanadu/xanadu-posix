#include <xanadu-posix/pipe.h>
#if !defined(XANADU_SYSTEM_WINDOWS)
#include <xanadu-posix/filesystem.h>
#endif
#include <xanadu-posix/system.h>



// Create a pair of anonymous pipes
_XPOSIXAPI_ int __xcall__ x_pipe_create(x_pipe_t* _Read, x_pipe_t* _Write)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	SECURITY_ATTRIBUTES	sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (CreatePipe(_Read, _Write, &sa, 0))
	{
		return 0;
	}
	return -1;
#else
	int		vHandle[2] = {0};
	int 		vError = pipe(vHandle);
	if(vError == 0 && _Read && _Write)
	{
		*_Read = vHandle[0];
		*_Write = vHandle[1];
	}
	return vError;
#endif
}

// write data to pipe
_XPOSIXAPI_ int __xcall__ x_pipe_write(x_pipe_t _Handle, const void* _Bytes, x_size_t _Size)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	DWORD 		vSyncSize;
	if(WriteFile(_Handle, _Bytes, _Size, &vSyncSize, NULL))
	{
		return (int)vSyncSize;
	}
	return -1;
#else
	return x_posix_write(_Handle, _Bytes, _Size);
#endif
}

// read data from pipe
_XPOSIXAPI_ int __xcall__ x_pipe_read(x_pipe_t _Handle, void* _Bytes, x_size_t _Size)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	DWORD 		vSyncSize;
	if(ReadFile(_Handle, _Bytes, _Size, &vSyncSize, NULL))
	{
		return (int)vSyncSize;
	}
	return -1;
#else
	return x_posix_read(_Handle, _Bytes, _Size);
#endif
}

// Close a fifo.
_XPOSIXAPI_ int __xcall__ x_pipe_close(x_pipe_t _Handle)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return CloseHandle(_Handle) ? 0 : x_posix_errno();
#else
	return x_posix_close(_Handle);
#endif
}
