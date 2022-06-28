#include <xanadu-posix/string.h>
#include <xanadu-posix/locale.h>
#include <xanadu-posix/memory.h>
#include <stdarg.h>



// posix : toupper
_XPOSIXAPI_ int __xcall__ x_posix_toupper(int _C)
{
	return toupper(_C);
}

// posix : tolower
_XPOSIXAPI_ int __xcall__ x_posix_tolower(int _C)
{
	return tolower(_C);
}





// posix : towupper
_XPOSIXAPI_ wchar_t __xcall__ x_posix_towupper(wchar_t _C)
{
	return towupper(_C);
}

// posix : towlower
_XPOSIXAPI_ wchar_t __xcall__ x_posix_towlower(wchar_t _C)
{
	return towlower(_C);
}





// posix : strlen
_XPOSIXAPI_ size_t __xcall__ x_posix_strlen(const char* _String)
{
	return strlen(_String ? _String : "");
}

// posix : strcmp
_XPOSIXAPI_ int __xcall__ x_posix_strcmp(const char* _Str1, const char* _Str2)
{
	if (_Str1 == _Str2)
	{
		return 0;
	}
	if (_Str1 && _Str2)
	{
		return strcmp(_Str1, _Str2);
	}
	else if(_Str1)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

// posix : stricmp
_XPOSIXAPI_ int __xcall__ x_posix_stricmp(const char* _Str1, const char* _Str2)
{
	if (_Str1 == _Str2)
	{
		return 0;
	}
	if (_Str1 && _Str2)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		return _stricmp(_Str1, _Str2);
#else
		return strcasecmp(_Str1, _Str2);
#endif
	}
	else if(_Str1)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

// posix : strcasecmp
_XPOSIXAPI_ int __xcall__ x_posix_strcasecmp(const char* _Str1, const char* _Str2)
{
	return x_posix_stricmp(_Str1, _Str2);
}

// posix : strncmp
_XPOSIXAPI_ int __xcall__ x_posix_strncmp(const char* _Str1, const char* _Str2, size_t _Length)
{
	if (_Str1 == _Str2)
	{
		return 0;
	}
	if (_Str1 && _Str2)
	{
		return strncmp(_Str1, _Str2, _Length);
	}
	else if(_Str1)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

// posix : strnicmp
_XPOSIXAPI_ int __xcall__ x_posix_strnicmp(const char* _Str1, const char* _Str2, size_t _Length)
{
	if (_Str1 == _Str2)
	{
		return 0;
	}
	if (_Str1 && _Str2)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		return _strnicmp(_Str1, _Str2, _Length);
#else
		return strncasecmp(_Str1, _Str2, _Length);
#endif
	}
	else if(_Str1)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

// posix : strchr
_XPOSIXAPI_ const char* __xcall__ x_posix_strchr(const char* _Str, int _Ch)
{
	if(_Str == NULL || _Ch == 0)
	{
		return NULL;
	}
	return strchr(_Str, _Ch);
}

// posix : strichr
_XPOSIXAPI_ const char* __xcall__ x_posix_strichr(const char* _Str, int _Ch)
{
	if(_Str == NULL || _Ch == 0)
	{
		return NULL;
	}
	_Ch = toupper(_Ch);
	while(*_Str != 0 && toupper(*_Str) != _Ch)
	{
		++_Str;
	}
	return _Str;
}

// posix : strrchr
_XPOSIXAPI_ const char* __xcall__ x_posix_strrchr(const char* _Str, int _Ch)
{
	if(_Str == NULL || _Ch == 0)
	{
		return NULL;
	}
	return strrchr(_Str, _Ch);
}

// posix : strirchr
_XPOSIXAPI_ const char* __xcall__ x_posix_strirchr(const char* _Str, int _Ch)
{
	if(_Str == NULL || _Ch == 0)
	{
		return NULL;
	}
	_Ch = toupper(_Ch);
	const char*	vEnd = _Str + x_posix_strlen(_Str) - 1;
	while(vEnd <= _Str && toupper(*vEnd) != _Ch)
	{
		--vEnd;
	}
	if(vEnd > _Str)
	{
		return NULL;
	}
	return vEnd;
}

// posix : strstr
_XPOSIXAPI_ const char* __xcall__ x_posix_strstr(const char* _Str, const char* _SubStr)
{
	if(_Str == NULL || _SubStr == NULL)
	{
		return NULL;
	}
	return strstr(_Str, _SubStr);
}

// posix : stristr
_XPOSIXAPI_ const char* __xcall__ x_posix_stristr(const char* _Str, const char* _SubStr)
{
	if(_Str == NULL || _SubStr == NULL)
	{
		return NULL;
	}

	if(0 == *_SubStr)
	{
		return _Str;
	}

	const char*		s1 = NULL;
	const char*		s2 = NULL;

	while(0 != *_Str)
	{
		s1 = _Str;
		s2 = _SubStr;

		while(*s1 && *s2 && !(tolower(*s1) - tolower(*s2)))
		{
			++s1;
			++s2;
		}
		if (!*s2)
		{
			return _Str;
		}
		++_Str;
	}
	return NULL;
}

// posix : strrstr
_XPOSIXAPI_ const char* __xcall__ x_posix_strrstr(const char* _Str, const char* _SubStr)
{
	int 		vIndex = 0;
	if(_Str && _SubStr)
	{
		size_t		vStrLength = x_posix_strlen(_Str);
		size_t		vSubLength = x_posix_strlen(_SubStr);
		if(vStrLength && vSubLength && vStrLength >= vSubLength)
		{
			for(vIndex = (int)(vStrLength - vSubLength); vIndex >= 0; --vIndex)
			{
				if(x_posix_strcmp(_Str + vIndex, _SubStr) == 0)
				{
					return _Str + vIndex;
				}
			}
		}
	}
	return NULL;
}

// posix : strirstr
_XPOSIXAPI_ const char* __xcall__ x_posix_strirstr(const char* _Str, const char* _SubStr)
{
	int 		vIndex = 0;
	if(_Str && _SubStr)
	{
		size_t		vStrLength = x_posix_strlen(_Str);
		size_t		vSubLength = x_posix_strlen(_SubStr);
		if(vStrLength && vSubLength && vStrLength >= vSubLength)
		{
			for(vIndex = (int)(vStrLength - vSubLength); vIndex >= 0; --vIndex)
			{
				if(x_posix_stricmp(_Str + vIndex, _SubStr) == 0)
				{
					return _Str + vIndex;
				}
			}
		}
	}
	return NULL;
}

// posix : strcpy
_XPOSIXAPI_ char* __xcall__ x_posix_strcpy(char* _Dst, const char* _Source)
{
	return strcpy(_Dst, _Source);
}

// posix : strncpy
_XPOSIXAPI_ char* __xcall__ x_posix_strncpy(char* _Dst, const char* _Source, size_t _Length)
{
	return strncpy(_Dst, _Source, _Length);
}

// posix : strcat
_XPOSIXAPI_ char* __xcall__ x_posix_strcat(char* _Str1, const char* _Str2)
{
	return strcat(_Str1, _Str2);
}

// posix : strncat
_XPOSIXAPI_ char* __xcall__ x_posix_strncat(char* _Str1, const char* _Str2, size_t _Length)
{
	return strncat(_Str1, _Str2, _Length);
}

// posix : strdup
_XPOSIXAPI_ char* __xcall__ x_posix_strdup(const char* _String)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return _strdup(_String ? _String : "");
#else
	return strdup(_String ? _String : "");
#endif
}

// posix : strupr
_XPOSIXAPI_ char* __xcall__ x_posix_strupr(char* _String)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return _String ? _strupr(_String) : NULL;
#else
	size_t 		vSize = x_posix_strlen(_String);
	for(size_t vPos = 0; vPos < vSize; ++vPos)
	{
		_String[vPos] = (char)toupper(_String[vPos]);
	}
	return _String;
#endif
}

