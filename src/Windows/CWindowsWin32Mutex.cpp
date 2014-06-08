#define INSANITY_BUILDING_LIBRARY

#include "CWindowsWin32Mutex.hpp"

#if defined(PLATFORM_MSWINDOWS)

#include "CWindowsWin32CriticalSection.hpp"

namespace Insanity
{
	IMutex * IMutex::Create()
	{
		//in most cases, this is what you really want
		return new CWindowsWin32CriticalSection{};

		//scriptable create will allow Windows-specific property that creates a Mutex instead.
	}

	CWindowsWin32Mutex::CWindowsWin32Mutex() :
		_mtx{ CreateMutex(nullptr, FALSE, nullptr) }
	{
	}
	CWindowsWin32Mutex::~CWindowsWin32Mutex()
	{
		CloseHandle(_mtx);
	}

	//=====================================================
	//Interface: IMutex
	//=====================================================
	void CWindowsWin32Mutex::Lock()
	{
		WaitForSingleObject(_mtx,INFINITE);
	}
	void CWindowsWin32Mutex::Unlock()
	{
		ReleaseMutex(_mtx);
	}
	bool CWindowsWin32Mutex::TryLock()
	{
		DWORD ret{ WaitForSingleObject(_mtx, 0) };
		return !(ret == WAIT_TIMEOUT || ret == WAIT_ABANDONED);
	}
}

#endif