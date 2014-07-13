#define INSANITY_BUILDING_LIBRARY

#include "CGenericConfigObject.hpp"

#include <sstream>
#include <stdexcept>

namespace Insanity
{
	CGenericConfigObject::CGenericConfigObject()
	{
	}
	CGenericConfigObject::~CGenericConfigObject()
	{
	}
	
	//=====================================================
	//Interface: IConfigObject
	//=====================================================
	bool CGenericConfigObject::HasProperty(char const * propName) const
	{
		return _propList.count(propName) == 1;
	}
	char const * CGenericConfigObject::GetProperty(char const * propName, char const * def) const
	{
		char const * ret{def};
		auto prop = _propList.find(propName);
		if (prop != _propList.end()) ret = prop->second.c_str();
		return ret;
	}
	s64 CGenericConfigObject::GetProperty(char const * propName, s64 def) const
	{
		s64 ret{def};
		auto prop = _propList.find(propName);
		if (prop != _propList.end()) ret = std::stoll(prop->second);
		return ret;
	}
	double CGenericConfigObject::GetProperty(char const * propName, double def) const
	{
		double ret{def};
		auto prop = _propList.find(propName);
		if (prop != _propList.end()) ret = std::stod(prop->second);
		return ret;
	}
	
	void CGenericConfigObject::SetProperty(char const * propName, char const * value)
	{
		_propList[propName] = value;
	}
	void CGenericConfigObject::SetProperty(char const * propName, s64 value)
	{
		//lexical-cast value to a string, and store it
		_propList[propName] = std::to_string(value);
	}
	void CGenericConfigObject::SetProperty(char const * propName, double value)
	{
		//lexical-cast value to a string, and store it
		_propList[propName] = std::to_string(value);
	}
}
