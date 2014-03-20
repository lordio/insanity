#define INSANITY_BUILDING_LIBRARY

#include "CLinuxX11Window.hpp"

#if defined(PLATFORM_LINUX)

#include <IApplication.hpp>
#include <IString.hpp>
#include "CLinuxX11EventPumpTask.hpp"
#include "../unused/ConfigFile.hpp"
#include <IConfigObject.hpp>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glxext.h>

#include <iostream>

namespace
{
	Insanity::EMouseButton translate(int xbutton)
	{
		//will need to test these.
		//Specifically, 6 and 7.
		Insanity::EMouseButton ret;
		switch(xbutton)
		{
		case 1:
			ret = Insanity::EMouseButton::Left;
			break;
		case 2:
			ret = Insanity::EMouseButton::Middle;
			break;
		case 3:
			ret = Insanity::EMouseButton::Right;
			break;
		case 6:
			ret = Insanity::EMouseButton::X1;
			break;
		case 7:
			ret = Insanity::EMouseButton::X2;
			break;
		}
		return ret;
	}
	int translate(Insanity::EMouseButton button)
	{
		//reverse translation of XButton constants to EMouseButton.
		int ret;
		switch(button)
		{
		case Insanity::EMouseButton::Left:
			ret = 1;
			break;
		case Insanity::EMouseButton::Middle:
			ret = 2;
			break;
		case Insanity::EMouseButton::Right:
			ret = 3;
			break;
		case Insanity::EMouseButton::X1:
			ret = 6;
			break;
		case Insanity::EMouseButton::X2:
			ret = 7;
			break;
		default:
			ret = 0;
		}
		return ret;
	}
}

namespace Insanity
{
	Display * CLinuxX11Window::s_dpy = nullptr;
	CLinuxX11EventPumpTask * CLinuxX11Window::s_pump = nullptr;
	u64 CLinuxX11Window::s_winCount = 0; //when it goes to 0, unregister the event pump task.
	u8 CLinuxX11Window::s_glxVersion = 0; //valid values are 0x10 (glX 1.0) through 0x14 (glX 1.4). 0xFF indicates no glX support.
	s32 CLinuxX11Window::s_errorBase = 0; //add these to the error and event constants.
	s32 CLinuxX11Window::s_eventBase = 0;
	GLXFBConfig CLinuxX11Window::s_fbc = nullptr; //GLXFBConfig is a typedef'd pointer.
	Atom CLinuxX11Window::s_del = None; //Atom is an XID (probably).

	IWindow * IWindow::Create(IWindow * ext, IConfigObject const * cfg)
	{
		return new CLinuxX11Window(ext,cfg);
	}

	CLinuxX11Window::CLinuxX11Window(IWindow * ext, IConfigObject const * cfg) :
		_rect(nullptr), _ext(ext), _win(0), _isOpen(false)
	{
		_rect = new TRectangle<s16,u16>(
			static_cast<s16>(cfg->GetProperty("dims.x", (s64)0)),
			static_cast<s16>(cfg->GetProperty("dims.y", (s64)0)),
			static_cast<u16>(cfg->GetProperty("dims.width", (s64)640)),
			static_cast<u16>(cfg->GetProperty("dims.height", (s64)480)));
		_rect->Retain();
		
		_InitXDisplay();
		_InitGLX();
		
		XVisualInfo * xvi = _GetXVisual(
			static_cast<int>(cfg->GetProperty("Linux.GLX.red", (s64)8)),	//GLX since it has more to do with OpenGL than X...
			static_cast<int>(cfg->GetProperty("Linux.GLX.green", (s64)8)),
			static_cast<int>(cfg->GetProperty("Linux.GLX.blue", (s64)8)),
			static_cast<int>(cfg->GetProperty("Linux.GLX.depth", (s64)24)),	//...especially here.
			cfg->GetProperty("Linux.GLX.doubleBuffer", (s64)1) > 0);		//Sort of a cast to bool
		
		XSetWindowAttributes xswa;
		_InitWindowAttributes(&xswa,xvi);
		
		_InitXWindow(cfg->GetProperty("title", IString<char>::Create("")), xvi, &xswa);
		
		_isOpen = true;
		
		if(xvi) XFree(xvi);
		
		_SetPumpProc();
		Move(_rect->GetX(), _rect->GetY());
		Resize(_rect->GetWidth(), _rect->GetHeight());
	}
	CLinuxX11Window::~CLinuxX11Window()
	{
		s_pump->Clear(_win);
		
		_rect->Release();
		
		//destroy the window
		XDestroyWindow(s_dpy,_win);
		
		if(--s_winCount == 0)
		{
			//if another window is created after the last one is destroyed, redo GLX initialization.
			XFree(s_fbc);
			s_glxVersion = 0;
		}
	}
	
