#ifndef			_XANADU_POSIX_PROCESS_H_
#define			_XANADU_POSIX_PROCESS_H_

#include <xanadu-posix/header.h>


#if defined(__cplusplus)
extern "C" {
#endif


// X-Series type definition : x_process_stream_t
#if defined(XANADU_SYSTEM_WINDOWS)
typedef				HANDLE 				x_process_stream_t;
typedef				DWORD 				x_process_id_t;
#else
typedef				void*				x_process_stream_t;
typedef				pid_t 				x_process_id_t;
#endif

// Maximum allowed path length
#define 			_X_PROCESS_MAX_NAME		256
#define 			_X_PROCESS_MAX_PATH		4096

// process data type
typedef struct _xanadu_process_data
{
	char 			name[_X_PROCESS_MAX_NAME];
	char 			path[_X_PROCESS_MAX_PATH];
	x_process_id_t		id;
}x_process_data_t;



// posix : chdir
_XPOSIXAPI_ int __xcall__ x_posix_chdir(const char* _Directory);

// posix : getcwd
_XPOSIXAPI_ char* __xcall__ x_posix_getcwd(char* _Directory, size_t _Size);

// posix : popen
_XPOSIXAPI_ FILE* __xcall__ x_posix_popen(const char* _Command, const char* _Mode);

// posix : pclose
_XPOSIXAPI_ int __xcall__ x_posix_pclose(FILE* _Stream);

// posix : perror
_XPOSIXAPI_ void __xcall__ x_posix_perror(const char* _ErrorMessage);

// posix : getpid
_XPOSIXAPI_ pid_t __xcall__ x_posix_getpid(void);

// posix : getppid
_XPOSIXAPI_ pid_t __xcall__ x_posix_getppid(void);

// posix : kill
_XPOSIXAPI_ int __xcall__ x_posix_kill(pid_t _Pid, int _Sig);





// This function returns the process identifier of the calling process.
_XPOSIXAPI_ x_process_id_t x_process_get_id();

// Enable process privilege (Windows only)
_XPOSIXAPI_ int x_process_enable_privilege();

// Kill the process with the specified process id
_XPOSIXAPI_ int x_process_kill_id(x_process_id_t _ProcessID, int _Signal);

// Kill the process with the specified process name
_XPOSIXAPI_ int x_process_kill_name(const char* _ProcessName, int _Signal);

// Get data according to process ID
_XPOSIXAPI_ int x_process_get_data_by_id(x_process_id_t _ProcessID, x_process_data_t* _ProcessData);



// Process lookup start
_XPOSIXAPI_ x_process_stream_t x_process_find_first(x_process_data_t* _ProcessData);

// Find the next process. If successful returns 0, Failure returned - 1.
_XPOSIXAPI_ int x_process_find_next(x_process_stream_t _Handle, x_process_data_t* _ProcessData);

// This function closes the specified search handle. If successful returns 0, Failure returned - 1.
_XPOSIXAPI_ int x_process_find_close(x_process_stream_t _Handle);


#if defined(__cplusplus)
}
#endif


#endif
