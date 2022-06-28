#ifndef			_XANADU_POSIX_MMAP_H_
#define			_XANADU_POSIX_MMAP_H_

#include <xanadu-posix/header.h>

XANADU_CXX_EXTERN_BEGIN


// mmap type definition
#if defined(XANADU_COMPILER_MSVC)

#define PROT_NONE       0
#define PROT_READ       1
#define PROT_WRITE      2
#define PROT_EXEC       4

#define MAP_FILE        0
#define MAP_SHARED      1
#define MAP_PRIVATE     2
#define MAP_TYPE        0xf
#define MAP_FIXED       0x10
#define MAP_ANONYMOUS   0x20
#define MAP_ANON        MAP_ANONYMOUS

#define MAP_FAILED      ((void *)-1)

// Flags for msync
#define MS_ASYNC        1
#define MS_SYNC         2
#define MS_INVALIDATE   4

#endif


// creates  a  new  mapping  in the virtual address space of the calling process.
_XPOSIXAPI_ void* __xcall__ x_posix_mmap(void* _Addr, size_t _Length, int _Prot, int _Flags, int _Fildes, off_t _Off);

// deletes the mappings for the specified address range
_XPOSIXAPI_ int __xcall__ x_posix_munmap(void* _Addr, size_t _Length);

// changes  protection  for the calling process's memory page(s) containing any part of the address range in the interval [addr, addr+len-1].
_XPOSIXAPI_ int __xcall__ x_posix_mprotect(void* _Addr, size_t _Length, int _Prot);

// flushes changes made to the in-core copy of a file that was mapped into memory using mmap back to the filesystem.
_XPOSIXAPI_ int __xcall__ x_posix_msync(void* _Addr, size_t _Length, int _Flags);

// lock part or all of the calling process's virtual address space into RAM
_XPOSIXAPI_ int __xcall__ x_posix_mlock(const void* _Addr, size_t _Length);

// unlocking part  or  all  of  the  calling process's  virtual address space
_XPOSIXAPI_ int __xcall__ x_posix_munlock(const void* _Addr, size_t _Length);



XANADU_CXX_EXTERN_END

#endif