	Window CLinuxX11Window::GetWindow() const
	{
		return _win;
	}
	Display * CLinuxX11Window::GetDisplay()
	{
		return s_dpy;
	}
	GLXFBConfig CLinuxX11Window::GetFBConfig()
	{
		return s_fbc;
	}
	u8 CLinuxX11Window::GetGLXVersion()
	{
		return s_glxVersion;
	}
	
	void CLinuxX11Window::_InitXDisplay()
	{
		if(!s_dpy) s_dpy = XOpenDisplay(NULL);
	}
	void CLinuxX11Window::_InitGLX()
	{
		if(!s_glxVersion)
		{
			Bool isSupported = glXQueryExtension(s_dpy, &s_errorBase, &s_eventBase);
			if(!isSupported) s_glxVersion = 0xff;
			else
			{
				int glxMajor = 0;
				int glxMinor = 0;
				glXQueryVersion(s_dpy,&glxMajor,&glxMinor);
				s_glxVersion = static_cast<u8>( (glxMajor << 4) + glxMinor );
			}
		}
	}
	XVisualInfo * CLinuxX11Window::_GetXVisual(int redBits, int greenBits, int blueBits, int depthBits, bool doubleBuffer)
	{
		XVisualInfo * xvi = nullptr;
		if(s_glxVersion != 0xFF)
		{
			GLXFBConfigID cfgid = 0; //XID typedef, which is an int of some stripe.
			int attribs[] =
			{
				//not bad candidates for a config script.
				//May also want to specify TrueColor, as DirectColor and PseudoColor have undefined colormaps on creation.
				GLX_DOUBLEBUFFER, doubleBuffer,
				GLX_RED_SIZE, redBits,
				GLX_GREEN_SIZE, greenBits,
				GLX_BLUE_SIZE, blueBits,
				GLX_DEPTH_SIZE, depthBits,
				GLX_RENDER_TYPE, GLX_RGBA_BIT,
				GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT | GLX_PIXMAP_BIT | GLX_PBUFFER_BIT,
				None
			};
			int cfgCount = 0;
			GLXFBConfig * cfgs = glXChooseFBConfig(s_dpy,
				DefaultScreen(s_dpy),
				attribs,	//attrib_list (array of ints)
				&cfgCount);	//nelements (cfgs count)
				
			//might be worthwhile to ensure cfgCount is not 0
			//this way, if no valid context is returned, fall back on X rendering.
			if(cfgCount != 0)
			{
				//decide on the config to use, and store it.
				//release cfgs using XFree once no longer needed.
			
				//get the XID so that we can free the other, unused FBC's.
				//first one should be fine for now, could also enumerate over them, but I don't see the point.
				glXGetFBConfigAttrib(s_dpy, *cfgs, GLX_FBCONFIG_ID, reinterpret_cast<int*>(&cfgid));
				XFree(cfgs);
				int singleAttribs[] =
				{
					GLX_FBCONFIG_ID, static_cast<int>(cfgid),
					None
				};
				//this should only return one.
				s_fbc = *glXChooseFBConfig(s_dpy, DefaultScreen(s_dpy), singleAttribs, &cfgCount);
				xvi = glXGetVisualFromFBConfig(s_dpy, s_fbc);
			}
		}
		return xvi;
	}
	void CLinuxX11Window::_InitWindowAttributes(XSetWindowAttributes * xswa, XVisualInfo const * xvi)
	{
		xswa->border_pixel = WhitePixel(s_dpy, DefaultScreen(s_dpy));
		xswa->background_pixel = BlackPixel(s_dpy, DefaultScreen(s_dpy));
		xswa->event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | StructureNotifyMask | PointerMotionMask;
		if(xvi) xswa->colormap = XCreateColormap(s_dpy, DefaultRootWindow(s_dpy), xvi->visual, AllocNone);
	}
	void CLinuxX11Window::_InitXWindow(IString<char> const * title, XVisualInfo const * xvi, XSetWindowAttributes * xswa)
	{
		//_rect should already be defined
		_win = XCreateWindow(s_dpy,
			DefaultRootWindow(s_dpy),
			_rect->GetX(), _rect->GetY(),
			_rect->GetWidth(), _rect->GetHeight(), //is there some way to account for window decoration?
			1,	//border width
			(xvi ? xvi->depth : CopyFromParent),	//depth
			InputOutput, //class (InputOutput, InputOnly, or CopyFromParent)
			(xvi ? xvi->visual : CopyFromParent),	//visual
			CWBackPixel | CWBorderPixel | CWEventMask | (xvi ? CWColormap : 0),	//attribute mask
			xswa);	//XSetWindowAttributes*
			
		XStoreName(s_dpy, _win, title->Array());
		
		if(s_del == None) s_del = XInternAtom(s_dpy,"WM_DELETE_WINDOW",False);
		
		XSetWMProtocols(s_dpy,_win,&s_del,1);
		XMapWindow(s_dpy, _win);
		XFlush(s_dpy);
	}
	void CLinuxX11Window::_SetPumpProc()
	{
		if(!s_pump) IApplication::GetInstance()->RegisterTask(s_pump = new CLinuxX11EventPumpTask(s_dpy));

		s_pump->RegisterProc(_win, [this](XEvent * xe) -> void
		{
			IWindow * call = (this->_ext ? this->_ext : this);
			//switch on the event type
			switch(xe->type)
			{
			case Expose:
				//maybe a paint handler isn't such a bad idea.
				break;
			case ButtonPress:
				{
					//scroll events are reported as buttons 4 and 5. Research mappings for 5-button mice (for EMouseButton::X1 and X2).
					//Testing shows 4 is up, 5 is down.
					if(xe->xbutton.button == 4) call->ScrollHandler(EMouseScrollDirection::Up,1);
					else if(xe->xbutton.button == 5) call->ScrollHandler(EMouseScrollDirection::Down,1);
					else
					{
						EMouseButton button = translate(xe->xbutton.button);
						call->MouseHandler(button,EMouseButtonState::Down,xe->xbutton.x,xe->xbutton.y);
					}
				}
				break;
			case ButtonRelease:
				{
					//ignore scroll wheel events.
					if(xe->xbutton.button == 4 || xe->xbutton.button == 5) break;
					
					EMouseButton button = translate(xe->xbutton.button);
				
					//TODO: need to store and compare last up time (or down, depending) and report as double click instead (or in addition, again, depending)
					call->MouseHandler(button,EMouseButtonState::Up,xe->xbutton.x,xe->xbutton.y);
				}
				break;
			case KeyPress:
				{
					int key = 1;
					KeySym * sym = XGetKeyboardMapping(s_dpy, xe->xkey.keycode, 1, &key);
					
					call->KeyHandler((EKey)*sym,EKeyState::Down);
					
					XFree(sym);
				}
				break;
			case KeyRelease:
				{
					int key = 1;
					KeySym * sym = XGetKeyboardMapping(s_dpy, xe->xkey.keycode, 1, &key);
					
					call->KeyHandler((EKey)*sym,EKeyState::Up);
					
					XFree(sym);
				}
				break;
			case MotionNotify:
				call->MouseHandler(EMouseButton::Null, EMouseButtonState::Null, xe->xmotion.x, xe->xmotion.y);
				break;
			case ClientMessage:
				if((Atom)xe->xclient.data.l[0] == s_del) call->CloseHandler();
				break;
			case ConfigureNotify:
				if(xe->xconfigure.width != _rect->GetWidth() ||
					xe->xconfigure.height != _rect->GetHeight())
				{
					call->ResizeHandler(xe->xconfigure.width, xe->xconfigure.height);
				}
				if(xe->xconfigure.x != _rect->GetX() || 
					xe->xconfigure.y != _rect->GetY())
				{
					call->MoveHandler(xe->xconfigure.x, xe->xconfigure.y);
				}
				break;
			case MapNotify:
				call->ShowHandler(true);
				break;
			case UnmapNotify:
				call->ShowHandler(false);
				break;
			}
		});
	}
	
