#ifndef INSANITY_OBJECTIVEC_MACOSX_COCOA_THREAD
#define INSANITY_OBJECTIVEC_MACOSX_COCOA_THREAD

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

#import <Foundation/NSThread.h>

#include "CMacOSXCocoaSubThread.hpp"
#include <Ptr.hpp>

@interface OMacOSXCocoaThread : NSThread
{
	Insanity::WeakPtr<Insanity::CMacOSXCocoaSubThread> _thrd;
}
-(void)main;
-(id)initWithThread:(Insanity::CMacOSXCocoaSubThread*)thrd;
@end

#endif

#endif