#ifndef INSANITY_INTERFACE_THREAD
#define INSANITY_INTERFACE_THREAD

#include "Constants.hpp"
#include "IObject.hpp"

//For some stupid reason, Win32 defined Yield() as a macro that expands to... ABSOLUTELY NOTHING.
//	Undefine it if this is the case.

#if defined(Yield)
#undef Yield
#endif

namespace Insanity
{
	class IGarbageCollector;
	class ITask;
	
	class INSANITY_API IThread : public virtual IObject
	{
	public:
		//=================================================
		//Returns the currently executing thread.
		//Should return thread extension if ISubThread.
		//=================================================
		static IThread * Current();

		//=================================================
		//	checks to see if it should continue, and returns false if not
		//	runs all tasks.
		//	cycles the garbage collector
		//	returns false if End was called after initial check.
		//		true otherwise.
		//Should only be called relative to the current thread.
		//	Will behave properly, but code called from it may be dependent on IThread::Current().
		//=================================================
		virtual bool Update() = 0;

		//=================================================
		//Requests the thread cease execution.
		//	May be called from any thread.
		//=================================================
		virtual void End() = 0;
		
		//=================================================
		//Returns the Garbage Collector for this thread.
		//Not intended for use outside the library.
		//=================================================
		virtual IGarbageCollector * GetGarbageCollector() const = 0;
		
		//=================================================
		//Gives up the remainder of the thread's timeslice.
		//Should only be called by the currently executing thread.
		//	It will not have the intended effect otherwise.
		//=================================================
		virtual void Yield() const = 0;

		//=================================================
		//Adds a task to a list that is performed on Update.
		//	Marks the Task as being enqueued.
		//Intended to be called from the represented thread.
		//=================================================
		virtual void RegisterTask(ITask * task) = 0;
		
		//=================================================
		//Transfer garbage collection duty from the current thread
		//	to the called-upon thread.
		//e.g., for some IThread1 * worker,
		//	for some code in the main thread,
		//	and for some IObject * obj,
		//	worker->Transfer(obj);
		//	will remove obj from the main thread's garbage collector
		//	and add it to worker's collector.
		//This method does not inherently ensure the garbage collector is ready to accept a new object.
		//	Add a mutex to threads expecting Transferred objects.
		//=================================================
		virtual void Transfer(IObject * obj) = 0;

		//=================================================
		//Returns true if this thread object represents the
		//	thread currently executing code.
		//	Otherwise false.
		//=================================================
		virtual bool IsCurrentThread() const = 0;
	};
}

#endif
