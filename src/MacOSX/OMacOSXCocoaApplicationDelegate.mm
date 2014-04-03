#define INSANITY_BUILDING_LIBRARY

#include "OMacOSXCocoaApplicationDelegate.hpp"

#if defined(PLATFORM_MACOSX)

@implementation OMacOSXCocoaApplicationDelegate
-(NSApplicationTerminateReply)applicationShouldTerminate:(id)sender
{
	return NSTerminateNow;
}
-(BOOL)applicationShouldTerminateWhenLastWindowClosed:(id)sender
{
	return YES;
}
@end

#endif