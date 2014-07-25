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
			virtual TRectangle<s16, u16> const * GetRect() const override;
			virtual char const * GetTitle() const override;
			virtual void SetTitle(char const * title) override;
			virtual void Mouse(EMouseButton button, EMouseButtonState state, u16 x, u16 y) override;
			virtual void Key(EKey key, EKeyState state) override;
			virtual void Scroll(EMouseScrollDirection dir, u16 delta) override;
			virtual void Show(bool show) override;
			virtual void Move(s16 x, s16 y) override;
			virtual void Resize(u16 width, u16 height) override;
			virtual void Close() override;
			virtual void MouseHandler(EMouseButton button, EMouseButtonState state, u16 x, u16 y) override;
			virtual void KeyHandler(EKey key, EKeyState state) override;
			virtual void ScrollHandler(EMouseScrollDirection dir, u16 delta) override;
			virtual void ShowHandler(bool show) override;
			virtual void MoveHandler(s16 x, s16 y) override;
			virtual void ResizeHandler(u16 width, u16 height) override;
			virtual void CloseHandler() override;
		};
	}
}

#endif
