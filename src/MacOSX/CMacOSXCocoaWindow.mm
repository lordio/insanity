#define INSANITY_BUILDING_LIBRARY

#include "CMacOSXCocoaWindow.hpp"

#if defined(PLATFORM_MACOSX)

#include <IApplication.hpp>
#include <IConfigObject.hpp>

#include "CMacOSXCocoaEventPumpTask.hpp"

#include <cmath>
#import <AppKit/NSWindow.h>
#import <Foundation/NSProcessInfo.h>
#include "OMacOSXCocoaWindowDelegate.hpp"
#include "NSEvent+OMacOSXCocoaMouseEvent.hpp"

/*
A note regarding the keyboard API:
	I'm using the Cocoa NSEvent API for all keys, including modifiers, just for now.
	There is a much lower-level API, HIToolkit, which reports key events in a manner more in line with Win32 and X11.
	That can be switched to later (in fact, probably should).

	If NSEvents report all key events (including modifiers), this shouldn't be a problem if NSEvent's -(unsigned short)keyCode is used.
*/

namespace Insanity
{
    Ptr<CMacOSXCocoaEventPumpTask> CMacOSXCocoaWindow::s_pump{};
    u64 CMacOSXCocoaWindow::s_winCount{};
    
	IWindow * IWindow::Create(IWindow * ext, IConfigObject const * cfg)
	{
		return new CMacOSXCocoaWindow{ext,cfg};
	}

	CMacOSXCocoaWindow::CMacOSXCocoaWindow(IWindow * ext, IConfigObject const * cfg) :
		_win{nil}, _ext{ext}, _rect{}
	{
		_rect.SetX(static_cast<s16>(cfg->GetProperty("dims.x", (s64)0)));
		_rect.SetY(static_cast<s16>(cfg->GetProperty("dims.y", (s64)0)));
		_rect.SetWidth(static_cast<u16>(cfg->GetProperty("dims.width", (s64)640)));
		_rect.SetHeight(static_cast<u16>(cfg->GetProperty("dims.height", (s64)480)));

		NSRect windowRect = NSMakeRect(_rect.GetX(), _rect.GetY(), _rect.GetWidth(), _rect.GetHeight());

		_win = [[NSWindow alloc]
			initWithContentRect:windowRect
			styleMask:(NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask)
			backing:NSBackingStoreBuffered
			defer:YES];

		[_win setDelegate:(_delegate = [[OMacOSXCocoaWindowDelegate alloc] initWithWindow: (_ext ? _ext : this)])];
		
		SetTitle(cfg->GetProperty("title", ""));

		_SetPumpProc();

		++s_winCount;
	}
	CMacOSXCocoaWindow::~CMacOSXCocoaWindow()
	{
		_delegate = nil;
		if(--s_winCount) s_pump = nullptr;
	}

	void CMacOSXCocoaWindow::_SetPumpProc()
	{
		if(!s_pump) IApplication::GetInstance()->RegisterTask(s_pump = new CMacOSXCocoaEventPumpTask{});
	
		//not all things Insanity considers events come through this method;
		//	move, resize, close, and show events are reported by the WindowDelegate.
		s_pump->RegisterProc(_win, [this](NSEvent * evt) -> void
		{
			IWindow * call{this->_ext ? this->_ext.Get() : this};
			NSPoint mouseLoc = [NSEvent mouseLocation];
			//should this be [NSEvent locationInWindow]?
			//is there an exception that gets thrown if the event isn't mouse-related?
			
			//switch on event type, calling handlers.
			switch([evt type])
			{
			case NSLeftMouseDown:
				call->MouseHandler(EMouseButton::Left, EMouseButtonState::Down, mouseLoc.x, mouseLoc.y);
				break;
			case NSLeftMouseUp:
				call->MouseHandler(EMouseButton::Left, EMouseButtonState::Up, mouseLoc.x, mouseLoc.y);
				break;
			case NSRightMouseDown:
				call->MouseHandler(EMouseButton::Right, EMouseButtonState::Down, mouseLoc.x, mouseLoc.y);
				break;
			case NSRightMouseUp:
				call->MouseHandler(EMouseButton::Right, EMouseButtonState::Up, mouseLoc.x, mouseLoc.y);
				break;
			//research values returned by [evt buttonNumber] for NSOtherMouse* events (also NSLeftMouse* and NSRightMouse*)
			case NSOtherMouseDown:
				//split up based on [evt buttonNumber], I think middle, X1, and X2 will all come in through this.
				break;
			case NSOtherMouseUp:
				//same as above
				break;
			case NSKeyDown:
				call->KeyHandler([evt keyCode], EKeyState::Down);
				break;
			case NSKeyUp:
				call->KeyHandler([evt keyCode], EKeyState::Up);
				break;
			case NSScrollWheel:
				{
					//Apple notes deltaY returns device delta, which is flipped relative to the screen.
					CGFloat delta{-[evt deltaY]};
					call->ScrollHandler((delta > 0 ? EMouseScrollDirection::Up : EMouseScrollDirection::Down), static_cast<u16>(abs(delta)));
				}
				break;
			case NSMouseMoved: //is this sent instead of, xor in addition to, NS*MouseDragged?
				//may need to call [_window setAcceptsMouseMovedEvents:YES] in order to receive these.
				call->MouseHandler(EMouseButton::Null, EMouseButtonState::Null, mouseLoc.x, mouseLoc.y);
				break;
			default:
				[NSApp sendEvent:evt];
			}
		});

		//not all events Insanity handles are reported as NSEvents; some are handled through the Delegate.
		//extra incentive to consider having handlers return bool; returning false stops normal processing of the event.
	}
	NSWindow * CMacOSXCocoaWindow::GetWindow() const
	{
		return _win;
	}
	
