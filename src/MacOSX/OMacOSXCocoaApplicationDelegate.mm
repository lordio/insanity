#define INSANITY_BUILDING_LIBRARY

#include "OMacOSXCocoaApplicationDelegate.hpp"

#if defined(PLATFORM_MACOSX)

@implementation OMacOSXCocoaApplicationDelegate
-(NSTerminateReply)applicationShouldTerminate:(id)sender
{
	return NSTerminateNow;
}
-(BOOL)applicationShouldTerminateWhenLastWindowClosed:(id)sender
{
	return YES;
}
@end

#endif