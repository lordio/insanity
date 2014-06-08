#ifndef INSANITY_IMPLEMENTATION_MACOSX_NSGL_RENDERER
#define INSANITY_IMPLEMENTATION_MACOSX_NSGL_RENDERER

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

#include "CMacOSXCocoaWindow.hpp"
#include <TRectangle.hpp>
#include <IRenderer.hpp>
#include <default/Object.hpp>
#include <Ptr.hpp>

@class NSWindow;
@class OMacOSXCocoaOpenGLView;

namespace Insanity
{
    class CMacOSXCocoaWindow;
    class IWindow;
    class IConfigObject;
    
    class CMacOSXNSGLRenderer final : public IRenderer, public Default::Object
    {
        WeakPtr<IRenderer> _ext;
        OMacOSXCocoaOpenGLView * _nsrend; //ObjC object pointer; managed by ARC
        WeakPtr<CMacOSXCocoaWindow> _win;
        
        Ptr<IShaderProgram> _program;
		Ptr<TRectangle<s16,u16>> _rect;
        
        NSWindow * _Init(IWindow * win);
        void _MakeContext(NSWindow * win, IConfigObject const * cfg);
    public:
        CMacOSXNSGLRenderer(IRenderer * ext, IWindow * win, IConfigObject const * cfg);
        ~CMacOSXNSGLRenderer();
        
        void Render() override;
        void Present() override;
        
        void ClearColorBuffer(float color[4]) override;
        void Resize(u16 width, u16 height) override;
        
        IShaderProgram * CreateShaderProgram() override;
        bool UseShaderProgram(IShaderProgram * program) override;

		TRectangle<s16,u16> const * GetRenderRect() const override;
    };
}

#endif

#endif
