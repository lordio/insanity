#ifndef INSANITY_OBJECTIVEC_MACOSX_COCOA_OPENGL_VIEW
#define INSANITY_OBJECTIVEC_MACOSX_COCOA_OPENGL_VIEW

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

#include <IConfigObject.hpp>
#include "CMacOSXCocoaWindow.hpp"

#include <AppKit/NSOpenGLView.h>

@interface OMacOSXCocoaOpenGLView : NSOpenGLView
{
}

-(id)initWithConfig:(Insanity::IConfigObject const *)cfg window:(Insanity::CMacOSXCocoaWindow*)win;
@end

#endif

#endif