#define INSANITY_BUILDING_LIBRARY

#include "CMacOSXNSGLRenderer.hpp"

#if defined(PLATFORM_MACOSX)

#include "CMacOSXCocoaWindow.hpp"
#include "CMacOSXOpenGLShaderProgram.hpp"
#include <IWindow.hpp>
#include <IConfigObject.hpp>
#include <TRectangle.hpp>
#include <default/Window.hpp>

#import <AppKit/NSOpenGL.h>
#include <OpengL/gl3.h>

@interface _Insanity_MacOSXNSGLRenderer : NSOpenGLView
{
}

-(id)initWithConfig:(Insanity::IConfigObject const*)cfg window:(Insanity::CMacOSXCocoaWindow*)win;
@end

@implementation _Insanity_MacOSXNSGLRenderer
-(id)initWithConfig:(Insanity::IConfigObject const*)cfg window:(Insanity::CMacOSXCocoaWindow*)win
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

	NSOpenGLPixelFormat * fmt = [[[NSOpenGLPixelFormat alloc] initWithAttributes:pfa] autorelease];
	NSOpenGLContext * ctx = [[[NSOpenGLContext alloc] initWithFormat:fmt shareContext:nil] autorelease];

    //TODO: replace nil (frame) with window's content rectangle.
    Insanity::TRectangle<Insanity::s16, Insanity::u16> const * winrect = win->GetRect();
	if(![super initWithFrame:NSMakeRect(winrect->GetX(), winrect->GetY(), winrect->GetWidth(), winrect->GetHeight()) pixelFormat:fmt]) return nil;

	[self setOpenGLContext:ctx];
	[ctx makeCurrentContext];
	
	return self;
}
@end

namespace Insanity
{
    IRenderer * IRenderer::Create(IRenderer * ext, IWindow * win, IConfigObject const * cfg)
    {
    	//no special processing to do here, Macs only ever provide one OpenGL level.
    	//could split up between 3.3 and 4.1 (the two supported levels on 10.9, based on hardware)
        return new CMacOSXNSGLRenderer(ext,win,cfg);
    }
    
    CMacOSXNSGLRenderer::CMacOSXNSGLRenderer(IRenderer * ext, IWindow * win, IConfigObject const * cfg) :
        _ext(ext), _nsrend(nil), _win(nullptr), _rect(new TRectangle<s16,u16>(0,0,0,0))
    {
		_rect->Retain();

        NSWindow * nswin = _Init(win);
        
        //each version of MacOSX supports a specific version of OpenGL. No more, no less.
        //Of course, in our case, if less is asked for, we can certainly provide that (provided no removed functionality is requested...)
        _MakeContext(nswin, cfg);
    }
    CMacOSXNSGLRenderer::~CMacOSXNSGLRenderer()
    {
        [_nsrend release];

		_rect->Release();
    }
    
    NSWindow * CMacOSXNSGLRenderer::_Init(IWindow * win)
    {
        _win = win->As<CMacOSXCocoaWindow>();
        
        if(!_win)
        {
            //Try interpreting it as a Default::Window, and getting the extended window.
            Default::Window * dwin = win->As<Default::Window>();
            if(!dwin) return nil; //If it's not a Default::Window, then shrug.
            
            _win = dwin->GetExtended()->As<CMacOSXCocoaWindow>();
            if(!_win) return nil; //If that failed, we really don't know.
        }
        
		TRectangle<s16,u16> const * winrect = _win->GetRect();
		_rect->SetWidth(winrect->GetWidth());
		_rect->SetHeight(winrect->GetHeight());

        return _win->GetWindow();
    }
    void CMacOSXNSGLRenderer::_MakeContext(NSWindow * win, IConfigObject const * cfg)
    {
        _nsrend = [[_Insanity_MacOSXNSGLRenderer alloc] initWithConfig:cfg window:_win];
        [win setContentView:_nsrend];
        //is that all it takes? I know initWithConfig:window: does most of the work, but is there ANYTHING else to do from here?
    }
    
    //=====================================================
    //Interface: IRenderer
    //=====================================================
    void CMacOSXNSGLRenderer::Render()
    {
    }
    void CMacOSXNSGLRenderer::Present()
    {
    	//Mac desktop is GL-accelerated already. Calling glFlush indicates application is ready to be composited with the rest of the screen.
    	glFlush();
    }
    void CMacOSXNSGLRenderer::ClearColorBuffer(float color[4])
    {
    	//glClearBuffer should work, but test it.
    	glClearBufferfv(GL_COLOR, 0, color);
    }
    void CMacOSXNSGLRenderer::Resize(u16 width, u16 height)
    {
    	glViewport(0, 0, width, height);

		_rect->SetWidth(width);
		_rect->SetHeight(height);
    }
	IShaderProgram * CMacOSXNSGLRenderer::CreateShaderProgram()
	{
		return new CMacOSXOpenGLShaderProgram();
	}
	bool CMacOSXNSGLRenderer::UseShaderProgram(IShaderProgram * program)
	{
		if(program)
			if(!program->Link())
				return false;
		
		if(_program) _program->Release();
		_program = program;
		if(_program)
		{
			_program->Retain();
			glUseProgram(program->As<CMacOSXOpenGLShaderProgram>()->GetProgramName());
		}
		else glUseProgram(0);
		
		return true;
	}
	TRectangle<s16,u16> const * CMacOSXNSGLRenderer::GetRenderRect() const
	{
		return _rect;
	}
}

#endif
