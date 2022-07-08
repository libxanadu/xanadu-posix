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

// posix : strndup
_XPOSIXAPI_ char* __xcall__ x_posix_strndup(const char* _String, size_t _Length)
{
	if(_String == NULL)
	{
		return NULL;
	}

	char*		vMemory = x_posix_malloc(sizeof(char*) * (_Length + 1));
	if(vMemory)
	{
		x_posix_strncpy(vMemory, _String, _Length);
		vMemory[_Length] = '\0';
	}
	return vMemory;
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

// posix : wcsndup
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcsndup(const wchar_t* _String, size_t _Length)
{
	if(_String == NULL)
	{
		return NULL;
	}

	wchar_t*	vMemory = x_posix_malloc(sizeof(wchar_t*) * (_Length + 1));
	if(vMemory)
	{
		x_posix_wcsncpy(vMemory, _String, _Length);
		vMemory[_Length] = L'\0';
	}
	return vMemory;
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
	size_t 		vLength = x_posix_utftowcs(_UTF8, NULL, 0);
	if(vLength == (size_t)-1)
	{
		return NULL;
	}

	vUnicode = x_posix_malloc(sizeof(wchar_t) * (vLength + XANADU_STDIO_VSNPRINTF_EXTRA));
	if(vUnicode)
	{
		x_posix_memset(vUnicode, 0, sizeof(wchar_t) * (vLength + XANADU_STDIO_VSNPRINTF_EXTRA));
		x_posix_utftowcs(_UTF8, vUnicode, vLength);
	}
	return vUnicode;
}

// posix : stratow
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_stratow(const char* _ASCII)
{
	wchar_t*	vUnicode = NULL;
	x_size_t 	vLength = x_posix_mbstowcs(NULL, _ASCII ? _ASCII : "", 0);
	if(vLength == (x_size_t)-1)
	{
		return NULL;
	}

	vUnicode = (wchar_t*)x_posix_malloc(sizeof(wchar_t) * (vLength + XANADU_STDIO_VSNPRINTF_EXTRA));
	if(vUnicode)
	{
		x_posix_memset(vUnicode, 0, sizeof(wchar_t) * (vLength + XANADU_STDIO_VSNPRINTF_EXTRA));
		x_posix_mbstowcs(vUnicode, _ASCII, vLength);
	}
	return vUnicode;
}

// posix : strwtou
_XPOSIXAPI_ char* __xcall__ x_posix_strwtou(const wchar_t* _UNICODE)
{
	char*		vUtf8 = NULL;
	size_t		vLength = x_posix_wcstoutf(_UNICODE, NULL, 0);
	if(vLength == (size_t)-1)
	{
		return NULL;
	}

	vUtf8 = x_posix_malloc(sizeof(char) * (vLength + XANADU_STDIO_VSNPRINTF_EXTRA));
	if(vUtf8)
	{
		x_posix_memset(vUtf8, 0, sizeof(char) * (vLength + XANADU_STDIO_VSNPRINTF_EXTRA));
		x_posix_wcstoutf(_UNICODE, vUtf8, vLength);
	}
	return vUtf8;
}

// posix : strwtoa
_XPOSIXAPI_ char* __xcall__ x_posix_strwtoa(const wchar_t* _UNICODE)
{
	char*		vAscii = NULL;
	x_size_t 	vLength = x_posix_wcstombs(NULL, _UNICODE ? _UNICODE : L"", 0);
	if(vLength == (x_size_t)-1)
	{
		return NULL;
	}

	vAscii = (char*)x_posix_malloc(sizeof(char) * (vLength + XANADU_STDIO_VSNPRINTF_EXTRA));
	if(vAscii)
	{
		x_posix_memset(vAscii, 0, sizeof(char) * (vLength + XANADU_STDIO_VSNPRINTF_EXTRA));
		x_posix_wcstombs(vAscii, _UNICODE, vLength);
	}
	return vAscii;
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

// posix : strtoul
_XPOSIXAPI_ unsigned long __xcall__ x_posix_strtoul(const char* _String, char** _EndPtr, int _Radix)
{
	return strtoul(_String, _EndPtr, _Radix);
}

// posix : strtoll
_XPOSIXAPI_ long long __xcall__ x_posix_strtoll(const char* _String, char** _EndPtr, int _Radix)
{
	return strtoll(_String, _EndPtr, _Radix);
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
		return NULL;
	}
#endif
	char*		vUpper = x_posix_strdup(_String);
	x_posix_strupr(vUpper);
	return vUpper;
}

// 转换字符串至小写
_XPOSIXAPI_ char* __xcall__ x_posix_strtolower(const char* _String)
{
#if defined(XANADU_PARAMETER_VALIDATION)
	if(_String == NULL)
	{
		return NULL;
	}
#endif
	char*		vLower = x_posix_strdup(_String);
	x_posix_strlwr(vLower);
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
