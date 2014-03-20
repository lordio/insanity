#define INSANITY_BUILDING_LIBRARY

#include <Constants.hpp>

#if defined(PLATFORM_LINUX)

#include <IMod.hpp>
#include <IString.hpp>
#include <map>
#include <string>

#include <dlfcn.h>

namespace
{
	struct ModPair
	{
		void * lib;
		Insanity::IMod * mod;
	};
	typedef std::map<std::string, ModPair*> ModMap;
	ModMap s_cache;
}

namespace Insanity
{
	typedef IMod*(*ModCtor)();

	IMod * IMod::GetInstance(char const * modName)
	{
		{
			auto tmp = s_cache.find(modName);
			if (tmp != s_cache.end()) return tmp->second->mod;
		}

		IString<char> * libName = IString<char>::Create(modName);
		libName->Append(".so");

		void * mod = dlopen(libName->Array(), RTLD_LAZY | RTLD_GLOBAL);
		ModCtor ctor = (ModCtor)dlsym(mod,"InitMod");
		IMod * modObject = ctor();

		s_cache[modName] = new ModPair{mod, modObject};
		modObject->Retain();

		return modObject;
	}
	
	void IMod::ShrinkCache()
	{
		for(ModMap::iterator pr = s_cache.begin(); pr != s_cache.end();)
		{
			//if the only reference to it is ours...
			if(pr->second->mod->GetReferenceCount() == 1)
			{
				//mods don't use normal garbage collection, so going to refcount 0 deletes them.
				pr->second->mod->Release(); //should delete the mod object, since we held the last reference.
				dlclose(pr->second->lib);
				
				delete pr->second;
				pr = s_cache.erase(pr);
			}
			else pr++;
		}
	}
	void IMod::ClearCache()
	{
		//Assume no relevant references exist to mods (most likely case is program shutdown)
		//Would it make more sense to start at the end, since least-dependent mods should be at the beginning?
		for(ModMap::iterator pr = s_cache.begin(); s_cache.size() > 0;)
		{
			//Release, not Delete; the Garbage Collector won't like it if something it tracks has already been deleted.
			//Mods (using Default::Mod) aren't GC'ed. Delete was correct.
			pr->second->mod->Delete();
			dlclose(pr->second->lib);
			
			delete pr->second;
			pr = s_cache.erase(pr);
		}
	}
}

#endif
