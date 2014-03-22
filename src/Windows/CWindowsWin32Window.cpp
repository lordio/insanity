#define INSANITY_BUILDING_LIBRARY

#include "CWindowsWin32Window.hpp"

#if defined(PLATFORM_MSWINDOWS)

#include <IThread.hpp>
#include <IGarbageCollector.hpp>
#include <IApplication.hpp>
#include <IString.hpp>
#include <TRectangle.hpp>
#include <IConfigObject.hpp>

#include <windowsx.h>
#include <CommCtrl.h>

#include <iostream>

namespace Insanity
{
	IWindow * IWindow::Create(IWindow * ext, IConfigObject const * cfg)
	{
		return new CWindowsWin32Window(ext, cfg);
	}

	bool CWindowsWin32Window::s_windowClassRegistered = false;
	CWindowsWin32EventPumpTask * CWindowsWin32Window::s_pumpTask = nullptr;
	u64 CWindowsWin32Window::s_winCount = 0;

	u64 CWindowsWin32Window::GetWindowCount()
	{
		return s_winCount;
	}

	CWindowsWin32Window::CWindowsWin32Window(IWindow * ext, IConfigObject const * cfg) :
		_ext(ext), _rect(nullptr)
	{
		HMODULE hInst = GetModuleHandle(nullptr);

		_InitWindowClass(hInst);
		_InitEventPump();

		_InitWindow(hInst, cfg);

		s_winCount++;
	}
	CWindowsWin32Window::~CWindowsWin32Window()
	{
		if(--s_winCount == 0)
		{
			s_pumpTask->Release(); //The windows don't need it anymore.
			//the pump task will not be deleted until it's dequeued from the thread task list.
		}
		
		//A comment on SetWindowSubclass says to remove the subclass before destroying the window.
		RemoveWindowSubclass(_win,WindowProc,0);
		DestroyWindow(_win);
		_rect->Release();
	}

