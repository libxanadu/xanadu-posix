#include <xanadu-posix/endian.h>



// Check whether the operating system is in big-endian order
_XPOSIXAPI_ bool __xcall__ x_endian_is_big()
{
	return !x_endian_is_little();
}

// Check whether the operating system is in little-endian order
_XPOSIXAPI_ bool __xcall__ x_endian_is_little()
{
	union UCheck_Little
	{
		int		_VALUE4;
		char		_VALUE1;
	}_ValueLittle;
	_ValueLittle._VALUE4 = 1;
	// The big-endian returns 0 and the little-endian returns 1
	return _ValueLittle._VALUE1 == 1;
}





// Ignore byte order and force reverse order : unsigned short
_XPOSIXAPI_ unsigned short __xcall__ x_endian_reverse_16(unsigned short _Number)
{
	return (((_Number & 0xFF00U) >> 8) | ((_Number & 0x00FFU) << 8));
}

// Ignore byte order and force reverse order : unsigned int
_XPOSIXAPI_ unsigned int __xcall__ x_endian_reverse_32(unsigned int _Number)
{
	return (((_Number & 0xFF000000U) >> 24) | ((_Number & 0x00FF0000U) >> 8) | ((_Number & 0x0000FF00U) << 8) | ((_Number & 0x000000FFU) << 24));
}

// Ignore byte order and force reverse order : unsigned short
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_reverse_64(unsigned long long _Number)
{
	return (((_Number & 0x00000000000000FFULL) << 56) | ((_Number & 0x000000000000FF00ULL) << 40) |
		((_Number & 0x0000000000FF0000ULL) << 24) | ((_Number & 0x00000000FF000000ULL) << 8) |
		((_Number & 0x000000FF00000000ULL) >> 8) | ((_Number & 0x0000FF0000000000ULL) >> 24) |
		((_Number & 0x00FF000000000000ULL) >> 40) | ((_Number & 0xFF00000000000000ULL) >> 56));
}





// CAutomatic conversion according to byte order : unsigned short
_XPOSIXAPI_ unsigned short __xcall__ x_endian_convert_16(unsigned short _Number)
{
	if(x_endian_is_little())
	{
		return (((_Number & 0xFF00U) >> 8) | ((_Number & 0x00FFU) << 8));
	}
	return _Number;
}

// Automatic conversion according to byte order : unsigned int
_XPOSIXAPI_ unsigned int __xcall__ x_endian_convert_32(unsigned int _Number)
{
	if(x_endian_is_little())
	{
		return (((_Number & 0xFF000000U) >> 24) | ((_Number & 0x00FF0000U) >> 8) | ((_Number & 0x0000FF00U) << 8) | ((_Number & 0x000000FFU) << 24));
	}
	return _Number;
}

// Automatic conversion according to byte order : unsigned short
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_convert_64(unsigned long long _Number)
{
	if(x_endian_is_little())
	{
		return (((_Number & 0x00000000000000FFULL) << 56) | ((_Number & 0x000000000000FF00ULL) << 40) |
			((_Number & 0x0000000000FF0000ULL) << 24) | ((_Number & 0x00000000FF000000ULL) << 8) |
			((_Number & 0x000000FF00000000ULL) >> 8) | ((_Number & 0x0000FF0000000000ULL) >> 24) |
			((_Number & 0x00FF000000000000ULL) >> 40) | ((_Number & 0xFF00000000000000ULL) >> 56));
	}
	return _Number;
}





// Conversion from native byte order to network byte order : unsigned short
_XPOSIXAPI_ unsigned short __xcall__ x_endian_host_to_network_16(unsigned short _Number)
{
	if(x_endian_is_little())
	{
		return (((_Number & 0xFF00U) >> 8) | ((_Number & 0x00FFU) << 8));
	}
	return _Number;
}

// Conversion from native byte order to network byte order : unsigned int
_XPOSIXAPI_ unsigned int __xcall__ x_endian_host_to_network_32(unsigned int _Number)
{
	if(x_endian_is_little())
	{
		return (((_Number & 0xFF000000U) >> 24) | ((_Number & 0x00FF0000U) >> 8) | ((_Number & 0x0000FF00U) << 8) | ((_Number & 0x000000FFU) << 24));
	}
	return _Number;
}

// Conversion from native byte order to network byte order : unsigned short
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_host_to_network_64(unsigned long long _Number)
{
	if(x_endian_is_little())
	{
		return (((_Number & 0x00000000000000FFULL) << 56) | ((_Number & 0x000000000000FF00ULL) << 40) |
			((_Number & 0x0000000000FF0000ULL) << 24) | ((_Number & 0x00000000FF000000ULL) << 8) |
			((_Number & 0x000000FF00000000ULL) >> 8) | ((_Number & 0x0000FF0000000000ULL) >> 24) |
			((_Number & 0x00FF000000000000ULL) >> 40) | ((_Number & 0xFF00000000000000ULL) >> 56));
	}
	return _Number;
}

// Conversion from network byte order to native byte order : unsigned short
_XPOSIXAPI_ unsigned short __xcall__ x_endian_network_to_host_16(unsigned short _Number)
{
	if(x_endian_is_little())
	{
		return (((_Number & 0xFF00U) >> 8) | ((_Number & 0x00FFU) << 8));
	}
	return _Number;
}

// Conversion from network byte order to native byte order : unsigned int
_XPOSIXAPI_ unsigned int __xcall__ x_endian_network_to_host_32(unsigned int _Number)
{
	if(x_endian_is_little())
	{
		return (((_Number & 0xFF000000U) >> 24) | ((_Number & 0x00FF0000U) >> 8) | ((_Number & 0x0000FF00U) << 8) | ((_Number & 0x000000FFU) << 24));
	}
	return _Number;
}

// Conversion from network byte order to native byte order : unsigned short
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_network_to_host_64(unsigned long long _Number)
{
	if(x_endian_is_little())
	{
		return (((_Number & 0x00000000000000FFULL) << 56) | ((_Number & 0x000000000000FF00ULL) << 40) |
			((_Number & 0x0000000000FF0000ULL) << 24) | ((_Number & 0x00000000FF000000ULL) << 8) |
			((_Number & 0x000000FF00000000ULL) >> 8) | ((_Number & 0x0000FF0000000000ULL) >> 24) |
			((_Number & 0x00FF000000000000ULL) >> 40) | ((_Number & 0xFF00000000000000ULL) >> 56));
	}
	return _Number;
}
