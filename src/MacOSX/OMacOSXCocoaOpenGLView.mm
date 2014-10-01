#define INSANITY_BUILDING_LIBRARY

#include "OMacOSXCocoaOpenGLView.hpp"

#if defined(PLATFORM_MACOSX)

#include <TRectangle.hpp>

#include <AppKit/NSOpenGL.h>
#include <OpenGL/gl3.h>

@implementation OMacOSXCocoaOpenGLView
-(id)initWithConfig:(Insanity::IConfigObject const *)cfg window:(Insanity::CMacOSXCocoaWindow*)win
{
	//get properties from cfg, initialize ctx and fmt.
	//need some way to entirely skip unused boolean values.
	NSOpenGLPixelFormatAttribute pfa[] =
	{
		NSOpenGLPFAColorSize, static_cast<NSOpenGLPixelFormatAttribute>(cfg->GetProperty("MacOSX.NSOpenGL.color", (Insanity::s64)32)),
		NSOpenGLPFADepthSize, static_cast<NSOpenGLPixelFormatAttribute>(cfg->GetProperty("MacOSX.NSOpenGL.depth", (Insanity::s64)24)),
		NSOpenGLPFAStencilSize, static_cast<NSOpenGLPixelFormatAttribute>(cfg->GetProperty("MacOSX.NSOpenGL.stencil", (Insanity::s64)0)),
		NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
		static_cast<NSOpenGLPixelFormatAttribute>((cfg->GetProperty("MacOSX.NSOpenGL.accelerated", (Insanity::s64)1) ? NSOpenGLPFAAccelerated : 0)),
		0
	};
    
    //what I could do is provide enough spaces for all the possible Boolean values
    //  (or, at least the ones the should be configurable), and check each,
    //  setting the first empty spot to an active Boolean.
	//Or, of course, I could just use a std::vector.

	NSOpenGLPixelFormat * fmt = [[NSOpenGLPixelFormat alloc] initWithAttributes:pfa];
	NSOpenGLContext * ctx = [[NSOpenGLContext alloc] initWithFormat:fmt shareContext:nil];

    Insanity::TRectangle<Insanity::s16, Insanity::u16> const& winrect{win->GetRect()};
	if(![super initWithFrame:NSMakeRect(winrect.GetX(), winrect.GetY(), winrect.GetWidth(), winrect.GetHeight()) pixelFormat:fmt]) return nil;

	[self setOpenGLContext:ctx];
	[ctx makeCurrentContext];
	
	return self;
}
@end

#endif