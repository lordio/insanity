#ifndef INSANITY_IMPLEMENTATION_WINDOWS_WIN32_MUTEX
#define INSANITY_IMPLEMENTATION_WINDOWS_WIN32_MUTEX

#include <Constants.hpp>

#if defined(PLATFORM_MSWINDOWS)

#include <IMutex.hpp>
#include <Windows.h>

#include "../Generic/CGenericObject.hpp"

namespace Insanity
{
	class CWindowsWin32Mutex final : public IMutex, public CGenericObject
	{
		HANDLE _mtx;
	public:
		CWindowsWin32Mutex();
		~CWindowsWin32Mutex();

		//=================================================
		//Interface: IMutex
		//=================================================
		void Lock() override;
		void Unlock() override;
		bool TryLock() override;
	};
}

#endif

#endif