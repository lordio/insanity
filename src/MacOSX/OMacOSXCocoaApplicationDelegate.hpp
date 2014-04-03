#ifndef INSANITY_OBJECTIVEC_MACOSX_COCOA_APPLICATION_DELEGATE
#define INSANITY_OBJECTIVEC_MACOSX_COCOA_APPLICATION_DELEGATE

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

#include <Foundation/NSObject.h>
#include <AppKit/NSApplication.h>

@interface OMacOSXCocoaApplicationDelegate : NSObject <NSApplicationDelegate>
{
}

-(NSApplicationTerminateReply)applicationShouldTerminate:(id)sender;
-(BOOL)applicationShouldTerminateWhenLastWindowClosed:(id)sender;
@end

#endif

#endif