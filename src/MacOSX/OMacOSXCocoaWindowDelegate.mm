#define INSANITY_BUILDING_LIBRARY

#include "OMacOSXCocoaWindowDelegate.hpp"

#if defined(PLATFORM_MACOSX)

@implementation OMacOSXCocoaWindowDelegate
-(id)initWithWindow:(Insanity::CMacOSXCocoaWindow*)window
{
	if(self = [super init])
	{
		_window = window;
	}

	return self;
}

-(void)windowDidMove:(NSNotification*)notification
{
	NSPoint origin = [[notification object] frame].origin;
	_window->MoveHandler(origin.x, origin.y);
}
-(NSSize)windowWillResize:(NSWindow*)window toSize:(NSSize)size
{
	_window->ResizeHandler(size.width, size.height);
    return size;
}
-(void)windowWillClose:(NSNotification*)notification
{
	_window->CloseHandler();
}
-(void)windowDidMiniaturize:(NSNotification*)notification
{
	_window->ShowHandler(false);
}
-(void)windowDidDeminiaturize:(NSNotification*)notification
{
	_window->ShowHandler(true);
}

@end

#endif