#ifndef			_XANADU_POSIX_SYS_COMPILER_H_
#define			_XANADU_POSIX_SYS_COMPILER_H_


/// ********** ********** ********** ********** ********** **********
/// Information about the current compiler
/// ********** ********** ********** ********** ********** **********


// Compiler : MSVC
#if defined(_MSC_VER)
#define 		XANADU_COMPILER_MSVC			(1)
#endif

// Compiler : CLANG
#if defined(__clang__)
#define 		XANADU_COMPILER_CLANG			(1)
#endif

// Compiler : GNUC
#if defined(__GNUC__)
#define 		XANADU_COMPILER_GNUC			(1)
#endif


// Check whether the compiler supports
#if !defined(XANADU_COMPILER_MSVC) && !defined(XANADU_COMPILER_GNUC) && !defined(XANADU_COMPILER_CLANG)
#error This compiler is not supported yet
#endif



// Compiler export and import definitions
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



// X-Series cxx compatible export packaging
#if defined(__cplusplus)
#define 		XANADU_CXX_EXTERN_BEGIN			extern "C" {
#else
#define 		XANADU_CXX_EXTERN_BEGIN
#endif
#if defined(__cplusplus)
#define 		XANADU_CXX_EXTERN_END			}
#else
#define 		XANADU_CXX_EXTERN_END
#endif


#endif