// posix : strlwr
_XPOSIXAPI_ char* __xcall__ x_posix_strlwr(char* _String)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return _String ? _strlwr(_String) : NULL;
#else
	size_t 		vSize = x_posix_strlen(_String);
	for(size_t vPos = 0; vPos < vSize; ++vPos)
	{
		_String[vPos] = (char)tolower(_String[vPos]);
	}
	return _String;
#endif
}

// posix : strrev
_XPOSIXAPI_ char* __xcall__ x_posix_strrev(char* _String)
{
	return x_posix_memrev(_String, _String ? strlen(_String) : 0);
}





// posix : wcslen
_XPOSIXAPI_ size_t __xcall__ x_posix_wcslen(const wchar_t* _String)
{
	return wcslen(_String ? _String : L"");
}

// posix : wcscmp
_XPOSIXAPI_ int __xcall__ x_posix_wcscmp(const wchar_t* _Str1, const wchar_t* _Str2)
{
	if (_Str1 == _Str2)
	{
		return 0;
	}
	if (_Str1 && _Str2)
	{
		return wcscmp(_Str1, _Str2);
	}
	else if(_Str1)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

// posix : wcsicmp
_XPOSIXAPI_ int __xcall__ x_posix_wcsicmp(const wchar_t* _Str1, const wchar_t* _Str2)
{
	if (_Str1 == _Str2)
	{
		return 0;
	}
	if (_Str1 && _Str2)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		return _wcsicmp(_Str1, _Str2);
#else
		return wcscasecmp(_Str1, _Str2);
#endif
	}
	else if(_Str1)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

// posix : wcscasecmp
_XPOSIXAPI_ int __xcall__ x_posix_wcscasecmp(const wchar_t* _Str1, const wchar_t* _Str2)
{
	return x_posix_wcsicmp(_Str1, _Str2);
}

// posix : wcsncmp
_XPOSIXAPI_ int __xcall__ x_posix_wcsncmp(const wchar_t* _Str1, const wchar_t* _Str2, size_t _Length)
{
	if (_Str1 == _Str2)
	{
		return 0;
	}
	if (_Str1 && _Str2)
	{
		return wcsncmp(_Str1, _Str2, _Length);
	}
	else if(_Str1)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

// posix : wcschr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wcschr(const wchar_t* _Str, wchar_t _Ch)
{
	if(_Str == NULL || _Ch == 0)
	{
		return NULL;
	}
	return wcschr(_Str, _Ch);
}

// posix : wcsichr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wcsichr(const wchar_t* _Str, wchar_t _Ch)
{
	if(_Str == NULL || _Ch == 0)
	{
		return NULL;
	}
	_Ch = towupper(_Ch);
	while(*_Str != 0 && towupper(*_Str) != (wint_t)_Ch)
	{
		++_Str;
	}
	return _Str;
}

// posix : wcsrchr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wcsrchr(const wchar_t* _Str, wchar_t _Ch)
{
	if(_Str == NULL || _Ch == 0)
	{
		return NULL;
	}
	return wcsrchr(_Str, _Ch);
}

// posix : wcsirchr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wcsirchr(const wchar_t* _Str, wchar_t _Ch)
{
	if(_Str == NULL || _Ch == 0)
	{
		return NULL;
	}
	_Ch = towupper(_Ch);
	const wchar_t*	vEnd = _Str + x_posix_wcslen(_Str) - 1;
	while(vEnd <= _Str && towupper(*vEnd) != (wint_t)_Ch)
	{
		--vEnd;
	}
	if(vEnd > _Str)
	{
		return NULL;
	}
	return vEnd;
}

// posix : wcsstr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wcsstr(const wchar_t* _Str, const wchar_t* _SubStr)
{
	if(_Str == NULL || _SubStr == NULL)
	{
		return NULL;
	}
	return wcsstr(_Str, _SubStr);
}

// posix : wcsistr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wcsistr(const wchar_t* _Str, const wchar_t* _SubStr)
{
	if(_Str == NULL || _SubStr == NULL)
	{
		return NULL;
	}

	if(0 == *_SubStr)
	{
		return _Str;
	}

	const wchar_t*		s1 = NULL;
	const wchar_t*		s2 = NULL;

	while(0 != *_Str)
	{
		s1 = _Str;
		s2 = _SubStr;

		while(*s1 && *s2 && !(towlower(*s1) - towlower(*s2)))
		{
			++s1;
			++s2;
		}
		if (!*s2)
		{
			return _Str;
		}
		++_Str;
	}
	return NULL;
}

// posix : wcscpy
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcscpy(wchar_t* _Dst, const wchar_t* _Source)
{
	return wcscpy(_Dst, _Source);
}

// posix : wcsncpy
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcsncpy(wchar_t* _Dst, const wchar_t* _Source, size_t _Length)
{
	return wcsncpy(_Dst, _Source, _Length);
}

// posix : wcscat
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcscat(wchar_t* _Str1, const wchar_t* _Str2)
{
	return wcscat(_Str1, _Str2);
}

// posix : wcsncat
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcsncat(wchar_t* _Str1, const wchar_t* _Str2, size_t _Length)
{
	return wcsncat(_Str1, _Str2, _Length);
}

// posix : wcsdup
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcsdup(const wchar_t* _String)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return _wcsdup(_String ? _String : L"");
#else
	return wcsdup(_String ? _String : L"");
#endif
}

// posix : wcsupr
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcsupr(wchar_t* _String)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return _String ? _wcsupr(_String) : NULL;
#else
	size_t 		vSize = x_posix_wcslen(_String);
	for(size_t vPos = 0; vPos < vSize; ++vPos)
	{
		_String[vPos] = towupper(_String[vPos]);
	}
	return _String;
#endif
}

