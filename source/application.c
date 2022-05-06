#include <xanadu-posix/application.h>
#include <xanadu-posix/filesystem.h>
#include <xanadu-posix/system.h>
#include <xanadu-posix/string.h>
#include <xanadu-posix/memory.h>
#if defined(XANADU_SYSTEM_WINDOWS)
#include <Shlobj.h>
#endif
#if defined(XANADU_SYSTEM_DARWIN)
#include <mach-o/dyld.h>
#endif


// Gets the path of the current application
_XPOSIXAPI_ const char* x_application_native_path()
{
	static char		vApplicationPath[X_FILESYSTEM_MAX_PATH] = {0};
	if(0 == x_posix_strlen(vApplicationPath))
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		wchar_t		vDirectory[X_FILESYSTEM_MAX_PATH] = { 0 };
		GetModuleFileNameW(GetModuleHandleW(NULL), vDirectory, X_FILESYSTEM_MAX_PATH);
		x_string_replace_wchar_t(vDirectory, L'\\', L'/');
		char*		vDirectoryU = x_posix_strwtou(vDirectory);
		if(vDirectoryU)
		{
			x_posix_strcpy(vApplicationPath, vDirectoryU);
			x_posix_free(vDirectoryU);
		}
#else
#if defined(XANADU_SYSTEM_DARWIN)
		char		vDirectory[X_FILESYSTEM_MAX_PATH];
		uint32_t	vLength = X_FILESYSTEM_MAX_PATH;
		if(_NSGetExecutablePath(vDirectory, &vLength) != 0)
		{
			vDirectory[0] = '\0';
		}
		else
		{
			char*		vAbsolutePath = realpath(vDirectory, NULL);
			if(vAbsolutePath)
			{
				x_posix_strncpy(vDirectory, vAbsolutePath, vLength);
				free(vAbsolutePath);
			}
		}
		x_posix_strcpy(vApplicationPath, vDirectory);
#else
		char		vDirectory[X_FILESYSTEM_MAX_PATH] = { 0 };
		ssize_t		vCount = readlink("/proc/self/exe", vDirectory, X_FILESYSTEM_MAX_PATH);
		if(0 <= vCount || vCount <= X_FILESYSTEM_MAX_PATH)
		{
			x_posix_strcpy(vApplicationPath, vDirectory);
		}
#endif
#endif
	}
	return vApplicationPath;
}

// Gets the directory of the current application
_XPOSIXAPI_ const char* x_application_native_directory()
{
	static char	vApplicationDirectory[X_FILESYSTEM_MAX_PATH] = {0};
	if(0 == x_posix_strlen(vApplicationDirectory))
	{
		const char*	vApplicationPath = x_application_native_path();
		const char*	vStrFind = x_posix_strrchr(vApplicationPath, '/');
		if(vStrFind)
		{
			x_posix_strncpy(vApplicationDirectory, vApplicationPath, vStrFind - vApplicationPath);
		}
	}
	return vApplicationDirectory;
}

// Gets the name of the current application
_XPOSIXAPI_ const char* x_application_native_name()
{
	static char	vApplicationName[X_FILESYSTEM_MAX_PATH] = {0};
	if(0 == x_posix_strlen(vApplicationName))
	{
		const char*	vApplicationPath = x_application_native_path();
		const char*	vStrFind = x_posix_strrchr(vApplicationPath, '/');
		if(vStrFind && (vStrFind + 1))
		{
			x_posix_strcpy(vApplicationName, vStrFind + 1);
		}
	}
	return vApplicationName;
}



// Application com name
static const char* x_application_com_xanadu_name()
{
	static char	_static_com_xanadu_name[_X_FILESYSTEM_MAX_NAME] = {0};
	if(0 == x_posix_strlen(_static_com_xanadu_name))
	{
		const char*	vNameSuffix = NULL;
		char 		vApplicationPrefix[_X_FILESYSTEM_MAX_NAME] = {0};
		const char*	vApplicationName = x_application_native_name();
		char*		vApplicationNameL = x_posix_strtolower(vApplicationName);
		if(vApplicationNameL)
		{
			size_t 		vNameSize = x_posix_strlen(vApplicationNameL);
			if(vNameSize > 4)
			{
				vNameSuffix = vApplicationNameL + vNameSize - 4;
				if(x_posix_stricmp(vNameSuffix, ".exe") || x_posix_stricmp(vNameSuffix, ".com"))
				{
					x_posix_strncpy(vApplicationPrefix, vApplicationNameL, vNameSize - 4);
				}
				else
				{
					x_posix_strcpy(vApplicationPrefix, vApplicationNameL);
				}
			}
			else
			{
				x_posix_strcpy(vApplicationPrefix, vApplicationNameL);
			}
			x_posix_strcat(_static_com_xanadu_name, "com.xanadu.");
			x_posix_strcat(_static_com_xanadu_name, vApplicationPrefix);
			x_posix_free(vApplicationNameL);
		}
	}
	return _static_com_xanadu_name;
}

// Gets the cache directory of the current application
_XPOSIXAPI_ const char* x_application_cache_directory()
{
	static char	_static_application_cache_directory[X_FILESYSTEM_MAX_PATH] = {0};
	if(0 == x_posix_strlen(_static_application_cache_directory))
	{
		char		vApplicationDirectoryCache[X_FILESYSTEM_MAX_PATH] = {0};
		const char*	vComXanaduName = x_application_com_xanadu_name();
		const char*	vSystemDirectory = x_system_cache_directory();

		x_posix_strcpy(vApplicationDirectoryCache, vSystemDirectory);
		x_posix_strcat(vApplicationDirectoryCache, "/");
		x_posix_strcat(vApplicationDirectoryCache, vComXanaduName);

		x_posix_mkdir(vApplicationDirectoryCache, 0777);
		x_posix_strcpy(_static_application_cache_directory, vApplicationDirectoryCache);
	}
	return _static_application_cache_directory;
}

// Gets the config directory of the current application
_XPOSIXAPI_ const char* x_application_config_directory()
{
	static char	_static_application_config_directory[X_FILESYSTEM_MAX_PATH] = {0};
	if (0 == x_posix_strlen(_static_application_config_directory))
	{
		char		vApplicationDirectoryConfig[X_FILESYSTEM_MAX_PATH] = {0};
		const char*	vComXanaduName = x_application_com_xanadu_name();
		const char*	vSystemDirectory = x_system_config_directory();

		x_posix_strcpy(vApplicationDirectoryConfig, vSystemDirectory);
		x_posix_strcat(vApplicationDirectoryConfig, "/");
		x_posix_strcat(vApplicationDirectoryConfig, vComXanaduName);

		x_posix_mkdir(vApplicationDirectoryConfig, 0777);
		x_posix_strcpy(_static_application_config_directory, vApplicationDirectoryConfig);
	}
	return _static_application_config_directory;
}
