#ifndef			_XANADU_POSIX_BASE64_H_
#define			_XANADU_POSIX_BASE64_H_

#include <xanadu-posix/header.h>


#if defined(__cplusplus)
extern "C" {
#endif


// Encode the memory of the specified length as Base64
_XPOSIXAPI_ bool x_base64_encode(const unsigned char* _Memory, size_t _Length, unsigned char** _Output, size_t* _Size);

// Decode a segment of Base64 memory
_XPOSIXAPI_ bool x_base64_decode(const unsigned char* _Memory, size_t _Length, unsigned char** _Output, size_t* _Size);


#if defined(__cplusplus)
}
#endif


#endif