// posix : wcslwr
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcslwr(wchar_t* _String)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return _String ? _wcslwr(_String) : NULL;
#else
	size_t 		vSize = x_posix_wcslen(_String);
	for(size_t vPos = 0; vPos < vSize; ++vPos)
	{
		_String[vPos] = towlower(_String[vPos]);
	}
	return _String;
#endif
}

// posix : wcsrev
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcsrev(wchar_t* _String)
{
	return x_posix_wmemrev(_String, _String ? wcslen(_String) : 0);
}





// posix : strutow
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_strutow(const char* _UTF8)
{
	wchar_t*	vUnicode = NULL;
	size_t 		vLength = x_string_convert_utf8_to_unicode(_UTF8, NULL, 0) + XANADU_STDIO_VSNPRINTF_EXTRA;
	if(vLength == (size_t)-1)
	{
		return NULL;
	}
	vUnicode = x_posix_malloc(sizeof(wchar_t) * vLength);
	if(vUnicode)
	{
		x_posix_memset(vUnicode, 0, sizeof(wchar_t) * vLength);
		x_string_convert_utf8_to_unicode(_UTF8, vUnicode, vLength);
	}
	return vUnicode;
}

// posix : stratow
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_stratow(const char* _ASCII)
{
	size_t 		vLength = 0;
	wchar_t*	vUnicode = NULL;
	if(_ASCII)
	{
		vLength = (x_posix_strlen(_ASCII) * 2) + XANADU_STDIO_VSNPRINTF_EXTRA;
		vUnicode = (wchar_t*)x_posix_malloc(sizeof(wchar_t) * vLength);
		if(vUnicode)
		{
			x_posix_wmemset(vUnicode, 0, vLength);
			x_posix_mbstowcs(vUnicode, _ASCII, vLength);
			return vUnicode;
		}
	}
	return NULL;
}

