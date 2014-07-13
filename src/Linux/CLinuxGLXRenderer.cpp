#define INSANITY_BUILDING_LIBRARY

#include "CLinuxGLXRenderer.hpp"

#if defined(PLATFORM_LINUX)

#include <IWindow.hpp>
#include <IConfigObject.hpp>
#include "CLinuxX11Window.hpp"
#include <Default/Window.hpp>

#include "../../gel/gel.hpp"
#include <GL/glxext.h>

#include <iostream>
#include <cassert>

namespace Insanity
{
	CLinuxGLXRenderer::CLinuxGLXRenderer(IRenderer * ext, IWindow * win, IConfigObject const * cfg) :
		_ext{ext},
		_win{},
		_rect{new TRectangle<s16,u16>{0,0,0,0}}
	{
		Window xwin{_Init(win)};

		int major{static_cast<int>(cfg->GetProperty("OpenGL.version.major", s64{2}))};
		int minor{static_cast<int>(cfg->GetProperty("OpenGL.version.minor", s64{1}))};
		
		_MakeContext(xwin, major, minor);
		
		gel::init(major,minor);
	}
	CLinuxGLXRenderer::~CLinuxGLXRenderer()
	{
		//force-unset the context.
		glXMakeContextCurrent(_dpy, None, None, NULL);
		
		glXDestroyWindow(_dpy, _glxwin);
		glXDestroyContext(_dpy, _ctx);
	}
	
	Window CLinuxGLXRenderer::_Init(IWindow * win)
	{
		_win = win->As<CLinuxX11Window>();
		if(_win == nullptr)
		{
			//win may be a Default::Window. Try casting to that, and getting the extended object.
			WeakPtr<Default::Window> dwin{win->As<Default::Window>()};
			assert(dwin); //No idea, then.
			
			_win = dwin->GetExtended()->As<CLinuxX11Window>();
			assert(_win); //Again, no idea.
		}
		
		_dpy = CLinuxX11Window::GetDisplay();
		_fbc = CLinuxX11Window::GetFBConfig();

		WeakPtr<const TRectangle<s16,u16>> winrect{_win->GetRect()};
		_rect->SetWidth(winrect->GetWidth());
		_rect->SetHeight(winrect->GetHeight());

		return _win->GetWindow();
	}
	void CLinuxGLXRenderer::_MakeContext(Window xwin, int major, int minor)
	{
		//Check the GLX version, and switch based on that.
		u8 version{CLinuxX11Window::GetGLXVersion()};
		
		//if the GLX version is at least 1.3, use the newer context creation interface.
		//Otherwise, assume older GLX interface.
		//version is packed; high nybble is major version, low nybble is minor version.
		if(((version & 0xf0) == 0x10) && ((version & 0x0f) >= 3))
		{
			auto glXCreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC)glXGetProcAddress((GLubyte*)"glXCreateContextAttribsARB");

			//Documentation of glXGetProcAddress says it returns nullptr if the function does not exist.
			//	Experimentation supports this.
			if(glXCreateContextAttribsARB)
			{
				int glxcca_attribs[]
				{
					GLX_CONTEXT_MAJOR_VERSION_ARB, major,
					GLX_CONTEXT_MINOR_VERSION_ARB, minor,
					GLX_RENDER_TYPE, GLX_RGBA_TYPE,
					GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
					GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
					None
				};
				_ctx = glXCreateContextAttribsARB(_dpy, _fbc, NULL, True, glxcca_attribs);
			}
			else _ctx = glXCreateNewContext(_dpy, _fbc, GLX_RGBA_TYPE, NULL, True);
		
			//no attributes defined for glXCreateWindow's attrib_list.
			_glxwin = glXCreateWindow(_dpy, _fbc, xwin, nullptr);
		
			glXMakeContextCurrent(_dpy, _glxwin, _glxwin, _ctx);
		}
		else
		{
			//have to use GLX 1.2 interface. Shouldn't be necessary.
		}

		glViewport(_rect->GetX(), _rect->GetY(), _rect->GetWidth(), _rect->GetHeight());
	}
	
	//=====================================================
	//Interface: IRenderer
	//=====================================================
	void CLinuxGLXRenderer::Render()
	{
	}
	void CLinuxGLXRenderer::Present()
	{
		glXSwapBuffers(_dpy, _glxwin);
	}
	
	void CLinuxGLXRenderer::ClearColorBuffer(float color[4])
	{
		glClearBufferfv(GL_COLOR, 0, color);
	}
	void CLinuxGLXRenderer::Resize(u16 width, u16 height)
	{
		glViewport(0,0,width,height);

		_rect->SetWidth(width);
		_rect->SetHeight(height);
	}
	TRectangle<s16,u16> const * CLinuxGLXRenderer::GetRenderRect() const
	{
		return _rect;
	}
}

#endif
