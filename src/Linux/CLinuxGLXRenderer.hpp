#ifndef INSANITY_IMPLEMENTATION_LINUX_GLX_RENDERER
#define INSANITY_IMPLEMENTATION_LINUX_GLX_RENDERER

#include <Constants.hpp>

#if defined(PLATFORM_LINUX)

#include "CLinuxX11Window.hpp"

#include <IRenderer.hpp>
#include <Default/Object.hpp>
#include <Ptr.hpp>

#include <X11/Xlib.h>
#include <GL/glx.h>

namespace Insanity
{
	class CLinuxX11Window;
	class IConfigObject;
	class IWindow;
	
	//Non-Mesa GLX; should be used for versions higher than 3.1 (Mesa 9) or 3.3 (Mesa 10), for systems with manufacturer drivers.
	class CLinuxGLXRenderer final : public IRenderer, public Default::Object
	{
		WeakPtr<IRenderer> _ext;
		WeakPtr<CLinuxX11Window> _win;
		GLXContext _ctx{};
		GLXFBConfig _fbc{};
		GLXWindow _glxwin{};
		Display * _dpy{};
		
		Ptr<TRectangle<s16,u16>> _rect;
		
		//=================================================
		//Performs initialization of simple members:
		//	_win, _fbc, _dpy
		//Returns the X11 Window being used.
		//=================================================
		Window _Init(IWindow * win);
		
		//=================================================
		//Creates the GLX context and GLXWindow, and makes
		//	the two the current rendering state.
		//Requires the X11 Window, and the major and minor
		//	OpenGL version.
		//=================================================
		void _MakeContext(Window xwin, int major, int minor);
	public:
		CLinuxGLXRenderer(IRenderer * ext, IWindow * win, IConfigObject const * cfg);
		~CLinuxGLXRenderer();
		
		//=================================================
		//Interface: IRenderer
		//=================================================
		void Render() override;
		void Present() override;
		
		void ClearColorBuffer(float color[4]) override;
		void Resize(u16 width, u16 height) override;

		TRectangle<s16,u16> const * GetRenderRect() const override;
	};
}

#endif

#endif
