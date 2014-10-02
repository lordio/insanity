#include "CGenericObject.hpp"

namespace Insanity
{
	CGenericObject::CGenericObject() :
		Default::Object{}
	{
	}
	CGenericObject::~CGenericObject()
	{
	}

	//=====================================================
	//Interface: IObject
	//=====================================================
	bool CGenericObject::ShouldBeTracked() const
	{
		return true;
	}
}