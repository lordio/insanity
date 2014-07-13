#ifndef INSANITY_OBJECTIVEC_MACOSX_COCOA_WINDOW_DELEGATE
#define INSANITY_OBJECTIVEC_MACOSX_COCOA_WINDOW_DELEGATE

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

#import <AppKit/NSWindow.h>
#include <IWindow.hpp>
#include <Ptr.hpp>

@interface OMacOSXCocoaWindowDelegate : NSObject <NSWindowDelegate>
{
	Insanity::WeakPtr<Insanity::IWindow> _window;
}
//should pass the window that will respond to events (usually a Default::Window inheritor)
-(id)initWithWindow:(Insanity::IWindow*)window;

-(void)windowDidMove:(NSNotification*)notification;
-(NSSize)windowWillResize:(NSWindow*)window toSize:(NSSize)size;
-(void)windowWillClose:(NSNotification*)notification;
-(void)windowDidMiniaturize:(NSNotification*)notification;
-(void)windowDidDeminiaturize:(NSNotification*)notification;
@end

#endif

#endif