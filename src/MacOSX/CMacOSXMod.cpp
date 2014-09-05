#define INSANITY_BUILDING_LIBRARY

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

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
	std::map<std::string, std::unique_ptr<ModPair>> s_cache{};
}

namespace Insanity
{
    typedef IMod*(*ModCtor)();
    
    IMod * IMod::GetInstance(char const * modName)
    {
        {
            auto tmp = s_cache.find(modName);
            if(tmp != s_cache.end()) return tmp->second->mod;
		}

		std::string libName{modName};
		libName += ".dylib";

		void * mod{dlopen(libName.c_str(), RTLD_LAZY | RTLD_GLOBAL)};
		if(!mod) return nullptr;

		dlerror(); //clear errors
		ModCtor ctor{(ModCtor)dlsym(mod,"InitMod")};
		if(dlerror())
		{
			dlclose(mod);
			return nullptr;
		}

		WeakPtr<IMod> modObject{ctor()};
		if(!modObject)
		{
			dlclose(mod);
			return nullptr;
		}
        
        s_cache[modName].reset(new ModPair{mod,modObject});
        
        return modObject;
    }
    
    void IMod::ShrinkCache()
    {
        for(auto iter = s_cache.begin(); iter != s_cache.end();)
        {
            if(iter->second->mod->GetReferenceCount() == 1)
            {
                iter->second->mod = nullptr;
                dlclose(iter->second->lib);
                
                iter = s_cache.erase(iter);
            }
            else iter++;
        }
    }
    void IMod::ClearCache()
    {
        //might this need to reverse-iterate, so that least-dependent mods are unloaded last?
        for(auto iter = s_cache.begin(); iter != s_cache.end();)
        {
            //important to release the mod before closing the library.
            iter->second->mod = nullptr;
            dlclose(iter->second->lib);
            
            iter = s_cache.erase(iter);
        }
    }
}

#endif