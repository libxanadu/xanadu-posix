#ifndef			_XANADU_POSIX_HEADER_H_
#define			_XANADU_POSIX_HEADER_H_

#include <xanadu-posix/sys/compiler.h>
#include <xanadu-posix/sys/macro.h>
#include <xanadu-posix/sys/platform.h>
#include <xanadu-posix/sys/types.h>



// X-Series macro definition: call
#if defined(XANADU_COMPILER_MSVC)
#define			XANADU_POSIX_CALL				__cdecl
#elif defined(XANADU_COMPILER_GNUC) || defined(XANADU_COMPILER_CLANG)
// #define		XANADU_POSIX_CALL				__attribute__((__cdecl__))
#define			XANADU_POSIX_CALL
#else
#define			XANADU_POSIX_CALL
#endif
#define			__xcall__					XANADU_POSIX_CALL



// X-Series macro definition: Platform
#define			__XFILE__					__FILE__
#define			__XLINE__					__LINE__
#if defined(XANADU_COMPILER_MSVC)
#define			__XFUNCTION__					__FUNCTION__
#else
#define			__XFUNCTION__					__func__
#endif
#if defined(XANADU_COMPILER_MSVC)
#define			__XFUNCSIG__					__FUNCSIG__
#else
#define			__XFUNCSIG__					__PRETTY_FUNCTION__
#endif
#define			__XTIMESTAMP__					__TIMESTAMP__



// X-Series macro definition: Export
#if defined(XANADU_POSIX_BUILD_STATIC)
#define			_XPOSIXAPI_
#else
#if defined(XANADU_POSIX_BUILD_LOCAL)
#define			_XPOSIXAPI_					XANADU_COMPILER_API_EXP
#else
#define			_XPOSIXAPI_					XANADU_COMPILER_API_IMP
#endif
#endif



// X-Series macro definition: Control
#define 		XANADU_UNUSED(_Param)				((void)_Param)
#define			XANADU_PATH_MAX					(1024)
#define			XANADU_STDIO_VSNPRINTF_EXTRA			(10)



#endif
