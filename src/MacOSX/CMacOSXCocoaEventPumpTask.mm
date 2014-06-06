#define INSANITY_BUILDING_LIBRARY

#include "CMacOSXCocoaEventPumpTask.hpp"

#if defined(PLATFORM_MACOSX)

#include <stdexcept>

#import <AppKit/NSApplication.h>
#import <Foundation/NSAutoreleasePool.h>
#import <Foundation/NSRunLoop.h>

namespace Insanity
{
	CMacOSXCocoaEventPumpTask::CMacOSXCocoaEventPumpTask() :
		Default::Task{}, _procmap{}
	{
	}
	CMacOSXCocoaEventPumpTask::~CMacOSXCocoaEventPumpTask()
	{
	}

	//=====================================================
	//Implementation-specific
	//=====================================================
	void CMacOSXCocoaEventPumpTask::RegisterProc(NSWindow * wnd, ProcType proc)
	{
		//ARC handles reference management in ctors and dtors.
		_procmap[wnd] = proc;
	}
	void CMacOSXCocoaEventPumpTask::Clear(NSWindow * wnd)
	{
		_procmap.erase(wnd);
	}

	//=====================================================
	//Interface: ITask
	//=====================================================
	void CMacOSXCocoaEventPumpTask::Perform()
	{
		NSEvent * evt{nil};

		do
		{
			@autoreleasepool{
				//does this normally return nil if no event is available?
				evt = [NSApp nextEventMatchingMask:NSAnyEventMask
					untilDate:[NSDate distantPast]
					inMode:NSDefaultRunLoopMode
					dequeue:YES];

				try
				{
					//Apple notes right mouse-down events on a window of an inactive application send the event to NSApplication,
					//	with a window number of 0.
					_procmap.at([evt window])(evt);
				}
				catch(std::out_of_range oor)
				{
					//if we don't at least catch it, it'll get thrown further out.
					//however, there's nothing to do here.
				}

				//perform default processing of the event.
				[NSApp sendEvent: evt];
			}
		} while(evt != nil);

		[NSApp updateWindows];
	}
	bool CMacOSXCocoaEventPumpTask::ShouldRequeue()
	{
		return _procmap.size() != 0;
	}
}

#endif