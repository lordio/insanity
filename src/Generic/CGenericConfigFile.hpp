#ifndef INSANITY_IMPLEMENTATION_GENERIC_CONFIG_FILE
#define INSANITY_IMPLEMENTATION_GENERIC_CONFIG_FILE

#include <Constants.hpp>
#include <IConfigFile.hpp>
#include <Default/Object.hpp>
#include <Ptr.hpp>

#include <string>
#include <map>

namespace Insanity
{
	class CGenericConfigFile final : public IConfigFile, public Default::Object
	{
	private:
		std::map<std::string,Ptr<IConfigObject>> _objMap;
		bool _valid;
		
		static std::map<std::string,Ptr<IConfigFile>> s_cache;
	public:
		CGenericConfigFile(char const * filename);
		~CGenericConfigFile();
		
		static IConfigFile * GetInstance(char const * filename);
		
		//=================================================
		//Interface: IConfigFile
		//=================================================
		bool IsValid() const;
		IConfigObject const * GetObject(char const * objName) const;
	};
}

#endif
