#ifndef INSANITY_INTERFACE_CONFIG_FILE
#define INSANITY_INTERFACE_CONFIG_FILE

#include "Constants.hpp"
#include "IObject.hpp"

namespace Insanity
{
	class IConfigObject;
	
	class INSANITY_API IConfigFile : public virtual IObject
	{
	public:
		//=================================================
		//If [filename] refers to a cached config file,
		//	return a pointer to it.
		//Else, open the new file and return a pointer to it.
		//Will ALWAYS return non-nullptr. Check IsValid().
		//=================================================
		static IConfigFile * GetInstance(char const * filename);
		
		//=================================================
		//Returns false if:
		//	The file has syntax errors.
		//	The file is not a config file.
		//	The file is empty or did not exist.
		//Otherwise returns true.
		//=================================================
		virtual bool IsValid() const = 0;
		
		//=================================================
		//Returns a pointer to the specified ConfigObject,
		//	or nullptr if none exists.
		//=================================================
		virtual IConfigObject const * GetObject(char const * objName) const = 0;
	};
}

#endif
