#ifndef INSANITY_INTERFACE_WINDOW
#define INSANITY_INTERFACE_WINDOW

#include "Constants.hpp"
#include "IObject.hpp"
#include "EKeyMap.hpp"

namespace Insanity
{
	template<typename _xytype, typename _whtype>
	class TRectangle;
	
	class IConfigObject;

	enum class EMouseButton
	{
		Null,
		Left,
		Middle,
		Right,
		X1,
		X2
	};
	enum class EMouseButtonState
	{
		Null, //reports mouse movement
		Down,
		Up,
		DoubleClick
	};
	enum class EKeyState
	{
		Down,
		Up
	};
	enum class EMouseScrollDirection
	{
		Down,
		Up
	};

	class INSANITY_API IWindow : public virtual IObject
	{
		//=================================================
		//Window ConfigObject parameters:
		//	dims
		//		x					[Integer]
		//		y					[Integer]
		//		width				[Integer]
		//		height				[Integer]
		//	title					[String]
		//	fullscreen				[Integer]
		//	constrain				[Integer]
		//	Linux
		//		X11
		//			border			[Integer]
		//		GLX
		//			red				[Integer]
		//			green			[Integer]
		//			blue			[Integer]
		//			depth			[Integer]
		//			doubleBuffer	[Integer]
		//=================================================
	public:
		//=================================================
		//Create a window with configuration specified by
		//	[cfg], extended by [ext].
		//=================================================
		static IWindow * Create(IWindow * ext, IConfigObject const * cfg);
		
		//=================================================
		//Get the window's current content rectangle.
		//=================================================
		virtual TRectangle<s16,u16> const * GetRect() const = 0;

		//=================================================
		//Set/get the string shown in the window's title bar.
		//=================================================
		virtual void SetTitle(char const * title) = 0;
		virtual char const * GetTitle() const = 0;

		//=================================================
		//Input simulation methods
		//=================================================
		
		//=================================================
		//Simulate [button] taking [state] at pixel
		//	coordinate ([x], [y]).
		//For button == EMouseButton::Null and state ==
		//	EMouseButtonState::Null, move the mouse cursor
		//	to (x,y)
		//=================================================
		virtual void Mouse(EMouseButton button, EMouseButtonState state, u16 x, u16 y) = 0;
		
		//=================================================
		//Simulate [key] taking [state].
		//=================================================
		virtual void Key(EKey key, EKeyState state) = 0;
		
		//=================================================
		//Simulate the mouse scroll wheel moving [delta]
		//	clicks in direction [dir].
		//=================================================
		virtual void Scroll(EMouseScrollDirection dir, u16 delta) = 0;

		//=================================================
		//Window appearance manipulation methods
		//=================================================
		
		//=================================================
		//Request the window show ([show] == true) or hide
		//	([show] == false) itself.
		//=================================================
		virtual void Show(bool show) = 0;
		
		//=================================================
		//Request the window move to pixel coordinate
		//	([x], [y]).
		//=================================================
		virtual void Move(s16 x, s16 y) = 0;
		
		//=================================================
		//Request the window take on pixel dimensions
		//	[width] and [height].
		//=================================================
		virtual void Resize(u16 width, u16 height) = 0;
		
		//=================================================
		//Request the window close, which should both hide
		//	it and call its CloseHandler.
		//=================================================
		virtual void Close() = 0;

		//=================================================
		//Event callbacks
		//	Not intended to be called directly;
		//	application-side implementations should use
		//	these to handle events received.
		//=================================================
		
		//=================================================
		//Reports [button] changed to [state] at pixel
		//	coordinate ([x],[y]).
		//If button and state are Null, reports mouse movement.
		//=================================================
		virtual void MouseHandler(EMouseButton button, EMouseButtonState state, u16 x, u16 y) = 0;
		
		//=================================================
		//Reports [key] changed to [state].
		//=================================================
		virtual void KeyHandler(EKey key, EKeyState state) = 0;
		
		//=================================================
		//Reports the mouse wheel scrolled [delta] clicks
		//	in direction [dir].
		//=================================================
		virtual void ScrollHandler(EMouseScrollDirection dir, u16 delta) = 0;
		
		//=================================================
		//Reports a request that the window either show 
		//	([show] == true), or hide ([show] == false) itself.
		//=================================================
		virtual void ShowHandler(bool show) = 0;
		
		//=================================================
		//Reports that the window has been moved to pixel
		//	coordinate ([x], [y]).
		//=================================================
		virtual void MoveHandler(s16 x, s16 y) = 0;
		
		//=================================================
		//Reports that the window client area has been
		//	resized to pixel dimensions [width] and [height].
		//=================================================
		virtual void ResizeHandler(u16 width, u16 height) = 0;
		
		//=================================================
		//Reports that the window has been closed, either
		//	by the Close() method, or a non-client 'X' button.
		//=================================================
		virtual void CloseHandler() = 0;
	};
}

#endif
