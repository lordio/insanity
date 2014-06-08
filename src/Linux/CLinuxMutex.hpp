#ifndef INSANITY_IMPLEMENTATION_LINUX_MUTEX
#define INSANITY_IMPLEMENTATION_LINUX_MUTEX

#include <Constants.hpp>

#if defined(PLATFORM_LINUX)

#include <IMutex.hpp>
#include <pthread.h>

#include <Default/Object.hpp>

namespace Insanity
{
	class CLinuxMutex final : public IMutex, public Default::Object
	{
		pthread_mutex_t _mtx;
	public:
		CLinuxMutex();
		~CLinuxMutex();

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
