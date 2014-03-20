#ifndef INSANITY_IMPLEMENTATION_WINDOWS_WIN32_MUTEX
#define INSANITY_IMPLEMENTATION_WINDOWS_WIN32_MUTEX

#include <Constants.hpp>

#if defined(PLATFORM_MSWINDOWS)

#include <IMutex.hpp>
#include <Windows.h>

#include <Default.hpp>

namespace Insanity
{
	class CWindowsWin32Mutex final : public IMutex, public Default::Object
	{
		HANDLE _mtx;
		//u64 _ref;
	public:
		CWindowsWin32Mutex();
		~CWindowsWin32Mutex();

		//=================================================
		//Interface: IMutex
		//=================================================
		void Lock() override;
		void Unlock() override;
		bool TryLock() override;

		//=================================================
		//Interface: IObject
		//=================================================
		//void Retain() override;
		//void Release() override;
		//u64 GetReferenceCount() const override;
		//void Delete() override;
	};
}

#endif

#endif