#ifndef INSANITY_TEMPLATE_STRING
#define INSANITY_TEMPLATE_STRING

#include <string>

namespace Insanity
{
	//=====================================================
	//Convenience class for application-side strings.
	//	DO NOT USE FOR INTERNAL STRINGS.
	//=====================================================
	template<typename _ctype> class TString : public std::basic_string<_ctype, std::char_traits<_ctype>, std::allocator<_ctype>>
	{
	public:
		inline operator _ctype const *() { return this->c_str(); }

		//If MSVC would keep up with C++11, could just inherit basic_string's ctors.
		TString() : std::basic_string<_ctype>() {}
		TString(_ctype const* rv) : std::basic_string<_ctype>( rv ) {}
		TString(std::basic_string<_ctype> const& rv) : std::basic_string<_ctype>( rv ) {}
		TString(std::basic_string<_ctype> && rv) : std::basic_string<_ctype>( rv ) {}
	};

	using String = TString<char>;
}

#endif