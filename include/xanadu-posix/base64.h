#ifndef			_XANADU_POSIX_BASE64_H_
#define			_XANADU_POSIX_BASE64_H_

#include <xanadu-posix/header.h>

XANADU_CXX_EXTERN_BEGIN



// Encode the memory of the specified length as Base64
_XPOSIXAPI_ bool __xcall__ x_base64_encode(const unsigned char* _Memory, size_t _Length, unsigned char** _Output, size_t* _Size);

// Decode a segment of Base64 memory
_XPOSIXAPI_ bool __xcall__ x_base64_decode(const unsigned char* _Memory, size_t _Length, unsigned char** _Output, size_t* _Size);



XANADU_CXX_EXTERN_END

#endif
