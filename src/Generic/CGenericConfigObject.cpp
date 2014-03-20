#define INSANITY_BUILDING_LIBRARY

#include "CGenericConfigObject.hpp"
#include <IString.hpp>

#include <sstream>
#include <stdexcept>

//Make IMutableConfigObject a hidden interface extending IConfigObject, that provides the SetProperty methods,
//	so that they're not public APIs.

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
	IString<char> const * CGenericConfigObject::GetProperty(char const * propName, char const * def) const
	{
		IString<char> const * ret = nullptr;
		try
		{
			ret = IString<char>::Create(_propList.at(propName).c_str());
		}
		catch (std::out_of_range oor)
		{
			ret = IString<char>::Create(propName);
		}
		return ret;
	}

	//why does this take a nonconst string, and return the same?
	IString<char> const * CGenericConfigObject::GetProperty(char const * propName, IString<char> const * def) const
	{
		IString<char> const * ret = nullptr;
		try
		{
			ret = IString<char>::Create(_propList.at(propName).c_str());
		}
		catch(std::out_of_range oor)
		{
			ret = def;
		}
		return ret;
	}
	s64 CGenericConfigObject::GetProperty(char const * propName, s64 def) const
	{
		s64 ret = 0;
		try
		{
			std::istringstream strm(_propList.at(propName));
			strm >> ret;
		}
		catch(std::out_of_range oor)
		{
			ret = def;
		}
		return ret;
	}
	double CGenericConfigObject::GetProperty(char const * propName, double def) const
	{
		double ret = 0;
		try
		{
			std::istringstream strm(_propList.at(propName));
			strm >> ret;
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
	void CGenericConfigObject::SetProperty(char const * propName, IString<char> const * value)
	{
		_propList[propName] = value->Array();
	}
	void CGenericConfigObject::SetProperty(char const * propName, s64 value)
	{
		//lexical-cast value to a string, and store it
		std::stringstream strm;
		strm << value;
		strm >> _propList[propName];
	}
	void CGenericConfigObject::SetProperty(char const * propName, double value)
	{
		//lexical-cast value to a string, and store it
		std::stringstream strm;
		strm << value;
		strm >> _propList[propName];
	}
}
