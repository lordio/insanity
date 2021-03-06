#define INSANITY_BUILDING_LIBRARY

#include "CLinuxMutex.hpp"

#if defined(PLATFORM_LINUX)

namespace Insanity
{
	IMutex * IMutex::Create()
	{
		return new CLinuxMutex{};
	}

	CLinuxMutex::CLinuxMutex() :
		CGenericObject{}
	{
		pthread_mutex_init(&_mtx,nullptr);
	}
	CLinuxMutex::~CLinuxMutex()
	{
		pthread_mutex_destroy(&_mtx);
	}

	//=====================================================
	//Interface: IThread
	//=====================================================
	void CLinuxMutex::Lock()
	{
		pthread_mutex_lock(&_mtx);
	}
	void CLinuxMutex::Unlock()
	{
		pthread_mutex_unlock(&_mtx);
	}
	bool CLinuxMutex::TryLock()
	{
		//pthread_mutex_trylock returns 0 if lock is acquired.
		//Will return EBUSY if lock is not acquired
		return pthread_mutex_trylock(&_mtx) == 0;
	}
}

#endif
