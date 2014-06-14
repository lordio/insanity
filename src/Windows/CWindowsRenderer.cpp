#define INSANITY_BUILDING_LIBRARY

#include <IRenderer.hpp>

#if defined(PLATFORM_MSWINDOWS)

#include <IConfigObject.hpp>

#include "CWindowsDirect3D9Renderer.hpp"
#include "CWindowsDirect3D11Renderer.hpp"
#include "CWindowsWGLRenderer.hpp"

namespace Insanity
{
	IRenderer * IRenderer::Create(IRenderer * ext, IWindow * win, IConfigObject const * cfg)
	{
		bool preferD3D{ cfg->GetProperty("Windows.useDirect3D", s64{}) >= 1 };
		WeakPtr<IRenderer> ret{};

		if (preferD3D)
		{
			//D3D
			s64 version{ cfg->GetProperty("Windows.D3D.version", s64{ 9 }) };
			switch (version)
			{
			case 9:
				ret = new CWindowsDirect3D9Renderer{ ext, win, cfg };
			case 11:
				ret = new CWindowsDirect3D11Renderer{ ext, win, cfg };
			}
		}
		else
		{
			//WGL
			s64 major{ cfg->GetProperty("OpenGL.version.major", s64{ 2 }) };
			s64 minor{ cfg->GetProperty("OpenGL.version.minor", s64{ 1 }) };

			switch (major)
			{
			case 3:
				ret = new CWindowsWGLRenderer{ ext, win, cfg };
				break;
			case 4:
				switch (minor)
				{
				case 3:
				case 4:
					ret = new CWindowsWGLRenderer{ ext, win, cfg };
				}
			}
		}
		return ret;
	}
}

#endif