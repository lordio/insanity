#ifndef INSANITY_IMPLEMENTATION_MACOSX_COCOA_MUTEX
#define INSANITY_IMPLEMENTATION_MACOSX_COCOA_MUTEX

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

#include <IMutex.hpp>
#include "../Generic/CGenericObject.hpp"

#include <Foundation/NSLock.h>

namespace Insanity
{
	class INSANITY_API CMacOSXCocoaMutex : public IMutex, public CGenericObject
	{
		NSRecursiveLock * _lock;
	public:
		CMacOSXCocoaMutex();
		~CMacOSXCocoaMutex();

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
