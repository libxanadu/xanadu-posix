#ifndef			_XANADU_POSIX_STREAM_H_
#define			_XANADU_POSIX_STREAM_H_

#include <xanadu-posix/header.h>

XANADU_CXX_EXTERN_BEGIN



// posix : printf
_XPOSIXAPI_ int __xcall__ x_posix_printf(const char* _Format, ...);

// posix : vprintf
_XPOSIXAPI_ int __xcall__ x_posix_vprintf(const char* _Format, va_list _ArgList);

// posix : sprintf
_XPOSIXAPI_ int __xcall__ x_posix_sprintf(char* _Buffer, const char* _Format, ...);

// posix : vsprintf
_XPOSIXAPI_ int __xcall__ x_posix_vsprintf(char* _Buffer, const char* _Format, va_list _ArgList);

// posix : snprintf
_XPOSIXAPI_ int __xcall__ x_posix_snprintf(char* _Buffer, size_t _BufferCount, const char* _Format, ...);

// posix : vsnprintf
_XPOSIXAPI_ int __xcall__ x_posix_vsnprintf(char* _Buffer, size_t _BufferCount, const char* _Format, va_list _ArgList);

// posix : fprintf
_XPOSIXAPI_ int __xcall__ x_posix_fprintf(FILE* _Stream, const char* _Format, ...);

// posix : vfprintf
_XPOSIXAPI_ int __xcall__ x_posix_vfprintf(FILE* _Stream, const char* _Format, va_list _ArgList);

// posix : asprintf
_XPOSIXAPI_ int __xcall__ x_posix_asprintf(char** _Buffer, const char* _Format, ...);

// posix : vasprintf
_XPOSIXAPI_ int __xcall__ x_posix_vasprintf(char** _Buffer, const char* _Format, va_list _ArgList);

// posix : scanf
_XPOSIXAPI_ int __xcall__ x_posix_scanf(const char* _Format, ...);

// posix : vscanf
_XPOSIXAPI_ int __xcall__ x_posix_vscanf(const char* _Format, va_list _ArgList);

// posix : sscanf
_XPOSIXAPI_ int __xcall__ x_posix_sscanf(const char* _Buffer, const char* _Format, ...);

// posix : vsscanf
_XPOSIXAPI_ int __xcall__ x_posix_vsscanf(const char* _Buffer, const char* _Format, va_list _ArgList);

// posix : fscanf
_XPOSIXAPI_ int __xcall__ x_posix_fscanf(FILE* _Stream, const char* _Format, ...);

// posix : vfscanf
_XPOSIXAPI_ int __xcall__ x_posix_vfscanf(FILE* _Stream, const char* _Format, va_list _ArgList);

// posix : fflush
_XPOSIXAPI_ int __xcall__ x_posix_fflush(FILE* _Stream);



XANADU_CXX_EXTERN_END

#endif
