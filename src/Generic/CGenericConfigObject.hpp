#ifndef INSANITY_IMPLEMENTATION_GENERIC_CONFIG_OBJECT
#define INSANITY_IMPLEMENTATION_GENERIC_CONFIG_OBJECT

#include <Constants.hpp>
#include <IConfigObject.hpp>
#include <Default/Object.hpp>

#include <string>
#include <map>

namespace Insanity
{
	class CGenericConfigObject final : public IConfigObject, public Default::Object
	{
		//		 property	  value
		std::map<std::string, std::string> _propList{ {} };
	public:
		CGenericConfigObject();
		~CGenericConfigObject();
		
		//=================================================
		//Interface: IConfigObject
		//=================================================
		bool HasProperty(char const * propName) const override;

		char const * GetProperty(char const * propName, char const * def) const override;
		s64 GetProperty(char const * propName, s64 def) const override;
		double GetProperty(char const * propName, double def) const override;
		
		void SetProperty(char const * propName, char const * value) override;
		void SetProperty(char const * propName, s64 value) override;
		void SetProperty(char const * propName, double value) override;
	};
}

#endif
