#ifndef INSANITY_IMPLEMENTATION_GENERIC_WCHART_STRING
#define INSANITY_IMPLEMENTATION_GENERIC_WCHART_STRING

#include <Constants.hpp>
#include <IString.hpp>
#include <string>
#include <default/Object.hpp>

namespace Insanity
{
	class CGenericWCharTString final : public IString<wchar_t>, public Default::Object
	{
		std::wstring _str;
	public:
		CGenericWCharTString();
		CGenericWCharTString(char const * str);
		CGenericWCharTString(wchar_t const * str);
		CGenericWCharTString(IString<char> const * str);
		CGenericWCharTString(IString<wchar_t> const * str);
		~CGenericWCharTString();
		
		//=================================================
		//Interface: IString<wchar_t>
		//=================================================
		void Assign(wchar_t const * str) override;
		void Assign(IString<wchar_t> const * str) override;

		void Append(wchar_t chr) override;
		void Append(wchar_t const * str) override;
		void Append(IString<wchar_t> const * str) override;

		bool Compare(wchar_t const * str) const override;
		bool Compare(IString<wchar_t> const * str) const override;

		wchar_t const * Array() const override;
		u64 Size() const override;
		void Clear() override;

		//=================================================
		//Interface: IClonable
		//=================================================
		IString<wchar_t> * Clone() const override;
	};
}

#endif
