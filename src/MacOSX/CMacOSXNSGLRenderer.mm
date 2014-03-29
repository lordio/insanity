#define INSANITY_BUILDING_LIBRARY

#include "CMacOSXNSGLRenderer.hpp"

#if defined(PLATFORM_MACOSX)

#include "CMacOSXCocoaWindow.hpp"
#include "CMacOSXOpenGLShaderProgram.hpp"
#incldue "OMacOSXCocoaOpenGLView.hpp"
#include <IWindow.hpp>
#include <IConfigObject.hpp>
#include <TRectangle.hpp>
#include <default/Window.hpp>

#import <AppKit/NSOpenGL.h>
#import <AppKit/NSOpenGLView.h>
#include <OpenGL/gl3.h>

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
		[_nsrend setOpenGLContext:nil];
		[NSOpenGLContext clearCurrentContext];
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
        _nsrend = [[OMacOSXCocoaOpenGLView alloc] initWithConfig:cfg window:_win];
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
