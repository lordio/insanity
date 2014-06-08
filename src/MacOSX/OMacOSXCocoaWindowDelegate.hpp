#ifndef INSANITY_OBJECTIVEC_MACOSX_COCOA_WINDOW_DELEGATE
#define INSANITY_OBJECTIVEC_MACOSX_COCOA_WINDOW_DELEGATE

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

#include <AppKit/NSWindow.h>
#include "CMacOSXCocoaWindow.hpp"
#include <Ptr.hpp>

@interface OMacOSXCocoaWindowDelegate : NSObject <NSWindowDelegate>
{
	Insanity::WeakPtr<Insanity::CMacOSXCocoaWindow> _window;
}
-(id)initWithWindow:(Insanity::CMacOSXCocoaWindow*)window;

-(void)windowDidMove:(NSNotification*)notification;
-(NSSize)windowWillResize:(NSWindow*)window toSize:(NSSize)size;
-(void)windowWillClose:(NSNotification*)notification;
-(void)windowDidMiniaturize:(NSNotification*)notification;
-(void)windowDidDeminiaturize:(NSNotification*)notification;
@end

#endif

#endif