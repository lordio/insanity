#include "WindowsStringConversion.hpp"

#ifdef PLATFORM_MSWINDOWS

#include <Windows.h>

#include <memory>

namespace Insanity
{
	void atow(std::string const& src, std::wstring & dst)
	{
		//Param 4 (cbMultiByte) is -1, so str is assumed to be null-terminated.
		//Param 5 (lpWideChar) is NULL and 6 (cchWideChar) is 0, so no conversion is performed; the number of characters needed is returned.
		//Note that MultiByteToWideChar does include the null-term in the return value.
		int charcount{ MultiByteToWideChar(CP_UTF8, 0, src.c_str(), -1, NULL, 0) };
		std::unique_ptr<wchar_t []> chars{ new wchar_t[charcount] };
		MultiByteToWideChar(CP_UTF8, 0, src.c_str(), -1, chars.get(), charcount);
		dst = chars.get();
	}
	void wtoa(std::wstring const& src, std::string & dst)
	{
		//Windows does not use UTF8 for char strings by default, and that locale cannot be set through setlocale.
		//Manually convert using Win32 API WideCharToMultiByte
		//If param 4 (cchWideChar) is -1, it assumes [str] is null-terminated, which is all we could guess anyway.
		//If param 5 (lpMultiByteStr) is NULL and param 6 (cbMultiByte) is 0, does not store the translation; just returns the number of bytes needed to do so.
		//Params 7 (lpDefaultChar) and 8 (lpUsedDefaultChar) must be NULL for CP_UTF8
		//Should return byte count, including null-terminator
		int bytecount{ WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, NULL, 0, NULL, NULL) };
		std::unique_ptr<char []> bytes{ new char[bytecount] };
		WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, bytes.get(), bytecount, NULL, NULL);
		dst = bytes.get();
	}
}

#endif