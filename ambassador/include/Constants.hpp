#ifndef AMBASSADOR
#define AMBASSADOR

/*
Ambassador is a simple, single header used to create preprocessor macros that simplify the build environment.

It is a separate file because it is used by multiple projects.
*/

/*
Token namespaces:
	PLATFORM: Determine which platform is being compiled for.
	COMPILER: Determine which compiler is being used.
	CONFIGURE: Other environmental configurations where the above two are inappropriate.
	ATTRIBUTE: Usable on declarations to modify storage specification.
*/
#if defined(__cplusplus) //if C++
#	define CONFIGURE_CPP
#	if __cplusplus > 201100L //if C++11
#		define CONFIGURE_CPP11
#	endif
#	if defined(__OBJC__) //if Objective-C++
#		define CONFIGURE_OBJC
#		define CONFIGURE_OBJCPP
#	endif
#elif defined(__OBJC__) //if Objective-C
#	define CONFIGURE_OBJC
#else 					//plain C
#	define CONFIGURE_C
#endif

#if defined(_WIN32)
#	define PLATFORM_MSWINDOWS
#	if defined(_WIN64)
#		define CONFIGURE_64BIT
#	endif
#	define ATTRIBUTE_EXPORT __declspec(dllexport)
#	define ATTRIBUTE_IMPORT __declspec(dllimport)
#	define ATTRIBUTE_LOCAL
#	define ATTRIBUTE_DEPRECATED __declspec(deprecated)
#	define ATTRIBUTE_UNUSED
#	define ATTRIBUTE_THREAD_LOCAL __declspec(thread)
#elif defined(__linux) || defined(linux)
#	define PLATFORM_LINUX
#	if defined(_LP64) || defined(__LP64__)
#		define CONFIGURE_64BIT
#	endif
#	define ATTRIBUTE_EXPORT __attribute__((visibility("default")))
#	define ATTRIBUTE_IMPORT
#	define ATTRIBUTE_LOCAL __attribute__((visibility("hidden")))
#	define ATTRIBUTE_DEPRECATED __attribute__((deprecated))
#	define ATTRIBUTE_UNUSED __attribute__((unused))
#	define ATTRIBUTE_THREAD_LOCAL __thread
#elif defined(__APPLE__) || defined(__MACH__)
#	define PLATFORM_MACOSX
#	if defined(_LP64) || defined(__LP64__)
#		define CONFIGURE_64BIT
#	endif
#	define ATTRIBUTE_EXPORT __attribute__((visibility("default")))
#	define ATTRIBUTE_IMPORT
#	define ATTRIBUTE_LOCAL __attribute__((visibility("hidden")))
#	define ATTRIBUTE_DEPRECATED __attribute__((deprecated))
#	define ATTRIBUTE_UNUSED __attribute__((unused))
#	define ATTRIBUTE_THREAD_LOCAL __thread
#else
#	error Attempted to use Ambassador with an unsupported platform.
#endif

#if defined(_MSC_VER)
#	define COMPILER_MSVC
#	if defined(_DEBUG)
#		define CONFIGURE_DEBUG
#	endif
#elif defined(__GNUC__)
#	define COMPILER_GCC
#	if defined(DEBUG)
#		define CONFIGURE_DEBUG
#	endif
#elif defined(__clang__)
#	define COMPILER_CLANG
#	if !defined(__OPTIMIZE__)
#		define CONFIGURE_DEBUG
#	endif
#else
#	error Attempted to use Ambassador with an unsupported compiler.
#endif

/*
At this point, the following tokens WILL BE defined:
	ATTRIBUTE_EXPORT
	ATTRIBUTE_IMPORT
	ATTRIBUTE_LOCAL
	ATTRIBUTE_DEPRECATED
	ATTRIBUTE_UNUSED
	ATTRIBUTE_THREAD_LOCAL
	One of the COMPILER_* macros.
	One of the PLATFORM_* macros

If making a debug build, CONFIGURE_DEBUG will be defined.
If C++11 is supported, CONFIGURE_CPP11 will be defined.
*/

#endif
