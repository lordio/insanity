#ifndef INSANITY_CONSTANTS
#define INSANITY_CONSTANTS

#include "../ambassador/include/Constants.hpp"

#ifndef CONFIGURE_CPP
#	error Unable to compile without C++ support.
#endif

#if defined(PLATFORM_MSWINDOWS)
#	pragma warning(disable : 4250) //Method definition dominates base-class virtual; significant for multiple inheritance.
#endif

#if defined(INSANITY_BUILDING_LIBRARY)
#	define INSANITY_API ATTRIBUTE_EXPORT
#else
#	define INSANITY_API ATTRIBUTE_IMPORT
#endif

#include <cstdint>

namespace Insanity
{
	typedef uint8_t u8;
	typedef uint16_t u16;
	typedef uint32_t u32;
	typedef uint64_t u64;
	
	typedef int8_t s8;
	typedef int16_t s16;
	typedef int32_t s32;
	typedef int64_t s64;
}

#if defined(PLATFORM_MSWINDOWS) && defined(INSANITY_BUILDING_LIBRARY)
#pragma comment(lib,"ComCtl32.lib")
#endif

#endif
