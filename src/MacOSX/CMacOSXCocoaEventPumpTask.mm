#define INSANITY_BUILDING_LIBRARY

#include "CMacOSXCocoaEventPumpTask.hpp"

#if defined(PLATFORM_MACOSX)

#include <stdexcept>

#import <Foundation/NSAutoreleasePool.h>

namespace Insanity
{
	CMacOSXCocoaEventPumpTask::CMacOSXCocoaEventPumpTask()
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
		//key reference should be strong.
		_procmap[wnd] = proc;
		[wnd retain];
	}
	void CMacOSXCocoaEventPumpTask::Clear(NSWindow * wnd)
	{
		_procmap.erase(wnd);
		[wnd release];
	}

	//=====================================================
	//Interface: ITask
	//=====================================================
	void CMacOSXCocoaEventPumpTask::Perform()
	{
		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

		NSEvent * evt = nil;

		do
		{
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
		} while(evt != nil);

		[NSApp updateWindows];

		[pool drain];
	}
	bool CMacOSXCocoaEventPumpTask::ShouldRequeue()
	{
		return _procmap.size() != 0;
	}
}

#endif