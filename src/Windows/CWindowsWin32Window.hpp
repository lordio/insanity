#ifndef INSANITY_IMPLEMENTATION_WINDOWS_WIN32_WINDOW
#define INSANITY_IMPLEMENTATION_WINDOWS_WIN32_WINDOW

#include <Constants.hpp>

#if defined(PLATFORM_MSWINDOWS)

#include <IWindow.hpp>
#include <TRectangle.hpp>
#include <Windows.h>

#include "CWindowsWin32EventPumpTask.hpp"

#include "../Generic/CGenericObject.hpp"
#include <Ptr.hpp>

#include <string>

namespace Insanity
{
	template<typename _xytype, typename _whtype>
	class TRectangle;

	class IConfigObject;

	class CWindowsWin32Window final : public IWindow, public CGenericObject
	{
	private:
		TRectangle<s16,u16> _rect;
		WeakPtr<IWindow> _ext;
		HWND _win;
		std::string _title;

		static bool s_windowClassRegistered;
		static Ptr<CWindowsWin32EventPumpTask> s_pumpTask;
		static u64 s_winCount;

		//for any messages before WindowProc can be assigned
		static LRESULT CALLBACK InitialWindowProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK WindowProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uSubclassId, DWORD_PTR dwRefData);

		static void _InitWindowClass(HINSTANCE hInst);
		static void _InitEventPump();
		void _InitWindow(HINSTANCE hInst, IConfigObject const * cfg);
	public:
		CWindowsWin32Window(IWindow * ext, IConfigObject const * cfg);
		~CWindowsWin32Window();

		static u64 GetWindowCount();
		HWND GetWindow() const;

		//=================================================
		//Interface: IWindow
		//=================================================
		TRectangle<s16,u16> const & GetRect() const override;
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
