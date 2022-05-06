#include <xanadu-posix/memory.h>



// posix : malloc
_XPOSIXAPI_ void* __xcall__ x_posix_malloc(size_t _Size)
{
	return malloc(_Size);
}

// posix : calloc
_XPOSIXAPI_ void* __xcall__ x_posix_calloc(size_t _Count, size_t _Size)
{
	return calloc(_Count, _Size);
}

// posix : realloc
_XPOSIXAPI_ void* __xcall__ x_posix_realloc(void* _Block, size_t _Size)
{
	return realloc(_Block, _Size);
}

// posix : memdup
_XPOSIXAPI_ void* __xcall__ x_posix_memdup(const void* _Memory, size_t _Size)
{
	if(_Memory == NULL || _Size == 0)
	{
		return NULL;
	}
	void*		vTarget = x_posix_malloc(_Size);
	if(vTarget)
	{
		x_posix_memcpy(vTarget, _Memory, _Size);
	}
	return vTarget;
}

// posix : free
_XPOSIXAPI_ void __xcall__ x_posix_free(void* _Memory)
{
	free(_Memory);
}





// posix : memset
_XPOSIXAPI_ void* __xcall__ x_posix_memset(void* _Memory, int _Value, size_t _Size)
{
	return memset(_Memory, _Value, _Size);
}

// posix : memcpy
_XPOSIXAPI_ void* __xcall__ x_posix_memcpy(void* _Dst, const void* _Src, size_t _Size)
{
	return memcpy(_Dst, _Src, _Size);
}

// posix : memmove
_XPOSIXAPI_ void* __xcall__ x_posix_memmove(void* _Dst, const void* _Src, size_t _Size)
{
	return memmove(_Dst, _Src, _Size);
}

// posix : memchr
_XPOSIXAPI_ void* __xcall__ x_posix_memchr(const void* _Buf, int _Val, size_t _MaxCount)
{
	return memchr(_Buf, _Val, _MaxCount);
}

// posix : memrchr
_XPOSIXAPI_ void* __xcall__ x_posix_memrchr(const void* _Buf, int _Val, size_t _MaxCount)
{
	if(_Buf == NULL || _MaxCount == 0)
	{
		return NULL;
	}

	unsigned char		vChar = (unsigned char)_Val;
	const unsigned char*	vBegin = ((const unsigned char*)_Buf);
	const unsigned char*	vMemory = vBegin + _MaxCount - 1;

	while(*vMemory != vChar && vMemory >= vBegin)
	{
		--vMemory;
	}
	if(vMemory < vBegin)
	{
		return NULL;
	}
	return (void*)vMemory;
}

// posix : memcmp
_XPOSIXAPI_ int __xcall__ x_posix_memcmp(const void* _Buf1, const void* _Buf2, size_t _Size)
{
	return memcmp(_Buf1, _Buf2, _Size);
}





// posix : wmemset
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wmemset(wchar_t* _Memory, wchar_t _Value, size_t _Size)
{
	return wmemset(_Memory, _Value, _Size);
}

// posix : wmemcpy
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wmemcpy(wchar_t* _Dst, const wchar_t* _Src, size_t _Size)
{
	return wmemcpy(_Dst, _Src, _Size);
}

// posix : wmemmove
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wmemmove(wchar_t* _Dst, const wchar_t* _Src, size_t _Size)
{
	return wmemmove(_Dst, _Src, _Size);
}

// posix : wmemchr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wmemchr(const wchar_t* _Buf, wchar_t _Val, size_t _MaxCount)
{
	return wmemchr(_Buf, _Val, _MaxCount);
}

// posix : wmemrchr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wmemrchr(const wchar_t* _Buf, wchar_t _Val, size_t _MaxCount)
{
	if(_Buf == NULL || _MaxCount == 0)
	{
		return NULL;
	}

	wchar_t			vChar = _Val;
	const wchar_t*		vBegin = _Buf;
	const wchar_t*		vMemory = vBegin + _MaxCount - 1;

	while(*vMemory != vChar && vMemory >= vBegin)
	{
		--vMemory;
	}
	if(vMemory < vBegin)
	{
		return NULL;
	}
	return (void*)vMemory;
}

// posix : wmemcmp
_XPOSIXAPI_ int __xcall__ x_posix_wmemcmp(const wchar_t* _Buf1, const wchar_t* _Buf2, size_t _Size)
{
	return wmemcmp(_Buf1, _Buf2, _Size);
}
