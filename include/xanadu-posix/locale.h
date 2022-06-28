#ifndef			_XANADU_POSIX_LOCALE_H_
#define			_XANADU_POSIX_LOCALE_H_

#include <xanadu-posix/header.h>

XANADU_CXX_EXTERN_BEGIN



// posix : setlocale
_XPOSIXAPI_ char* __xcall__ x_posix_setlocale(int _Category, const char* _Locale);

// posix : wcstombs
_XPOSIXAPI_ size_t __xcall__ x_posix_wcstombs(char* _MBS, const wchar_t* _WCS, size_t _Length);

// posix : mbstowcs
_XPOSIXAPI_ size_t __xcall__ x_posix_mbstowcs(wchar_t* _WCS, const char* _MBS, size_t _Length);



XANADU_CXX_EXTERN_END

#endif