	void CWindowsWin32Window::_InitWindowClass(HINSTANCE hInst)
	{
		if (!s_windowClassRegistered)
		{
			WNDCLASSEXW wcex;
			ZeroMemory(&wcex, sizeof(wcex));
			wcex.cbClsExtra = 0;						//Won't be able to access
			wcex.cbSize = sizeof(wcex);					//Constant
			wcex.cbWndExtra = 0;						//Won't be able to access
			wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW);//More or less constant.
			wcex.hCursor = (HCURSOR) LoadImage(hInst, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED); //Can be assigned later
			wcex.hIcon = (HICON) LoadImage(hInst, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_SHARED); //Can be assigned later
			wcex.hIconSm = (HICON) LoadImage(hInst, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_SHARED); //Can be assigned later
			wcex.hInstance = hInst;						//Constant
			wcex.lpfnWndProc = InitialWindowProc;		//Will assign WindowProc after window creation
			wcex.lpszClassName = L"InsanityWindowClass";//Constant
			wcex.lpszMenuName = nullptr;				//Can be assigned if/when a Menu is added.
			wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; //First two needed, third needed for uniformity with other platforms.

			RegisterClassExW(&wcex);

			s_windowClassRegistered = true;
		}
	}
	void CWindowsWin32Window::_InitWindow(HINSTANCE hInst, IConfigObject const * cfg)
	{
		//_rect stores the dimensions of the client area of the window.
		_rect = new TRectangle<s16, u16>(static_cast<s16>(cfg->GetProperty("dims.x", (s64)0)),
			static_cast<s16>(cfg->GetProperty("dims.y", (s64)0)),
			static_cast<u16>(cfg->GetProperty("dims.width", (s64)640)),
			static_cast<u16>(cfg->GetProperty("dims.height", (s64)480)));
		_rect->Retain();
		
		//Need to adjust for non-client area of window for CreateWindow.
		RECT adj;
		adj.left = _rect->GetLeft();
		adj.top = _rect->GetTop();
		adj.right = _rect->GetRight();
		adj.bottom = _rect->GetBottom();
		AdjustWindowRectEx(&adj, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);
		
		//convert the title to a wchar_t string. Let the garbage collector take care of it.
		IString<wchar_t> * wtitle = IString<wchar_t>::Create(cfg->GetProperty("title", ""));

		_win = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW,	//will either want this or options for fullscreen
			L"InsanityWindowClass",						//Constant
			wtitle->Array(),							//Good candidate for Config file
			WS_OVERLAPPEDWINDOW,						//as dwExStyle
			adj.left, adj.top,
			adj.right - adj.left, adj.bottom - adj.top,	//Dimensions are another good candidate
			HWND_DESKTOP,								//If in Config file, would need a way to specify another window
			NULL,										//Menu can be assigned later
			hInst,										//Constant
			nullptr);									//Constant (unused)

		SetWindowSubclass(_win, WindowProc, 0, reinterpret_cast<DWORD_PTR>(this));

		ShowWindow(_win, SW_SHOWDEFAULT);
	}
	void CWindowsWin32Window::_InitEventPump()
	{
		if (s_pumpTask == nullptr)
		{
			//creates a pump task, assigns it to the static pointer, and passes it to RegisterTask.
			IApplication::GetInstance()->RegisterTask(s_pumpTask = new CWindowsWin32EventPumpTask());
		}
		
		//Other platforms have to register an event procedure with the event pump task.
		//	Since that's basically an emulation of Windows' event setup, we use the native setup here.
	}
	
	LRESULT CALLBACK CWindowsWin32Window::InitialWindowProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		//this will receive at least WM_NCCREATE, WM_NCCALCSIZE, and WM_CREATE before assigning WindowProc subclass.
		return DefWindowProcW(wnd,msg,wParam,lParam);
	}
	LRESULT CALLBACK CWindowsWin32Window::WindowProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uSubclassId, DWORD_PTR dwRefData)
	{
		//this is the main method for processing window messages.
		CWindowsWin32Window * self = reinterpret_cast<CWindowsWin32Window*>(dwRefData);
		self->Retain();

		IWindow * call = (self->_ext ? self->_ext : self);

		POINTS pt = MAKEPOINTS(lParam);
		WORD highWParam = HIWORD(wParam);

		switch(msg)
		{
		case WM_LBUTTONDOWN:
			call->MouseHandler(EMouseButton::Left, EMouseButtonState::Down, pt.x, pt.y);
			break;
		case WM_LBUTTONUP:
			call->MouseHandler(EMouseButton::Left, EMouseButtonState::Up, pt.x, pt.y);
			break;
		case WM_LBUTTONDBLCLK:
			call->MouseHandler(EMouseButton::Left, EMouseButtonState::DoubleClick, pt.x, pt.y);
			break;
		case WM_RBUTTONDOWN:
			call->MouseHandler(EMouseButton::Right, EMouseButtonState::Down, pt.x, pt.y);
			break;
		case WM_RBUTTONUP:
			call->MouseHandler(EMouseButton::Right, EMouseButtonState::Up, pt.x, pt.y);
			break;
		case WM_RBUTTONDBLCLK:
			call->MouseHandler(EMouseButton::Right, EMouseButtonState::DoubleClick, pt.x, pt.y);
			break;
		case WM_MBUTTONDOWN:
			call->MouseHandler(EMouseButton::Middle, EMouseButtonState::Down, pt.x, pt.y);
			break;
		case WM_MBUTTONUP:
			call->MouseHandler(EMouseButton::Middle, EMouseButtonState::Up, pt.x, pt.y);
			break;
		case WM_MBUTTONDBLCLK:
			call->MouseHandler(EMouseButton::Middle, EMouseButtonState::DoubleClick, pt.x, pt.y);
			break;
		case WM_XBUTTONDOWN:
			call->MouseHandler((highWParam == 1 ? EMouseButton::X1 : EMouseButton::X2), EMouseButtonState::Down, pt.x, pt.y);
			break;
		case WM_XBUTTONUP:
			call->MouseHandler((highWParam == 1 ? EMouseButton::X1 : EMouseButton::X2), EMouseButtonState::Up, pt.x, pt.y);
			break;
		case WM_XBUTTONDBLCLK:
			call->MouseHandler((highWParam == 1 ? EMouseButton::X1 : EMouseButton::X2), EMouseButtonState::DoubleClick, pt.x, pt.y);
			break;
		case WM_KEYUP:
			call->KeyHandler((EKey) wParam, EKeyState::Up);
			break;
		case WM_KEYDOWN:
			call->KeyHandler((EKey) wParam, EKeyState::Down);
			break;
		case WM_CLOSE:
			std::cout << "Close message received." << std::endl;
			call->CloseHandler();
			break;
		case WM_SHOWWINDOW:
			call->ShowHandler(wParam == TRUE);
			break;
		case WM_DESTROY:
			//should only be sent when the window object is destroyed.
			//should do any code on window destruction in the dtor, not here or a handler.
			break;
		case WM_MOVE:
			//coordinates reported are the upper-left corner of the client area in screen coordinates.
			call->MoveHandler(pt.x, pt.y);
			break;
		case WM_SIZE:
			call->ResizeHandler(pt.x, pt.y);
			break;
		case WM_MOUSEMOVE:
			call->MouseHandler(EMouseButton::Null, EMouseButtonState::Null, pt.x, pt.y);
			break;
		case WM_MOUSEWHEEL:
			{
				//need the sign from highWParam
				SHORT delta = (SHORT)highWParam;
				
				//the second parameter to ScrollHandler is a simple magnitude (unsigned), so take the absolute value.
				call->ScrollHandler((delta > 0 ? EMouseScrollDirection::Up : EMouseScrollDirection::Down), abs(delta / WHEEL_DELTA));
			}
			break;
		}

		self->Release();
		return DefSubclassProc(wnd,msg,wParam,lParam);
	}
	
	HWND CWindowsWin32Window::GetWindow() const
	{
		return _win;
	}

	//=====================================================
	//Interface: IWindow
	//=====================================================
	TRectangle<s16,u16> const * CWindowsWin32Window::GetRect() const
	{
		return _rect;
	}
	void CWindowsWin32Window::MouseHandler(EMouseButton button, EMouseButtonState state, u16 x, u16 y)
	{
	}
	void CWindowsWin32Window::KeyHandler(EKey key, EKeyState state)
	{
	}
	void CWindowsWin32Window::ScrollHandler(EMouseScrollDirection dir, u16 delta)
	{
	}
	void CWindowsWin32Window::ShowHandler(bool show)
	{
	}
	void CWindowsWin32Window::MoveHandler(s16 x, s16 y)
	{
		_rect->SetX(x);
		_rect->SetY(y);
	}
	void CWindowsWin32Window::ResizeHandler(u16 width, u16 height)
	{
		_rect->SetWidth(width);
		_rect->SetHeight(height);
	}
	void CWindowsWin32Window::CloseHandler()
	{
	}
	void CWindowsWin32Window::Mouse(EMouseButton button, EMouseButtonState state, u16 x, u16 y)
	{
		UINT msg = 0;
		WORD xButton = 0;
		switch (button)
		{
		case EMouseButton::Left:
			msg = WM_LBUTTONDOWN;
			break;
		case EMouseButton::Middle:
			msg = WM_MBUTTONDOWN;
			break;
		case EMouseButton::Right:
			msg = WM_RBUTTONDOWN;
			break;
		case EMouseButton::X1:
			xButton = 1;
			msg = WM_XBUTTONDOWN;
			break;
		case EMouseButton::X2:
			xButton = 2;
			msg = WM_XBUTTONDOWN;
			break;
		case EMouseButton::Null:
			msg = WM_MOUSEMOVE;
			break;
		}

		if (button != EMouseButton::Null) //ignore the state; should be Null, but don't count on it.
		{
			switch (state)
			{
			case EMouseButtonState::Down:
				//no-op, Down is already set.
				break;
			case EMouseButtonState::Up:
				msg += 1;
				break;
			case EMouseButtonState::DoubleClick:
				msg += 2;
				break;
			}
		}
		DWORD tmpX = x;
		DWORD tmpY = y;
		LPARAM lParam = (tmpY << 16) | tmpX;
		PostMessage(_win, msg, xButton << 16, lParam);
	}
	void CWindowsWin32Window::Key(EKey key, EKeyState state)
	{
		//LPARAM is a bunch of state flags we have no way of tracking, so ignore it.
		PostMessage(_win, (state == EKeyState::Down ? WM_KEYDOWN : WM_KEYUP), (WPARAM)key, 0);
	}
	void CWindowsWin32Window::Scroll(EMouseScrollDirection dir, u16 delta)
	{
		//mask off the sign bit (shouldn't cause problems)
		SHORT postDelta = delta & 0x7fff;
		postDelta *= (dir == EMouseScrollDirection::Up ? 1 : -1);
		
		//Last parameter should be the current mouse position, but that's not provided nor tracked internally.
		PostMessage(_win, WM_MOUSEWHEEL, (static_cast<DWORD>(postDelta)) << 16, 0);
	}
	void CWindowsWin32Window::Show(bool show)
	{
		ShowWindow(_win, (show ? SW_SHOWNORMAL : SW_HIDE));
	}
	void CWindowsWin32Window::Move(s16 x, s16 y)
	{
		MoveWindow(_win,x,y,0,0,TRUE);
	}
	void CWindowsWin32Window::Resize(u16 width, u16 height)
	{
		MoveWindow(_win,0,0,width,height,TRUE);
	}
	void CWindowsWin32Window::Close()
	{
		PostMessage(_win, WM_CLOSE, 0, 0);
	}
}

#endif
