#define INSANITY_BUILDING_LIBRARY

#include <Constants.hpp>

#if defined(PLATFORM_LINUX)

#include <IRenderer.hpp>
#include <IConfigObject.hpp>

#include "../../experimental/CLinuxMesa9Renderer.hpp"

namespace Insanity
{
	//not interacted with, just passed along to ctors.
	class IWindow;
	
	IRenderer * IRenderer::Create(IRenderer * ext, IWindow * win, IConfigObject * cfg)
	{
		s64 major{cfg->GetProperty("OpenGL.version.major", s64{2})};
		s64 minor{cfg->GetProperty("OpenGL.version.minor", s64{1})};
		
		if(major == 3)
		{
			switch(minor)
			{
			case 0:
			case 1:
				return new CLinuxMesa9Renderer{ext,win,cfg}; //Mesa9 Renderer accounts for quirks of the Mesa GL implementation.
				//Mesa supposedly is at 3.1 now, but glClearBufferfv (a 3.0 method, interestingly) isn't supported correctly.
			case 2:
			case 3:
				//return new CLinuxMesa10Renderer();
			default:
				break;
			}
		}
		else if(major == 4) {} //Mesa does not yet support this, so must be using a manufacturer driver.
		//return new CLinuxOpenGL4*Renderer();
		
		return nullptr;
	}
}

#endif
