#ifndef INSANITY_IMPLEMENTATION_WINDOWS_DIRECT3D11_RENDERER
#define INSANITY_IMPLEMENTATION_WINDOWS_DIRECT3D11_RENDERER

#include <Constants.hpp>

#if defined(PLATFORM_MSWINDOWS)

#include "CWindowsWin32Window.hpp"

#include <IRenderer.hpp>
#include <Default/Object.hpp>
#include <TRectangle.hpp>
#include <Ptr.hpp>

#include <Windows.h>

struct ID3D11DepthStencilState;
struct ID3D11DepthStencilView;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RasterizerState;
struct ID3D11RenderTargetView;
struct ID3D11Texture2D;
struct IDXGISwapChain;

namespace Insanity
{
	class IConfigObject;
	class IWindow;
	class CWindowsWin32Window;

	class CWindowsDirect3D11Renderer final : public IRenderer, public Default::Object
	{
		Ptr<TRectangle<s16,u16>> _rect;
		WeakPtr<IRenderer> _ext;
		WeakPtr<CWindowsWin32Window> _win;

		ID3D11Device * _dev;
		ID3D11DeviceContext * _ctx;
		IDXGISwapChain * _swap;
		ID3D11RenderTargetView * _view;
		ID3D11Texture2D * _depth;
		ID3D11DepthStencilState * _stencil;
		ID3D11DepthStencilView * _stencilView;
		ID3D11RasterizerState * _raster;

		HWND _Init(IWindow * win);
		void _MakeContext(HWND wnd, IConfigObject const * cfg);
	public:
		CWindowsDirect3D11Renderer(IRenderer * ext, IWindow * win, IConfigObject const * cfg);
		~CWindowsDirect3D11Renderer();

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