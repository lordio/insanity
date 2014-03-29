#ifndef INSANITY_OBJECTIVEC_MACOSX_COCOA_MOUSE_EVENT
#define INSANITY_OBJECTIVEC_MACOSX_COCOA_MOUSE_EVENT

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

//shamelessly ripped from GNUstep's implementation of NSEvent, because it just makes sense.
//Available as of 3/26/2014 from https://github.com/gnustep/gnustep-gui/blob/master/Source/NSEvent.m L194-234
//I mean, if this is how you synthesize NSOtherMouse* events, why does the default message not let you specify the button number?
//Similarly, scroll events and delta{X,Y,Z}.

#include <AppKit/NSEvent.h>

@interface NSEvent (OMacOSXCocoaMouseEvent)
+(NSEvent*)mouseEventWithType:(NSEventType)type 
	location:(NSPoint)location 
	modifierFlags:(NSUInteger)flags 
	timestamp:(NSTimeInterval)time
	windowNumber:(NSInteger)windowNum
	context:(NSGraphicsContext*)context
	eventNumber:(NSInteger)eventNum
	clickCount:(NSInteger)clickNum
	pressure:(float)pressureValue
	buttonNumber:(NSInteger)buttonNum
	deltaX:(CGFloat)deltaX
	deltaY:(CGFloat)deltaY
	deltaZ:(CGFloat)deltaZ;

@end

#endif

#endif