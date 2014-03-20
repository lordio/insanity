#define INSANITY_BUILDING_LIBRARY

#include "CWindowsWin32CriticalSection.hpp"

#if defined(PLATFORM_MSWINDOWS)

namespace Insanity
{
	CWindowsWin32CriticalSection::CWindowsWin32CriticalSection() //:
		//_ref(0)
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

	//=====================================================
	//Interface: IObject
	//=====================================================
	//void CWindowsWin32CriticalSection::Retain()
	//{
	//	_ref++;
	//}
	//void CWindowsWin32CriticalSection::Release()
	//{
	//	if(_ref == 0) return;
	//	--_ref;
	//}
	//u64 CWindowsWin32CriticalSection::GetReferenceCount() const
	//{
	//	return _ref;
	//}
	//void CWindowsWin32CriticalSection::Delete()
	//{
	//	delete this;
	//}
}

#endif