#ifndef			_XANADU_POSIX_SYS_COMPILER_H_
#define			_XANADU_POSIX_SYS_COMPILER_H_


/// ********** ********** ********** ********** ********** **********
/// 该文件主要定义了当前编译器的相关信息
/// ********** ********** ********** ********** ********** **********


// 编译器 : MSVC
#if defined(_MSC_VER)
#define 		XANADU_COMPILER_MSVC			(1)
#endif

// 编译器 : CLANG
#if defined(__clang__)
#define 		XANADU_COMPILER_CLANG			(1)
#endif

// 编译器 : GNUC
#if defined(__GNUC__)
#define 		XANADU_COMPILER_GNUC			(1)
#endif


// Check whether the compiler supports
#if !defined(XANADU_COMPILER_MSVC) && !defined(XANADU_COMPILER_GNUC) && !defined(XANADU_COMPILER_CLANG)
#error This compiler is not supported yet
#endif



// 编译器的导出与导入定义
#if defined(XANADU_COMPILER_MSVC)
#define			XANADU_COMPILER_API_EXP			__declspec(dllexport)
#define			XANADU_COMPILER_API_IMP			__declspec(dllimport)
#define			XANADU_COMPILER_API_DEF
#elif defined(XANADU_COMPILER_GNUC) || defined(XANADU_COMPILER_CLANG)
#define			XANADU_COMPILER_API_EXP			__attribute__((visibility("default")))
#define			XANADU_COMPILER_API_IMP			__attribute__((visibility("default")))
#define			XANADU_COMPILER_API_DEF			__attribute__((visibility("default")))
#else
#define			XANADU_COMPILER_API_EXP
#define			XANADU_COMPILER_API_IMP
#define			XANADU_COMPILER_API_DEF
#endif


#endif
