#define INSANITY_BUILDING_LIBRARY

#include "CWindowsDirect3D9Renderer.hpp"

#if defined(PLATFORM_MSWINDOWS)

#include <IWindow.hpp>
#include <default/Window.hpp>

#include "../src/Windows/CWindowsWin32Window.hpp"

#include <TRectangle.hpp>

#include <d3d9.h>

#include <cassert>

#pragma comment(lib, "d3d9.lib")

namespace Insanity
{
	CWindowsDirect3D9Renderer::CWindowsDirect3D9Renderer(IRenderer * ext, IWindow * win, IConfigObject const * cfg) :
		CGenericObject{},
		_ext{ ext },
		_win{},
		_rect{0, 0, 0, 0},
		_d3d9{},
		_dev{}
	{
		HWND hwnd{ _Init(win) };
		_MakeContext(hwnd, cfg);
	}
	CWindowsDirect3D9Renderer::~CWindowsDirect3D9Renderer()
	{
		_dev->Release();
		_d3d9->Release();
	}

	HWND CWindowsDirect3D9Renderer::_Init(IWindow * win)
	{
		_win = win->As<CWindowsWin32Window>();
		if (_win == nullptr)
		{
			WeakPtr<Default::Window> dwin{ win->As<Default::Window>() };
			assert(dwin);

			_win = dwin->GetExtended()->As<CWindowsWin32Window>();
			assert(_win);
		}

		TRectangle<s16, u16> const & winrect = _win->GetRect();
		_rect.SetWidth(winrect.GetWidth());
		_rect.SetHeight(winrect.GetHeight());

		return _win->GetWindow();
	}
	void CWindowsDirect3D9Renderer::_MakeContext(HWND hwnd, IConfigObject const * cfg)
	{
		_d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.BackBufferCount = 1;
		d3dpp.hDeviceWindow = hwnd;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.Windowed = TRUE;

		_d3d9->CreateDevice(NULL, D3DDEVTYPE_HAL, hwnd, 0, &d3dpp, &_dev);
	}

	//=====================================================
	//Interface: IRenderer
	//=====================================================
	void CWindowsDirect3D9Renderer::Render()
	{
		_dev->BeginScene();
	}
	void CWindowsDirect3D9Renderer::Present()
	{
		_dev->EndScene();
		_dev->Present(nullptr, nullptr, NULL, nullptr);
	}
	void CWindowsDirect3D9Renderer::ClearColorBuffer(float color[4])
	{
		_dev->Clear(0, nullptr, 0, D3DCOLOR_RGBA((int) (color[0] * 255), (int) (color[1] * 255), (int) (color[2] * 255), (int) (color[3] * 255)), 1.0f, 0);
	}
	void CWindowsDirect3D9Renderer::Resize(u16 width, u16 height)
	{
		D3DVIEWPORT9 vp;
		_dev->GetViewport(&vp);
		vp.Width = width;
		vp.Height = height;
		_dev->SetViewport(&vp);

		_rect.SetWidth(width);
		_rect.SetHeight(height);
	}
	TRectangle<s16, u16> const & CWindowsDirect3D9Renderer::GetRenderRect() const
	{
		return _rect;
	}
}

#endif