#ifndef INSANITY_IMPLEMENTATION_WINDOWS_WIN32_CRITICAL_SECTION
#define INSANITY_IMPLEMENTATION_WINDOWS_WIN32_CRITICAL_SECTION

#include <Constants.hpp>

#if defined(PLATFORM_MSWINDOWS)

#include <Windows.h>
#include <IMutex.hpp>

#include <Default.hpp>

namespace Insanity
{
	//implementation using the faster critical section, which only provides cross-thread mutual exclusion
	//	Win32 Mutex does cross-process, but is much slower.
	class CWindowsWin32CriticalSection final : public IMutex, public Default::Object
	{
		CRITICAL_SECTION _mtx;
	public:
		CWindowsWin32CriticalSection();
		~CWindowsWin32CriticalSection();

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