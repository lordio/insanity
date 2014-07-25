#ifndef INSANITY_IMPLEMENTATION_MACOSX_COCOA_WINDOW
#define INSANITY_IMPLEMENTATION_MACOSX_COCOA_WINDOW

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

#include "CMacOSXCocoaEventPumpTask.hpp"
#include <TRectangle.hpp>
#include <IWindow.hpp>
#include <default/Object.hpp>
#include <Ptr.hpp>
#include <string>

//#import <AppKit/NSWindow.h>
@class NSWindow;
@class OMacOSXCocoaWindowDelegate;

namespace Insanity
{
	template<typename _ctype>
	class IString;

	template<typename _xytype, typename _whtype>
	class TRectangle;

	class CMacOSXCocoaEventPumpTask;

	class CMacOSXCocoaWindow final : public IWindow, public Default::Object
	{
	private:
		NSWindow * _win; //ARC pointer.
		WeakPtr<IWindow> _ext;
		Ptr<TRectangle<s16,u16>> _rect;
		OMacOSXCocoaWindowDelegate * _delegate;
		std::string _title{};

		static Ptr<CMacOSXCocoaEventPumpTask> s_pump;
		static u64 s_winCount;

		void _SetPumpProc();
	public:
        CMacOSXCocoaWindow(IWindow * ext, IConfigObject const * cfg);
		~CMacOSXCocoaWindow();
        
        NSWindow * GetWindow() const;

		//=================================================
		//Interface: IWindow
		//=================================================
		TRectangle<s16,u16> const * GetRect() const override;
		char const * GetTitle() const override;
		void SetTitle(char const * title) override;
		void Mouse(EMouseButton button, EMouseButtonState state, u16 x, u16 y) override;
		void Key(EKey key, EKeyState state) override;
		void Scroll(EMouseScrollDirection dir, u16 delta) override;
		void Show(bool show) override;
		void Move(s16 x, s16 y) override;
		void Resize(u16 width, u16 height) override;
		void Close() override;

		void MouseHandler(EMouseButton button, EMouseButtonState state, u16 x, u16 y) override;
		void KeyHandler(EKey key, EKeyState state) override;
		void ScrollHandler(EMouseScrollDirection dir, u16 delta) override;
		void ShowHandler(bool show) override;
		void MoveHandler(s16 x, s16 y) override;
		void ResizeHandler(u16 width, u16 height) override;
		void CloseHandler() override;
	};
}

#endif

#endif
