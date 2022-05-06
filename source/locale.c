#include <xanadu-posix/locale.h>



// posix : setlocale
_XPOSIXAPI_ char* __xcall__ x_posix_setlocale(int _Category, const char* _Locale)
{
	return setlocale(_Category, _Locale);
}

// posix : wcstombs
_XPOSIXAPI_ size_t __xcall__ x_posix_wcstombs(char* _MBS, const wchar_t* _WCS, size_t _Length)
{
	if(_MBS == NULL)
	{
		return 0;
	}
	return wcstombs(_MBS, _WCS, _Length);
}

// posix : mbstowcs
_XPOSIXAPI_ size_t __xcall__ x_posix_mbstowcs(wchar_t* _WCS, const char* _MBS, size_t _Length)
{
	if(_WCS == NULL)
	{
		return 0;
	}
	return mbstowcs(_WCS, _MBS, _Length);
}
