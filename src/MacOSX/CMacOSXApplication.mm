#define INSANITY_BUILDING_LIBRARY

#include "CMacOSXApplication.hpp"

#if defined(PLATFORM_MACOSX)

#include <IGarbageCollector.hpp>
#include <IMod.hpp>
#include <IThread.hpp>
#include <ITask.hpp>

#import <AppKit/NSApplication.h>
#import <AppKit/NSEvent.h>
#include <sched.h>
#include "OMacOSXCocoaApplicationDelegate.hpp"

#include <algorithm>

//Need autoreleasepool blocks anywhere that creates temporary Objective-C objects.
//	If all created objects outlive the method, no block is necessary.
//	Also need one in a thread.

namespace Insanity
{
	IApplication * IApplication::s_app{};

	IApplication * IApplication::GetInstance()
	{
		if(s_app) return s_app;

		return s_app = new CMacOSXApplication{};
	}

	CMacOSXApplication::CMacOSXApplication() :
		_gc{IGarbageCollector::Create()}
	{
		[[NSApplication sharedApplication] setActivationPolicy:NSApplicationActivationPolicyRegular];
		[NSApp setDelegate:(_appDelegate = [[OMacOSXCocoaApplicationDelegate alloc] init])];
		[NSApp finishLaunching];
	}
	CMacOSXApplication::~CMacOSXApplication()
	{
		IMod::ClearCache();

		s_app = nullptr;
        _appDelegate = nil;
	}

	//=====================================================
	//Interface: IThread
	//=====================================================
	bool CMacOSXApplication::Update()
	{
		if(!_running) return false;

		//Run all waiting tasks.
		for(auto iter = _taskList.begin(); iter != _taskList.end();)
		{
			(*iter)->Perform();

			if(!(*iter)->ShouldRequeue())
			{
				(*iter)->Dequeue();
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
		return _gc.get();
	}
	void CMacOSXApplication::Yield() const
	{
		if(IsCurrentThread()) sched_yield();
	}
	void CMacOSXApplication::RegisterTask(ITask * task)
	{
		_taskList.push_back(task);
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
