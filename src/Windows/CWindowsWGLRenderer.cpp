#define INSANITY_BUILDING_LIBRARY

#include "CWindowsWGLRenderer.hpp"

#if defined(PLATFORM_MSWINDOWS)

#include "CWindowsWin32Window.hpp"

#include "../Generic/CGenericOpenGL41ShaderProgram.hpp"
#include "../Generic/CGenericGLShaderProgram.hpp"

#include "../Generic/IOpenGLShaderProgram.hpp"

#include <IConfigObject.hpp>
#include <TRectangle.hpp>

#include "../../gel/gel.hpp"
#include <gl/wglext.h>

#include <cassert>

#pragma comment(lib, "opengl32.lib")

namespace Insanity
{
	CWindowsWGLRenderer::CWindowsWGLRenderer(IRenderer * ext, IWindow * win, IConfigObject const * cfg) :
		_ext{ ext },
		_win{},
		_dc{},
		_rc{},
		_program{},
		_rect{ new TRectangle<s16, u16>(0, 0, 0, 0) },
		_major{},
		_minor{}
	{
		HWND hwnd{ _Init(win) };

		_MakeContext(hwnd, cfg);
	}
	CWindowsWGLRenderer::~CWindowsWGLRenderer()
	{
		wglMakeCurrent(NULL,NULL);

		//so that's confusing. WGL uses wglDeleteContext, whereas GLX has glXDestroyContext.
		wglDeleteContext(_rc);
	}

	HWND CWindowsWGLRenderer::_Init(IWindow * win)
	{
		_win = win->As<CWindowsWin32Window>();
		//try assuming win is a Default::Window if that fails.

		if (_win == nullptr)
		{
			WeakPtr<Default::Window> dwin{ win->As<Default::Window>() };
			assert(dwin); //making a renderer is meaningless if we can't use the provided window

			_win = dwin->GetExtended()->As<CWindowsWin32Window>();
			assert(_win);
		}

		HWND ret{ _win->GetWindow() };
		_dc = GetDC(ret);

		WeakPtr<const TRectangle<s16, u16>> winrect = _win->GetRect();
		_rect->SetWidth(winrect->GetWidth());
		_rect->SetHeight(winrect->GetHeight());

		return ret;
	}
	void CWindowsWGLRenderer::_MakeContext(HWND hwnd, IConfigObject const * cfg)
	{
		PIXELFORMATDESCRIPTOR pfd;
		ZeroMemory(&pfd, sizeof(pfd));
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL |
			PFD_GENERIC_ACCELERATED |
			(cfg->GetProperty("Windows.WGL.doubleBuffer", (s64) 0) > 0 ? PFD_DOUBLEBUFFER : 0);
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = static_cast<BYTE>(cfg->GetProperty("Windows.WGL.color", (s64) 24));
		pfd.cRedBits = static_cast<BYTE>(cfg->GetProperty("Windows.WGL.red", (s64) 8));
		pfd.cGreenBits = static_cast<BYTE>(cfg->GetProperty("Windows.WGL.green", (s64) 8));
		pfd.cBlueBits = static_cast<BYTE>(cfg->GetProperty("Windows.WGL.blue", (s64) 8));
		pfd.cAccumBits = static_cast<BYTE>(cfg->GetProperty("Windows.WGL.accum", (s64) 0));
		pfd.cAccumRedBits = static_cast<BYTE>(cfg->GetProperty("Windows.WGL.accumRed", (s64) 0));
		pfd.cAccumGreenBits = static_cast<BYTE>(cfg->GetProperty("Windows.WGL.accumGreen", (s64) 0));
		pfd.cAccumBlueBits = static_cast<BYTE>(cfg->GetProperty("Windows.WGL.accumBlue", (s64) 0));
		pfd.cAccumAlphaBits = static_cast<BYTE>(cfg->GetProperty("Windows.WGL.accumAlpha", (s64) 0));
		pfd.cDepthBits = static_cast<BYTE>(cfg->GetProperty("Windows.WGL.depth", (s64) 0));
		pfd.cStencilBits = static_cast<BYTE>(cfg->GetProperty("Windows.WGL.stencil", (s64) 0));
		//dwVisibleMask and bReserved might be made available, if I determine their use.
		SetPixelFormat(_dc, ChoosePixelFormat(_dc, &pfd), &pfd);

		HGLRC tmp{ wglCreateContext(_dc) };
		wglMakeCurrent(_dc, tmp);

		_major = static_cast<int>(cfg->GetProperty("OpenGL.version.major", (s64) 2));
		_minor = static_cast<int>(cfg->GetProperty("OpenGL.version.minor", (s64) 1));

		auto wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");
		int attribs[]
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, _major,
			WGL_CONTEXT_MINOR_VERSION_ARB, _minor,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
			0
		};
		_rc = wglCreateContextAttribsARB(_dc, NULL, attribs);
		wglMakeCurrent(_dc, _rc);
		wglDeleteContext(tmp);

		glViewport(_rect->GetX(), _rect->GetY(), _rect->GetWidth(), _rect->GetHeight());

		gel::init(_major, _minor);
	}
	
	//=====================================================
	//Interface: IRenderer
	//=====================================================
	void CWindowsWGLRenderer::Render()
	{
	}
	void CWindowsWGLRenderer::Present()
	{
		SwapBuffers(_dc);
	}

	void CWindowsWGLRenderer::ClearColorBuffer(float color[4])
	{
		//ClearBuffer was introduced in 3.0, so if contexts before that are supported, this may need to be a call to glClear
		//Alternatively, could clear all buffers in use (color, depth, stencil) with one call, also to glClear
		glClearBufferfv(GL_COLOR, 0, color);
	}
	void CWindowsWGLRenderer::Resize(u16 width, u16 height)
	{
		glViewport(0, 0, width, height);

		_rect->SetWidth(width);
		_rect->SetHeight(height);
	}

	IShaderProgram * CWindowsWGLRenderer::CreateShaderProgram()
	{
		if (_major > 4 || (_major == 4 && _minor > 1)) return new CGenericOpenGL41ShaderProgram();
		else return new CGenericGLShaderProgram();
	}
	bool CWindowsWGLRenderer::UseShaderProgram(IShaderProgram * program)
	{
		if (program)
			if (!program->Link())
				return false;

		_program = program;
		if (_program) glUseProgram(program->As<IOpenGLShaderProgram>()->GetProgramName());
		else glUseProgram(0);

		return true;
	}
	TRectangle<s16, u16> const * CWindowsWGLRenderer::GetRenderRect() const
	{
		return _rect;
	}
}

#endif
