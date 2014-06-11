#define INSANITY_BUILDING_LIBRARY

#include "NSEvent+OMacOSXCocoaMouseEvent.hpp"

#if defined(PLATFORM_MACOSX)

#import <Foundation/NSException.h>

namespace
{
	const NSEventMask _MouseEvents =
		NSLeftMouseDownMask |
		NSLeftMouseUpMask |
		NSRightMouseDownMask |
		NSRightMouseUpMask |
		NSMouseMovedMask |
		NSLeftMouseDraggedMask |
		NSRightMouseDraggedMask |
		NSMouseEnteredMask |
		NSMouseExitedMask |
		NSCursorUpdateMask |
		NSScrollWheelMask |
		NSOtherMouseDownMask |
		NSOtherMouseUpMask |
		NSOtherMouseDraggedMask;
}

@implementation NSEvent (OMacOSXCocoaMouseEvent)
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
	deltaZ:(CGFloat)deltaZ
{
	NSEvent * e;

	if(!(NSEventMaskFromType(type) & _MouseEvents))
		[NSException raise: NSInvalidArgumentException
			format: @"mouseEvent with wrong type"];

	//documentation says NSDefaultMallocZone(), which GNUstep uses, is deprecated.
	//	It also says to pass NULL to NSAllocateObject's third param for the default, so just do that.
	//	NSAllocateObject isn't allowed in ARC. What about [NSEvent alloc]?
	//	See what happens when compiling.
    //  Fails.
	//e = (NSEvent*)NSAllocateObject(self, 0, NULL);
    e = [NSEvent alloc];

	//Builds on Mac, so seems to be okay.
	e->_type = type;
	e->_location = location;
	e->_modifierFlags = (unsigned int)flags;
	e->_timestamp = time;
	e->_windowNumber = windowNum;
	e->_context = context;
	e->_data.mouse.eventNumber = (int)eventNum;
	e->_data.mouse.clickCount = (int)clickNum;
	e->_data.mouse.pressure = pressureValue;
	e->_data.mouse.buttonNumber = buttonNum;
	e->_data.scrollWheel.deltaX = deltaX; //scrollWheel's and mouse's deltaX and deltaY overlap, so setting one sets the other.
	e->_data.scrollWheel.deltaY = deltaY;
	e->_data.scrollWheel.deltaZ = deltaZ; //overwrites mouse event's subtype, but we don't really use that.

	return e;
}

@end

#endif