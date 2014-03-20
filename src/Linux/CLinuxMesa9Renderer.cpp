#define INSANITY_BUILDING_LIBRARY

#include "CLinuxMesa9Renderer.hpp"

#if defined(PLATFORM_LINUX)

#include "../src/Linux/CLinuxX11Window.hpp"
#include "../src/Generic/CGenericGLShaderProgram.hpp"
#include <default/Window.hpp>
#include <IConfigObject.hpp>
#include <TRectangle.hpp>

#include "../gel/gel.hpp"

#include <iostream>

namespace Insanity
{
	CLinuxMesa9Renderer::CLinuxMesa9Renderer(IRenderer * ext, IWindow * win, IConfigObject const * cfg) :
		_ext(ext), _win(nullptr), _program(nullptr), _rect(new TRectangle<s16,u16>(0,0,0,0))
	{
		_rect->Retain();
		
		Window xwin = _Init(win);
		
		int major = (int)cfg->GetProperty("OpenGL.version.major", (s64)3);
		int minor = (int)cfg->GetProperty("OpenGL.version.minor", (s64)1);
		
		_MakeContext(xwin,major,minor);
		
		gel::init(major, minor);
		
		std::cout << "Using Linux Mesa 9 Renderer (OpenGL version " << major << "." << minor << ")." << std::endl;
	}
	CLinuxMesa9Renderer::~CLinuxMesa9Renderer()
	{
		glXMakeContextCurrent(_dpy, None, None, NULL);
		
		glXDestroyWindow(_dpy, _glxwin);
		glXDestroyContext(_dpy, _ctx);
		
		_rect->Release();
	}
	
	Window CLinuxMesa9Renderer::_Init(IWindow * win)
	{
		_win = win->As<CLinuxX11Window>();
		if(!_win)
		{
			Default::Window * dwin = win->As<Default::Window>();
			if(!dwin) return None;
			
			_win = dwin->GetExtended()->As<CLinuxX11Window>();
			if(!_win) return None; //need a window to render to.
		}
		
		_dpy = CLinuxX11Window::GetDisplay();
		_fbc = CLinuxX11Window::GetFBConfig();
		
		TRectangle<s16,u16> const * winrect = _win->GetRect();
		_rect->SetWidth(winrect->GetWidth());
		_rect->SetHeight(winrect->GetHeight());
		
		return _win->GetWindow();
	}
	void CLinuxMesa9Renderer::_MakeContext(Window xwin, int major, int minor)
	{
		u8 glxver = CLinuxX11Window::GetGLXVersion();
		
		//if glX version is at least 1.3
		if(((glxver & 0xf0) == 0x10) && ((glxver & 0x0f) >= 3))
		{
			auto glXCreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC)glXGetProcAddress((GLubyte*)"glXCreateContextAttribsARB");
			
			if(glXCreateContextAttribsARB)
			{
				int glxcca_attribs[] =
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
			
			//no attributes defined for glXCreateWindow's attrib parameter
			_glxwin = glXCreateWindow(_dpy, _fbc, xwin, nullptr);
			glXMakeContextCurrent(_dpy, _glxwin, _glxwin, _ctx);
		}
		else
		{
			//glX 1.2 and earlier interface. Write only when necessary.
		}
	}
	
	//=====================================================
	//Interface: IRenderer
	//=====================================================
	void CLinuxMesa9Renderer::Render()
	{
	}
	void CLinuxMesa9Renderer::Present()
	{
		glXSwapBuffers(_dpy, _glxwin);
	}
	
	void CLinuxMesa9Renderer::ClearColorBuffer(float color[4])
	{
		glClearColor(color[0], color[1], color[2], color[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void CLinuxMesa9Renderer::Resize(u16 width, u16 height)
	{
		glViewport(0, 0, width, height);
	
		_rect->SetWidth(width);
		_rect->SetHeight(height);
	}
	
	IShaderProgram * CLinuxMesa9Renderer::CreateShaderProgram()
	{
		return new CGenericGLShaderProgram();
	}
	bool CLinuxMesa9Renderer::UseShaderProgram(IShaderProgram * program)
	{
		if(program)
			if(!program->Link())
				return false;
				
		if(_program) _program->Release();
		_program = program;
		if(_program)
		{
			_program->Retain();
			
			glUseProgram(program->As<CGenericGLShaderProgram>()->GetProgramName());
		}
		else glUseProgram(0);
		
		return true;
	}
	TRectangle<s16,u16> const * CLinuxMesa9Renderer::GetRenderRect() const
	{
		return _rect;
	}
}

#endif
