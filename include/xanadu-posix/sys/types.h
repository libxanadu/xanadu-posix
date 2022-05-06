#ifndef			_XANADU_POSIX_SYS_TYPES_H_
#define			_XANADU_POSIX_SYS_TYPES_H_

#include <xanadu-posix/sys/compiler.h>
#include <xanadu-posix/sys/platform.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <locale.h>
#include <sys/stat.h>
#include <wctype.h>
#include <wchar.h>
#if defined(XANADU_SYSTEM_WINDOWS)
#include <WS2tcpip.h>
#include <Windows.h>
#include <direct.h>
#else
#if defined(XANADU_SYSTEM_LINUX)
#include <sys/sysmacros.h>
#undef major
#undef minor
#endif
#include <unistd.h>
#include <dirent.h>
#if defined(XANADU_SYSTEM_DARWIN)
#include <xlocale.h>
#endif
#endif


#if defined(__cplusplus)
extern "C" {
#endif


// xanadu系列类型定义 : Integer range
#define 		X_INT16S_MIN					(-32768)
#define 		X_INT16S_MAX					(0x7FFF)
#define 		X_INT16U_MIN					(0U)
#define 		X_INT16U_MAX					(0xFFFFU)
#define 		X_INT32S_MIN					(-2147483647 - 1)
#define 		X_INT32S_MAX					(0x7FFFFFFF)
#define 		X_INT32U_MIN					(0U)
#define 		X_INT32U_MAX					(0xFFFFFFFFU)
#define 		X_INT64S_MIN					(-9223372036854775807 - 1)
#define 		X_INT64S_MAX					(0x7FFFFFFFFFFFFFFFLL)
#define 		X_INT64U_MIN					(0ULL)
#define 		X_INT64U_MAX					(0xFFFFFFFFFFFFFFFFULL)

// xanadu系列类型定义 : ssize_t
#if defined(XANADU_SYSTEM_WINDOWS) && !defined(__ssize_t_defined)
typedef 		SSIZE_T			ssize_t;
#define __ssize_t_defined
#endif

// xanadu系列类型定义 : locale_t
#if defined(XANADU_SYSTEM_WINDOWS)
typedef			_locale_t		locale_t;
#endif

// xanadu系列类型定义 : mode_t
#if defined(XANADU_SYSTEM_WINDOWS)
typedef			unsigned int		mode_t;
#endif

// xanadu系列类型定义 : pid_t
#if defined(XANADU_SYSTEM_WINDOWS)
typedef			int			pid_t;
#endif

// xanadu系列类型定义 : WINAPI
#if !defined(XANADU_SYSTEM_WINDOWS) && !defined(WINAPI)
#define			WINAPI			__xcall__
#endif

// xanadu系列类型定义 : HANDLE
#if !defined(XANADU_SYSTEM_WINDOWS)
typedef 		void*			HANDLE;
#endif

// xanadu系列类型定义 : PVOID
#if !defined(XANADU_SYSTEM_WINDOWS)
typedef			void*			PVOID;
#endif

// xanadu系列类型定义 : NTSTATUS
#if !defined(XANADU_SYSTEM_WINDOWS)
typedef			long			NTSTATUS;
#endif

// xanadu系列类型定义 : ULONG
#if !defined(XANADU_SYSTEM_WINDOWS)
typedef			unsigned long		ULONG;
#endif

// xanadu系列类型定义 : PULONG
#if !defined(XANADU_SYSTEM_WINDOWS)
typedef			unsigned long*		PULONG;
#endif

// xanadu系列类型定义 : DWORD
#if !defined(XANADU_SYSTEM_WINDOWS)
typedef			unsigned long		DWORD;
#endif

// xanadu系列类型定义 : SOCKET
#if !defined(XANADU_SYSTEM_WINDOWS)
typedef			unsigned int		SOCKET;
#endif



// xanadu系列类型定义 : DIR
#if defined(XANADU_COMPILER_MSVC)
typedef struct dirent
{
	long					d_ino;			/* inode number */
	off_t					d_off;			/* offset to this dirent */
	unsigned short				d_reclen;		/* length of this d_name */
	unsigned char				d_type;			/* the type of d_name */
	char					d_name[MAX_PATH];	/* file name (null-terminated) */
}dirent;
typedef struct __dirstream
{
	void*					__fd;			/* `struct hurd_fd' pointer for descriptor.   */
	char*					__data;			/* Directory block.   */
	int					__entry_data;		/* Entry number `__data' corresponds to.   */
	char*					__ptr;			/* Current pointer into the block.   */
	int					__entry_ptr;		/* Entry number `__ptr' corresponds to.   */
	size_t					__allocation;		/* Space allocated for the block.   */
	size_t					__size;			/* Total valid data in the block.   */

	char*					__directory;		/* Directory path */
	void*					__finddata64;		/* Compatible _findfirst64 */
	void*					__dirent;
}DIR;
#endif


#if defined(__cplusplus)
}
#endif


#endif
