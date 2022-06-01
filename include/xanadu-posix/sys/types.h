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


// X-Series type definition : Integer range
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



// X-Series type definition : ssize_t
#if defined(XANADU_SYSTEM_WINDOWS) && !defined(__ssize_t_defined)
typedef 		SSIZE_T			ssize_t;
#define __ssize_t_defined
#endif



// X-Series type definition : locale_t
#if defined(XANADU_SYSTEM_WINDOWS)
typedef			_locale_t		locale_t;
#endif



// X-Series type definition : mode_t
#if defined(XANADU_SYSTEM_WINDOWS)
typedef			unsigned int		mode_t;
#endif



// X-Series type definition : pid_t
#if defined(XANADU_SYSTEM_WINDOWS)
typedef			int			pid_t;
#endif



// X-Series type definition : WINAPI
#if !defined(XANADU_SYSTEM_WINDOWS) && !defined(WINAPI)
#define			WINAPI			__xcall__
#endif



// X-Series type definition : HANDLE
#if !defined(XANADU_SYSTEM_WINDOWS)
typedef 		void*			HANDLE;
#endif
#define 		X_INVALID_HANDLE	((HANDLE)(-1))



// X-Series type definition : PVOID
#if !defined(XANADU_SYSTEM_WINDOWS)
typedef			void*			PVOID;
#endif



// X-Series type definition : NTSTATUS
#if !defined(XANADU_SYSTEM_WINDOWS)
typedef			long			NTSTATUS;
#endif



// X-Series type definition : ULONG
#if !defined(XANADU_SYSTEM_WINDOWS)
typedef			unsigned long		ULONG;
#endif



// X-Series type definition : PULONG
#if !defined(XANADU_SYSTEM_WINDOWS)
typedef			unsigned long*		PULONG;
#endif



// X-Series type definition : DWORD
#if !defined(XANADU_SYSTEM_WINDOWS)
typedef			unsigned long		DWORD;
#endif



// X-Series type definition : SOCKET
#if !defined(XANADU_SYSTEM_WINDOWS)
typedef			unsigned int		SOCKET;
#endif



// X-Series type definition : DIR
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



// Define some basic types
typedef		bool				x_bool_t;
typedef		char				x_char_t;
typedef		unsigned char			x_uchar_t;
typedef		short				x_short_t;
typedef		unsigned short			x_ushort_t;
typedef		int				x_int_t;
typedef		unsigned int			x_uint_t;
typedef		long				x_long_t;
typedef		unsigned long			x_ulong_t;
typedef		long long			x_llong_t;
typedef		unsigned long long		x_ullong_t;
typedef		float				x_float_t;
typedef		double				x_double_t;
typedef		long double			x_ldouble_t;



// Define some types related to platform bits
#if defined(XANADU_PLATFORM_BIT_32)
typedef		int				x_ssize_t;
typedef		unsigned int			x_size_t;
#else
typedef		long long			x_ssize_t;
typedef		unsigned long long		x_size_t;
#endif



// Define range types for some data
typedef 	x_size_t			x_pos_type;
typedef 	x_ssize_t			x_diff_type;
typedef 	x_llong_t			x_time_type;



#if defined(__cplusplus)
}
#endif


#endif
