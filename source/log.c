#include <xanadu-posix/log.h>
#include <xanadu-posix/process.h>
#include <xanadu-posix/thread.h>
#include <xanadu-posix/memory.h>
#include <xanadu-posix/string.h>
#include <xanadu-posix/stream.h>
#include <xanadu-posix/application.h>
#include <stdarg.h>
#if defined(XANADU_SYSTEM_ANDROID)
#include <android/log.h>
#endif



// Global variable
static x_log_level_t		_global_log_level = XLOG_LEVEL_VERBOSE;
static xanadu_log_printf_cb_t	_global_log_printf = NULL;
static FILE*			_global_log_stream = NULL;



// x_log_printf_level_to_android
#if defined(XANADU_SYSTEM_ANDROID)
static int __xcall__ x_log_printf_level_to_android(x_log_level_t _Level)
{
	switch(_Level)
	{
		case XLOG_LEVEL_VERBOSE:
			return ANDROID_LOG_VERBOSE;
		case XLOG_LEVEL_DEBUG:
			return ANDROID_LOG_DEBUG;
		case XLOG_LEVEL_INFO:
			return ANDROID_LOG_INFO;
		case XLOG_LEVEL_WARNING:
			return ANDROID_LOG_WARN;
		case XLOG_LEVEL_ERROR:
			return ANDROID_LOG_ERROR;
		case XLOG_LEVEL_FATAL:
			return ANDROID_LOG_FATAL;
		default:
			return ANDROID_LOG_UNKNOWN;
	}

	return _Level;
}
#endif

// x_log_printf_get_prefix_time >> [%04d-%02d-%02dT%02d:%02d:%02d.%03dZ]
static char* __xcall__ x_log_printf_get_prefix_time()
{
	char*			vTimePrefix = NULL;
#if defined(XANADU_SYSTEM_WINDOWS)
	SYSTEMTIME		vSystemTime;
	GetSystemTime(&vSystemTime);
	vTimePrefix = x_string_format("[%04d-%02d-%02dT%02d:%02d:%02d.%03dZ]",
				      vSystemTime.wYear, vSystemTime.wMonth, vSystemTime.wDay,
				      vSystemTime.wHour, vSystemTime.wMinute, vSystemTime.wSecond,
				      vSystemTime.wMilliseconds);
#else
	struct timespec		vTime;
	struct tm		vNowTime;
	clock_gettime(CLOCK_REALTIME, &vTime);
	localtime_r(&vTime.tv_sec, &vNowTime);
	vTimePrefix = x_string_format("[%04d-%02d-%02dT%02d:%02d:%02d.%03dZ]",
				      vNowTime.tm_year + 1900, vNowTime.tm_mon + 1, vNowTime.tm_mday,
				      vNowTime.tm_hour, vNowTime.tm_min, vNowTime.tm_sec,
				      vTime.tv_nsec / 1000000);
#endif
	return vTimePrefix;
}

// x_log_printf_get_prefix_level >> [%04d-%02d-%02dT%02d:%02d:%02d.%03dZ]
static const char* __xcall__ x_log_printf_get_prefix_level(x_log_level_t _Level)
{
	switch (_Level)
	{
		case XLOG_LEVEL_VERBOSE:	return "V";
		case XLOG_LEVEL_DEBUG:		return "D";
		case XLOG_LEVEL_INFO:		return "I";
		case XLOG_LEVEL_WARNING:	return "W";
		case XLOG_LEVEL_ERROR:		return "E";
		case XLOG_LEVEL_FATAL:		return "F";
		default:			return "U";
	}
}

