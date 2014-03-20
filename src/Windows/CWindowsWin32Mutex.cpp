#define INSANITY_BUILDING_LIBRARY

#include "CWindowsWin32Mutex.hpp"

#if defined(PLATFORM_MSWINDOWS)

#include "CWindowsWin32CriticalSection.hpp"

namespace Insanity
{
	IMutex * IMutex::Create()
	{
		//in most cases, this is what you really want
		return new CWindowsWin32CriticalSection();

		//scriptable create will allow Windows-specific property that creates a Mutex instead.
	}

	CWindowsWin32Mutex::CWindowsWin32Mutex() :
		_mtx(NULL)//, _ref(0)
	{
		_mtx = CreateMutex(nullptr,FALSE,nullptr);
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
		DWORD ret = WaitForSingleObject(_mtx,0);
		return !(ret == WAIT_TIMEOUT || ret == WAIT_ABANDONED);
	}

	//=====================================================
	//Interface: IObject
	//=====================================================
	//void CWindowsWin32Mutex::Retain()
	//{
	//	++_ref;
	//}
	//void CWindowsWin32Mutex::Release()
	//{
	//	if(_ref == 0) return;
	//	--_ref;
	//}
	//u64 CWindowsWin32Mutex::GetReferenceCount() const
	//{
	//	return _ref;
	//}
	//void CWindowsWin32Mutex::Delete()
	//{
	//	delete this;
	//}
}

#endif