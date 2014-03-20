#define INSANITY_BUILDING_LIBRARY

#include "CMacOSXCocoaSubThread.hpp"

#if defined(PLATFORM_MACOSX)

#include <IGarbageCollector.hpp>
#include <IApplication.hpp>
#include <ITask.hpp>

#import <Foundation/NSThread.h>
#import <Foundation/NSDictionary.h>

#include <algorithm>
#include <sched.h>

//MacOSX stores current thread as CMacOSXCocoaSubThread*.

@interface MacObjCThreadWrapper : NSThread
{
	Insanity::CMacOSXCocoaSubThread * _thrd;
}

-(void)main;
-(id)initWithThread:(Insanity::CMacOSXCocoaSubThread*)thrd;
@end

@implementation MacObjCThreadWrapper
-(void)main
{
	//Set up the autorelease pool, for Objective-C objects created in this thread.
	//	The GarbageCollector handles Insanity objects.
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	//do any other thread initialization, and call user's Main method.
	//set IThread pointer in TLS
    [[self threadDictionary] setObject:[NSValue valueWithPointer:_thrd] forKey:@"CurrentThread"];
	
	_thrd->_ThreadBoilerplate();
	
	[pool drain];
}

-(id)initWithThread:(Insanity::CMacOSXCocoaSubThread*)thrd
{
	if([super init] == nil) return nil;
	
	_thrd = thrd;
	
	return self;
}
@end

namespace Insanity
{
	ISubThread * ISubThread::Create(ISubThread * ext, bool start)
	{
		return new CMacOSXCocoaSubThread(ext,start);
	}
	
	IThread * IThread::Current()
	{
		return CMacOSXCocoaSubThread::_Current();
	}
	
	IThread * CMacOSXCocoaSubThread::_Current()
	{
		//Since we use NSThreads, and when one is created, Cocoa is put in threaded mode
		//	if threaded mode is not enabled, we must not have created any threads.
		if(![NSThread isMultiThreaded]) return IApplication::GetInstance();
		
		//objectForKey: returns nil if no value has been associated with the key
		id spec = [[[NSThread currentThread] threadDictionary] objectForKey:@"CurrentThread"];
		
		//if spec is nil, we must be running on the main thread, since the key for it is never assigned.
		if(spec == nil) return IApplication::GetInstance();
		
		//If we made it past the previous checks, we must be running on a thread.
		//spec is an NSValue storing the thread pointer, so send it a pointerValue message and cast the result.
        CMacOSXCocoaSubThread * ret = reinterpret_cast<CMacOSXCocoaSubThread*>([spec pointerValue]);
        return ret;
	}
	
	CMacOSXCocoaSubThread::CMacOSXCocoaSubThread(ISubThread * ext, bool start) :
		_gc(IGarbageCollector::Create()), _ext(ext), _thrd(nil), _condition(0)
	{
		//NOTE: The ctor is being called in the parent thread.
		
		//Cheat to ensure SubThread survives transfer to the new thread.
		Retain();
		
		if(start) Start();
		else _condition |= ThreadWaiting;
	}
	CMacOSXCocoaSubThread::~CMacOSXCocoaSubThread()
	{
	}
	
	void CMacOSXCocoaSubThread::_ThreadBoilerplate()
	{
		Main();

		_condition &= ~ThreadRunning;
		_condition |= ThreadReturned;
		_gc->Clean();
		Release();
	}
	
	//=====================================================
	//Interface: ISubThread
	//=====================================================
	void CMacOSXCocoaSubThread::Start()
	{
		//if the thread is already running or completed, don't start it again.
		if(_condition & ThreadRunning ||
			_condition & ThreadReturned) return;

		_condition |= ThreadRunning;
		_condition &= ~ThreadWaiting;
		
		_thrd = [[MacObjCThreadWrapper alloc] initWithThread:this]; //the thread calls this' Main, which calls the extension's Main.
		[_thrd start];
	}
	void CMacOSXCocoaSubThread::Main()
	{
        if(_ext) _ext->Main();
	}
	
	//=====================================================
	//Interface: IThread
	//=====================================================
	bool CMacOSXCocoaSubThread::Update()
	{
		if(!(_condition & ThreadRunning)) return false;

		for(auto iter = _tasks.begin(); iter < _tasks.end();)
		{
			(*iter)->Perform();

			if(!(*iter)->ShouldRequeue())
			{
				(*iter)->Dequeue();
				(*iter)->Release();
				iter = _tasks.erase(iter);
			}
		}

		if(++_gcTicker == 60)
		{
			_gc->Collect();
			_gcTicker = 0;
		}

		return (_condition & ThreadRunning) == ThreadRunning;
	}
	void CMacOSXCocoaSubThread::End()
	{
		_condition &= ~ThreadRunning;
	}
	IGarbageCollector * CMacOSXCocoaSubThread::GetGarbageCollector() const
	{
		return _gc;
	}
	void CMacOSXCocoaSubThread::Yield() const
	{
		//should only call sched_yield() if called within the represented thread.
		if(IsCurrentThread()) sched_yield();
	}
	void CMacOSXCocoaSubThread::RegisterTask(ITask * task)
	{
		_tasks.push_back(task);
		task->Retain();
	}
	void CMacOSXCocoaSubThread::Transfer(IObject * obj)
	{
		//Called from thread of which obj is already a resident,
		//	on thread to which to transfer the object.
		//	e.g., someThread->Transfer(someObj) transfers
		//	someObj from the currently executing thread to someThread.
		IThread::Current()->GetGarbageCollector()->Untrack(obj);
		_gc->Track(obj);
	}
	bool CMacOSXCocoaSubThread::IsCurrentThread() const
	{
		return IThread::Current() == (IThread*)this;
	}
}

#endif
