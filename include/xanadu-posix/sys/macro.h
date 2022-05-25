#ifndef			_XANADU_POSIX_SYS_MACRO_H_
#define			_XANADU_POSIX_SYS_MACRO_H_


/// ********** ********** ********** ********** ********** **********
/// Macros for the target operating system
/// ********** ********** ********** ********** ********** **********

#include <xanadu-posix/sys/platform.h>
#include <sys/stat.h>



#if defined(__cplusplus)
extern "C" {
#endif



// X-Series macro definition : file access
#if defined(XANADU_SYSTEM_WINDOWS) && !defined(XANADU_POSIX_MACRO_FILE_ACCESS)
#define			XANADU_POSIX_MACRO_FILE_ACCESS				(1)
#define			R_OK							(4)			// Read-only
#define			W_OK							(2)			// Write-only
#define			X_OK							(1)			// The executable
#define			F_OK							(0)			// Existence only
#endif



// X-Series macro definition : file type
#if defined(XANADU_SYSTEM_WINDOWS) && !defined(XANADU_POSIX_MACRO_FILE_TYPE)
#define			XANADU_POSIX_MACRO_FILE_TYPE				(1)
#define			S_IFIFO							_S_IFIFO		// named pipe (fifo)
#define			S_IFBLK							(0060000)		// block special
#define			S_IFLNK							(0120000)		// symbolic link
#define			S_IFSOCK						(0140000)		// socket
#define			S_IFWHT							(0160000)		// whiteout
#endif



// X-Series macro definition : file check
#if defined(XANADU_SYSTEM_WINDOWS) && !defined(XANADU_POSIX_MACRO_FILE_MODE)
#define			XANADU_POSIX_MACRO_FILE_MODE				(1)

#if !defined(__S_ISTYPE) && defined(S_IFMT)
#define			__S_ISTYPE(mode, mask)					(((mode) & S_IFMT) == (mask))
#endif

#if !defined(S_ISDIR) && defined(S_IFDIR) && defined(S_IFMT)
#define			S_ISDIR(mode)						(((mode) & S_IFMT) == S_IFDIR)
#endif

#if !defined(S_ISCHR) && defined(S_IFCHR)
#define			S_ISCHR(mode)						__S_ISTYPE((mode), S_IFCHR)
#endif

#if !defined(S_ISBLK) && defined(S_IFBLK)
#define			S_ISBLK(mode)						__S_ISTYPE((mode), S_IFBLK)
#endif

#if !defined(S_ISREG) && defined(S_IFREG)
#define			S_ISREG(mode)						__S_ISTYPE((mode), S_IFREG)
#endif

#if !defined(S_ISFIFO) && defined(S_IFIFO)
#define			S_ISFIFO(mode)						__S_ISTYPE((mode), S_IFIFO)
#endif

#if !defined(S_ISSOCK) && defined(S_IFSOCK)
#define			S_ISSOCK(mode)						__S_ISTYPE((mode), S_IFSOCK)
#endif

#if !defined(S_ISLNK) && defined(S_IFLNK)
#define			S_ISLNK(mode)						__S_ISTYPE((mode), S_IFLNK)
#endif

#endif



// X-Series macro definition : file power
#if defined(XANADU_SYSTEM_WINDOWS) && !defined(XANADU_POSIX_MACRO_FILE_PERMS)
#define			XANADU_POSIX_MACRO_FILE_PERMS				(1)
#define			S_IRWXU							0000700			// RWX mask for owner
#define			S_IRUSR							0000400			// R for owner
#define			S_IWUSR							0000200			// W for owner
#define			S_IXUSR							0000100			// X for owner

#define			S_IRWXG							0000070			// RWX mask for group
#define			S_IRGRP							0000040			// R for group
#define			S_IWGRP							0000020			// W for group
#define			S_IXGRP							0000010			// X for group

#define			S_IRWXO							0000007			// RWX mask for other
#define			S_IROTH							0000004			// R for other
#define			S_IWOTH							0000002			// W for other
#define			S_IXOTH							0000001			// X for other

#define			S_ISUID							0004000			// set user id on execution
#define			S_ISGID							0002000			// set group id on execution
#define			S_ISVTX							0001000			// save swapped text even after use
#endif



// X-Series macro definition : MAX_PATH
#if !defined(XANADU_SYSTEM_WINDOWS) && !defined(MAX_PATH)
#define			MAX_PATH						260
#endif



// X-Series macro definition : snprintf
#if !defined(XANADU_SYSTEM_WINDOWS) && !defined(_snprintf)
#define			_snprintf						snprintf
#endif



// X-Series macro definition : size
#define			XANADU_SIZE_PHASE					(1024)
#define			XANADU_SIZE_BIT						(8)
#define			XANADU_SIZE_BYTE					(1)
#define			XANADU_SIZE_KB						(1024ULL)
#define			XANADU_SIZE_MB						(1048576ULL)
#define			XANADU_SIZE_GB						(1073741824ULL)
#define			XANADU_SIZE_TB						(1099511627776ULL)
#define			XANADU_SIZE_PB						(XANADU_SIZE_PHASE * XANADU_SIZE_TB)
#define			XANADU_SIZE_EB						(XANADU_SIZE_PHASE * XANADU_SIZE_PB)
#define			XANADU_SIZE_ZB						(XANADU_SIZE_PHASE * XANADU_SIZE_EB)
#define			XANADU_SIZE_YB						(XANADU_SIZE_PHASE * XANADU_SIZE_ZB)
#define			XANADU_SIZE_BB						(XANADU_SIZE_PHASE * XANADU_SIZE_YB)
#define			XANADU_SIZE_NB						(XANADU_SIZE_PHASE * XANADU_SIZE_BB)
#define			XANADU_SIZE_DB						(XANADU_SIZE_PHASE * XANADU_SIZE_NB)
#define			XANADU_SIZE_CB						(XANADU_SIZE_PHASE * XANADU_SIZE_DB)


#if defined(__cplusplus)
}
#endif


#endif
