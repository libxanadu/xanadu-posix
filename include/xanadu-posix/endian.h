#ifndef			_XANADU_POSIX_ENDIAN_H_
#define			_XANADU_POSIX_ENDIAN_H_

#include <xanadu-posix/header.h>

XANADU_CXX_EXTERN_BEGIN



// Check whether the operating system is in big-endian order
_XPOSIXAPI_ bool __xcall__ x_endian_is_big();

// Check whether the operating system is in little-endian order
_XPOSIXAPI_ bool __xcall__ x_endian_is_little();





// Ignore byte order and force reverse order : unsigned short
_XPOSIXAPI_ unsigned short __xcall__ x_endian_reverse_16(unsigned short _Number);

// Ignore byte order and force reverse order : unsigned int
_XPOSIXAPI_ unsigned int __xcall__ x_endian_reverse_32(unsigned int _Number);

// Ignore byte order and force reverse order : unsigned short
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_reverse_64(unsigned long long _Number);





// Automatic conversion according to byte order : unsigned short
_XPOSIXAPI_ unsigned short __xcall__ x_endian_convert_16(unsigned short _Number);

// Automatic conversion according to byte order : unsigned int
_XPOSIXAPI_ unsigned int __xcall__ x_endian_convert_32(unsigned int _Number);

// Automatic conversion according to byte order : unsigned short
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_convert_64(unsigned long long _Number);





// Conversion from native byte order to network byte order : unsigned short
_XPOSIXAPI_ unsigned short __xcall__ x_endian_host_to_network_16(unsigned short _Number);

// Conversion from native byte order to network byte order : unsigned int
_XPOSIXAPI_ unsigned int __xcall__ x_endian_host_to_network_32(unsigned int _Number);

// Conversion from native byte order to network byte order : unsigned short
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_host_to_network_64(unsigned long long _Number);

// Conversion from network byte order to native byte order : unsigned short
_XPOSIXAPI_ unsigned short __xcall__ x_endian_network_to_host_16(unsigned short _Number);

// Conversion from network byte order to native byte order : unsigned int
_XPOSIXAPI_ unsigned int __xcall__ x_endian_network_to_host_32(unsigned int _Number);

// Conversion from network byte order to native byte order : unsigned short
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_network_to_host_64(unsigned long long _Number);


XANADU_CXX_EXTERN_END

#endif
