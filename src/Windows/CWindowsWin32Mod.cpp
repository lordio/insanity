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
	typedef void(*ModDtor)(IMod*);

	//The only thing that needs to be defined is IMod::GetInstance
	IMod * IMod::GetInstance(char const * modName)
	{
		{
			auto tmp = s_cache.find(modName);
			if (tmp != s_cache.end()) return tmp->second->mod;
		}

		//Objects are guaranteed to exist for their initial scope,
		//	since the garbage collector in charge of them runs in the same thread.

		std::wstring libName{};
		atow(modName, libName);
		libName += L".dll";

		HMODULE mod{ LoadLibraryW(libName.c_str()) };
		if (!mod) return nullptr;

		ModCtor ctor{ (ModCtor) GetProcAddress(mod, "InitMod") };
		if (!ctor)
		{
			FreeLibrary(mod);
			return nullptr;
		}

		WeakPtr<IMod> modObject{ ctor() };
		if (!modObject)
		{
			FreeLibrary(mod);
			return nullptr;
		}

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
				ModDtor dtor{ (ModDtor) GetProcAddress(iter->second->lib, "DeleteMod") };
				if (dtor)
				{
					IMod * mod{ iter->second->mod };
					mod->Retain();
					iter->second->mod = nullptr;

					//need to delete mod inside library, so it still has to be open.
					dtor(mod);
				}
				else iter->second->mod = nullptr;
				//if mod dtor doesn't exist, mod API is bad. We can try to delete it locally, but it will probably not go well.

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
			ModDtor dtor{ (ModDtor) GetProcAddress(iter->second->lib, "DeleteMod") };
			if (dtor)
			{
				IMod * mod{ iter->second->mod };
				mod->Retain();
				iter->second->mod = nullptr;

				dtor(mod);
			}
			else iter->second->mod = nullptr; //if dtor doesn't exist, mod API is bad. ClearCache doesn't care all that much, but it will be smoother if it is correct.

            FreeLibrary(iter->second->lib);
            
            iter = s_cache.erase(iter);
        }
    }
}

#endif