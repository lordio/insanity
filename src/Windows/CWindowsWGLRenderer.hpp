#ifndef INSANITY_IMPLEMENTATION_WINDOWS_WGL_RENDERER
#define INSANITY_IMPLEMENTATION_WINDOWS_WGL_RENDERER

#include <Constants.hpp>

#if defined(PLATFORM_MSWINDOWS)

#include <IRenderer.hpp>
#include <default/Object.hpp>

#include <Windows.h>

namespace Insanity
{
	class CWindowsWin32Window;
	class IConfigObject;
	
	class CWindowsWGLRenderer final : public IRenderer, public Default::Object
	{
	private:
		IRenderer * _ext;
		CWindowsWin32Window * _win;
		HDC _dc;
		HGLRC _rc;

		IShaderProgram * _program;
		TRectangle<s16,u16> * _rect;

		u8 _major;
		u8 _minor;

		HWND _Init(IWindow * win);
		void _MakeContext(HWND hwnd, IConfigObject const * cfg);
	public:
		CWindowsWGLRenderer(IRenderer * ext, IWindow * win, IConfigObject const * cfg);
		~CWindowsWGLRenderer();
		
		//=================================================
		//Interface: IRenderer
		//=================================================
		void Render() override;
		void Present() override;

		void ClearColorBuffer(float color[4]) override;
		void Resize(u16 width, u16 height) override;

		IShaderProgram * CreateShaderProgram() override;
		bool UseShaderProgram(IShaderProgram * program) override;

		TRectangle<s16, u16> const * GetRenderRect() const override;
	};
}

#endif

#endif
