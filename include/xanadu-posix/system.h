#ifndef			_XANADU_POSIX_SYSTEM_H_
#define			_XANADU_POSIX_SYSTEM_H_

#include <xanadu-posix/header.h>

XANADU_CXX_EXTERN_BEGIN



// posix : system
_XPOSIXAPI_ int __xcall__ x_posix_system(const char* _Command);

// posix : pause
_XPOSIXAPI_ int __xcall__ x_posix_pause(void);





// posix : wsystem
_XPOSIXAPI_ int __xcall__ x_posix_wsystem(const wchar_t* _Command);





// posix : gethostid
_XPOSIXAPI_ long __xcall__ x_posix_gethostid(void);

// posix : errno
_XPOSIXAPI_ int __xcall__ x_posix_errno(void);

// posix : seterrno
_XPOSIXAPI_ int __xcall__ x_posix_seterrno(int _Errno);

// posix : strerror
_XPOSIXAPI_ char* __xcall__ x_posix_strerror(int _Error);

// posix : abort
_XPOSIXAPI_ void __xcall__ x_posix_abort(void);

// posix : exit
_XPOSIXAPI_ void __xcall__ x_posix_exit(int _Status);





// posix : getenv
_XPOSIXAPI_ char* __xcall__ x_posix_getenv(const char* _Name);

// posix : setenv
_XPOSIXAPI_ int __xcall__ x_posix_setenv(const char* _Name, const char* _Value, int _Overwrite);

// posix : putenv
_XPOSIXAPI_ int __xcall__ x_posix_putenv(char* _String);

// posix : unsetenv
_XPOSIXAPI_ int __xcall__ x_posix_unsetenv(const char* _Name);





// posix : dlopen
_XPOSIXAPI_ void* __xcall__ x_posix_dlopen(const char* _Library, int _Mode);

// posix : dlsym
_XPOSIXAPI_ void* __xcall__ x_posix_dlsym(void* _Handle, const char* _ProcName);

// posix : dlclose
_XPOSIXAPI_ int __xcall__ x_posix_dlclose(void* _Handle);





// Sets the last-error code for the calling thread.
_XPOSIXAPI_ void __xcall__ x_system_set_last_error(int _Error);

// Gets the last-error code for the calling thread.
_XPOSIXAPI_ int __xcall__ x_system_get_last_error(void);



// Get operating system bits
_XPOSIXAPI_ size_t __xcall__ x_system_os_bits(void);



// Get the number of CPU cores
_XPOSIXAPI_ size_t __xcall__ x_system_cpu_core_count(void);

// Get the number of CPU threads
_XPOSIXAPI_ size_t __xcall__ x_system_cpu_thread_count(void);

// Get the size of cpu cache line
_XPOSIXAPI_ size_t __xcall__ x_system_cpu_cache_line_size(void);



// The name of the user who is now logged in
_XPOSIXAPI_ const char* __xcall__ x_system_current_user(void);

// Computer name
_XPOSIXAPI_ const char* __xcall__ x_system_host_name(void);

// Gets the directory for the current user
_XPOSIXAPI_ const char* __xcall__ x_system_user_home(void);

// Get system cache directory
_XPOSIXAPI_ const char* __xcall__ x_system_cache_directory(void);

// Get system config directory
_XPOSIXAPI_ const char* __xcall__ x_system_config_directory(void);



XANADU_CXX_EXTERN_END

#endif