// posix : strwtou
_XPOSIXAPI_ char* __xcall__ x_posix_strwtou(const wchar_t* _UNICODE)
{
	char*		vUtf8 = NULL;
	size_t		vLength = x_string_convert_unicode_to_utf8(_UNICODE, NULL, 0) + XANADU_STDIO_VSNPRINTF_EXTRA;
	if(vLength == (size_t)-1)
	{
		return NULL;
	}
	vUtf8 = x_posix_malloc(sizeof(char) * vLength);
	if(vUtf8)
	{
		x_posix_memset(vUtf8, 0, sizeof(char) * vLength);
		x_string_convert_unicode_to_utf8(_UNICODE, vUtf8, vLength);
	}
	return vUtf8;
}

// posix : strwtoa
_XPOSIXAPI_ char* __xcall__ x_posix_strwtoa(const wchar_t* _UNICODE)
{
	size_t 		vLength = 0;
	char*		vAscii = NULL;
	if(_UNICODE)
	{
		vLength = (x_posix_wcslen(_UNICODE) * 4) + XANADU_STDIO_VSNPRINTF_EXTRA;
		vAscii = (char*)x_posix_malloc(vLength);
		if(vAscii)
		{
			x_posix_memset(vAscii, 0, vLength);
			x_posix_wcstombs(vAscii, _UNICODE, vLength);
			return vAscii;
		}
	}
	return NULL;
}





