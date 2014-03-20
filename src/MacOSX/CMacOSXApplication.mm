#define INSANITY_BUILDING_LIBRARY

#include "CMacOSXApplication.hpp"

#if defined(PLATFORM_MACOSX)

#include <IGarbageCollector.hpp>
#include <IMod.hpp>
#include <IThread.hpp>
#include <ITask.hpp>

#import <AppKit/NSApplication.h>
#import <AppKit/NSApplicationDelegate.h>
#import <Foundation/NSAutoreleasePool.h>
#include <sched.h>

#include <algorithm>

//figure out a policy for Objective-C classes defined to help OSX implementations.
//	id est, keep them in the file they are used with, or a separate file?
//	Also, a uniform naming scheme.
@interface InsanityApplicationDelegate : NSObject <NSApplicationDelegate>
{
}
@end

@implementation InsanityApplicationDelegate
-(NSApplicationTerminateReply) applicationShouldTerminate:(NSApplication*)sender
{
	return NSTerminateNow;
}
-(BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender
{
	return YES;
}
@end

@interface InsanityApplication : NSApplication
{
	bool insAppIsRunning;
	CMacOSXCocoaEventPumpTask * pumpTask;
}
@end

@implementation InsanityApplication
//Is init called on NSApplication subclasses?
-(id) init
{
	if(self = [super init])
	{
		insAppIsRunning = true;

		[self setActivationPolicy:NSApplicationActivationPolicyRegular];
		[self setDelegate: [[InsanityApplicationDelegate alloc] init]];
	}

	return self;
}
//=========================================================
//Retrieve all available events from OSX event queue, and
//	process them.
//Returns false if an event has requested the application
//	terminate.
//=========================================================
-(bool) processEvents
{
	NSEvent * evt = nil;

	while(evt = [self nextEventMatchingMask:NSAnyEventMask untilDate:[NSDate distantPast] inMode:NSDefaultRunLoopMode dequeue:YES])
	{
		[self sendEvent: evt];
	}
}
-(void) terminate:(id) sender
{
	insAppIsRunning = false;

	[super terminate:sender];
}
@end

namespace Insanity
{
	IApplication * IApplication::s_app = nullptr;

	IApplication * IApplication::GetInstance()
	{
		if(s_app) return s_app;

		return s_app = new CMacOSXApplication();
	}

	CMacOSXApplication::CMacOSXApplication() :
		_gc(IGarbageCollector::Create()), _ref(0), _running(true)
	{
		//don't need to catch it, as it's added to the thread behind the scenes
		//	may want it for [pool drain] in dtor.
		//	Does ARC use the autorelease annotation? How will that work with this?
		//	I'm thinking I'd need to put autorelease tags in any method that interacts with ObjC objects.
		[[NSAutoreleasePool alloc] init];

		//do I need to provide a delegate for anything?
		[InsanityApplication sharedApplication];
		[NSApp finishLaunching];
	}
	CMacOSXApplication::~CMacOSXApplication()
	{
		IMod::ClearCache();

		_gc->Clean();
		delete _gc;

		s_app = nullptr;
	}

	//=====================================================
	//Interface: IThread
	//=====================================================
	bool CMacOSXApplication::Update()
	{
		if(!_running) return false;

		//Run all waiting tasks.
		for(auto iter = _taskList.begin(); iter < _taskList.end();)
		{
			(*iter)->Perform();

			if(!(*iter)->ShouldRequeue())
			{
				(*iter)->Dequeue();
				(*iter)->Release();
				iter = _taskList.erase(iter);
			}
			else iter++;
		}

		//Can play with this value to change garbage collection frequency
		if(++_gcTicker == 60)
		{
			_gc->Collect();
			_gcTicker = 0;
		}

		return _running;
	}
	void CMacOSXApplication::End()
	{
		_running = false;
	}
	IGarbageCollector * CMacOSXApplication::GetGarbageCollector() const
	{
		return _gc;
	}
	void CMacOSXApplication::Yield() const
	{
		if(IsCurrentThread()) sched_yield();
	}
	void CMacOSXApplication::RegisterTask(ITask * task)
	{
		_taskList.push_back(task);
		task->Retain();
	}
	void CMacOSXApplication::Transfer(IObject * obj)
	{
		IThread::Current()->GetGarbageCollector()->Untrack(obj);
		_gc->Track(obj);
	}
	bool CMacOSXApplication::IsCurrentThread() const
	{
		return IThread::Current() == (IThread*)this;
	}

	//=====================================================
	//Interface: IObject
	//=====================================================
	void CMacOSXApplication::Retain() const
	{
		++_ref;
	}
	void CMacOSXApplication::Release() const
	{
		if(_ref == 0) return;
		if(--_ref == 0) delete this;
	}
	u64 CMacOSXApplication::GetReferenceCount() const
	{
		return _ref;
	}
	void CMacOSXApplication::Delete()
	{
		delete this;
	}
}

#endif
