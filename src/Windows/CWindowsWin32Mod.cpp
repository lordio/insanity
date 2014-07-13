#define INSANITY_BUILDING_LIBRARY

#include <Constants.hpp>

#if defined(PLATFORM_MSWINDOWS)

#include <IMod.hpp>
#include <Ptr.hpp>
#include "WindowsStringConversion.hpp"

#include <Windows.h>

#include <map>
#include <string>
#include <memory>

namespace
{
    struct ModPair
    {
        HMODULE lib;
        Insanity::Ptr<Insanity::IMod> mod;
    };
    typedef std::map<std::string, std::unique_ptr<ModPair>> ModMap;
	ModMap s_cache{};
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
		//IString<wchar_t> * libName = IString<wchar_t>::Create(modName);
		//libName->Append(L".dll");

		std::wstring libName{};
		atow(modName, libName);
		libName += L".dll";

		HMODULE mod{ LoadLibraryW(libName.c_str()) };

		ModCtor ctor{ (ModCtor) GetProcAddress(mod, "InitMod") };
		WeakPtr<IMod> modObject{ ctor() };

		s_cache[modName].reset(new ModPair{mod,modObject});

		return modObject;
	}
    void IMod::ShrinkCache()
    {
        for(auto iter = s_cache.begin(); iter != s_cache.end();)
        {
            //If the only reference is the cache reference...
            if(iter->second->mod->GetReferenceCount() == 1)
            {
				//need to release the mod before closing the library.
				iter->second->mod = nullptr;
                FreeLibrary(iter->second->lib);
                
                iter = s_cache.erase(iter);
            }
            else iter++;
        }
    }
    void IMod::ClearCache()
    {
        for(auto iter = s_cache.begin(); iter != s_cache.end();)
        {
			iter->second->mod = nullptr;
            FreeLibrary(iter->second->lib);
            
            iter = s_cache.erase(iter);
        }
    }
}

#endif