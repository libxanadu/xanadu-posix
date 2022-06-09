#include <xanadu-posix/base64.h>
#include <xanadu-posix/memory.h>



// Encode the memory of the specified length as Base64
_XPOSIXAPI_ bool __xcall__ x_base64_encode(const unsigned char* _Memory, size_t _Length, unsigned char** _Output, size_t* _Size)
{
	if(_Memory == NULL || _Length == 0 || _Output == NULL || _Size == NULL)
	{
		return false;
	}

	const char		vAlphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	const unsigned char*	vByteArray = _Memory;
	const char		vPadChar = '=';
	int			vPadLength = 0;
	size_t			vIndex = 0;
	size_t 			vEncodeSize = ((_Length + 2) / 3 * 4) + 1;
	size_t			vEncodeIndex = 0;
	unsigned char*		vEncodeData = (unsigned char*)x_posix_malloc(vEncodeSize);
	while(vIndex < _Length && vEncodeData)
	{
		// encode 3 bytes at a time
		int		vChunk = 0;
		vChunk |= ((int)((unsigned char)(vByteArray[vIndex++]))) << 16;
		if(vIndex == _Length)
		{
			vPadLength = 2;
		}
		else
		{
			vChunk |= (int)((unsigned char)(vByteArray[vIndex++])) << 8;
			if(vIndex == _Length)
			{
				vPadLength = 1;
			}
			else
			{
				vChunk |= (int)((unsigned char)(vByteArray[vIndex++]));
			}
		}

		unsigned char	vValue1 = (unsigned char)((vChunk & 0x00FC0000) >> 18);
		unsigned char	vValue2 = (unsigned char)((vChunk & 0x0003F000) >> 12);
		unsigned char	vValue3 = (unsigned char)((vChunk & 0x00000FC0) >> 6);
		unsigned char	vValue4 = (unsigned char)(vChunk & 0x0000003F);
		vEncodeData[vEncodeIndex++] = vAlphabet[vValue1];
		vEncodeData[vEncodeIndex++] = vAlphabet[vValue2];

		if(vPadLength > 1)
		{
			vEncodeData[vEncodeIndex++] = vPadChar;
		}
		else
		{
			vEncodeData[vEncodeIndex++] = vAlphabet[vValue3];
		}
		if(vPadLength > 0)
		{
			vEncodeData[vEncodeIndex++] = vPadChar;
		}
		else
		{
			vEncodeData[vEncodeIndex++] = vAlphabet[vValue4];
		}
	}
	if(vEncodeData)
	{
		vEncodeData[vEncodeIndex] = 0;
		*_Size = vEncodeIndex;
		*_Output = vEncodeData;
		return true;
	}
	return false;
}

// Decode a segment of Base64 memory
_XPOSIXAPI_ bool __xcall__ x_base64_decode(const unsigned char* _Memory, size_t _Length, unsigned char** _Output, size_t* _Size)
{
	if(_Memory == NULL || 0 == _Length || (_Length % 4) || _Output == NULL || _Size == NULL)
	{
		return false;
	}

	unsigned int	vBuffer = 0;
	int		vBits = 0;
	int		vOffset = 0;
	uint32_t 	vDecodeSize = ((_Length * 3) / 4) + 1;
	unsigned char*	vDecodeData = (unsigned char*)x_posix_malloc(vDecodeSize);

	for(size_t vIndex = 0; vIndex < _Length && vDecodeData; ++vIndex)
	{
		int		vChar = _Memory[vIndex];
		int		vValue = 0;

		if(vChar >= 'A' && vChar <= 'Z')
		{
			vValue = vChar - 'A';
		}
		else if(vChar >= 'a' && vChar <= 'z')
		{
			vValue = vChar - 'a' + 26;
		}
		else if(vChar >= '0' && vChar <= '9')
		{
			vValue = vChar - '0' + 52;
		}
		else if(vChar == '+')
		{
			vValue = 62;
		}
		else if(vChar == '/')
		{
			vValue = 63;
		}
		else
		{
			vValue = -1;
		}

		if(vValue != -1)
		{
			vBuffer = (vBuffer << 6) | vValue;
			vBits += 6;
			if(vBits >= 8)
			{
				vBits -= 8;
				vDecodeData[vOffset++] = (char)(vBuffer >> vBits);
				vBuffer &= (1 << vBits) - 1;
			}
		}
	}
	if(vDecodeData)
	{
		vDecodeData[vOffset] = 0;
		*_Size = vOffset;
		*_Output = vDecodeData;
		return true;
	}
	return false;
}
