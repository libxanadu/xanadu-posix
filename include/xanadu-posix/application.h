#ifndef			_XANADU_POSIX_APPLICATION_H_
#define			_XANADU_POSIX_APPLICATION_H_

#include <xanadu-posix/header.h>

XANADU_CXX_EXTERN_BEGIN



// Gets the path of the current application
_XPOSIXAPI_ const char* __xcall__ x_application_native_path();

// Gets the directory of the current application
_XPOSIXAPI_ const char* __xcall__ x_application_native_directory();

// Gets the name of the current application
_XPOSIXAPI_ const char* __xcall__ x_application_native_name();





// Gets the cache directory of the current application
_XPOSIXAPI_ const char* __xcall__ x_application_cache_directory();

// Gets the config directory of the current application
_XPOSIXAPI_ const char* __xcall__ x_application_config_directory();



XANADU_CXX_EXTERN_END

#endif