// posix : atof
_XPOSIXAPI_ double __xcall__ x_posix_atof(const char* _String)
{
	return atof(_String);
}

// posix : atoi
_XPOSIXAPI_ int __xcall__ x_posix_atoi(const char* _String)
{
	return atoi(_String);
}

// posix : atol
_XPOSIXAPI_ long __xcall__ x_posix_atol(const char* _String)
{
	return atol(_String);
}

// posix : atoll
_XPOSIXAPI_ long long __xcall__ x_posix_atoll(const char* _String)
{
	return atoll(_String);
}

// posix : strtof
_XPOSIXAPI_ float __xcall__ x_posix_strtof(const char* _String, char** _EndPtr)
{
	return strtof(_String, _EndPtr);
}

// posix : strtod
_XPOSIXAPI_ double __xcall__ x_posix_strtod(const char* _String, char** _EndPtr)
{
	return strtod(_String, _EndPtr);
}

// posix : strtold
_XPOSIXAPI_ long double __xcall__ x_posix_strtold(const char* _String, char** _EndPtr)
{
	return strtold(_String, _EndPtr);
}

// posix : strtol
_XPOSIXAPI_ long __xcall__ x_posix_strtol(const char* _String, char** _EndPtr, int _Radix)
{
	return strtol(_String, _EndPtr, _Radix);
}

// posix : strtoll
_XPOSIXAPI_ long long __xcall__ x_posix_strtoll(const char* _String, char** _EndPtr, int _Radix)
{
	return strtoll(_String, _EndPtr, _Radix);
}

// posix : strtoul
_XPOSIXAPI_ unsigned long __xcall__ x_posix_strtoul(const char* _String, char** _EndPtr, int _Radix)
{
	return strtoul(_String, _EndPtr, _Radix);
}

// posix : strtoull
_XPOSIXAPI_ unsigned long long __xcall__ x_posix_strtoull(const char* _String, char** _EndPtr, int _Radix)
{
	return strtoull(_String, _EndPtr, _Radix);
}





// 转换字符串至大写
_XPOSIXAPI_ char* __xcall__ x_posix_strtoupper(const char* _String)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_String == NULL)
	{
		return x_posix_strdup("");
	}
#endif
	char*		vUpper = x_posix_strdup(_String);
	uint64_t 	vLength = x_posix_strlen(vUpper);
	for(uint64_t vIndex = 0; vIndex < vLength; ++vIndex)
	{
		vUpper[vIndex] = (char)toupper(vUpper[vIndex]);
	}
	return vUpper;
}

