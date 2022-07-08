#include <xanadu-posix/locale.h>
#include <xanadu-posix/memory.h>



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

/// Convert UTF-8 to UNICODE
_XPOSIXAPI_ size_t __xcall__ x_posix_utftowcs(const char* _UTF8, wchar_t* _Unicode, size_t _WLength)
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
	size_t 			vULength = strlen((const char*)_UTF8);
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
				return (x_size_t)-1;
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
				return (x_size_t)-1;
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
				return (x_size_t)-1;
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
				return (x_size_t)-1;
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
				return (x_size_t)-1;
			}
			*(vUByte + 0)     = (u5 << 6) + (u6 & 0x3F);
			*(vUByte + 1) = (u5 << 4) + ((u6 >> 2) & 0x0F);
			*(vUByte + 2) = (u3 << 2) + ((u4 >> 4) & 0x03);
			*(vUByte + 3) = ((u1 << 6) & 0x40) + (u2 & 0x3F);
		}
		else
		{
			return (x_size_t)-1;
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
_XPOSIXAPI_ size_t __xcall__ x_posix_wcstoutf(const wchar_t* _Unicode, char* _UTF8, size_t _ULength)
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
			return (x_size_t)-1;
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
