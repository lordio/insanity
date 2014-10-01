#define INSANITY_BUILDING_LIBRARY

#include "CWindowsDirect3D11Renderer.hpp"

#if defined(PLATFORM_MSWINDOWS)

#include "../src/Windows/CWindowsWin32Window.hpp"

#include <IWindow.hpp>
#include <TRectangle.hpp>
#include <d3d11.h>

#include <cassert>

#pragma comment(lib, "d3d11.lib")

namespace Insanity
{
	//IRenderer Create methods should be moved to their own .cpp, that uses a configobject property to determine whether to use
	//	OpenGL, or D3D (and in the latter case, which version)
	CWindowsDirect3D11Renderer::CWindowsDirect3D11Renderer(IRenderer * ext, IWindow * win, IConfigObject const * cfg) :
		_rect{ 0, 0, 0, 0 }, _ext{ ext }, _win{}
	{
		HWND wnd{ _Init(win) };

		_MakeContext(wnd,cfg);
	}
	CWindowsDirect3D11Renderer::~CWindowsDirect3D11Renderer()
	{
		_depth->Release();
		_view->Release();
		_swap->Release();
		_dev->Release();
		_ctx->Release();
	}

	HWND CWindowsDirect3D11Renderer::_Init(IWindow * win)
	{
		_win = win->As<CWindowsWin32Window>();
		if (!_win)
		{
			//try the window as a Default::Window
			WeakPtr<Default::Window> dwin{ win->As<Default::Window>() };
			assert(dwin); //can't do anything meaningful without dwin.

			_win = dwin->GetExtended()->As<CWindowsWin32Window>();
			assert(_win); //that didn't work, either. Too bad.
		}

		TRectangle<s16, u16> const & winrect = _win->GetRect();
		_rect.SetHeight(winrect.GetHeight());
		_rect.SetWidth(winrect.GetWidth());

		return _win->GetWindow();
	}
	void CWindowsDirect3D11Renderer::_MakeContext(HWND wnd, IConfigObject const * cfg)
	{
		D3D_FEATURE_LEVEL features = D3D_FEATURE_LEVEL_11_0;
		DXGI_SWAP_CHAIN_DESC dscd;
		dscd.BufferDesc.Width = _rect.GetWidth();
		dscd.BufferDesc.Height = _rect.GetHeight();
		dscd.BufferDesc.RefreshRate.Numerator = 60; //configurable?
		dscd.BufferDesc.RefreshRate.Denominator = 1;
		dscd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //configurable?
		dscd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //configurable?
		dscd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; //configurable?
		dscd.SampleDesc.Count = 0; //configurable
		dscd.SampleDesc.Quality = 0; //configurable
		dscd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		dscd.BufferCount = 2; //configurable, docs say front buffer included.
		dscd.OutputWindow = wnd;
		dscd.Windowed = TRUE; //can change later with IDXGISwapChain::SetFullscreenState, or can detect from [c?]win.
		dscd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //configurable?
		dscd.Flags = 0; //configurable?

		D3D11CreateDeviceAndSwapChain(nullptr,	//default adapter
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
#if defined(CONFIGURE_DEBUG)
			D3D11_CREATE_DEVICE_DEBUG |
#endif
			0,	//Creation flags, allow configuration to specify D3D11_CREATE_DEVICE_SINGLETHREADED, BGRA_SUPPORT?
			&features,	//feature levels; if left as nullptr, treats as { 11, 10.1, 10, 9.3, 9.2, 9.1 }
			1,	//feature level count
			D3D11_SDK_VERSION,
			&dscd, //DXGI_SWAP_CHAIN_DESC
			&_swap, //IDXGISwapChain**
			&_dev, //ID3D11Device**
			&features, //D3D_FEATURE_LEVEL*, needed? Not marked "opt" in docs.
			&_ctx); //ID3D11DeviceContext**

		ID3D11Texture2D * backBuffer{};
		_swap->GetBuffer(0, __uuidof(ID3D11RenderTargetView), (void**) &backBuffer);

		_dev->CreateRenderTargetView(backBuffer, nullptr, &_view);
		backBuffer->Release();

		D3D11_TEXTURE2D_DESC dtd;
		dtd.Width = _rect.GetWidth();
		dtd.Height = _rect.GetHeight();
		dtd.MipLevels = 1;
		dtd.ArraySize = 1;
		dtd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dtd.SampleDesc.Count = 1;
		dtd.SampleDesc.Quality = 0;
		dtd.Usage = D3D11_USAGE_DEFAULT;
		dtd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		dtd.CPUAccessFlags = 0;
		dtd.MiscFlags = 0;

		_dev->CreateTexture2D(&dtd, nullptr, &_depth);

		D3D11_DEPTH_STENCIL_DESC ddsd;
		ddsd.DepthEnable = TRUE;
		ddsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		ddsd.DepthFunc = D3D11_COMPARISON_LESS;
		ddsd.StencilEnable = TRUE;
		ddsd.StencilReadMask = 0xFF;
		ddsd.StencilWriteMask = 0xFF;
		ddsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		ddsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		ddsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		ddsd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		ddsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		ddsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		ddsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		ddsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		_dev->CreateDepthStencilState(&ddsd, &_stencil);
		_ctx->OMSetDepthStencilState(_stencil, 1);

		D3D11_DEPTH_STENCIL_VIEW_DESC ddsvd;
		ZeroMemory(&ddsvd, sizeof(ddsvd));
		ddsvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		ddsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		ddsvd.Texture2D.MipSlice = 0;
		_dev->CreateDepthStencilView(_depth, &ddsvd, &_stencilView);

		_ctx->OMSetRenderTargets(1, &_view, _stencilView);

		D3D11_RASTERIZER_DESC drd;
		drd.AntialiasedLineEnable = FALSE;
		drd.CullMode = D3D11_CULL_BACK;
		drd.DepthBias = 0;
		drd.DepthBiasClamp = 0.0f;
		drd.DepthClipEnable = TRUE;
		drd.FillMode = D3D11_FILL_SOLID;
		drd.FrontCounterClockwise = FALSE;
		drd.MultisampleEnable = FALSE;
		drd.ScissorEnable = FALSE;
		drd.SlopeScaledDepthBias = 0.0f;
		_dev->CreateRasterizerState(&drd, &_raster);

		_ctx->RSSetState(_raster);

		D3D11_VIEWPORT viewport;
		viewport.Width = (float) _rect.GetWidth();
		viewport.Height = (float) _rect.GetHeight();
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		_ctx->RSSetViewports(1, &viewport);
	}

	//=====================================================
	//Interface: IRenderer
	//=====================================================
	void CWindowsDirect3D11Renderer::Render()
	{
	}
	void CWindowsDirect3D11Renderer::Present()
	{
		_swap->Present(0,0); //swapinterval, flags
	}

	void CWindowsDirect3D11Renderer::ClearColorBuffer(float color[4])
	{
		_ctx->ClearRenderTargetView(_view,color);
	}
	void CWindowsDirect3D11Renderer::Resize(u16 width, u16 height)
	{
		DXGI_MODE_DESC dmd;
		dmd.Width = width;
		dmd.Height = height;
		dmd.RefreshRate.Numerator = 60;
		dmd.RefreshRate.Denominator = 1;
		dmd.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		dmd.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		dmd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		_swap->ResizeTarget(&dmd);
	}
	TRectangle<s16, u16> const & CWindowsDirect3D11Renderer::GetRenderRect() const
	{
		return _rect;
	}
}

#endif