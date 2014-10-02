#define INSANITY_BUILDING_LIBRARY

#include "CWindowsWin32CriticalSection.hpp"

#if defined(PLATFORM_MSWINDOWS)

namespace Insanity
{
	CWindowsWin32CriticalSection::CWindowsWin32CriticalSection() : CGenericObject{}
	{
		InitializeCriticalSection(&_mtx);
	}
	CWindowsWin32CriticalSection::~CWindowsWin32CriticalSection()
	{
		DeleteCriticalSection(&_mtx);
	}

	//=====================================================
	//Interface: IMutex
	//=====================================================
	void CWindowsWin32CriticalSection::Lock()
	{
		EnterCriticalSection(&_mtx);
	}
	void CWindowsWin32CriticalSection::Unlock()
	{
		LeaveCriticalSection(&_mtx);
	}
	bool CWindowsWin32CriticalSection::TryLock()
	{
		return TryEnterCriticalSection(&_mtx) != FALSE;
	}
}

#endif