#include <xanadu-posix/xanadu.h>



// Dynamic library process attach
void xanadu_posix_dynamic_library_process_attach()
{
}

// Dynamic library process detach
void xanadu_posix_dynamic_library_process_detach()
{
}

// Dynamic library thread attach
void xanadu_posix_dynamic_library_thread_attach()
{
}

// Dynamic library thread detach
void xanadu_posix_dynamic_library_thread_detach()
{
}


// Dynamic library entry
#if defined(XANADU_SYSTEM_WINDOWS)
#if defined(__cplusplus)
extern "C"
#endif
BOOL WINAPI DllMain(HANDLE _DllHandle, DWORD _Reason, LPVOID _Reserved)
{
	UNREFERENCED_PARAMETER(_DllHandle);
	UNREFERENCED_PARAMETER(_Reserved);

	switch(_Reason)
	{
		case DLL_PROCESS_ATTACH:
			xanadu_posix_dynamic_library_process_attach();
			break;
		case DLL_THREAD_ATTACH:
			xanadu_posix_dynamic_library_thread_attach();
			break;
		case DLL_THREAD_DETACH:
			xanadu_posix_dynamic_library_thread_detach();
			break;
		case DLL_PROCESS_DETACH:
			xanadu_posix_dynamic_library_process_detach();
			break;
		default:
			break;
	}
	return TRUE;
}
#else
__attribute((constructor)) void xanadu_posix_dynamic_library_init(void)
{
	xanadu_posix_dynamic_library_process_attach();
}

__attribute((destructor)) void xanadu_posix_dynamic_library_fini(void)
{
	xanadu_posix_dynamic_library_process_detach();
}
#endif
