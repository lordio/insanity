#define INSANITY_BUILDING_LIBRARY

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

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
    std::map<std::string, ModPair*> s_cache;
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
        
        IString<char> * libName = IString<char>::Create(modName);
        libName->Append(".dylib");
        
        void * mod = dlopen(libName->Array(), RTLD_LAZY | RTLD_GLOBAL);
        ModCtor ctor = (ModCtor)dlsym(mod,"InitMod");
        IMod * modObject = ctor();
        
        s_cache[modName] = new ModPair{mod,modObject};
        modObject->Retain();
        
        return modObject;
    }
    
    void IMod::ShrinkCache()
    {
        for(auto iter = s_cache.begin(); iter != s_cache.end();)
        {
            if(iter->second->mod->GetReferenceCount() == 1)
            {
                iter->second->mod->Release();
                dlclose(iter->second->lib);
                
                delete iter->second;
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
            iter->second->mod->Release();
            dlclose(iter->second->lib);
            
            delete iter->second;
            iter = s_cache.erase(iter);
        }
    }
}

#endif