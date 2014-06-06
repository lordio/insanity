#ifndef INSANITY_WINDOWS_STRING_CONVERSION
#define INSANITY_WINDOWS_STRING_CONVERSION

#include <Constants.hpp>

#if defined(PLATFORM_MSWINDOWS)

#include <string>

namespace Insanity
{
	//because Microsoft, silly as they are, thinks UTF-16 is the way to go, but we use UTF-8 for application-side strings,
	//	we have to convert between the two around Win32 API calls.
	void ATTRIBUTE_LOCAL atow(std::string const& src, std::wstring & dst);
	void ATTRIBUTE_LOCAL wtoa(std::wstring const& src, std::string * dst);
}

#endif

#endif