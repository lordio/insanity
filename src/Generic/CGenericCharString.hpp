#ifndef INSANITY_IMPLEMENTATION_GENERIC_CHAR_STRING
#define INSANITY_IMPLEMENTATION_GENERIC_CHAR_STRING

#include <Constants.hpp>
#include <IString.hpp>
#include <string>
#include <Default.hpp>

namespace Insanity
{
	class CGenericCharString final : public IString<char>, public Default::Object
	{
		std::string _str;
	public:
		CGenericCharString();
		CGenericCharString(char const * str);
		CGenericCharString(wchar_t const * str);
		CGenericCharString(IString<char> const * str);
		CGenericCharString(IString<wchar_t> const * str);
		~CGenericCharString();

		//=================================================
		//Interface: IString<char>
		//=================================================
		void Assign(char const * str) override;
		void Assign(IString<char> const * str) override;

		void Append(char chr) override;
		void Append(char const * str) override;
		void Append(IString<char> const * str) override;

		bool Compare(char const * str) const override;
		bool Compare(IString<char> const * str) const override;

		char const * Array() const override;
		u64 Size() const override;
		void Clear() override;

		//=================================================
		//Interface: IClonable
		//=================================================
		IString<char> * Clone() const override;
	};
}

#endif
