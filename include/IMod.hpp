#ifndef INSANITY_INTERFACE_MOD
#define INSANITY_INTERFACE_MOD

#include "Constants.hpp"
#include "IObject.hpp"

namespace Insanity
{
	class INSANITY_API IMod : public virtual IObject
	{
	public:
		//=================================================
		//Opens a mod library named "[modName]" + (platform
		//	library extension) and calls the exported
		//	InitMod method, or returns a pointer to the mod
		//	if it's already been loaded.
		//=================================================
		static IMod * GetInstance(char const * modName);
		
		//=================================================
		//Releases any mod that only has the cache reference.
		//=================================================
		static void ShrinkCache();
		
		//=================================================
		//Releases all mods.
		//=================================================
		static void ClearCache();
	};
}

#endif
