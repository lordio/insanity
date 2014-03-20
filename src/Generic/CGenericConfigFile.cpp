#define INSANITY_BUILDING_LIBRARY

#include "CGenericConfigFile.hpp"
#include "CGenericConfigObject.hpp"
#include <IString.hpp>
#include <stdexcept>
#include <iostream>
#include <fstream>

namespace Insanity
{
	std::map<std::string,IConfigFile*> CGenericConfigFile::s_cache;
	
	IConfigFile * IConfigFile::GetInstance(char const * filename)
	{
		return CGenericConfigFile::GetInstance(filename);
	}
	
	CGenericConfigFile::CGenericConfigFile(char const * filename) :
		_valid(false)
	{
		//should load and parse specified file
		std::ifstream file(filename);
		if(!file)
		{
			std::cout << "Error: Config file \"" << filename << "\" does not exist." << std::endl;
			return;
		}
		
		char current = 0;
		bool isComment = false;
		bool inQuotes = false; //doublequote toggles; ignore '#', include whitespace instead of doing special processing.
		std::string objType = "";
		std::string propObject = "";
		std::string property = "";
		std::string currentToken = "";
		std::string unkToken = ""; //in case the actual token type is unclear
		u64 lineCount = 1;
		while(file.get(current))
		{
			if(isComment && current == '\n') isComment = false;
			else if(!isComment)
			{
				if(inQuotes)
				{
					//bypass all normal processing unless the character is another doublequote or an escape sequence.
					if(current == '\"') inQuotes = false;
					else if(current == '\\')
					{
						//escape sequence. get the next character and perform action based on that.
						file.get(current);
						if(current == 'n') currentToken += '\n';
						else if(current == 't') currentToken += '\t';
						else if(current == '\\') currentToken += '\\';
						else if(current == '\"') currentToken += '\"';
						//all others are discarded, so backslash-newline can be used for formatting a string, and will be ignored by the parser.
						//singlequotes don't disrupt quoted literals.
					}
					else currentToken += current;
				}
				else if(current == '\"') inQuotes = true; //if not in quotes, enter quote mode on a doublequote.
				else if(current == '#') isComment = true;
				else if(current == ':')
				{
					objType = currentToken;
					currentToken = "";
				}
				else if(current == '\n')
				{
					if(objType != "")
					{
						//new object defined.
						
						//ensure it has a name
						if(currentToken == "")
						{
							std::cout << "Error: Invalid object in config file \"" << filename << "\", line " << lineCount << "." << std::endl;
							return;
						}
						
						//ensure it has a unique name
						try
						{
							//at() throws std::out_of_range if currentToken is not a key in _objMap.
							_objMap.at(currentToken);
							std::cout << "Error: Multiply-defined object \"" << currentToken << "\" in config file \"" << filename << "\", line " << lineCount << "." << std::endl;
							return;
						}
						catch(std::out_of_range oor)
						{
							auto obj = new CGenericConfigObject();
							obj->SetProperty("_type", IString<char>::Create(objType.c_str()));

							//place the object in the map, which should be a strong reference
							_objMap[currentToken] = obj;
							obj->Retain();
						}

						objType = "";
						currentToken = "";
					}
					else if(propObject != "")
					{
						//property of existing object defined.
						
						if(property == "")
						{
							std::cout << "Error: Invalid property in config file \"" << filename << "\", line " << lineCount << "." << std::endl;
							return;
						}
						_objMap[propObject]->SetProperty(property.c_str(),IString<char>::Create(currentToken.c_str()));

						propObject = "";
						property = "";
						currentToken = "";
					}
					//else blank line; the first token on a declarative line must be a type or object.
				}
				else if(current == '\r') {} //no-op; just ignore any /r in the file.
				else if(current == '=' && property == "")
				{
					//property set
					if(unkToken != "")
					{
						if(currentToken != "")
						{
							std::cout << "Warning: Garbage detected in config file \"" << filename << "\", line " << lineCount << "." << std::endl;
							currentToken = "";
						}
						property = unkToken;
						unkToken = "";
					}
					else if(currentToken != "")
					{
						property = currentToken;
						currentToken = "";
					}
					else
					{
						std::cout << "Error: Attempt to assign to anonymous property in config file " << filename << "\", line " << lineCount << "." << std::endl;
						return;
					}
				}
				else if(current == '.' && propObject == "")
				{
					if(unkToken != "")
					{
						if(currentToken != "")
						{
							std::cout << "Warning: Garbage detected in config file \"" << filename << "\", line " << lineCount << "." << std::endl;
							unkToken = "";
						}
						propObject = unkToken;
						unkToken = "";
					}
					else if(currentToken != "")
					{
						propObject = currentToken;
						currentToken = "";
					}
					else
					{
						std::cout << "Error: Attempt to assign to anonymous object in config file " << filename << "\", line " << lineCount << "." << std::endl;
						return;
					}
				}
				else if(current == ' ' || current == '\t')
				{
					//whitespace. End a token if one exists, skip it otherwise
					if(currentToken != "")
					{
						unkToken = currentToken;
						currentToken = "";
					}
				}
				else currentToken += current;
			}
			if(current == '\n') lineCount++;
		}
		
		//set valid to true if it successfully reaches the end of the ctor.
		_valid = true;
	}
	CGenericConfigFile::~CGenericConfigFile()
	{
		for (auto obj : _objMap)
		{
			//object map contains strong references, so release them.
			obj.second->Release();
		}
	}
	
	IConfigFile * CGenericConfigFile::GetInstance(char const * filename)
	{
		IConfigFile * ret = nullptr;
		try
		{
			ret = s_cache.at(filename);
		}
		catch(std::out_of_range oor)
		{
			ret = new CGenericConfigFile(filename);
			s_cache[filename] = ret;
			ret->Retain();
		}
		return ret;
	}
	
	//=====================================================
	//Interface: IConfigFile
	//=====================================================
	bool CGenericConfigFile::IsValid() const
	{
		return _valid;
	}
	IConfigObject const * CGenericConfigFile::GetObject(char const * objName) const
	{
		IConfigObject * ret = nullptr;
		try
		{
			ret = _objMap.at(objName);
		}
		catch(std::out_of_range oor)
		{
			//reassert ret as nullptr, just to be on the safe side.
			ret = nullptr;
		}
		return ret;
	}
}
