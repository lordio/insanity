#define INSANITY_BUILDING_LIBRARY

#include "CGenericCharString.hpp"

#if defined(PLATFORM_MSWINDOWS)
#include <Windows.h>
#else
#include <cwchar>
#include <cstring>
#endif

namespace Insanity
{
	template<> IString<char> * IString<char>::Create()
	{
		return new CGenericCharString();
	}
	template<> IString<char> * IString<char>::Create(char const * str)
	{
		return new CGenericCharString(str);
	}
	template<> IString<char> * IString<char>::Create(wchar_t const * str)
	{
		return new CGenericCharString(str);
	}
	template<> IString<char> * IString<char>::Create(IString<char> const * str)
	{
		return new CGenericCharString(str);
	}
	template<> IString<char> * IString<char>::Create(IString<wchar_t> const * str)
	{
		return new CGenericCharString(str);
	}

	CGenericCharString::CGenericCharString() :
		_str("")
	{
	}
	CGenericCharString::CGenericCharString(char const * str) :
		_str((str ? str : ""))
	{
	}
	CGenericCharString::CGenericCharString(wchar_t const * str) :
		_str("")
	{
#if defined(PLATFORM_MSWINDOWS)
		//Windows does not use UTF8 for char strings by default, and that locale cannot be set through setlocale.
		//Manually convert using Win32 API WideCharToMultiByte
		//If param 4 (cchWideChar) is -1, it assumes [str] is null-terminated, which is all we could guess anyway.
		//If param 5 (lpMultiByteStr) is NULL and param 6 (cbMultiByte) is 0, does not store the translation; just returns the number of bytes needed to do so.
		//Params 7 (lpDefaultChar) and 8 (lpUsedDefaultChar) must be NULL for CP_UTF8
		//Should return byte count, including null-terminator
		int bytecount = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
		char * bytes = new char[bytecount];
		WideCharToMultiByte(CP_UTF8, 0, str, -1, bytes, bytecount, NULL, NULL);
		_str = bytes;
		delete [] bytes;
#else
		//On non-Windows platforms, UTF8 chars are the default, so mbstowcs and the like are fine.
		//They also perform similarly to WideCharToMultiByte when a null destination pointer is passed.
		//Notably, wcsnrtombs does NOT include the null-terminator in the returned bytecount, so compensate for that.
		//Also notably, wcsnrtombs does convert an encountered null-terminator, which causes it to return.
		//Further, wcslen does not include the null-terminator in the character count. Compensate so that the null-term is converted.
		mbstate_t state;
		memset(&state, 0, sizeof(state));
		size_t bytecount = wcsnrtombs(nullptr,&str,wcslen(str) + 1,0,&state);
		char * bytes = new char[bytecount + 1];
		wcsnrtombs(bytes, &str, wcslen(str) + 1, bytecount + 1, &state);
		_str = bytes;
		delete [] bytes;
#endif
	}
	CGenericCharString::CGenericCharString(IString<char> const * str) :
		_str((str ? str->Array() : ""))
	{
	}
	CGenericCharString::CGenericCharString(IString<wchar_t> const * str) :
		CGenericCharString(str ? str->Array() : L"")	//delegate to (wchar_t const *) ctor.
	{
	}
	CGenericCharString::~CGenericCharString()
	{
	}

	//=====================================================
	//Interface: IString<char>
	//=====================================================
	void CGenericCharString::Append(char chr)
	{
		_str += chr;
	}
	void CGenericCharString::Append(char const * str)
	{
		_str += str;
	}
	void CGenericCharString::Append(IString<char> const * str)
	{
		_str += str->Array();
	}
	void CGenericCharString::Assign(char const * str)
	{
		_str = str;
	}
	void CGenericCharString::Assign(IString<char> const * str)
	{
		_str = str->Array();
	}
	bool CGenericCharString::Compare(char const * str) const
	{
		return (_str == str);
	}
	bool CGenericCharString::Compare(IString<char> const * str) const
	{
		return (_str == str->Array());
	}
	char const * CGenericCharString::Array() const
	{
		return _str.c_str();
	}
	u64 CGenericCharString::Size() const
	{
		return _str.size();
	}
	void CGenericCharString::Clear()
	{
		_str.clear();
	}

	//=====================================================
	//Interface: IClonable
	//=====================================================
	IString<char> * CGenericCharString::Clone() const
	{
		return IString<char>::Create(_str.c_str());
	}
}
