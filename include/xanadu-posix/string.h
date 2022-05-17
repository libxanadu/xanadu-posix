#ifndef			_XANADU_POSIX_STRING_H_
#define			_XANADU_POSIX_STRING_H_

#include <xanadu-posix/header.h>


#if defined(__cplusplus)
extern "C" {
#endif



// posix : toupper
_XPOSIXAPI_ int __xcall__ x_posix_toupper(int _C);

// posix : tolower
_XPOSIXAPI_ int __xcall__ x_posix_tolower(int _C);





// posix : towupper
_XPOSIXAPI_ wchar_t __xcall__ x_posix_towupper(wchar_t _C);

// posix : towlower
_XPOSIXAPI_ wchar_t __xcall__ x_posix_towlower(wchar_t _C);





// posix : strlen
_XPOSIXAPI_ size_t __xcall__ x_posix_strlen(const char* _String);

// posix : strcmp
_XPOSIXAPI_ int __xcall__ x_posix_strcmp(const char* _Str1, const char* _Str2);

// posix : stricmp
_XPOSIXAPI_ int __xcall__ x_posix_stricmp(const char* _Str1, const char* _Str2);

// posix : strcasecmp
_XPOSIXAPI_ int __xcall__ x_posix_strcasecmp(const char* _Str1, const char* _Str2);

// posix : strncmp
_XPOSIXAPI_ int __xcall__ x_posix_strncmp(const char* _Str1, const char* _Str2, size_t _Length);

// posix : strnicmp
_XPOSIXAPI_ int __xcall__ x_posix_strnicmp(const char* _Str1, const char* _Str2, size_t _Length);

// posix : strchr
_XPOSIXAPI_ const char* __xcall__ x_posix_strchr(const char* _Str, int _Ch);

// posix : strichr
_XPOSIXAPI_ const char* __xcall__ x_posix_strichr(const char* _Str, int _Ch);

// posix : strrchr
_XPOSIXAPI_ const char* __xcall__ x_posix_strrchr(const char* _Str, int _Ch);

// posix : strirchr
_XPOSIXAPI_ const char* __xcall__ x_posix_strirchr(const char* _Str, int _Ch);

// posix : strstr
_XPOSIXAPI_ const char* __xcall__ x_posix_strstr(const char* _Str, const char* _SubStr);

// posix : stristr
_XPOSIXAPI_ const char* __xcall__ x_posix_stristr(const char* _Str, const char* _SubStr);

// posix : strrstr
_XPOSIXAPI_ const char* __xcall__ x_posix_strrstr(const char* _Str, const char* _SubStr);

// posix : strirstr
_XPOSIXAPI_ const char* __xcall__ x_posix_strirstr(const char* _Str, const char* _SubStr);

// posix : strcpy
_XPOSIXAPI_ char* __xcall__ x_posix_strcpy(char* _Dst, const char* _Source);

// posix : strncpy
_XPOSIXAPI_ char* __xcall__ x_posix_strncpy(char* _Dst, const char* _Source, size_t _Length);

// posix : strcat
_XPOSIXAPI_ char* __xcall__ x_posix_strcat(char* _Str1, const char* _Str2);

// posix : strncat
_XPOSIXAPI_ char* __xcall__ x_posix_strncat(char* _Str1, const char* _Str2, size_t _Length);

// posix : strdup
_XPOSIXAPI_ char* __xcall__ x_posix_strdup(const char* _String);

// posix : strupr
_XPOSIXAPI_ char* __xcall__ x_posix_strupr(char* _String);

// posix : strlwr
_XPOSIXAPI_ char* __xcall__ x_posix_strlwr(char* _String);





// posix : wcslen
_XPOSIXAPI_ size_t __xcall__ x_posix_wcslen(const wchar_t* _String);

// posix : wcscmp
_XPOSIXAPI_ int __xcall__ x_posix_wcscmp(const wchar_t* _Str1, const wchar_t* _Str2);

// posix : wcsicmp
_XPOSIXAPI_ int __xcall__ x_posix_wcsicmp(const wchar_t* _Str1, const wchar_t* _Str2);

// posix : wcscasecmp
_XPOSIXAPI_ int __xcall__ x_posix_wcscasecmp(const wchar_t* _Str1, const wchar_t* _Str2);

// posix : wcsncmp
_XPOSIXAPI_ int __xcall__ x_posix_wcsncmp(const wchar_t* _Str1, const wchar_t* _Str2, size_t _Length);

// posix : wcschr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wcschr(const wchar_t* _Str, wchar_t _Ch);

// posix : wcsichr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wcsichr(const wchar_t* _Str, wchar_t _Ch);

// posix : wcsrchr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wcsrchr(const wchar_t* _Str, wchar_t _Ch);

// posix : wcsirchr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wcsirchr(const wchar_t* _Str, wchar_t _Ch);

// posix : wcsstr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wcsstr(const wchar_t* _Str, const wchar_t* _SubStr);

// posix : wcsistr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wcsistr(const wchar_t* _Str, const wchar_t* _SubStr);

// posix : wcscpy
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcscpy(wchar_t* _Dst, const wchar_t* _Source);

// posix : wcsncpy
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcsncpy(wchar_t* _Dst, const wchar_t* _Source, size_t _Length);

// posix : wcscat
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcscat(wchar_t* _Str1, const wchar_t* _Str2);

// posix : wcsncat
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcsncat(wchar_t* _Str1, const wchar_t* _Str2, size_t _Length);

// posix : wcsdup
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcsdup(const wchar_t* _String);

// posix : wcsupr
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcsupr(wchar_t* _String);

// posix : wcslwr
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcslwr(wchar_t* _String);





// posix : strutow
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_strutow(const char* _UTF8);

// posix : stratow
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_stratow(const char* _ASCII);

// posix : strwtou
_XPOSIXAPI_ char* __xcall__ x_posix_strwtou(const wchar_t* _UNICODE);

// posix : strwtoa
_XPOSIXAPI_ char* __xcall__ x_posix_strwtoa(const wchar_t* _UNICODE);





// posix : atof
_XPOSIXAPI_ double __xcall__ x_posix_atof(const char* _String);

// posix : atoi
_XPOSIXAPI_ int __xcall__ x_posix_atoi(const char* _String);

// posix : atol
_XPOSIXAPI_ long __xcall__ x_posix_atol(const char* _String);

// posix : atoll
_XPOSIXAPI_ long long __xcall__ x_posix_atoll(const char* _String);

// posix : strtoul
_XPOSIXAPI_ unsigned long __xcall__ x_posix_strtoul(char const* _String, char** _EndPtr, int _Radix);





// 转换字符串至大写
_XPOSIXAPI_ char* x_posix_strtoupper(const char* _String);

// 转换字符串至小写
_XPOSIXAPI_ char* x_posix_strtolower(const char* _String);

// Replaces the specified character in the string
_XPOSIXAPI_ const char* x_string_replace_char(char* _String, char _Src, char _Dest);

// Replaces the specified character in the string
_XPOSIXAPI_ const wchar_t* x_string_replace_wchar_t(wchar_t* _String, wchar_t _Src, wchar_t _Dest);



/// Request the appropriate memory format string according to vsnprintf
/// \param _Format : C string that contains a format string that follows the same specifications as format in printf (see printf for details).
/// \param ... : Depending on the format string, the function may expect a sequence of additional arguments
/// \return : The formatted string pointer is returned if successful, and null if failed. Need to call x_posix_free() release
_XPOSIXAPI_ char* x_string_format(const char* _Format, ...);



/// Convert UTF-8 to UNICODE
/// \param _UTF8 : A UTF-8 string ending in NULL
/// \param _Unicode : Buffer for storing converted strings
/// \param _WLength : Length of Unicode buffer
/// \return : The number of bytes after conversion is returned on success and -1 on failure.
/// \return : When the parameter \param _Unicode or \param _Length is null, the required memory length is returned
_XPOSIXAPI_ int x_string_convert_utf8_to_unicode(const char* _UTF8, wchar_t* _Unicode, size_t _WLength);

/// Convert UNICODE to UTF-8
/// \param _Unicode : A Unicode string ending in NULL
/// \param _UTF8 : Buffer for storing converted strings
/// \param _ULength : Length of UTF8 buffer
/// \return : The number of bytes after conversion is returned on success and -1 on failure.
/// \return : When the parameter \param _UTF8 or \param _Length is null, the required memory length is returned
_XPOSIXAPI_ int x_string_convert_unicode_to_utf8(const wchar_t* _Unicode, char* _UTF8, size_t _ULength);


#if defined(__cplusplus)
}
#endif


#endif
