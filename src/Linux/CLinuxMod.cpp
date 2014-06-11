#define INSANITY_BUILDING_LIBRARY

#include <Constants.hpp>

#if defined(PLATFORM_LINUX)

#include <IMod.hpp>
#include <Ptr.hpp>
#include <map>
#include <string>
#include <memory>

#include <dlfcn.h>

namespace
{
	struct ModPair
	{
		void * lib;
		Insanity::Ptr<Insanity::IMod> mod;
	};
	typedef std::map<std::string, std::unique_ptr<ModPair>> ModMap;
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

		std::string libName{modName};
		libName += ".so";

		void * mod{dlopen(libName.c_str(), RTLD_LAZY | RTLD_GLOBAL)};
		ModCtor ctor{(ModCtor)dlsym(mod,"InitMod")};
		WeakPtr<IMod> modObject{ctor()};

		s_cache[modName].reset(new ModPair{mod, modObject});

		return modObject;
	}
	
	void IMod::ShrinkCache()
	{
		for(auto pr = s_cache.begin(); pr != s_cache.end();)
		{
			//if the only reference to it is ours...
			if(pr->second->mod->GetReferenceCount() == 1)
			{
				pr->second->mod = nullptr;
				dlclose(pr->second->lib);
				
				pr = s_cache.erase(pr);
			}
			else pr++;
		}
	}
	void IMod::ClearCache()
	{
		//Assume no relevant references exist to mods (most likely case is program shutdown)
		//Would it make more sense to start at the end, since least-dependent mods should be at the beginning?
		for(auto pr = s_cache.begin(); s_cache.size() > 0;)
		{
			pr->second->mod = nullptr;
			dlclose(pr->second->lib);
			
			pr = s_cache.erase(pr);
		}
	}
}

#endif
