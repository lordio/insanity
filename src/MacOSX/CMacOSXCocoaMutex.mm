#define INSANITY_BUILDING_LIBRARY

#include "CMacOSXCocoaMutex.hpp"

#if defined(PLATFORM_MACOSX)

namespace Insanity
{
	IMutex * IMutex::Create()
	{
		return new CMacOSXCocoaMutex();
	}

	CMacOSXCocoaMutex::CMacOSXCocoaMutex()
	{
		_lock = [[NSRecursiveLock alloc] init];
	}
	CMacOSXCocoaMutex::~CMacOSXCocoaMutex()
	{
		[_lock release];
	}

	//=====================================================
	//Interface: IMutex
	//=====================================================
	void CMacOSXCocoaMutex::Lock()
	{
		[_lock lock];
	}
	void CMacOSXCocoaMutex::Unlock()
	{
		[_lock unlock];
	}
	bool CMacOSXCocoaMutex::TryLock()
	{
		return [_lock tryLock] == YES;
	}
}

#endif
