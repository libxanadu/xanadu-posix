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

/// Convert UTF-8 to UNICODE
/// \param _UTF8 : A UTF-8 string ending in NULL
/// \param _Unicode : Buffer for storing converted strings
/// \param _WLength : Length of Unicode buffer
/// \return : The number of bytes after conversion is returned on success and -1 on failure.
/// \return : When the parameter \param _Unicode or \param _Length is null, the required memory length is returned
_XPOSIXAPI_ size_t __xcall__ x_posix_utftowcs(const char* _UTF8, wchar_t* _Unicode, size_t _WLength);

/// Convert UNICODE to UTF-8
/// \param _Unicode : A Unicode string ending in NULL
/// \param _UTF8 : Buffer for storing converted strings
/// \param _ULength : Length of UTF8 buffer
/// \return : The number of bytes after conversion is returned on success and -1 on failure.
/// \return : When the parameter \param _UTF8 or \param _Length is null, the required memory length is returned
_XPOSIXAPI_ size_t __xcall__ x_posix_wcstoutf(const wchar_t* _Unicode, char* _UTF8, size_t _ULength);



XANADU_CXX_EXTERN_END

#endif
