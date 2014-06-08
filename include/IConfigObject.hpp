#ifndef INSANITY_INTERFACE_CONFIG_OBJECT
#define INSANITY_INTERFACE_CONFIG_OBJECT

#include "Constants.hpp"
#include "IObject.hpp"

namespace Insanity
{
	template<typename _ctype>
	class IString;
	
	//=====================================================
	//A single collection of configuration options.
	//=====================================================
	class INSANITY_API IConfigObject : public virtual IObject
	{
		//no public Create method; ConfigFile handles creating ConfigObjects.
	public:
		//=================================================
		//Returns false if [propName] will return the
		//	default value provided to a GetProperty call.
		//	Otherwise true.
		//=================================================
		virtual bool HasProperty(char const * propName) const = 0;

		//=================================================
		//Retrieves specified property as type of [def],
		//	or returns [def] if property was not specified.
		//=================================================
		virtual char const * GetProperty(char const * propName, char const * def) const = 0; //should return char const *
		virtual s64 GetProperty(char const * propName, s64 def) const = 0;
		virtual double GetProperty(char const * propName, double def) const = 0;
		
		//=================================================
		//Sets property to a new value.
		//=================================================
		virtual void SetProperty(char const * propName, char const * value) = 0;
		virtual void SetProperty(char const * propName, s64 value) = 0;
		virtual void SetProperty(char const * propName, double value) = 0;
	};
}

#endif