// 转换字符串至小写
_XPOSIXAPI_ char* __xcall__ x_posix_strtolower(const char* _String)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_String == NULL)
	{
		return x_posix_strdup("");
	}
#endif
	char*		vLower = x_posix_strdup(_String);
	uint64_t 	vLength = x_posix_strlen(vLower);
	for(uint64_t vIndex = 0; vIndex < vLength; ++vIndex)
	{
		vLower[vIndex] = (char)tolower(vLower[vIndex]);
	}
	return vLower;
}

// Replaces the specified character in the string
_XPOSIXAPI_ const char* __xcall__ x_string_replace_char(char* _String, char _Src, char _Dest)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_String == NULL)
	{
		return NULL;
	}
#endif
	size_t 		vLength = x_posix_strlen(_String);
	for(size_t vIndex = 0; vIndex < vLength; ++vIndex)
	{
		if(_String[vIndex] == _Src)
		{
			_String[vIndex] = _Dest;
		}
	}
	return _String;
}

// Replaces the specified character in the string
_XPOSIXAPI_ const wchar_t* __xcall__ x_string_replace_wchar_t(wchar_t* _String, wchar_t _Src, wchar_t _Dest)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_String == NULL)
	{
		return NULL;
	}
#endif
	size_t 		vLength = wcslen(_String);
	for(size_t vIndex = 0; vIndex < vLength; ++vIndex)
	{
		if(_String[vIndex] == _Src)
		{
			_String[vIndex] = _Dest;
		}
	}
	return _String;
}





/// Request the appropriate memory format string according to vsnprintf
_XPOSIXAPI_ char* __xcall__ x_string_format(const char* _Format, ...)
{
	char*		vString = NULL;
	va_list		vArgs1;
	va_list		vArgs2;
	va_start(vArgs1, _Format);
	va_copy(vArgs2, vArgs1);
	int		vSize = vsnprintf(NULL, 0, _Format, vArgs1);
	if(vSize > 0)
	{
		vString = x_posix_malloc(vSize + XANADU_STDIO_VSNPRINTF_EXTRA);
		if(vString)
		{
			x_posix_memset(vString, 0, vSize + XANADU_STDIO_VSNPRINTF_EXTRA);
			vsnprintf(vString, vSize + XANADU_STDIO_VSNPRINTF_EXTRA, _Format, vArgs2);
		}
	}
	else
	{
		vString = (char*)x_posix_malloc(XANADU_STDIO_VSNPRINTF_EXTRA);
		x_posix_memset(vString, 0, XANADU_STDIO_VSNPRINTF_EXTRA);
	}
	va_end(vArgs1);
	va_end(vArgs2);
	return vString;
}





