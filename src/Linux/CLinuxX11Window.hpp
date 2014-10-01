#ifndef INSANITY_IMPLEMENTATION_LINUX_X11_WINDOW
#define INSANITY_IMPLEMENTATION_LINUX_X11_WINDOW

#include <Constants.hpp>

#if defined(PLATFORM_LINUX)

#include <IWindow.hpp>
#include <TRectangle.hpp>
#include <Default/Object.hpp>
#include <Ptr.hpp>

#include <X11/Xlib.h>
#include <GL/glx.h>

#include <string>

namespace Insanity
{
	class CLinuxX11EventPumpTask;
	class IConfigObject;

	class CLinuxX11Window final : public IWindow, public Default::Object
	{
		static Display * s_dpy;
		static Ptr<CLinuxX11EventPumpTask> s_pump;
		static u64 s_winCount;
		static u8 s_glxVersion;
		static s32 s_errorBase;
		static s32 s_eventBase;
		static GLXFBConfig s_fbc;
		static Atom s_del;

		TRectangle<s16,u16> _rect;
		WeakPtr<IWindow> _ext;
		Window _win;
		std::string _title{};
		
		static void _InitXDisplay();
		static void _InitGLX();
		XVisualInfo * _GetXVisual(int redBits, int greenBits, int blueBits, int depthBits, bool doubleBuffer = true);
		static void _InitWindowAttributes(XSetWindowAttributes * xswa, XVisualInfo const * xvi);
		void _InitXWindow(char const * title, XVisualInfo const * xvi, XSetWindowAttributes * xswa);
		void _SetPumpProc();
	public:
		CLinuxX11Window(IWindow * ext, IConfigObject const * cfg);
		~CLinuxX11Window();
		
		Window GetWindow() const;
		static Display * GetDisplay();
		static GLXFBConfig GetFBConfig();
		static u8 GetGLXVersion();

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
