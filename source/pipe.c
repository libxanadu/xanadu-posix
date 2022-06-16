#include <xanadu-posix/pipe.h>
#include <xanadu-posix/filesystem.h>
#include <xanadu-posix/system.h>



// Create a pair of anonymous pipes
_XPOSIXAPI_ int __xcall__ x_pipe_create(x_pipe_handle* _Read, x_pipe_handle* _Write)
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





// creates a new fifo file with name path.
_XPOSIXAPI_ x_pipe_handle __xcall__ x_fifo_create(const char* _Path, mode_t _Mode)
{
	x_pipe_handle		vHandle = X_INVALID_HANDLE;
#if defined(XANADU_SYSTEM_WINDOWS)
	XANADU_UNUSED(_Mode);
	vHandle = CreateNamedPipeA(_Path, PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, 1, 0, 0, 1000, NULL);
	if (vHandle == X_INVALID_HANDLE)
	{
		return X_INVALID_HANDLE;
	}
	if (ConnectNamedPipe(vHandle, NULL) == FALSE)
	{
		CloseHandle(vHandle);
		return X_INVALID_HANDLE;
	}
#else
	vHandle = mkfifo(_Path, _Mode);
#endif
	return vHandle;
}

// connect to a named pipe that already exists
_XPOSIXAPI_ x_pipe_handle __xcall__ x_fifo_connect(const char* _Path, int _Flag)
{
	x_pipe_handle		vHandle = X_INVALID_HANDLE;
#if defined(XANADU_SYSTEM_WINDOWS)
	XANADU_UNUSED(_Flag);
	vHandle = CreateFileA(_Path, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
#else
	vHandle = x_posix_open(_Path, _Flag);
#endif
	return vHandle;
}





// write data to pipe
_XPOSIXAPI_ int __xcall__ x_pipe_write(x_pipe_handle _Handle, const void* _Bytes, x_size_t _Size)
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
_XPOSIXAPI_ int __xcall__ x_pipe_read(x_pipe_handle _Handle, void* _Bytes, x_size_t _Size)
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
_XPOSIXAPI_ int __xcall__ x_pipe_close(x_pipe_handle _Handle)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return CloseHandle(_Handle) ? 0 : x_posix_errno();
#else
	return x_posix_close(_Handle);
#endif
}
