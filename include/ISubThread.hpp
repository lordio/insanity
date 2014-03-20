#ifndef INSANITY_INTERFACE_SUB_THREAD
#define INSANITY_INTERFACE_SUB_THREAD

#include "Constants.hpp"
#include "IThread.hpp"

namespace Insanity
{
	//"Sub," in opposition to the "main" thread, represented by IApplication.
	class INSANITY_API ISubThread : public virtual IThread
	{
	public:
		//=================================================
		//Create a new subthread.
		//Not intended for use outside the library.
		//Inherit from Default::Thread instead.
		//=================================================
		static ISubThread * Create(ISubThread * ext, bool start = true);

		//=================================================
		//Start a thread that is not currently running,
		//	whether it hasn't started yet,
		//	or has already returned.
		//Immediately returns if called relative to current thread.
		//=================================================
		virtual void Start() = 0;
		
		//=================================================
		//The main body of a thread's operations.
		//	An implementation will call this through the function
		//	passed to the platform-specific thread creation API.
		//=================================================
		virtual void Main() = 0;
	};
}

#endif