/// Convert UTF-8 to UNICODE
_XPOSIXAPI_ int __xcall__ x_string_convert_utf8_to_unicode(const char* _UTF8, wchar_t* _Unicode, size_t _WLength)
{
	if(_UTF8 == NULL)
	{
		return -1;
	}

	unsigned char		u1 = 0;
	unsigned char		u2 = 0;
	unsigned char		u3 = 0;
	unsigned char		u4 = 0;
	unsigned char		u5 = 0;
	unsigned char		u6 = 0;

	unsigned int		vUChar = 0;
	unsigned char*		vUByte = (unsigned char*)&vUChar;
	size_t 			vUIndex = 0;
	size_t 			vULength = x_posix_strlen((const char*)_UTF8);
	unsigned char		vChar = 0;
	size_t 			vPos = 0;

	while(vUIndex < vULength)
	{
		vUChar = 0;
		vChar = _UTF8[vUIndex];
		if(vChar <= 0x7F && vULength - vUIndex >= 1)
		{
			// U-00000000 - U-0000007F: 0xxxxxxx
			*(vUByte + 0) = _UTF8[vUIndex++];
		}
		else if(0xC0 <= vChar && vChar <= 0xDF && vULength - vUIndex >= 2)
		{
			// U-00000080 - U-000007FF: 110xxxxx 10xxxxxx
			u1 = _UTF8[vUIndex++];
			u2 = _UTF8[vUIndex++];
			if ( (u2 & 0xE0) != 0x80 )
			{
				return -1;
			}
			*(vUByte + 0)     = (u1 << 6) + (u2 & 0x3F);
			*(vUByte + 1) = (u1 >> 2) & 0x07;
		}
		else if(0xE0 <= vChar && vChar <= 0xEF && vULength - vUIndex >= 3)
		{
			// U-00000800 - U-0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx
			u1 = _UTF8[vUIndex++];
			u2 = _UTF8[vUIndex++];
			u3 = _UTF8[vUIndex++];
			if ( ((u2 & 0xC0) != 0x80) || ((u3 & 0xC0) != 0x80) )
			{
				return -1;
			}
			*(vUByte + 0)     = (u2 << 6) + (u3 & 0x3F);
			*(vUByte + 1) = (u1 << 4) + ((u2 >> 2) & 0x0F);
		}
		else if(0xF0 <= vChar && vChar <= 0xF7 && vULength - vUIndex >= 4)
		{
			// U-00010000 - U-001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
			u1 = _UTF8[vUIndex++];
			u2 = _UTF8[vUIndex++];
			u3 = _UTF8[vUIndex++];
			u4 = _UTF8[vUIndex++];
			if ( ((u2 & 0xC0) != 0x80) || ((u3 & 0xC0) != 0x80) || ((u4 & 0xC0) != 0x80) )
			{
				return -1;
			}
			*(vUByte + 0)     = (u3 << 6) + (u4 & 0x3F);
			*(vUByte + 1) = (u2 << 4) + ((u3 >> 2) & 0x0F);
			*(vUByte + 2) = ((u1 << 2) & 0x1C)  + ((u2 >> 4) & 0x03);
		}
		else if(0xF8 <= vChar && vChar <= 0xFB && vULength - vUIndex >= 5)
		{
			// U-00200000 - U-03FFFFFF: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
			u1 = _UTF8[vUIndex++];
			u2 = _UTF8[vUIndex++];
			u3 = _UTF8[vUIndex++];
			u4 = _UTF8[vUIndex++];
			u5 = _UTF8[vUIndex++];
			if ( ((u2 & 0xC0) != 0x80) || ((u3 & 0xC0) != 0x80) || ((u4 & 0xC0) != 0x80) || ((u5 & 0xC0) != 0x80) )
			{
				return -1;
			}
			*(vUByte + 0)     = (u4 << 6) + (u5 & 0x3F);
			*(vUByte + 1) = (u3 << 4) + ((u4 >> 2) & 0x0F);
			*(vUByte + 2) = (u2 << 2) + ((u3 >> 4) & 0x03);
			*(vUByte + 3) = (u1 << 6);
		}
		else if(0xFC <= vChar && vChar <= 0xFD && vULength - vUIndex >= 6)
		{
			// U-04000000 - U-7FFFFFFF: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
			u1 = _UTF8[vUIndex++];
			u2 = _UTF8[vUIndex++];
			u3 = _UTF8[vUIndex++];
			u4 = _UTF8[vUIndex++];
			u5 = _UTF8[vUIndex++];
			u6 = _UTF8[vUIndex++];
			if ( ((u2 & 0xC0) != 0x80) || ((u3 & 0xC0) != 0x80) || ((u4 & 0xC0) != 0x80) || ((u5 & 0xC0) != 0x80) || ((u6 & 0xC0) != 0x80) )
			{
				return -1;
			}
			*(vUByte + 0)     = (u5 << 6) + (u6 & 0x3F);
			*(vUByte + 1) = (u5 << 4) + ((u6 >> 2) & 0x0F);
			*(vUByte + 2) = (u3 << 2) + ((u4 >> 4) & 0x03);
			*(vUByte + 3) = ((u1 << 6) & 0x40) + (u2 & 0x3F);
		}
		else
		{
			return -1;
		}

		if(_Unicode && _WLength > vPos)
		{
			_Unicode[vPos] = (wchar_t)vUChar;
		}
		++vPos;
	}
	if(_Unicode && _WLength > vPos)
	{
		_Unicode[vPos] = 0;
	}
	return (int)vPos + 1;
}

