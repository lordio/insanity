#ifndef INSANITY_INTERFACE_RENDERER
#define INSANITY_INTERFACE_RENDERER

#include "Constants.hpp"

#include "IObject.hpp"

namespace Insanity
{
	class IWindow;
	class IConfigObject;

	template<typename _xytype, typename _whtype>
	class TRectangle;
	
	class INSANITY_API IRenderer : public virtual IObject
	{
		//Note: could probably make color a pseudo-object,
		//	containing size, red, green, blue. Same for accum
		//	(plus alpha in that case).
		//Might be worthwhile to specify ConfigObject parameters
		//	relative to the implementation, since most properties
		//	are implementation-specific.
		
		//=================================================
		//Renderer ConfigObject parameters:
		//	OpenGL
		//		version
		//			major			[Integer]
		//			minor			[Integer]
		//	Windows
		//		useDirect3D			[Integer]	(0)
		//		D3D
		//			version			[Integer]	(9)
		//		WGL
		//			color			[Integer]
		//			red				[Integer]
		//			green			[Integer]
		//			blue			[Integer]
		//			depth			[Integer]
		//			doubleBuffer	[Integer]
		//			accum			[Integer]
		//			accumRed		[Integer]
		//			accumGreen		[Integer]
		//			accumBlue		[Integer]
		//			accumAlpha		[Integer]
		//			stencil			[Integer]
		//	Linux
		//		useMesa				[Integer]	(1)
		//		Mesa
		//			version			[Integer]	(9)
		//=================================================
	public:
		//=================================================
		//Create a new renderer on [win], extended by [ext].
		//	Use [cfg] for configuration.
		//=================================================
		static IRenderer * Create(IRenderer * ext, IWindow * win, IConfigObject const * cfg);
	
		//=================================================
		//Perform all draw requests.
		//	To be completely compliant, a client-side renderer
		//	must call the base object's Render method first
		//	in its own implementation.
		//=================================================
		virtual void Render() = 0;
		
		//=================================================
		//If the renderer is double-buffered, copies the
		//	back buffer to the front.
		//=================================================
		virtual void Present() = 0;

		//=================================================
		//Clears the color buffer to the specified color.
		//	[color] should contain RGBA color values in the
		//	range [0.0, 1.0]. Colors outside this range
		//	cause implementation-defined behavior.
		//=================================================
		virtual void ClearColorBuffer(float color[4]) = 0;
		
		//=================================================
		//Resize the rendering viewport.
		//	Params should be the pixel size of the drawing
		//	surface.
		//=================================================
		virtual void Resize(u16 width, u16 height) = 0;

		//=================================================
		//Returns a TRectangle<s16,u16> representing the
		//	current viewport.
		//	Dimensions should be specified in window
		//	coordinates.
		//=================================================
		virtual TRectangle<s16, u16> const * GetRenderRect() const = 0;
	};
}

#endif
