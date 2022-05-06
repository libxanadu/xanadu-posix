#ifndef			_XANADU_POSIX_SYS_PLATFORM_H_
#define			_XANADU_POSIX_SYS_PLATFORM_H_


/// ********** ********** ********** ********** ********** **********
/// 此文件定义有关目标操作系统的信息
/// ********** ********** ********** ********** ********** **********


// 平台相关定义 : Windows
#if defined(_WIN32)
#define			XANADU_SYSTEM_WINDOWS			(1)
#endif

// 平台相关定义 : Linux
#if defined (__linux__) || defined (_LINUX_)
#define			XANADU_SYSTEM_LINUX			(1)
#endif

// 平台相关定义 : Darwin
#if defined (__APPLE__)
#define			XANADU_SYSTEM_DARWIN			(1)
#endif

// 平台相关定义 : Android
#if defined (__ANDROID__) || defined (ANDROID)
#define			XANADU_SYSTEM_ANDROID			(1)
#define			XANADU_SYSTEM_LINUX			(1)
#define 		XANADU_SYSTEM_ARM				(1)
#endif

// 平台相关定义 : ARM
#if defined (__arm__) || defined (__ARM_ARCH)
#define			XANADU_SYSTEM_LINUX			(1)
#define 		XANADU_SYSTEM_ARM				(1)
#endif


// 检查操作系统是否受支持
#if !defined(XANADU_SYSTEM_WINDOWS) && !defined(XANADU_SYSTEM_DARWIN) && !defined(XANADU_SYSTEM_LINUX)
#error This compiler is not supported yet
#endif





// 目标平台位数
#if defined(__x86_64__) || defined(__amd64__) || defined(_WIN64) || defined(__aarch64__)
#define 		XANADU_PLATFORM_BIT_64			(1)
#elif defined(__i386__) || defined(_WIN32) || defined(__arm__)
#define 		XANADU_PLATFORM_BIT_32			(1)
#else
#error This compiler is not supported yet
#endif


#endif
