# CMake最低版本号要求
cmake_minimum_required(VERSION 3.8)


# 项目名称
set(PROJECT_CC_VERSION_MAJOR 0)
set(PROJECT_CC_VERSION_MINOR 0)
set(PROJECT_CC_VERSION_PATCH 1)
project(xanadu-posix VERSION ${PROJECT_CC_VERSION_MAJOR}.${PROJECT_CC_VERSION_MINOR}.${PROJECT_CC_VERSION_PATCH})


# 输出提示信息
message(STATUS "Operation System : ${CMAKE_SYSTEM}")
message(STATUS "CMAKE_INSTALL_PREFIX : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_C_COMPILER : ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER : ${CMAKE_CXX_COMPILER}")


# 配置文件
if (BUILD_SHARED_LIBS STREQUAL "OFF" OR BUILD_STATIC_LIBS STREQUAL "ON")
	set(XANADU_POSIX_BUILD_REPLACE XANADU_POSIX_BUILD_STATIC)
	set(X_SERIES_LIBRARY_TYPE "STATIC")
else()
	set(XANADU_POSIX_BUILD_REPLACE XANADU_POSIX_BUILD_SHARED)
	set(X_SERIES_LIBRARY_TYPE "SHARED")
endif ()
configure_file("${CMAKE_SOURCE_DIR}/config/${PROJECT_NAME}-config.cmake.in" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config.cmake")
configure_file("${CMAKE_SOURCE_DIR}/config/${PROJECT_NAME}.pc.in" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc")
configure_file("${CMAKE_SOURCE_DIR}/config/VersionInfo.rc.in" "${CMAKE_BINARY_DIR}/VersionInfo.rc")


# 设置模块搜索路径
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_INSTALL_PREFIX}/lib/cmake)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_INSTALL_PREFIX}/lib/cmake)
message(STATUS "CMAKE_MODULE_PATH : ${CMAKE_MODULE_PATH}")
message(STATUS "CMAKE_PREFIX_PATH : ${CMAKE_PREFIX_PATH}")


# 配置编译环境
if (MSVC)
	add_compile_options(/W4)
else()
	add_compile_options(-Wall)
endif()
if (X_SERIES_LIBRARY_TYPE STREQUAL "STATIC")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -static")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -static")
endif()
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd /Od")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD /Od")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG : ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE : ${CMAKE_CXX_FLAGS_RELEASE}")


# 平台检查
include(CheckTypeSize)
include(CheckSymbolExists)
include(CheckVariableExists)
include(CheckSymbolExists)
include(CheckStructHasMember)
include(CheckCSourceCompiles)
include(CheckPrototypeDefinition)

CHECK_TYPE_SIZE("uint8_t" X_CMAKE_HAVE_UINT8_T)
CHECK_TYPE_SIZE("uint16_t" X_CMAKE_HAVE_UINT16_T)
CHECK_TYPE_SIZE("uint32_t" X_CMAKE_HAVE_UINT32_T)
CHECK_TYPE_SIZE("uint64_t" X_CMAKE_HAVE_UINT64_T)
CHECK_TYPE_SIZE("short" X_CMAKE_SIZEOF_SHORT BUILTIN_TYPES_ONLY)
CHECK_TYPE_SIZE("int" X_CMAKE_SIZEOF_INT BUILTIN_TYPES_ONLY)
CHECK_TYPE_SIZE("unsigned" X_CMAKE_SIZEOF_UNSIGNED BUILTIN_TYPES_ONLY)
CHECK_TYPE_SIZE("unsigned int" X_CMAKE_SIZEOF_UNSIGNED_INT BUILTIN_TYPES_ONLY)
CHECK_TYPE_SIZE("long" X_CMAKE_SIZEOF_LONG BUILTIN_TYPES_ONLY)
CHECK_TYPE_SIZE("long long" X_CMAKE_SIZEOF_LONG_LONG BUILTIN_TYPES_ONLY)
CHECK_TYPE_SIZE("off_t" X_CMAKE_SIZEOF_OFF_T LANGUAGE C)
CHECK_TYPE_SIZE("ssize_t" X_CMAKE_SIZEOF_SSIZE_T_LOWER LANGUAGE C)
CHECK_TYPE_SIZE("SSIZE_T" X_CMAKE_SIZEOF_SSIZE_T_UPPER LANGUAGE C)
CHECK_TYPE_SIZE("uintptr_t" X_CMAKE_HAVE_UINTPTR_T)
CHECK_TYPE_SIZE("void*" X_CMAKE_SIZEOF_VOID_P)
CHECK_TYPE_SIZE("time_t" X_CMAKE_SIZEOF_TIME_T)

