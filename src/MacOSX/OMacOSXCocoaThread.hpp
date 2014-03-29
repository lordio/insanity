#ifndef INSANITY_OBJECTIVEC_MACOSX_COCOA_THREAD
#define INSANITY_OBJECTIVEC_MACOSX_COCOA_THREAD

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

#import <Foundation/NSThread.h>

@interface OMacOSXCocoaThread : NSThread
{
	//weak pointer
	Insanity::CMacOSXCocoaSubThread * _thrd;
}
-(void)main;
-(id)initWithThread:(Insanity::CMacOSXCocoaSubThread*)thrd;
@end

#endif

#endif