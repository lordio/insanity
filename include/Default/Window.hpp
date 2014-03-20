#ifndef INSANITY_IMPLEMENTATION_DEFAULT_WINDOW
#define INSANITY_IMPLEMENTATION_DEFAULT_WINDOW

#include "../IWindow.hpp"
#include "Object.hpp"

namespace Insanity
{
	class IConfigObject;
	
	namespace Default
	{
		class INSANITY_API Window : public IWindow, public Object
		{
		protected:
			IWindow * _base;
		public:
			Window(IConfigObject const * cfg);
			virtual ~Window();
			
			//=============================================
			//Interface: Default::Window
			//=============================================
			IWindow * GetExtended() const;

			//=============================================
			//Interface: IWindow
			//=============================================
			virtual TRectangle<s16,u16> const * GetRect() const;
			virtual void Mouse(EMouseButton button, EMouseButtonState state, u16 x, u16 y);
			virtual void Key(EKey key, EKeyState state);
			virtual void Scroll(EMouseScrollDirection dir, u16 delta);
			virtual void Show(bool show);
			virtual void Move(s16 x, s16 y);
			virtual void Resize(u16 width, u16 height);
			virtual void Close();
			virtual void MouseHandler(EMouseButton button, EMouseButtonState state, u16 x, u16 y);
			virtual void KeyHandler(EKey key, EKeyState state);
			virtual void ScrollHandler(EMouseScrollDirection dir, u16 delta);
			virtual void ShowHandler(bool show);
			virtual void MoveHandler(s16 x, s16 y);
			virtual void ResizeHandler(u16 width, u16 height);
			virtual void CloseHandler();
		};
	}
}

#endif
