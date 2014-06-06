#define INSANITY_BUILDING_LIBRARY

#include "CGenericConfigObject.hpp"

#include <sstream>
#include <stdexcept>

namespace Insanity
{
	CGenericConfigObject::CGenericConfigObject() : _propList{}
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
		try
		{
			_propList.at(propName);
		}
		catch (std::out_of_range oor)
		{
			return false;
		}
		return true;
	}
	char const * CGenericConfigObject::GetProperty(char const * propName, char const * def) const
	{
		char const * ret{};
		try
		{
			ret = _propList.at(propName).c_str();
		}
		catch (std::out_of_range oor)
		{
			ret = def;
		}
		return ret;
	}
	s64 CGenericConfigObject::GetProperty(char const * propName, s64 def) const
	{
		s64 ret{};
		try
		{
			ret = std::stoll(_propList.at(propName));
		}
		catch(std::out_of_range oor)
		{
			ret = def;
		}
		return ret;
	}
	double CGenericConfigObject::GetProperty(char const * propName, double def) const
	{
		double ret{};
		try
		{
			ret = std::stod(_propList.at(propName));
		}
		catch(std::out_of_range oor)
		{
			ret = def;
		}
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
