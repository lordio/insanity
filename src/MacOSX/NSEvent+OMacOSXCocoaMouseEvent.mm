#define INSANITY_BUILDING_LIBRARY

#include "NSEvent+OMacOSXCocoaMouseEvent.hpp"

#if defined(PLATFORM_MACOSX)

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
	e = (NSEvent*)NSAllocateObject(self, 0, NULL);

	//Not sure if this is the right way to do this
	//	or if this is even allowed on the Apple runtime.
	e->_type = type;
	e->_location = location;
	e->_modifierFlags = flags;
	e->_timestamp = time;
	e->_windowNumber = windowNum;
	e->_context = context;
	e->_data.mouse.eventNumber = eventNum;
	e->_data.mouse.clickCount = clickNum;
	e->_data.mouse.pressure = pressureValue;
	e->_data.mouse.buttonNumber = buttonNum;
	e->_data.scrollWheel.deltaX = deltaX; //scrollWheel's and mouse's deltaX and deltaY overlap, so setting one sets the other.
	e->_data.scrollWheel.deltaY = deltaY;
	e->_data.scrollWheel.deltaZ = deltaZ; //overwrites mouse event's subtype, but we don't really use that.

	return e;
}

@end

#endif