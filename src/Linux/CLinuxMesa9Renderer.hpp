#ifndef INSANITY_IMPLEMENTATION_LINUX_MESA9_RENDERER
#define INSANITY_IMPLEMENTATION_LINUX_MESA9_RENDERER

#include <Constants.hpp>

#if defined(PLATFORM_LINUX)

#include "CLinuxX11Window.hpp"
#include <IRenderer.hpp>
#include "../Generic/CGenericObject.hpp"
#include <Ptr.hpp>

#include <X11/Xlib.h>
#include <GL/glx.h>

namespace Insanity
{
	class CLinuxX11Window;
	class IConfigObject;
	
	//Mesa 9.2.1 (default on Ubuntu 13.10) implements OpenGL 3.1, but with quirks.
	//	By design, Mesa uses GLX
	class CLinuxMesa9Renderer final : public IRenderer, public CGenericObject
	{
		WeakPtr<IRenderer> _ext;
		WeakPtr<CLinuxX11Window> _win;
		
		GLXContext _ctx{};
		GLXFBConfig _fbc{};
		GLXWindow _glxwin{};
		Display * _dpy{};
		
		TRectangle<s16,u16> _rect;
		
		//Initializes _win, _fbc, and _dpy
		//	Returns None if [win] is neither a CLinuxX11Window, nor a Default::Window extending a CLinuxX11Window.
		Window _Init(IWindow * win);
		
		//Initializes _ctx and _glxwin, and makes them the current OpenGL rendering state.
		//	[major] and [minor] provided in case a lower functionality than 3.1 is desired.
		void _MakeContext(Window xwin, int major, int minor);
	public:
		CLinuxMesa9Renderer(IRenderer * ext, IWindow * win, IConfigObject const * cfg);
		~CLinuxMesa9Renderer();
		
		//=================================================
		//Interface: IRenderer
		//=================================================
		void Render() override;
		void Present() override;
		
		void ClearColorBuffer(float color[4]) override;
		void Resize(u16 width, u16 height) override;
		
		TRectangle<s16,u16> const & GetRenderRect() const override;
	};
}

#endif

#endif
