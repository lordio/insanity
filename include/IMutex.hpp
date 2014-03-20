#ifndef INSANITY_INTERFACE_MUTEX
#define INSANITY_INTERFACE_MUTEX

#include "Constants.hpp"
#include "IObject.hpp"

namespace Insanity
{
	class INSANITY_API IMutex : public virtual IObject
	{
		//thread properties
		//Windows.useCriticalSection (default true)
	public:
		static IMutex * Create();

		//=================================================
		//Obtain control of this Mutex for the current thread.
		//=================================================
		virtual void Lock() = 0;

		//=================================================
		//Release control of previously locked Mutex.
		//	Must be called once for each Lock and successful TryLock.
		//=================================================
		virtual void Unlock() = 0;

		//=================================================
		//Attempt to take control of the Mutex.
		//	returns true if current thread owns Mutex.
		//	returns false otherwise.
		//=================================================
		virtual bool TryLock() = 0;
	};
}

#endif