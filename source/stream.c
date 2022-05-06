#include <xanadu-posix/stream.h>
#include <xanadu-posix/memory.h>
#include <stdarg.h>



// posix : printf
_XPOSIXAPI_ int __xcall__ x_posix_printf(const char* _Format, ...)
{
	int 		vSync = 0;
	va_list		vArgs;

	va_start(vArgs, _Format);
	vSync = x_posix_vprintf(_Format, vArgs);
	va_end(vArgs);
	return vSync;
}

// posix : vprintf
_XPOSIXAPI_ int __xcall__ x_posix_vprintf(const char* _Format, va_list _ArgList)
{
	return vprintf(_Format, _ArgList);
}

// posix : sprintf
_XPOSIXAPI_ int __xcall__ x_posix_sprintf(char* _Buffer, const char* _Format, ...)
{
	int 		vSync = 0;
	va_list		vArgs;

	va_start(vArgs, _Format);
	vSync = x_posix_vsprintf(_Buffer, _Format, vArgs);
	va_end(vArgs);
	return vSync;
}

// posix : vsprintf
_XPOSIXAPI_ int __xcall__ x_posix_vsprintf(char* _Buffer, const char* _Format, va_list _ArgList)
{
	return vsprintf(_Buffer, _Format, _ArgList);
}

// posix : snprintf
_XPOSIXAPI_ int __xcall__ x_posix_snprintf(char* _Buffer, size_t _BufferCount, const char* _Format, ...)
{
	int 		vSync = 0;
	va_list		vArgs;

	va_start(vArgs, _Format);
	vSync = x_posix_vsnprintf(_Buffer, _BufferCount, _Format, vArgs);
	va_end(vArgs);
	return vSync;
}

// posix : vsnprintf
_XPOSIXAPI_ int __xcall__ x_posix_vsnprintf(char* _Buffer, size_t _BufferCount, const char* _Format, va_list _ArgList)
{
	return vsnprintf(_Buffer, _BufferCount, _Format, _ArgList);
}

// posix : fprintf
_XPOSIXAPI_ int __xcall__ x_posix_fprintf(FILE* _Stream, const char* _Format, ...)
{
	int 		vSync = 0;
	va_list		vArgs;

	va_start(vArgs, _Format);
	vSync = x_posix_vfprintf(_Stream, _Format, vArgs);
	va_end(vArgs);
	return vSync;
}

// posix : vfprintf
_XPOSIXAPI_ int __xcall__ x_posix_vfprintf(FILE* _Stream, const char* _Format, va_list _ArgList)
{
	return vfprintf(_Stream, _Format, _ArgList);
}

// posix : asprintf
_XPOSIXAPI_ int __xcall__ x_posix_asprintf(char** _Buffer, const char* _Format, ...)
{
	int		vStatus = 0;
	va_list		vArgs;

	va_start(vArgs, _Format);
	vStatus = x_posix_vasprintf(_Buffer, _Format, vArgs);
	va_end(vArgs);
	return vStatus;
}

// posix : vasprintf
_XPOSIXAPI_ int __xcall__ x_posix_vasprintf(char** _Buffer, const char* _Format, va_list _ArgList)
{
	int		vStatus = 0;
	va_list		vArgs1;
	va_list		vArgs2;

	va_copy(vArgs1, _ArgList);
	va_copy(vArgs2, _ArgList);

	vStatus = vsnprintf(NULL, 0, _Format, vArgs1);
	if (vStatus > 0)
	{
		*_Buffer = (char*)x_posix_malloc(vStatus + XANADU_STDIO_VSNPRINTF_EXTRA);
		if(*_Buffer)
		{
			x_posix_memset(*_Buffer, 0, vStatus + XANADU_STDIO_VSNPRINTF_EXTRA);
			vStatus = vsnprintf(*_Buffer, vStatus + XANADU_STDIO_VSNPRINTF_EXTRA, _Format, vArgs2);
		}
	}

	va_end(vArgs1);
	va_end(vArgs2);
	return vStatus;
}

// posix : scanf
_XPOSIXAPI_ int __xcall__ x_posix_scanf(const char* _Format, ...)
{
	int 		vSync = 0;
	va_list		vArgs;

	va_start(vArgs, _Format);
	vSync = x_posix_vscanf(_Format, vArgs);
	va_end(vArgs);
	return vSync;
}

// posix : vscanf
_XPOSIXAPI_ int __xcall__ x_posix_vscanf(const char* _Format, va_list _ArgList)
{
	return vscanf(_Format, _ArgList);
}

// posix : sscanf
_XPOSIXAPI_ int __xcall__ x_posix_sscanf(const char* _Buffer, const char* _Format, ...)
{
	int 		vSync = 0;
	va_list		vArgs;

	va_start(vArgs, _Format);
	vSync = x_posix_vsscanf(_Buffer, _Format, vArgs);
	va_end(vArgs);
	return vSync;
}

// posix : vsscanf
_XPOSIXAPI_ int __xcall__ x_posix_vsscanf(const char* _Buffer, const char* _Format, va_list _ArgList)
{
	return vsscanf(_Buffer, _Format, _ArgList);
}

// posix : fscanf
_XPOSIXAPI_ int __xcall__ x_posix_fscanf(FILE* _Stream, const char* _Format, ...)
{
	int 		vSync = 0;
	va_list		vArgs;

	va_start(vArgs, _Format);
	vSync = x_posix_vfscanf(_Stream, _Format, vArgs);
	va_end(vArgs);
	return vSync;
}

// posix : vfscanf
_XPOSIXAPI_ int __xcall__ x_posix_vfscanf(FILE* _Stream, const char* _Format, va_list _ArgList)
{
	return vfscanf(_Stream, _Format, _ArgList);
}

// posix : fflush
_XPOSIXAPI_ int __xcall__ x_posix_fflush(FILE* _Stream)
{
	return fflush(_Stream);
}
