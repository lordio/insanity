#define INSANITY_BUILDING_LIBRARY

#include "CMacOSXCocoaWindow.hpp"

#if defined(PLATFORM_MACOSX)

#include <IApplication.hpp>
#include <IConfigObject.hpp>
#include <IString.hpp>
#include <TRectangle.hpp>

#include "CMacOSXCocoaEventPumpTask.hpp"

#include <cmath>
#import <AppKit/NSWindow.h>
#import <AppKit/NSWindowDelegate.h>

/*
A note regarding the keyboard API:
	I'm using the Cocoa NSEvent API for all keys, including modifiers, just for now.
	There is a much lower-level API, HIToolkit, which reports key events in a manner more in line with Win32 and X11.
	That can be switched to later (in fact, probably should).

	If NSEvents report all key events (including modifiers), this should be a problem is NSEvent's -(unsigned short)keyCode is used.
*/

@interface MacObjCWindowWrapper : NSObject<NSWindowDelegate>
{
}
-(void) windowWillMove:(NSNotification*) notification;

@end

@implementation MacObjCWindowWrapper
@end

namespace
{
	Insanity::EKey translate(unichar value)
	{
        Insanity::EKey ret = value;
		if(ret >= 'A' && ret <= 'Z')
		{
			ret -= 'A';
			ret += 'a';
		}
		return ret;
	}
}

namespace Insanity
{
    CMacOSXCocoaEventPumpTask * CMacOSXCocoaWindow::s_pump = nullptr;
    
	IWindow * IWindow::Create(IWindow * ext, IConfigObject const * cfg)
	{
		return new CMacOSXCocoaWindow(ext,cfg);
	}

	CMacOSXCocoaWindow::CMacOSXCocoaWindow(IWindow * ext, IConfigObject const * cfg) :
		_win(nil), _ext(ext), _rect(nullptr)
	{
		_rect = new TRectangle<s16, u16>(static_cast<s16>(cfg->GetProperty("dims.x", (s64)0)),
			static_cast<s16>(cfg->GetProperty("dims.y", (s64)0)),
			static_cast<u16>(cfg->GetProperty("dims.width", (s64)640)),
			static_cast<u16>(cfg->GetProperty("dims.height", (s64)480)));
		_rect->Retain();

		NSRect windowRect = NSMakeRect(_rect->GetX(), _rect->GetY(), _rect->GetWidth(), _rect->GetHeight());

		_win = [[NSWindow alloc]
			initWithContentRect:windowRect
			styleMask:(NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask)
			backing:NSBackingStoreBuffered
			defer:YES];
		[_win retain];

		_SetPumpProc();
	}
	CMacOSXCocoaWindow::~CMacOSXCocoaWindow()
	{
		[_win release];
		_rect->Release();
	}

	void CMacOSXCocoaWindow::_SetPumpProc()
	{
		if(!s_pump) IApplication::GetInstance()->RegisterTask(s_pump = new CMacOSXCocoaEventPumpTask());
	
		s_pump->RegisterProc(_win, [this](NSEvent * evt) -> void
		{
			IWindow * call = (this->_ext ? this->_ext : this);
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
				//call->KeyHandler( tolower([[evt charactersIgnoringModifiers] characterAtIndex:0]), EKeyState::Down);
				break;
			case NSKeyUp:
				call->KeyHandler([evt keyCode], EKeyState::Up);
				//call->KeyHandler( tolower([[evt charactersIgnoringModifiers] characterAtIndex:0]), EKeyState::Up);
				break;
			case NSScrollWheel:
				{
					//Apple notes deltaY returns device delta, which is flipped relative to the screen.
					CGFloat delta = -[evt deltaY];
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
	TRectangle<s16,u16> const * CMacOSXCocoaWindow::GetRect() const
	{
		return _rect;
	}
	void CMacOSXCocoaWindow::Mouse(EMouseButton button, EMouseButtonState state, u16 x, u16 y)
	{
	}
	void CMacOSXCocoaWindow::Key(EKey key, EKeyState state)
	{
	}
	void CMacOSXCocoaWindow::Scroll(EMouseScrollDirection dir, u16 delta)
	{
	}
	void CMacOSXCocoaWindow::Close()
	{
	}
	void CMacOSXCocoaWindow::Show(bool show)
	{
	}
	void CMacOSXCocoaWindow::Move(s16 x, s16 y)
	{
	}
	void CMacOSXCocoaWindow::Resize(u16 width, u16 height)
	{
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
		_rect->SetX(x);
		_rect->SetY(y);
	}
	void CMacOSXCocoaWindow::ResizeHandler(u16 width, u16 height)
	{
		_rect->SetWidth(width);
		_rect->SetHeight(height);
	}
}

#endif