	//=====================================================
	//Interface: IWindow
	//=====================================================
	TRectangle<s16,u16> const & CMacOSXCocoaWindow::GetRect() const
	{
		return _rect;
	}
	char const * CMacOSXCocoaWindow::GetTitle() const
	{
		return _title.c_str();
	}
	void CMacOSXCocoaWindow::SetTitle(char const * title)
	{
		_title = title;
		[_win setTitle:[NSString stringWithCString:_title.c_str() encoding:NSUTF8StringEncoding]]; //is this the default for OSX?
	}
	void CMacOSXCocoaWindow::Mouse(EMouseButton button, EMouseButtonState state, u16 x, u16 y)
	{
		NSEventType type{};
		NSInteger buttonNumber{};
		switch(button)
		{
		case EMouseButton::Left:
			type = NSLeftMouseDown;
			//should probably figure out all the button numbers up to X2
			break;
		case EMouseButton::Right:
			type = NSRightMouseDown;
			break;
		case EMouseButton::Null:
			type = NSMouseMoved;
			break;
		case EMouseButton::Middle:
			type = NSOtherMouseDown;
			buttonNumber = 2; //just a guess, update when known.
			break;
		case EMouseButton::X1:
			type = NSOtherMouseDown;
			buttonNumber = 3; //again, test and update this
			break;
		case EMouseButton::X2:
			type = NSOtherMouseDown;
			buttonNumber = 4; //see above
			break;
		}
		if(button != EMouseButton::Null)
		{
			switch(state)
			{
			case EMouseButtonState::Null:
				//ignore the button; treat as a mouse move event.
				//TODO: Update other implementations to use this same behavior.
				type = NSMouseMoved;
				buttonNumber = 0;
				break;
			case EMouseButtonState::Down:
				//no-op; down is listed first for each mouse button
				break;
			case EMouseButtonState::Up:
				type++; //up is always listed immediately after down, so increment
				break;
            case EMouseButtonState::DoubleClick:
                //treat as Down event. May have to send custom event.
                break;
			}
		}

		NSPoint pt = NSMakePoint(x,y);
		//use the message provided by the OMacOSXCocoaMouseEvent category on NSEvent.
		NSEvent * evt{[NSEvent mouseEventWithType:type
			location:pt
			modifierFlags:0 
			timestamp:[[NSProcessInfo processInfo] systemUptime]
			windowNumber:[_win windowNumber]
			context:[_win graphicsContext]
			eventNumber:0 //no clear way to figure out a proper value
			clickCount:0 //not even sure how this is used.
			pressure:0.0f //not really necessary for non-tablet events
			buttonNumber:buttonNumber
			deltaX:0.0f
			deltaY:0.0f
			deltaZ:0.0f]};
		if(evt != nil) [NSApp sendEvent:evt];
	}
	void CMacOSXCocoaWindow::Key(EKey key, EKeyState state)
	{
		NSEvent * evt{[NSEvent keyEventWithType:(state == EKeyState::Down ? NSKeyDown : NSKeyUp)
			location:NSMakePoint(0,0) //I hope it doesn't care too much about this value
			modifierFlags:0
			timestamp:[[NSProcessInfo processInfo] systemUptime]
			windowNumber:[_win windowNumber]
			context:[_win graphicsContext] //is this right?
			characters:@"" //could have a translator function, but hopefully it's not necessary
			charactersIgnoringModifiers:@"" //as before
			isARepeat:NO
			keyCode:key]};
		if(evt != nil) [NSApp sendEvent:evt];
	}
	void CMacOSXCocoaWindow::Scroll(EMouseScrollDirection dir, u16 delta)
	{
		//FIXME: Implement this.
	}
	void CMacOSXCocoaWindow::Close()
	{
		[_win close];
	}
	void CMacOSXCocoaWindow::Show(bool show)
	{
		if(show) [_win deminiaturize:nil];
		else [_win miniaturize:nil];
	}
	void CMacOSXCocoaWindow::Move(s16 x, s16 y)
	{
		NSRect frame = [_win frame];
		frame.origin.x = x;
		frame.origin.y = y;
		[_win setFrame:frame display:YES];
	}
	void CMacOSXCocoaWindow::Resize(u16 width, u16 height)
	{
		NSRect frame = [_win frame];
		frame.size.width = width;
		frame.size.height = height;
		[_win setFrame:frame display:YES];
	}
	
	void CMacOSXCocoaWindow::MouseHandler(EMouseButton button, EMouseButtonState state, u16 x, u16 y)
	{
	}
	void CMacOSXCocoaWindow::KeyHandler(EKey key, EKeyState state)
	{
	}
	void CMacOSXCocoaWindow::ScrollHandler(EMouseScrollDirection dir, u16 delta)
	{
	}
	void CMacOSXCocoaWindow::CloseHandler()
	{
	}
	void CMacOSXCocoaWindow::ShowHandler(bool show)
	{
	}
	void CMacOSXCocoaWindow::MoveHandler(s16 x, s16 y)
	{
		_rect.SetX(x);
		_rect.SetY(y);
	}
	void CMacOSXCocoaWindow::ResizeHandler(u16 width, u16 height)
	{
		_rect.SetWidth(width);
		_rect.SetHeight(height);
	}
}

#endif