/// Convert UNICODE to UTF-8
_XPOSIXAPI_ int __xcall__ x_string_convert_unicode_to_utf8(const wchar_t* _Unicode, char* _UTF8, size_t _ULength)
{
	if(_Unicode == NULL)
	{
		return -1;
	}

	size_t 			vWPos = 0;
	size_t 			vUPos = 0;
	size_t 			vLength = wcslen(_Unicode);
	size_t 			vCSize = 0;
	unsigned int 		vChar = 0;
	unsigned char		vUBytes[6] = {0};

	while(vWPos < vLength)
	{
		vCSize = 0;
		vChar = _Unicode[vWPos++];
		if(vChar <= 0x0000007F)
		{
			vUBytes[vCSize++] = vChar & 0x7F;
		}
		else if(0x00000080 <= vChar && vChar <= 0x000007FF)
		{
			vUBytes[vCSize++] = ((vChar >>  6) & 0x1F) | 0xC0;
			vUBytes[vCSize++] = ((vChar >>  0) & 0x3F) | 0x80;
		}
		else if(0x00000800 <= vChar && vChar <= 0x0000FFFF)
		{
			vUBytes[vCSize++] = ((vChar >> 12) & 0x0F) | 0xE0;
			vUBytes[vCSize++] = ((vChar >>  6) & 0x3F) | 0x80;
			vUBytes[vCSize++] = ((vChar >>  0) & 0x3F) | 0x80;
		}
		else if(0x00010000 <= vChar && vChar <= 0x001FFFFF)
		{
			vUBytes[vCSize++] = ((vChar >> 18) & 0x07) | 0xF0;
			vUBytes[vCSize++] = ((vChar >> 12) & 0x3F) | 0x80;
			vUBytes[vCSize++] = ((vChar >>  6) & 0x3F) | 0x80;
			vUBytes[vCSize++] = ((vChar >>  0) & 0x3F) | 0x80;
		}
		else if(0x00200000 <= vChar && vChar <= 0x03FFFFFF)
		{
			vUBytes[vCSize++] = ((vChar >> 24) & 0x03) | 0xF8;
			vUBytes[vCSize++] = ((vChar >> 18) & 0x3F) | 0x80;
			vUBytes[vCSize++] = ((vChar >> 12) & 0x3F) | 0x80;
			vUBytes[vCSize++] = ((vChar >>  6) & 0x3F) | 0x80;
			vUBytes[vCSize++] = ((vChar >>  0) & 0x3F) | 0x80;
		}
		else if(0x04000000 <= vChar && vChar <= 0x7FFFFFFF)
		{
			vUBytes[vCSize++] = ((vChar >> 30) & 0x01) | 0xFC;
			vUBytes[vCSize++] = ((vChar >> 24) & 0x3F) | 0x80;
			vUBytes[vCSize++] = ((vChar >> 18) & 0x3F) | 0x80;
			vUBytes[vCSize++] = ((vChar >> 12) & 0x3F) | 0x80;
			vUBytes[vCSize++] = ((vChar >>  6) & 0x3F) | 0x80;
			vUBytes[vCSize++] = ((vChar >>  0) & 0x3F) | 0x80;
		}
		else
		{
			return -1;
		}

		if(_UTF8 && _ULength - vUPos > vCSize)
		{
			x_posix_memcpy(_UTF8 + vUPos, vUBytes, vCSize);
		}
		vUPos += vCSize;
	}
	if(_UTF8 && _ULength > vUPos)
	{
		_UTF8[vUPos] = 0;
	}
	return (int)vUPos + 1;
}
