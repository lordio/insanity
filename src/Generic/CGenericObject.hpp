#ifndef INSANITY_IMPLEMENTATION_GENERIC_OBJECT
#define INSANITY_IMPLEMENTATION_GENERIC_OBJECT

#include <Constants.hpp>
#include <Default/Object.hpp>

namespace Insanity
{
	class CGenericObject : public Default::Object
	{
	public:
		CGenericObject();
		virtual ~CGenericObject();

		//=================================================
		//Interface: IObject
		//=================================================
		bool ShouldBeTracked() const override;
	};
}

#endif