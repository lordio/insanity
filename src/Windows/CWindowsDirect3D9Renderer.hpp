#ifndef INSANITY_IMPLEMENTATION_WINDOWS_DIRECT3D9_RENDERER
#define INSANITY_IMPLEMENTATION_WINDOWS_DIRECT3D9_RENDERER

#include <Constants.hpp>

#if defined(PLATFORM_MSWINDOWS)

#include <IRenderer.hpp>
#include "CWindowsWin32Window.hpp"
#include <default/Object.hpp>
#include <TRectangle.hpp>
#include <Ptr.hpp>

#include <Windows.h>

struct IDirect3D9;
struct IDirect3DDevice9;

namespace Insanity
{
	class IWindow;

	class CWindowsDirect3D9Renderer final : public IRenderer, public Default::Object
	{
		WeakPtr<IRenderer> _ext;
		WeakPtr<CWindowsWin32Window> _win;
		Ptr<TRectangle<s16,u16>> _rect;

		IDirect3D9 * _d3d9;
		IDirect3DDevice9 * _dev;

		HWND _Init(IWindow * win);
		void _MakeContext(HWND win, IConfigObject const * cfg);
	public:
		CWindowsDirect3D9Renderer(IRenderer * ext, IWindow * win, IConfigObject const * cfg);
		~CWindowsDirect3D9Renderer();

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