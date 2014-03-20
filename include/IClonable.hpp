#ifndef INSANITY_INTERFACE_CLONABLE
#define INSANITY_INTERFACE_CLONABLE

#include "Constants.hpp"
#include "IObject.hpp"

namespace Insanity
{
	template<typename _rtype>
	class IClonable : public virtual IObject
	{
	public:
		//=================================================
		//Standardizes interface for cloning objects.
		//Cloned object should have the same properties as
		//	the source object, except the refcount should
		//	start at 0.
		//=================================================
		virtual _rtype * Clone() const = 0;
	};
}

#endif
