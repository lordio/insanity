#define INSANITY_BUILDING_LIBRARY

#include <Default/Window.hpp>

namespace Insanity
{
	namespace Default
	{
		Window::Window(IConfigObject const * cfg) : Object{}, _base{ IWindow::Create(this, cfg) }
		{
			_base->Retain();
		}
		Window::~Window()
		{
			_base->Release();
		}
		
		//=================================================
		//Interface: Default::Window
		//=================================================
		IWindow * Window::GetExtended() const
		{
			return _base;
		}

		//=================================================
		//Interface: IWindow
		//=================================================
		TRectangle<s16,u16> const * Window::GetRect() const
		{
			return _base->GetRect();
		}

		//simulation and change commands should not usually be overridden; they cause events that trigger handlers.
		void Window::Mouse(EMouseButton button, EMouseButtonState state, u16 x, u16 y)
		{
			_base->Mouse(button,state,x,y);
		}
		void Window::Key(EKey key, EKeyState state)
		{
			_base->Key(key,state);
		}
		void Window::Scroll(EMouseScrollDirection dir, u16 delta)
		{
			_base->Scroll(dir,delta);
		}
		void Window::Show(bool show)
		{
			_base->Show(show);
		}
		void Window::Move(s16 x, s16 y)
		{
			_base->Move(x,y);
		}
		void Window::Resize(u16 width, u16 height)
		{
			_base->Resize(width,height);
		}
		void Window::Close()
		{
			_base->Close();
		}

		//Handlers don't do anything by default; inheritors should override.
		void Window::MouseHandler(EMouseButton ATTRIBUTE_UNUSED button, 
			EMouseButtonState ATTRIBUTE_UNUSED state,
			u16 ATTRIBUTE_UNUSED x,
			u16 ATTRIBUTE_UNUSED y)
		{
		}
		void Window::KeyHandler(EKey ATTRIBUTE_UNUSED key,
			EKeyState ATTRIBUTE_UNUSED state)
		{
		}
		void Window::ScrollHandler(EMouseScrollDirection ATTRIBUTE_UNUSED dir,
			u16 ATTRIBUTE_UNUSED delta)
		{
		}
		void Window::ShowHandler(bool ATTRIBUTE_UNUSED show)
		{
		}
		void Window::MoveHandler(s16 x, s16 y)
		{
			if(_base) _base->MoveHandler(x, y);
		}
		void Window::ResizeHandler(u16 width, u16 height)
		{
			//resize events may be sent to the window during construction, but before assignment to _base.
			if(_base) _base->ResizeHandler(width, height);
		}
		void Window::CloseHandler()
		{
		}
	}
}
