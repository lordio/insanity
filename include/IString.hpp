#ifndef INSANITY_INTERFACE_STRING
#define INSANITY_INTERFACE_STRING

#include "Constants.hpp"
#include "IObject.hpp"
#include "IClonable.hpp"

namespace Insanity
{
	//INSANITY_API, since there's only a few preset valid chartypes
	//Apparently, char should now be UTF8. Linux/GCC already implements this. MSVC, unknown.
	template<typename _ctype>
	class INSANITY_API IString : public IClonable<IString<_ctype>>, public virtual IObject
	{
	public:
		//=================================================
		//Create a new String, optionally copying an existing string.
		//=================================================
		static IString<_ctype> * Create();
		static IString<_ctype> * Create(char const * str);
		static IString<_ctype> * Create(wchar_t const * str);
		static IString<_ctype> * Create(IString<char> const * str);
		static IString<_ctype> * Create(IString<wchar_t> const * str);

		//=================================================
		//Replace the entire current value.
		//=================================================
		virtual void Assign(_ctype const * str) = 0;
		virtual void Assign(IString<_ctype> const * str) = 0;

		//=================================================
		//Concatenate this string with the parameter.
		//=================================================
		virtual void Append(_ctype chr) = 0;
		virtual void Append(_ctype const * str) = 0;
		virtual void Append(IString<_ctype> const * str) = 0;

		//=================================================
		//Returns true if this string is lexically identical to the parameter.
		//=================================================
		virtual bool Compare(_ctype const * str) const = 0;
		virtual bool Compare(IString<_ctype> const * str) const = 0;

		//=================================================
		//Returns a C-style pointer to the internal string.
		//=================================================
		virtual _ctype const * Array() const = 0;

		//=================================================
		//Returns the number of characters in the string.
		//	NOTE: This number is technically the number of
		//	bytes stored in the object, divided by the size
		//	of _ctype.
		//=================================================
		virtual u64 Size() const = 0;

		//=================================================
		//Clears the internal string to the empty string.
		//Functionally the same as Assign("").
		//=================================================
		virtual void Clear() = 0;
	};
}

#endif
