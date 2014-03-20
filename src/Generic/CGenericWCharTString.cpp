#define INSANITY_BUILDING_LIBRARY

#include "CGenericWCharTString.hpp"

#if defined(PLATFORM_MSWINDOWS)
#include <Windows.h>
#else
#include <cwchar>
#include <cstring>
#endif

namespace Insanity
{
	template<> IString<wchar_t> * IString<wchar_t>::Create()
	{
		return new CGenericWCharTString();
	}
	template<> IString<wchar_t> * IString<wchar_t>::Create(char const * str)
	{
		return new CGenericWCharTString(str);
	}
	template<> IString<wchar_t> * IString<wchar_t>::Create(wchar_t const * str)
	{
		return new CGenericWCharTString(str);
	}
	template<> IString<wchar_t> * IString<wchar_t>::Create(IString<char> const * str)
	{
		return new CGenericWCharTString(str);
	}
	template<> IString<wchar_t> * IString<wchar_t>::Create(IString<wchar_t> const * str)
	{
		return new CGenericWCharTString(str);
	}
	
	CGenericWCharTString::CGenericWCharTString() :
		_str(L"")
	{
	}
	CGenericWCharTString::CGenericWCharTString(char const * str) :
		_str(L"")
	{
#if defined(PLATFORM_MSWINDOWS)
		//Param 4 (cbMultiByte) is -1, so str is assumed to be null-terminated.
		//Param 5 (lpWideChar) is NULL and 6 (cchWideChar) is 0, so no conversion is performed; the number of characters needed is returned.
		//Note that MultiByteToWideChar does include the null-term in the return value.
		int charcount = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
		wchar_t * chars = new wchar_t[charcount];
		MultiByteToWideChar(CP_UTF8, 0, str, -1, chars, charcount);
		_str = chars;
		delete [] chars;
#else
		//Remember that mbsnrtowcs does NOT include the null-term in the returned value, and will not convert an unencountered null-term.
		mbstate_t state;
		memset(&state, 0, sizeof(state));
		size_t charcount = mbsnrtowcs(nullptr, &str, strlen(str) + 1, 0, &state);
		wchar_t * chars = new wchar_t[charcount + 1];
		mbsnrtowcs(chars, &str, strlen(str) + 1, charcount + 1, &state);
		_str = chars;
		delete [] chars;
#endif
	}
	CGenericWCharTString::CGenericWCharTString(wchar_t const * str) :
		_str(str ? str : L"")
	{
	}
	CGenericWCharTString::CGenericWCharTString(IString<char> const * str) :
		CGenericWCharTString(str ? str->Array() : "")	//delegate to (char const *) ctor.
	{
	}
	CGenericWCharTString::CGenericWCharTString(IString<wchar_t> const * str) :
		_str(str ? str->Array() : L"")
	{
	}
	CGenericWCharTString::~CGenericWCharTString()
	{
	}
	
	//=====================================================
	//Interface: IString<wchar_t>
	//=====================================================
	void CGenericWCharTString::Append(wchar_t chr)
	{
		_str += chr;
	}
	void CGenericWCharTString::Append(wchar_t const * str)
	{
		_str += str;
	}
	void CGenericWCharTString::Append(IString<wchar_t> const * str)
	{
		_str += str->Array();
	}
	void CGenericWCharTString::Assign(wchar_t const * str)
	{
		_str = str;
	}
	void CGenericWCharTString::Assign(IString<wchar_t> const * str)
	{
		_str = str->Array();
	}
	bool CGenericWCharTString::Compare(wchar_t const * str) const
	{
		return (_str == str);
	}
	bool CGenericWCharTString::Compare(IString<wchar_t> const * str) const
	{
		return (_str == str->Array());
	}
	wchar_t const * CGenericWCharTString::Array() const
	{
		return _str.c_str();
	}
	u64 CGenericWCharTString::Size() const
	{
		return _str.size();
	}
	void CGenericWCharTString::Clear()
	{
		_str.clear();
	}
	
	//=====================================================
	//Interface: IClonable<IString<wchar_t>>
	//=====================================================
	IString<wchar_t> * CGenericWCharTString::Clone() const
	{
		return IString<wchar_t>::Create(_str.c_str());
	}
}