CHECK_SYMBOL_EXISTS("__func__"     "" X_CMAKE_HAVE___func__)
CHECK_SYMBOL_EXISTS("__FUNCTION__" "" X_CMAKE_HAVE___FUNCTION__)
CHECK_SYMBOL_EXISTS("asprintf" "stdio.h" "X_CMAKE_HAVE_ASPRINTF")
CHECK_SYMBOL_EXISTS("vasprintf" "stdio.h" "X_CMAKE_HAVE_VASPRINTF")
CHECK_SYMBOL_EXISTS("setenv" "stdlib.h" "X_CMAKE_HAVE_SETENV")
CHECK_SYMBOL_EXISTS("getenv" "stdlib.h" "X_CMAKE_HAVE_GETENV")
CHECK_SYMBOL_EXISTS("putenv" "stdlib.h" "X_CMAKE_HAVE_PUTENV")
CHECK_SYMBOL_EXISTS("unsetenv" "stdlib.h" "X_CMAKE_HAVE_UNSETENV")
CHECK_SYMBOL_EXISTS("getifaddrs" "ifaddrs.h" "X_CMAKE_HAVE_IFADDRS")
CHECK_SYMBOL_EXISTS("poll" "poll.h" "X_CMAKE_HAVE_POLL")
CHECK_SYMBOL_EXISTS("ppoll" "poll.h" "X_CMAKE_HAVE_PPOLL")
CHECK_SYMBOL_EXISTS("sigprocmask" "signal.h" "X_CMAKE_HAVE_SIGPROCMASK")


# 设置忽略路径
set(CMAKE_IGNORE_PATH ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})
message(STATUS "CMAKE_IGNORE_PATH : ${CMAKE_IGNORE_PATH}")


# 项目依赖
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR})


# C++支持
set(CMAKE_C_STANDARD 11)


# 头文件搜索目录


# 链接库搜索目录


# 宏定义
if (X_SERIES_LIBRARY_TYPE STREQUAL "STATIC")
	add_definitions(-DXANADU_POSIX_BUILD_STATIC)
else()
	add_definitions(-DXANADU_POSIX_BUILD_LOCAL)
endif()
add_definitions(-DXANADU_PARAMETER_VALIDATION)
add_definitions(-D_FILE_OFFSET_BITS=64)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS)
add_definitions(-D_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-DXANADU_BUILD_DEBUG)
else ()
	add_definitions(-DXANADU_BUILD_RELEASE)
endif ()


# 包含源文件
aux_source_directory(./source SRC)
aux_source_directory(./source/os SRC)
if (MSVC)
	list(APPEND SRC ${CMAKE_BINARY_DIR}/VersionInfo.rc)
endif ()


# 链接库
if (WIN32)
	link_libraries("Ws2_32.lib")
	link_libraries("Iphlpapi.lib")
	link_libraries("Wtsapi32.lib")
	link_libraries("Userenv.lib")
elseif (MINGW)
	link_libraries("Ws2_32")
	link_libraries("Iphlpapi")
	link_libraries("Wtsapi32")
	link_libraries("Userenv")
	link_libraries("stdc++")
else ()
	if (${CMAKE_CXX_COMPILER} MATCHES "android")
		link_libraries("android")
		link_libraries("log")
	else()
		link_libraries("pthread")
	endif ()
	link_libraries("dl")
endif ()


# 构建
if (X_SERIES_LIBRARY_TYPE STREQUAL "STATIC")
	add_library(${PROJECT_NAME} STATIC ${SRC})
else()
	add_library(${PROJECT_NAME} SHARED ${SRC})
endif()


# 设置项目属性
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_CC_VERSION_MAJOR})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -d)


if (X_SERIES_LIBRARY_TYPE STREQUAL "STATIC")
	# 设置安装文件(静态库)
	install(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
else()
	# 设置安装文件(动态库)
	install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endif()
# 设置安装文件(可执行文件)
#install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
# 设置安装文件(与库关联的PUBLIC头文件)
#install(TARGETS ${PROJECT_NAME} PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
# 设置安装文件(与库关联的PRIVATE头文件)
#install(TARGETS ${PROJECT_NAME} PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
# 安装头文件
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
# 安装头文件
#install(FILES ${PROJECT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
# 配置模块文件
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config.cmake DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake)
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)
