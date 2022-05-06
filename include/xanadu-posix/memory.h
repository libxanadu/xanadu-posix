#ifndef			_XANADU_POSIX_MEMORY_H_
#define			_XANADU_POSIX_MEMORY_H_

#include <xanadu-posix/header.h>


#if defined(__cplusplus)
extern "C" {
#endif



// posix : malloc
_XPOSIXAPI_ void* __xcall__ x_posix_malloc(size_t _Size);

// posix : calloc
_XPOSIXAPI_ void* __xcall__ x_posix_calloc(size_t _Count, size_t _Size);

// posix : realloc
_XPOSIXAPI_ void* __xcall__ x_posix_realloc(void* _Block, size_t _Size);

// posix : memdup
_XPOSIXAPI_ void* __xcall__ x_posix_memdup(const void* _Memory, size_t _Size);

// posix : free
_XPOSIXAPI_ void __xcall__ x_posix_free(void* _Memory);





// posix : memset
_XPOSIXAPI_ void* __xcall__ x_posix_memset(void* _Memory, int _Value, size_t _Size);

// posix : memcpy
_XPOSIXAPI_ void* __xcall__ x_posix_memcpy(void* _Dst, const void* _Src, size_t _Size);

// posix : memmove
_XPOSIXAPI_ void* __xcall__ x_posix_memmove(void* _Dst, const void* _Src, size_t _Size);

// posix : memchr
_XPOSIXAPI_ void* __xcall__ x_posix_memchr(const void* _Buf, int _Val, size_t _MaxCount);

// posix : memrchr
_XPOSIXAPI_ void* __xcall__ x_posix_memrchr(const void* _Buf, int _Val, size_t _MaxCount);

// posix : memcmp
_XPOSIXAPI_ int __xcall__ x_posix_memcmp(const void* _Buf1, const void* _Buf2, size_t _Size);





// posix : wmemset
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wmemset(wchar_t* _Memory, wchar_t _Value, size_t _Size);

// posix : wmemcpy
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wmemcpy(wchar_t* _Dst, const wchar_t* _Src, size_t _Size);

// posix : wmemmove
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wmemmove(wchar_t* _Dst, const wchar_t* _Src, size_t _Size);

// posix : wmemchr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wmemchr(const wchar_t* _Buf, wchar_t _Val, size_t _MaxCount);

// posix : wmemrchr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wmemrchr(const wchar_t* _Buf, wchar_t _Val, size_t _MaxCount);

// posix : wmemcmp
_XPOSIXAPI_ int __xcall__ x_posix_wmemcmp(const wchar_t* _Buf1, const wchar_t* _Buf2, size_t _Size);




#if defined(__cplusplus)
}
#endif


#endif
