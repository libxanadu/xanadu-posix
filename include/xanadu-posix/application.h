#ifndef			_XANADU_POSIX_APPLICATION_H_
#define			_XANADU_POSIX_APPLICATION_H_

#include <xanadu-posix/header.h>


#if defined(__cplusplus)
extern "C" {
#endif


// Gets the path of the current application
_XPOSIXAPI_ const char* x_application_native_path();

// Gets the directory of the current application
_XPOSIXAPI_ const char* x_application_native_directory();

// Gets the name of the current application
_XPOSIXAPI_ const char* x_application_native_name();



// Gets the cache directory of the current application
_XPOSIXAPI_ const char* x_application_cache_directory();

// Gets the config directory of the current application
_XPOSIXAPI_ const char* x_application_config_directory();


#if defined(__cplusplus)
}
#endif

#endif