// 输出到流中
static int __xcall__ x_log_printf_to_stream(FILE* _Stream, x_log_level_t _Level, const char* _TAG, const char* _Message)
{
	int 		vSync = 0;
	char*		vTimePrefix = x_log_printf_get_prefix_time();
	char* 		vProcessPrefix = x_string_format("%05d-%05d", (int)x_posix_getpid(), (int)x_posix_gettid());
	const char*	vApplicationPrefix = x_application_native_name();
	const char*	vLevelPrefix = x_log_printf_get_prefix_level(_Level);
#if defined(XANADU_SYSTEM_WINDOWS)
	wchar_t*	vMessageW = x_posix_strutow(_Message);
#endif

	if(vTimePrefix && vProcessPrefix && vApplicationPrefix && vLevelPrefix)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		if(vMessageW)
		{
			vSync = x_posix_fprintf(_Stream, "%s %s/%s %s/%s: %ls\n", vTimePrefix, vProcessPrefix, vApplicationPrefix, vLevelPrefix, _TAG, vMessageW);
		}
		else
		{
			vSync = x_posix_fprintf(_Stream, "%s %s/%s %s/%s: %s\n", vTimePrefix, vProcessPrefix, vApplicationPrefix, vLevelPrefix, _TAG, _Message);
		}
#else
		vSync = x_posix_fprintf(_Stream, "%s %s/%s %s/%s: %s\n", vTimePrefix, vProcessPrefix, vApplicationPrefix, vLevelPrefix, _TAG, _Message);
#endif
	}

	x_posix_free(vTimePrefix);
	x_posix_free(vProcessPrefix);
#if defined(XANADU_SYSTEM_WINDOWS)
	x_posix_free(vMessageW);
#endif
	return vSync;
}

// x_log_printf_string
static int __xcall__ x_log_printf_string(x_log_level_t _Level, const char* _TAG, const char* _Message)
{
	int 		vSync = 0;

	if(_global_log_printf)
	{
		return _global_log_printf(_Level, _TAG, _Message);
	}
	if(_global_log_stream)
	{
		return x_log_printf_to_stream(_global_log_stream, _Level, _TAG, _Message);
	}

#if defined(XANADU_SYSTEM_ANDROID)
	vSync = __android_log_print(x_log_printf_level_to_android(_Level), _TAG, "%s", _Message);
#else
	vSync = x_log_printf_to_stream(stdout, _Level, _TAG, _Message);
#endif
	return vSync;
}



/// Set log print level
_XPOSIXAPI_ void __xcall__ x_log_set_level(x_log_level_t _Level)
{
	_global_log_level = _Level;
}

/// Get log print level
_XPOSIXAPI_ x_log_level_t __xcall__ x_log_get_level()
{
	return _global_log_level;
}

/// 设置日志回调
_XPOSIXAPI_ void __xcall__ x_log_set_printf_cb(xanadu_log_printf_cb_t _Function)
{
	_global_log_printf = _Function;
}

/// 设置日志输出流
_XPOSIXAPI_ void __xcall__ x_log_set_printf_stream(FILE* _Stream)
{
	_global_log_stream = _Stream;
}

/// Format log output
_XPOSIXAPI_ int __xcall__ x_log_printf(x_log_level_t _Level, const char* _TAG, const char* _Format, ...)
{
	if(_Level < _global_log_level || _Format == NULL)
	{
		return -1;
	}

	int 		vSync = 0;
	va_list		vArgs;

	va_start(vArgs, _Format);
	vSync = x_log_vprintf(_Level, _TAG, _Format, vArgs);
	va_end(vArgs);
	return vSync;
}

/// Format log output. The rules are consistent with vprint()
_XPOSIXAPI_ int __xcall__ x_log_vprintf(x_log_level_t _Level, const char* _TAG, const char* _Format, va_list _ArgList)
{
	if(_Level < _global_log_level || _Format == NULL)
	{
		return -1;
	}

	int 		vSync = 0;
	char*		vLogString = NULL;

	x_posix_vasprintf(&vLogString, _Format, _ArgList);

	if(vLogString == NULL)
	{
		vLogString = (char*)x_posix_malloc(XANADU_STDIO_VSNPRINTF_EXTRA);
		x_posix_memset(vLogString, 0, XANADU_STDIO_VSNPRINTF_EXTRA);
	}

	if(vLogString)
	{
		vSync = x_log_printf_string(_Level, _TAG ? _TAG : "null", vLogString);
		x_posix_free(vLogString);
	}
	return vSync;
}
