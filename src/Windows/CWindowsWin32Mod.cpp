#define INSANITY_BUILDING_LIBRARY

#include <Constants.hpp>

#if defined(PLATFORM_MSWINDOWS)

#include <IMod.hpp>
#include <IString.hpp>
#include <map>
#include <string>

#include <Windows.h>

namespace
{
    struct ModPair
    {
        HMODULE lib;
        Insanity::IMod * mod;
    };
    typedef std::map<std::string, ModPair*> ModMap;
	ModMap s_cache;
}

namespace Insanity
{
	typedef IMod*(*ModCtor)();

	//The only thing that needs to be defined is IMod::GetInstance
	IMod * IMod::GetInstance(char const * modName)
	{
		{
			auto tmp = s_cache.find(modName);
			if (tmp != s_cache.end()) return tmp->second->mod;
		}

		//Objects are guaranteed to exist for their initial scope,
		//	since the garbage collector in charge of them runs in the same thread.
		IString<wchar_t> * libName = IString<wchar_t>::Create(modName);
		libName->Append(L".dll");

		HMODULE mod = LoadLibraryW(libName->Array());

		ModCtor ctor = (ModCtor)GetProcAddress(mod, "InitMod");
		IMod * modObject = ctor();

		//the static cache is a reference. Retain it.
		s_cache[modName] = new ModPair{mod,modObject};
		modObject->Retain();

		return modObject;
	}
    void IMod::ShrinkCache()
    {
        for(auto iter = s_cache.begin(); iter != s_cache.end();)
        {
            //If the only reference is the cache reference...
            if(iter->second->mod->GetReferenceCount() == 1)
            {
                iter->second->mod->Release();
                FreeLibrary(iter->second->lib);
                
                delete iter->second;
                iter = s_cache.erase(iter);
            }
            else iter++;
        }
    }
    void IMod::ClearCache()
    {
        for(auto iter = s_cache.begin(); iter != s_cache.end();)
        {
            iter->second->mod->Release();
            FreeLibrary(iter->second->lib);
            
            delete iter->second;
            iter = s_cache.erase(iter);
        }
    }
}

#endif