	//=====================================================
	//Interface: IWindow
	//=====================================================
	TRectangle<s16,u16> const * CLinuxX11Window::GetRect() const
	{
		return _rect;
	}
	void CLinuxX11Window::Mouse(EMouseButton button, EMouseButtonState state, u16 x, u16 y)
	{
		//hopefully the X11 server fills in anything I haven't here.
		//only forces send_event to True and sets the serial.
		XEvent xe;
		int downup = (state == EMouseButtonState::Up ? ButtonRelease : ButtonPress);
		//no way to have X11 report double-click events; track time of last up and report double if within certain limit (hard-baked or configured)
		xe.type = downup;
		xe.xbutton.send_event = True;
		xe.xbutton.display = s_dpy;
		xe.xbutton.window = _win;
		xe.xbutton.root = DefaultRootWindow(s_dpy);
		xe.xbutton.subwindow = _win;
		xe.xbutton.x = x;
		xe.xbutton.y = y;
		xe.xbutton.x_root = x + _rect->GetX();
		xe.xbutton.y_root = y + _rect->GetY();
		xe.xbutton.button = translate(button);
		xe.xbutton.same_screen = True;
		xe.xbutton.time = CurrentTime; //will this... work?
		XSendEvent(s_dpy, _win, True, 
			(downup == ButtonRelease ? ButtonReleaseMask : ButtonPressMask), &xe);
	}
	void CLinuxX11Window::Key(EKey key, EKeyState state)
	{
		XEvent xe;
		int downup = (state == EKeyState::Down ? KeyPress : KeyRelease);
		xe.type = downup;
		xe.xkey.send_event = True;
		xe.xkey.display = s_dpy;
		xe.xkey.window = _win;
		xe.xkey.root = DefaultRootWindow(s_dpy);
		xe.xkey.subwindow = _win;
		xe.xkey.keycode = static_cast<unsigned int>(key);
		xe.xkey.same_screen = True;
		xe.xkey.time = CurrentTime; //will this... work?
		XSendEvent(s_dpy, _win, True, 
			(downup == ButtonRelease ? ButtonReleaseMask : ButtonPressMask), &xe);
	}
	void CLinuxX11Window::Scroll(EMouseScrollDirection dir, u16 INSANITY_UNUSED delta)
	{
		XEvent xe;
		int scroll = (dir == EMouseScrollDirection::Up ? 4 : 5);
		xe.type = ButtonPress;
		xe.xbutton.send_event = True;
		xe.xbutton.display = s_dpy;
		xe.xbutton.window = _win;
		xe.xbutton.root = DefaultRootWindow(s_dpy);
		xe.xbutton.subwindow = _win;
		xe.xbutton.x = 0;
		xe.xbutton.y = 0;
		xe.xbutton.x_root = _rect->GetX();
		xe.xbutton.y_root = _rect->GetY();
		xe.xbutton.button = scroll;
		xe.xbutton.same_screen = True;
		xe.xbutton.time = CurrentTime; //will this... work?
		XSendEvent(s_dpy, _win, True, ButtonPressMask, &xe);
	}
	void CLinuxX11Window::Show(bool show)
	{
		//might be able to straight call the handler; no event for it that I know of
		//if(_ext) _ext->ShowHandler(show);
		//else ShowHandler(show);
		
		if(show) XMapWindow(s_dpy, _win);
		else XUnmapWindow(s_dpy, _win);
	}
	void CLinuxX11Window::Move(s16 x, s16 y)
	{
		//might also have to call the handler for this and Resize
		//if(_ext) _ext->MoveHandler(x,y);
		//else MoveHandler(x,y);
		
		XMoveWindow(s_dpy, _win, x, y);
	}
	void CLinuxX11Window::Resize(u16 width, u16 height)
	{
		//if(_ext) _ext->ResizeHandler(width, height);
		//else ResizeHandler(width, height);
		
		XResizeWindow(s_dpy, _win, width, height);
	}
	void CLinuxX11Window::Close()
	{
		//This actually has to send a ClientMessage with the delete atom attached.
		//if(_ext) _ext->CloseHandler();
		//else CloseHandler();
		
		XEvent xe;
		xe.xclient.type = ClientMessage;
		xe.xclient.send_event = True;
		xe.xclient.display = s_dpy;
		xe.xclient.window = _win;
		xe.xclient.format = 32;
		xe.xclient.data.l[0] = s_del;
		XSendEvent(s_dpy, _win, True, ClientMessage, &xe);
	}
	
	void CLinuxX11Window::MouseHandler(EMouseButton INSANITY_UNUSED button, 
		EMouseButtonState INSANITY_UNUSED state, 
		u16 INSANITY_UNUSED x, 
		u16 INSANITY_UNUSED y)
	{
	}
	void CLinuxX11Window::KeyHandler(EKey INSANITY_UNUSED key, 
		EKeyState INSANITY_UNUSED state)
	{
	}
	void CLinuxX11Window::ScrollHandler(EMouseScrollDirection INSANITY_UNUSED dir, u16 INSANITY_UNUSED delta)
	{
	}
	void CLinuxX11Window::ShowHandler(bool INSANITY_UNUSED show)
	{
	}
	void CLinuxX11Window::MoveHandler(s16 x, s16 y)
	{
		_rect->SetX(x);
		_rect->SetY(y);
	}
	void CLinuxX11Window::ResizeHandler(u16 width, u16 height)
	{
		_rect->SetWidth(width);
		_rect->SetHeight(height);
	}
	void CLinuxX11Window::CloseHandler()
	{
	}
}

#endif
