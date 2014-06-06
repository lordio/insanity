#define INSANITY_BUILDING_LIBRARY

#include "OMacOSXCocoaThread.hpp"

#if defined(PLATFORM_MACOSX)

#include "CMacOSXCocoaSubThread.hpp"

#import <Foundation/NSString.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSValue.h>

@implementation OMacOSXCocoaThread
-(void)main
{
	//Set up the autorelease pool, for Objective-C objects created in this thread.
	//	The GarbageCollector handles Insanity objects.
	@autoreleasepool{
		//do any other thread initialization, and call user's Main method.
		//set IThread pointer in TLS
		[[self threadDictionary] setObject:[NSValue valueWithPointer:_thrd] forKey:@"CurrentThread"];
	
		_thrd->_ThreadBoilerplate();
	}
}
-(id)initWithThread:(Insanity::CMacOSXCocoaSubThread*)thrd
{
	if(self = [super init])
	{
		_thrd = thrd;
	}
	
	return self;
}
@end

#endif