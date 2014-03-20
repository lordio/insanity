//#if 0

#define GEL_BUILDING_LIBRARY

#include "gel.hpp"

#if defined(GEL_MSWINDOWS)
//included for wglGetProcAddress
#undef WINGDIAPI
#include <windef.h>
#include <wingdi.h>
#elif defined(GEL_MACOSX)
#include <dlfcn.h>
#endif

namespace gel
{
	static unsigned int major;
	static unsigned int minor;
}

#if defined(GEL_MSWINDOWS)
#pragma region Function Pointers
#endif

#if defined(GL_VERSION_1_2) && defined(GEL_MSWINDOWS)
static PFNGLBLENDCOLORPROC _glBlendColor = nullptr;
static PFNGLBLENDEQUATIONPROC _glBlendEquation = nullptr;
static PFNGLDRAWRANGEELEMENTSPROC _glDrawRangeElements = nullptr;
static PFNGLTEXIMAGE3DPROC _glTexImage3D = nullptr;
static PFNGLTEXSUBIMAGE3DPROC _glTexSubImage3D = nullptr;
static PFNGLCOPYTEXSUBIMAGE3DPROC _glCopyTexSubImage3D = nullptr;
#endif //GL_VERSION_1_2 && GEL_MSWINDOWS

#if defined(GL_VERSION_1_3) && defined(GEL_MSWINDOWS)
static PFNGLACTIVETEXTUREPROC _glActiveTexture = nullptr;
static PFNGLSAMPLECOVERAGEPROC _glSampleCoverage = nullptr;
static PFNGLCOMPRESSEDTEXIMAGE3DPROC _glCompressedTexImage3D = nullptr;
static PFNGLCOMPRESSEDTEXIMAGE2DPROC _glCompressedTexImage2D = nullptr;
static PFNGLCOMPRESSEDTEXIMAGE1DPROC _glCompressedTexImage1D = nullptr;
static PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC _glCompressedTexSubImage3D = nullptr;
static PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC _glCompressedTexSubImage2D = nullptr;
static PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC _glCompressedTexSubImage1D = nullptr;
static PFNGLGETCOMPRESSEDTEXIMAGEPROC _glGetCompressedTexImage = nullptr;
#endif //GL_VERSION_1_3 && GEL_MSWINDOWS

#if defined(GL_VERSION_1_4)
static PFNGLBLENDFUNCSEPARATEPROC _glBlendFuncSeparate = nullptr;
static PFNGLMULTIDRAWARRAYSPROC _glMultiDrawArrays = nullptr;
static PFNGLMULTIDRAWELEMENTSPROC _glMultiDrawElements = nullptr;
static PFNGLPOINTPARAMETERFPROC _glPointParameterf = nullptr;
static PFNGLPOINTPARAMETERFVPROC _glPointParameterfv = nullptr;
static PFNGLPOINTPARAMETERIPROC _glPointParameteri = nullptr;
static PFNGLPOINTPARAMETERIVPROC _glPointParameteriv = nullptr;
#endif //GL_VERSION_1_4

#if defined(GL_VERSION_1_5)
static PFNGLGENQUERIESPROC _glGenQueries = nullptr;
static PFNGLDELETEQUERIESPROC _glDeleteQueries = nullptr;
static PFNGLISQUERYPROC _glIsQuery = nullptr;
static PFNGLBEGINQUERYPROC _glBeginQuery = nullptr;
static PFNGLENDQUERYPROC _glEndQuery = nullptr;
static PFNGLGETQUERYIVPROC _glGetQueryiv = nullptr;
static PFNGLGETQUERYOBJECTIVPROC _glGetQueryObjectiv = nullptr;
static PFNGLGETQUERYOBJECTUIVPROC _glGetQueryObjectuiv = nullptr;
static PFNGLBINDBUFFERPROC _glBindBuffer = nullptr;
static PFNGLDELETEBUFFERSPROC _glDeleteBuffers = nullptr;
static PFNGLGENBUFFERSPROC _glGenBuffers = nullptr;
static PFNGLISBUFFERPROC _glIsBuffer = nullptr;
static PFNGLBUFFERDATAPROC _glBufferData = nullptr;
static PFNGLBUFFERSUBDATAPROC _glBufferSubData = nullptr;
static PFNGLGETBUFFERSUBDATAPROC _glGetBufferSubData = nullptr;
static PFNGLMAPBUFFERPROC _glMapBuffer = nullptr;
static PFNGLUNMAPBUFFERPROC _glUnmapBuffer = nullptr;
static PFNGLGETBUFFERPARAMETERIVPROC _glGetBufferParameteriv = nullptr;
static PFNGLGETBUFFERPOINTERVPROC _glGetBufferPointerv = nullptr;
#endif //GL_VERSION_1_5

#if defined(GL_VERSION_2_0)
static PFNGLBLENDEQUATIONSEPARATEPROC _glBlendEquationSeparate = nullptr;
static PFNGLDRAWBUFFERSPROC _glDrawBuffers = nullptr;
static PFNGLSTENCILOPSEPARATEPROC _glStencilOpSeparate = nullptr;
static PFNGLSTENCILFUNCSEPARATEPROC _glStencilFuncSeparate = nullptr;
static PFNGLSTENCILMASKSEPARATEPROC _glStencilMaskSeparate = nullptr;
static PFNGLATTACHSHADERPROC _glAttachShader = nullptr;
static PFNGLBINDATTRIBLOCATIONPROC _glBindAttribLocation = nullptr;
static PFNGLCOMPILESHADERPROC _glCompileShader = nullptr;
static PFNGLCREATEPROGRAMPROC _glCreateProgram = nullptr;
static PFNGLCREATESHADERPROC _glCreateShader = nullptr;
static PFNGLDELETEPROGRAMPROC _glDeleteProgram = nullptr;
static PFNGLDELETESHADERPROC _glDeleteShader = nullptr;
static PFNGLDETACHSHADERPROC _glDetachShader = nullptr;
static PFNGLDISABLEVERTEXATTRIBARRAYPROC _glDisableVertexAttribArray = nullptr;
static PFNGLENABLEVERTEXATTRIBARRAYPROC _glEnableVertexAttribArray = nullptr;
static PFNGLGETACTIVEATTRIBPROC _glGetActiveAttrib = nullptr;
static PFNGLGETACTIVEUNIFORMPROC _glGetActiveUniform = nullptr;
static PFNGLGETATTACHEDSHADERSPROC _glGetAttachedShaders = nullptr;
static PFNGLGETATTRIBLOCATIONPROC _glGetAttribLocation = nullptr;
static PFNGLGETPROGRAMIVPROC _glGetProgramiv = nullptr;
static PFNGLGETPROGRAMINFOLOGPROC _glGetProgramInfoLog = nullptr;
static PFNGLGETSHADERIVPROC _glGetShaderiv = nullptr;
static PFNGLGETSHADERINFOLOGPROC _glGetShaderInfoLog = nullptr;
static PFNGLGETSHADERSOURCEPROC _glGetShaderSource = nullptr;
static PFNGLGETUNIFORMLOCATIONPROC _glGetUniformLocation = nullptr;
static PFNGLGETUNIFORMFVPROC _glGetUniformfv = nullptr;
static PFNGLGETUNIFORMIVPROC _glGetUniformiv = nullptr;
static PFNGLGETVERTEXATTRIBDVPROC _glGetVertexAttribdv = nullptr;
static PFNGLGETVERTEXATTRIBFVPROC _glGetVertexAttribfv = nullptr;
static PFNGLGETVERTEXATTRIBIVPROC _glGetVertexAttribiv = nullptr;
static PFNGLGETVERTEXATTRIBPOINTERVPROC _glGetVertexAttribPointerv = nullptr;
static PFNGLISPROGRAMPROC _glIsProgram = nullptr;
static PFNGLISSHADERPROC _glIsShader = nullptr;
static PFNGLLINKPROGRAMPROC _glLinkProgram = nullptr;
static PFNGLSHADERSOURCEPROC _glShaderSource = nullptr;
static PFNGLUSEPROGRAMPROC _glUseProgram = nullptr;
static PFNGLUNIFORM1FPROC _glUniform1f = nullptr;
static PFNGLUNIFORM2FPROC _glUniform2f = nullptr;
static PFNGLUNIFORM3FPROC _glUniform3f = nullptr;
static PFNGLUNIFORM4FPROC _glUniform4f = nullptr;
static PFNGLUNIFORM1IPROC _glUniform1i = nullptr;
static PFNGLUNIFORM2IPROC _glUniform2i = nullptr;
static PFNGLUNIFORM3IPROC _glUniform3i = nullptr;
static PFNGLUNIFORM4IPROC _glUniform4i = nullptr;
static PFNGLUNIFORM1FVPROC _glUniform1fv = nullptr;
static PFNGLUNIFORM2FVPROC _glUniform2fv = nullptr;
static PFNGLUNIFORM3FVPROC _glUniform3fv = nullptr;
static PFNGLUNIFORM4FVPROC _glUniform4fv = nullptr;
static PFNGLUNIFORM1IVPROC _glUniform1iv = nullptr;
static PFNGLUNIFORM2IVPROC _glUniform2iv = nullptr;
static PFNGLUNIFORM3IVPROC _glUniform3iv = nullptr;
static PFNGLUNIFORM4IVPROC _glUniform4iv = nullptr;
static PFNGLUNIFORMMATRIX2FVPROC _glUniformMatrix2fv = nullptr;
static PFNGLUNIFORMMATRIX3FVPROC _glUniformMatrix3fv = nullptr;
static PFNGLUNIFORMMATRIX4FVPROC _glUniformMatrix4fv = nullptr;
static PFNGLVALIDATEPROGRAMPROC _glValidateProgram = nullptr;
static PFNGLVERTEXATTRIB1DPROC _glVertexAttrib1d = nullptr;
static PFNGLVERTEXATTRIB1DVPROC _glVertexAttrib1dv = nullptr;
static PFNGLVERTEXATTRIB1FPROC _glVertexAttrib1f = nullptr;
static PFNGLVERTEXATTRIB1FVPROC _glVertexAttrib1fv = nullptr;
static PFNGLVERTEXATTRIB1SPROC _glVertexAttrib1s = nullptr;
static PFNGLVERTEXATTRIB1SVPROC _glVertexAttrib1sv = nullptr;
static PFNGLVERTEXATTRIB2DPROC _glVertexAttrib2d = nullptr;
static PFNGLVERTEXATTRIB2DVPROC _glVertexAttrib2dv = nullptr;
static PFNGLVERTEXATTRIB2FPROC _glVertexAttrib2f = nullptr;
static PFNGLVERTEXATTRIB2FVPROC _glVertexAttrib2fv = nullptr;
static PFNGLVERTEXATTRIB2SPROC _glVertexAttrib2s = nullptr;
static PFNGLVERTEXATTRIB2SVPROC _glVertexAttrib2sv = nullptr;
static PFNGLVERTEXATTRIB3DPROC _glVertexAttrib3d = nullptr;
static PFNGLVERTEXATTRIB3DVPROC _glVertexAttrib3dv = nullptr;
static PFNGLVERTEXATTRIB3FPROC _glVertexAttrib3f = nullptr;
static PFNGLVERTEXATTRIB3FVPROC _glVertexAttrib3fv = nullptr;
static PFNGLVERTEXATTRIB3SPROC _glVertexAttrib3s = nullptr;
static PFNGLVERTEXATTRIB3SVPROC _glVertexAttrib3sv = nullptr;
static PFNGLVERTEXATTRIB4NBVPROC _glVertexAttrib4Nbv = nullptr;
static PFNGLVERTEXATTRIB4NIVPROC _glVertexAttrib4Niv = nullptr;
static PFNGLVERTEXATTRIB4NSVPROC _glVertexAttrib4Nsv = nullptr;
static PFNGLVERTEXATTRIB4NUBPROC _glVertexAttrib4Nub = nullptr;
static PFNGLVERTEXATTRIB4NUBVPROC _glVertexAttrib4Nubv = nullptr;
static PFNGLVERTEXATTRIB4NUIVPROC _glVertexAttrib4Nuiv = nullptr;
static PFNGLVERTEXATTRIB4NUSVPROC _glVertexAttrib4Nusv = nullptr;
static PFNGLVERTEXATTRIB4BVPROC _glVertexAttrib4bv = nullptr;
static PFNGLVERTEXATTRIB4DPROC _glVertexAttrib4d = nullptr;
static PFNGLVERTEXATTRIB4DVPROC _glVertexAttrib4dv = nullptr;
static PFNGLVERTEXATTRIB4FPROC _glVertexAttrib4f = nullptr;
static PFNGLVERTEXATTRIB4FVPROC _glVertexAttrib4fv = nullptr;
static PFNGLVERTEXATTRIB4IVPROC _glVertexAttrib4iv = nullptr;
static PFNGLVERTEXATTRIB4SPROC _glVertexAttrib4s = nullptr;
static PFNGLVERTEXATTRIB4SVPROC _glVertexAttrib4sv = nullptr;
static PFNGLVERTEXATTRIB4UBVPROC _glVertexAttrib4ubv = nullptr;
static PFNGLVERTEXATTRIB4UIVPROC _glVertexAttrib4uiv = nullptr;
static PFNGLVERTEXATTRIB4USVPROC _glVertexAttrib4usv = nullptr;
static PFNGLVERTEXATTRIBPOINTERPROC _glVertexAttribPointer = nullptr;
#endif //GL_VERSION_2_0

#if defined(GL_VERSION_2_1)
static PFNGLUNIFORMMATRIX2X3FVPROC _glUniformMatrix2x3fv = nullptr;
static PFNGLUNIFORMMATRIX3X2FVPROC _glUniformMatrix3x2fv = nullptr;
static PFNGLUNIFORMMATRIX2X4FVPROC _glUniformMatrix2x4fv = nullptr;
static PFNGLUNIFORMMATRIX4X2FVPROC _glUniformMatrix4x2fv = nullptr;
static PFNGLUNIFORMMATRIX3X4FVPROC _glUniformMatrix3x4fv = nullptr;
static PFNGLUNIFORMMATRIX4X3FVPROC _glUniformMatrix4x3fv = nullptr;
#endif //GL_VERSION_2_1

#if defined(GL_VERSION_3_0)
//reused functions from ARB_framebuffer_object
static PFNGLISRENDERBUFFERPROC _glIsRenderbuffer = nullptr;
static PFNGLBINDRENDERBUFFERPROC _glBindRenderbuffer = nullptr;
static PFNGLDELETERENDERBUFFERSPROC _glDeleteRenderbuffers = nullptr;
static PFNGLGENRENDERBUFFERSPROC _glGenRenderbuffers = nullptr;
static PFNGLRENDERBUFFERSTORAGEPROC _glRenderbufferStorage = nullptr;
static PFNGLGETRENDERBUFFERPARAMETERIVPROC _glGetRenderbufferParameteriv = nullptr;
static PFNGLISFRAMEBUFFERPROC _glIsFramebuffer = nullptr;
static PFNGLBINDFRAMEBUFFERPROC _glBindFramebuffer = nullptr;
static PFNGLDELETEFRAMEBUFFERSPROC _glDeleteFramebuffers = nullptr;
static PFNGLGENFRAMEBUFFERSPROC _glGenFramebuffers = nullptr;
static PFNGLCHECKFRAMEBUFFERSTATUSPROC _glCheckFramebufferStatus = nullptr;
static PFNGLFRAMEBUFFERTEXTURE1DPROC _glFramebufferTexture1D = nullptr;
static PFNGLFRAMEBUFFERTEXTURE2DPROC _glFramebufferTexture2D = nullptr;
static PFNGLFRAMEBUFFERTEXTURE3DPROC _glFramebufferTexture3D = nullptr;
static PFNGLFRAMEBUFFERRENDERBUFFERPROC _glFramebufferRenderbuffer = nullptr;
static PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC _glGetFramebufferAttachmentParameteriv = nullptr;
static PFNGLGENERATEMIPMAPPROC _glGenerateMipmap = nullptr;
static PFNGLBLITFRAMEBUFFERPROC _glBlitFramebuffer = nullptr;
static PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC _glRenderbufferStorageMultisample = nullptr;
static PFNGLFRAMEBUFFERTEXTURELAYERPROC _glFramebufferTextureLayer = nullptr;

//reused functions from ARB_map_buffer_range
static PFNGLMAPBUFFERRANGEPROC _glMapBufferRange = nullptr;
static PFNGLFLUSHMAPPEDBUFFERRANGEPROC _glFlushMappedBufferRange = nullptr;

//reused functions from ARB_vertex_array_object
static PFNGLBINDVERTEXARRAYPROC _glBindVertexArray = nullptr;
static PFNGLDELETEVERTEXARRAYSPROC _glDeleteVertexArrays = nullptr;
static PFNGLGENVERTEXARRAYSPROC _glGenVertexArrays = nullptr;
static PFNGLISVERTEXARRAYPROC _glIsVertexArray = nullptr;

//functions introduced in OpenGL 3.0
static PFNGLCOLORMASKIPROC _glColorMaski = nullptr;
static PFNGLGETBOOLEANI_VPROC _glGetBooleani_v = nullptr;
static PFNGLGETINTEGERI_VPROC _glGetIntegeri_v = nullptr;
static PFNGLENABLEIPROC _glEnablei = nullptr;
static PFNGLDISABLEIPROC _glDisablei = nullptr;
static PFNGLISENABLEDIPROC _glIsEnabledi = nullptr;
static PFNGLBEGINTRANSFORMFEEDBACKPROC _glBeginTransformFeedback = nullptr;
static PFNGLENDTRANSFORMFEEDBACKPROC _glEndTransformFeedback = nullptr;
static PFNGLBINDBUFFERRANGEPROC _glBindBufferRange = nullptr;
static PFNGLBINDBUFFERBASEPROC _glBindBufferBase = nullptr;
static PFNGLTRANSFORMFEEDBACKVARYINGSPROC _glTransformFeedbackVaryings = nullptr;
static PFNGLGETTRANSFORMFEEDBACKVARYINGPROC _glGetTransformFeedbackVarying = nullptr;
static PFNGLCLAMPCOLORPROC _glClampColor = nullptr;
static PFNGLBEGINCONDITIONALRENDERPROC _glBeginConditionalRender = nullptr;
static PFNGLENDCONDITIONALRENDERPROC _glEndConditionalRender = nullptr;
static PFNGLVERTEXATTRIBIPOINTERPROC _glVertexAttribIPointer = nullptr;
static PFNGLGETVERTEXATTRIBIIVPROC _glGetVertexAttribIiv = nullptr;
static PFNGLGETVERTEXATTRIBIUIVPROC _glGetVertexAttribIuiv = nullptr;
static PFNGLVERTEXATTRIBI1IPROC _glVertexAttribI1i = nullptr;
static PFNGLVERTEXATTRIBI2IPROC _glVertexAttribI2i = nullptr;
static PFNGLVERTEXATTRIBI3IPROC _glVertexAttribI3i = nullptr;
static PFNGLVERTEXATTRIBI4IPROC _glVertexAttribI4i = nullptr;
static PFNGLVERTEXATTRIBI1UIPROC _glVertexAttribI1ui = nullptr;
static PFNGLVERTEXATTRIBI2UIPROC _glVertexAttribI2ui = nullptr;
static PFNGLVERTEXATTRIBI3UIPROC _glVertexAttribI3ui = nullptr;
static PFNGLVERTEXATTRIBI4UIPROC _glVertexAttribI4ui = nullptr;
static PFNGLVERTEXATTRIBI1IVPROC _glVertexAttribI1iv = nullptr;
static PFNGLVERTEXATTRIBI2IVPROC _glVertexAttribI2iv = nullptr;
static PFNGLVERTEXATTRIBI3IVPROC _glVertexAttribI3iv = nullptr;
static PFNGLVERTEXATTRIBI4IVPROC _glVertexAttribI4iv = nullptr;
static PFNGLVERTEXATTRIBI1UIVPROC _glVertexAttribI1uiv = nullptr;
static PFNGLVERTEXATTRIBI2UIVPROC _glVertexAttribI2uiv = nullptr;
static PFNGLVERTEXATTRIBI3UIVPROC _glVertexAttribI3uiv = nullptr;
static PFNGLVERTEXATTRIBI4UIVPROC _glVertexAttribI4uiv = nullptr;
static PFNGLVERTEXATTRIBI4BVPROC _glVertexAttribI4bv = nullptr;
static PFNGLVERTEXATTRIBI4SVPROC _glVertexAttribI4sv = nullptr;
static PFNGLVERTEXATTRIBI4UBVPROC _glVertexAttribI4ubv = nullptr;
static PFNGLVERTEXATTRIBI4USVPROC _glVertexAttribI4usv = nullptr;
static PFNGLGETUNIFORMUIVPROC _glGetUniformuiv = nullptr;
static PFNGLBINDFRAGDATALOCATIONPROC _glBindFragDataLocation = nullptr;
static PFNGLGETFRAGDATALOCATIONPROC _glGetFragDataLocation = nullptr;
static PFNGLUNIFORM1UIPROC _glUniform1ui = nullptr;
static PFNGLUNIFORM2UIPROC _glUniform2ui = nullptr;
static PFNGLUNIFORM3UIPROC _glUniform3ui = nullptr;
static PFNGLUNIFORM4UIPROC _glUniform4ui = nullptr;
static PFNGLUNIFORM1UIVPROC _glUniform1uiv = nullptr;
static PFNGLUNIFORM2UIVPROC _glUniform2uiv = nullptr;
static PFNGLUNIFORM3UIVPROC _glUniform3uiv = nullptr;
static PFNGLUNIFORM4UIVPROC _glUniform4uiv = nullptr;
static PFNGLTEXPARAMETERIIVPROC _glTexParameterIiv = nullptr;
static PFNGLTEXPARAMETERIUIVPROC _glTexParameterIuiv = nullptr;
static PFNGLGETTEXPARAMETERIIVPROC _glGetTexParameterIiv = nullptr;
static PFNGLGETTEXPARAMETERIUIVPROC _glGetTexParameterIuiv = nullptr;
static PFNGLCLEARBUFFERIVPROC _glClearBufferiv = nullptr;
static PFNGLCLEARBUFFERUIVPROC _glClearBufferuiv = nullptr;
static PFNGLCLEARBUFFERFVPROC _glClearBufferfv = nullptr;
static PFNGLCLEARBUFFERFIPROC _glClearBufferfi = nullptr;
static PFNGLGETSTRINGIPROC _glGetStringi = nullptr;
#endif //GL_VERSION_3_0

#if defined(GL_VERSION_3_1)
//reused functions from ARB_copy_buffer
static PFNGLCOPYBUFFERSUBDATAPROC _glCopyBufferSubData = nullptr;

//reused functions from ARB_uniform_buffer_object
static PFNGLGETUNIFORMINDICESPROC _glGetUniformIndices = nullptr;
static PFNGLGETACTIVEUNIFORMSIVPROC _glGetActiveUniformsiv = nullptr;
static PFNGLGETACTIVEUNIFORMNAMEPROC _glGetActiveUniformName = nullptr;
static PFNGLGETUNIFORMBLOCKINDEXPROC _glGetUniformBlockIndex = nullptr;
static PFNGLGETACTIVEUNIFORMBLOCKIVPROC _glGetActiveUniformBlockiv = nullptr;
static PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC _glGetActiveUniformBlockName = nullptr;
static PFNGLUNIFORMBLOCKBINDINGPROC _glUniformBlockBinding = nullptr;

//functions introduced in OpenGL 3.1
static PFNGLDRAWARRAYSINSTANCEDPROC _glDrawArraysInstanced = nullptr;
static PFNGLDRAWELEMENTSINSTANCEDPROC _glDrawElementsInstanced = nullptr;
static PFNGLTEXBUFFERPROC _glTexBuffer = nullptr;
static PFNGLPRIMITIVERESTARTINDEXPROC _glPrimitiveRestartIndex = nullptr;
#endif //GL_VERSION_3_1

#if defined(GL_VERSION_3_2)
//reused functions from ARB_draw_elements_base_vertex
static PFNGLDRAWELEMENTSBASEVERTEXPROC _glDrawElementsBaseVertex = nullptr;
static PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC _glDrawRangeElementsBaseVertex = nullptr;
static PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC _glDrawElementsInstancedBaseVertex = nullptr;
static PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC _glMultiDrawElementsBaseVertex = nullptr;

//reused functions from ARB_provoking_vertex
static PFNGLPROVOKINGVERTEXPROC _glProvokingVertex = nullptr;

//reused function from ARB_sync
static PFNGLFENCESYNCPROC _glFenceSync = nullptr;
static PFNGLISSYNCPROC _glIsSync = nullptr;
static PFNGLDELETESYNCPROC _glDeleteSync = nullptr;
static PFNGLCLIENTWAITSYNCPROC _glClientWaitSync = nullptr;
static PFNGLWAITSYNCPROC _glWaitSync = nullptr;
static PFNGLGETINTEGER64VPROC _glGetInteger64v = nullptr;
static PFNGLGETSYNCIVPROC _glGetSynciv = nullptr;

//reused functions from ARB_texture_multisample
static PFNGLTEXIMAGE2DMULTISAMPLEPROC _glTexImage2DMultisample = nullptr;
static PFNGLTEXIMAGE3DMULTISAMPLEPROC _glTexImage3DMultisample = nullptr;
static PFNGLGETMULTISAMPLEFVPROC _glGetMultisamplefv = nullptr;
static PFNGLSAMPLEMASKIPROC _glSampleMaski = nullptr;

//functions introduced in OpenGL 3.2
static PFNGLGETINTEGER64I_VPROC _glGetInteger64i_v = nullptr;
static PFNGLGETBUFFERPARAMETERI64VPROC _glGetBufferParameteri64v = nullptr;
static PFNGLFRAMEBUFFERTEXTUREPROC _glFramebufferTexture = nullptr;
#endif //GL_VERSION_3_2

#if defined(GL_VERSION_3_3)
//reused functions from ARB_blend_func_extended
static PFNGLBINDFRAGDATALOCATIONINDEXEDPROC _glBindFragDataLocationIndexed = nullptr;
static PFNGLGETFRAGDATAINDEXPROC _glGetFragDataIndex = nullptr;

//reused functions from ARB_sampler_objects
static PFNGLGENSAMPLERSPROC _glGenSamplers = nullptr;
static PFNGLDELETESAMPLERSPROC _glDeleteSamplers = nullptr;
static PFNGLISSAMPLERPROC _glIsSampler = nullptr;
static PFNGLBINDSAMPLERPROC _glBindSampler = nullptr;
static PFNGLSAMPLERPARAMETERIPROC _glSamplerParameteri = nullptr;
static PFNGLSAMPLERPARAMETERIVPROC _glSamplerParameteriv = nullptr;
static PFNGLSAMPLERPARAMETERFPROC _glSamplerParameterf = nullptr;
static PFNGLSAMPLERPARAMETERFVPROC _glSamplerParameterfv = nullptr;
static PFNGLSAMPLERPARAMETERIIVPROC _glSamplerParameterIiv = nullptr;
static PFNGLSAMPLERPARAMETERIUIVPROC _glSamplerParameterIuiv = nullptr;
static PFNGLGETSAMPLERPARAMETERIVPROC _glGetSamplerParameteriv = nullptr;
static PFNGLGETSAMPLERPARAMETERIIVPROC _glGetSamplerParameterIiv = nullptr;
static PFNGLGETSAMPLERPARAMETERFVPROC _glGetSamplerParameterfv = nullptr;
static PFNGLGETSAMPLERPARAMETERIUIVPROC _glGetSamplerParameterIuiv = nullptr;

//reused functions from ARB_timer_query
static PFNGLQUERYCOUNTERPROC _glQueryCounter = nullptr;
static PFNGLGETQUERYOBJECTI64VPROC _glGetQueryObjecti64v = nullptr;
static PFNGLGETQUERYOBJECTUI64VPROC _glGetQueryObjectui64v = nullptr;

//reused functions from ARB_vertex_type_2_10_10_10_rev
//static PFNGLVERTEXP2UIPROC _glVertexP2ui = nullptr;
//static PFNGLVERTEXP2UIVPROC _glVertexP2uiv = nullptr;
//static PFNGLVERTEXP3UIPROC _glVertexP3ui = nullptr;
//static PFNGLVERTEXP3UIVPROC _glVertexP3uiv = nullptr;
//static PFNGLVERTEXP4UIPROC _glVertexP4ui = nullptr;
//static PFNGLVERTEXP4UIVPROC _glVertexP4uiv = nullptr;
//static PFNGLTEXCOORDP1UIPROC _glTexCoordP1ui = nullptr;
//static PFNGLTEXCOORDP1UIVPROC _glTexCoordP1uiv = nullptr;
//static PFNGLTEXCOORDP2UIPROC _glTexCoordP2ui = nullptr;
//static PFNGLTEXCOORDP2UIVPROC _glTexCoordP2uiv = nullptr;
//static PFNGLTEXCOORDP3UIPROC _glTexCoordP3ui = nullptr;
//static PFNGLTEXCOORDP3UIVPROC _glTexCoordP3uiv = nullptr;
//static PFNGLTEXCOORDP4UIPROC _glTexCoordP4ui = nullptr;
//static PFNGLTEXCOORDP4UIVPROC _glTexCoordP4uiv = nullptr;
//static PFNGLMULTITEXCOORDP1UIPROC _glMultiTexCoordP1ui = nullptr;
//static PFNGLMULTITEXCOORDP1UIVPROC _glMultiTexCoordP1uiv = nullptr;
//static PFNGLMULTITEXCOORDP2UIPROC _glMultiTexCoordP2ui = nullptr;
//static PFNGLMULTITEXCOORDP2UIVPROC _glMultiTexCoordP2uiv = nullptr;
//static PFNGLMULTITEXCOORDP3UIPROC _glMultiTexCoordP3ui = nullptr;
//static PFNGLMULTITEXCOORDP3UIVPROC _glMultiTexCoordP3uiv = nullptr;
//static PFNGLMULTITEXCOORDP4UIPROC _glMultiTexCoordP4ui = nullptr;
//static PFNGLMULTITEXCOORDP4UIVPROC _glMultiTexCoordP4uiv = nullptr;
//static PFNGLNORMALP3UIPROC _glNormalP3ui = nullptr;
//static PFNGLNORMALP3UIVPROC _glNormalP3uiv = nullptr;
//static PFNGLCOLORP3UIPROC _glColorP3ui = nullptr;
//static PFNGLCOLORP3UIVPROC _glColorP3uiv = nullptr;
//static PFNGLCOLORP4UIPROC _glColorP4ui = nullptr;
//static PFNGLCOLORP4UIVPROC _glColorP4uiv = nullptr;
//static PFNGLSECONDARYCOLORP3UIPROC _glSecondaryColorP3ui = nullptr;
//static PFNGLSECONDARYCOLORP3UIVPROC _glSecondaryColorP3uiv = nullptr;
static PFNGLVERTEXATTRIBP1UIPROC _glVertexAttribP1ui = nullptr;
//static PFNGLVERTEXATTRIBP1UIVPROC _glVertexAttribP1uiv = nullptr;
static PFNGLVERTEXATTRIBP2UIPROC _glVertexAttribP2ui = nullptr;
//static PFNGLVERTEXATTRIBP2UIVPROC _glVertexAttribP2uiv = nullptr;
static PFNGLVERTEXATTRIBP3UIPROC _glVertexAttribP3ui = nullptr;
//static PFNGLVERTEXATTRIBP3UIVPROC _glVertexAttribP3uiv = nullptr;
static PFNGLVERTEXATTRIBP4UIPROC _glVertexAttribP4ui = nullptr;
//static PFNGLVERTEXATTRIBP4UIVPROC _glVertexAttribP4uiv = nullptr;

//functions introduced in OpenGL 3.3
static PFNGLVERTEXATTRIBDIVISORPROC _glVertexAttribDivisor = nullptr;
#endif //GL_VERSION_3_3

#if defined(GL_VERSION_4_0)
//reused functions from ARB_draw_indirect
static PFNGLDRAWARRAYSINDIRECTPROC _glDrawArraysIndirect = nullptr;
static PFNGLDRAWELEMENTSINDIRECTPROC _glDrawElementsIndirect = nullptr;

//reused functions from ARB_gpu_shader_fp64
static PFNGLUNIFORM1DPROC _glUniform1d = nullptr;
static PFNGLUNIFORM2DPROC _glUniform2d = nullptr;
static PFNGLUNIFORM3DPROC _glUniform3d = nullptr;
static PFNGLUNIFORM4DPROC _glUniform4d = nullptr;
static PFNGLUNIFORM1DVPROC _glUniform1dv = nullptr;
static PFNGLUNIFORM2DVPROC _glUniform2dv = nullptr;
static PFNGLUNIFORM3DVPROC _glUniform3dv = nullptr;
static PFNGLUNIFORM4DVPROC _glUniform4dv = nullptr;
static PFNGLUNIFORMMATRIX2DVPROC _glUniformMatrix2dv = nullptr;
static PFNGLUNIFORMMATRIX3DVPROC _glUniformMatrix3dv = nullptr;
static PFNGLUNIFORMMATRIX4DVPROC _glUniformMatrix4dv = nullptr;
static PFNGLUNIFORMMATRIX2X3DVPROC _glUniformMatrix2x3dv = nullptr;
static PFNGLUNIFORMMATRIX2X4DVPROC _glUniformMatrix2x4dv = nullptr;
static PFNGLUNIFORMMATRIX3X2DVPROC _glUniformMatrix3x2dv = nullptr;
static PFNGLUNIFORMMATRIX3X4DVPROC _glUniformMatrix3x4dv = nullptr;
static PFNGLUNIFORMMATRIX4X2DVPROC _glUniformMatrix4x2dv = nullptr;
static PFNGLUNIFORMMATRIX4X3DVPROC _glUniformMatrix4x3dv = nullptr;
static PFNGLGETUNIFORMDVPROC _glGetUniformdv = nullptr;

//reused functions from ARB_shader_subroutine
static PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC _glGetSubroutineUniformLocation = nullptr;
static PFNGLGETSUBROUTINEINDEXPROC _glGetSubroutineIndex = nullptr;
static PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC _glGetActiveSubroutineUniformiv = nullptr;
static PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC _glGetActiveSubroutineUniformName = nullptr;
static PFNGLGETACTIVESUBROUTINENAMEPROC _glGetActiveSubroutineName = nullptr;
static PFNGLUNIFORMSUBROUTINESUIVPROC _glUniformSubroutinesuiv = nullptr;
static PFNGLGETUNIFORMSUBROUTINEUIVPROC _glGetUniformSubroutineuiv = nullptr;
static PFNGLGETPROGRAMSTAGEIVPROC _glGetProgramStageiv = nullptr;

//reused functions from ARB_tessellation_shader
static PFNGLPATCHPARAMETERIPROC _glPatchParameteri = nullptr;
static PFNGLPATCHPARAMETERFVPROC _glPatchParameterfv = nullptr;

//reused functions from ARB_transform_feedback2
static PFNGLBINDTRANSFORMFEEDBACKPROC _glBindTransformFeedback = nullptr;
static PFNGLDELETETRANSFORMFEEDBACKSPROC _glDeleteTransformFeedbacks = nullptr;
static PFNGLGENTRANSFORMFEEDBACKSPROC _glGenTransformFeedbacks = nullptr;
static PFNGLISTRANSFORMFEEDBACKPROC _glIsTransformFeedback = nullptr;
static PFNGLPAUSETRANSFORMFEEDBACKPROC _glPauseTransformFeedback = nullptr;
static PFNGLRESUMETRANSFORMFEEDBACKPROC _glResumeTransformFeedback = nullptr;
static PFNGLDRAWTRANSFORMFEEDBACKPROC _glDrawTransformFeedback = nullptr;

//reused functions from ARB_transform_feedback3
static PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC _glDrawTransformFeedbackStream = nullptr;
static PFNGLBEGINQUERYINDEXEDPROC _glBeginQueryIndexed = nullptr;
static PFNGLENDQUERYINDEXEDPROC _glEndQueryIndexed = nullptr;
static PFNGLGETQUERYINDEXEDIVPROC _glGetQueryIndexediv = nullptr;

//functions introduced in OpenGL 4.0
static PFNGLMINSAMPLESHADINGPROC _glMinSampleShading = nullptr;
static PFNGLBLENDEQUATIONIPROC _glBlendEquationi = nullptr;
static PFNGLBLENDEQUATIONSEPARATEIPROC _glBlendEquationSeparatei = nullptr;
static PFNGLBLENDFUNCIPROC _glBlendFunci = nullptr;
static PFNGLBLENDFUNCSEPARATEIPROC _glBlendFuncSeparatei = nullptr;
#endif //GL_VERSION_4_0

#if defined(GL_VERSION_4_1)
//functions reused from ARB_ES2_compatibility
static PFNGLRELEASESHADERCOMPILERPROC _glReleaseShaderCompiler = nullptr;
static PFNGLSHADERBINARYPROC _glShaderBinary = nullptr;
static PFNGLGETSHADERPRECISIONFORMATPROC _glGetShaderPrecisionFormat = nullptr;
static PFNGLDEPTHRANGEFPROC _glDepthRangef = nullptr;
static PFNGLCLEARDEPTHFPROC _glClearDepthf = nullptr;

//functions reused from ARB_get_program_binary
static PFNGLGETPROGRAMBINARYPROC _glGetProgramBinary = nullptr;
static PFNGLPROGRAMBINARYPROC _glProgramBinary = nullptr;
static PFNGLPROGRAMPARAMETERIPROC _glProgramParameteri = nullptr;

//functions reused from ARB_separate_shader_objects
static PFNGLUSEPROGRAMSTAGESPROC _glUseProgramStages = nullptr;
static PFNGLACTIVESHADERPROGRAMPROC _glActiveShaderProgram = nullptr;
static PFNGLCREATESHADERPROGRAMVPROC _glCreateShaderProgramv = nullptr;
static PFNGLBINDPROGRAMPIPELINEPROC _glBindProgramPipeline = nullptr;
static PFNGLDELETEPROGRAMPIPELINESPROC _glDeleteProgramPipelines = nullptr;
static PFNGLGENPROGRAMPIPELINESPROC _glGenProgramPipelines = nullptr;
static PFNGLISPROGRAMPIPELINEPROC _glIsProgramPipeline = nullptr;
static PFNGLGETPROGRAMPIPELINEIVPROC _glGetProgramPipelineiv = nullptr;
static PFNGLPROGRAMUNIFORM1IPROC _glProgramUniform1i = nullptr;
static PFNGLPROGRAMUNIFORM1IVPROC _glProgramUniform1iv = nullptr;
static PFNGLPROGRAMUNIFORM1FPROC _glProgramUniform1f = nullptr;
static PFNGLPROGRAMUNIFORM1FVPROC _glProgramUniform1fv = nullptr;
static PFNGLPROGRAMUNIFORM1DPROC _glProgramUniform1d = nullptr;
static PFNGLPROGRAMUNIFORM1DVPROC _glProgramUniform1dv = nullptr;
static PFNGLPROGRAMUNIFORM1UIPROC _glProgramUniform1ui = nullptr;
static PFNGLPROGRAMUNIFORM1UIVPROC _glProgramUniform1uiv = nullptr;
static PFNGLPROGRAMUNIFORM2IPROC _glProgramUniform2i = nullptr;
static PFNGLPROGRAMUNIFORM2IVPROC _glProgramUniform2iv = nullptr;
static PFNGLPROGRAMUNIFORM2FPROC _glProgramUniform2f = nullptr;
static PFNGLPROGRAMUNIFORM2FVPROC _glProgramUniform2fv = nullptr;
static PFNGLPROGRAMUNIFORM2DPROC _glProgramUniform2d = nullptr;
static PFNGLPROGRAMUNIFORM2DVPROC _glProgramUniform2dv = nullptr;
static PFNGLPROGRAMUNIFORM2UIPROC _glProgramUniform2ui = nullptr;
static PFNGLPROGRAMUNIFORM2UIVPROC _glProgramUniform2uiv = nullptr;
static PFNGLPROGRAMUNIFORM3IPROC _glProgramUniform3i = nullptr;
static PFNGLPROGRAMUNIFORM3IVPROC _glProgramUniform3iv = nullptr;
static PFNGLPROGRAMUNIFORM3FPROC _glProgramUniform3f = nullptr;
static PFNGLPROGRAMUNIFORM3FVPROC _glProgramUniform3fv = nullptr;
static PFNGLPROGRAMUNIFORM3DPROC _glProgramUniform3d = nullptr;
static PFNGLPROGRAMUNIFORM3DVPROC _glProgramUniform3dv = nullptr;
static PFNGLPROGRAMUNIFORM3UIPROC _glProgramUniform3ui = nullptr;
static PFNGLPROGRAMUNIFORM3UIVPROC _glProgramUniform3uiv = nullptr;
static PFNGLPROGRAMUNIFORM4IPROC _glProgramUniform4i = nullptr;
static PFNGLPROGRAMUNIFORM4IVPROC _glProgramUniform4iv = nullptr;
static PFNGLPROGRAMUNIFORM4FPROC _glProgramUniform4f = nullptr;
static PFNGLPROGRAMUNIFORM4FVPROC _glProgramUniform4fv = nullptr;
static PFNGLPROGRAMUNIFORM4DPROC _glProgramUniform4d = nullptr;
static PFNGLPROGRAMUNIFORM4DVPROC _glProgramUniform4dv = nullptr;
static PFNGLPROGRAMUNIFORM4UIPROC _glProgramUniform4ui = nullptr;
static PFNGLPROGRAMUNIFORM4UIVPROC _glProgramUniform4uiv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX2FVPROC _glProgramUniformMatrix2fv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX3FVPROC _glProgramUniformMatrix3fv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX4FVPROC _glProgramUniformMatrix4fv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX2DVPROC _glProgramUniformMatrix2dv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX3DVPROC _glProgramUniformMatrix3dv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX4DVPROC _glProgramUniformMatrix4dv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC _glProgramUniformMatrix2x3fv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC _glProgramUniformMatrix3x2fv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC _glProgramUniformMatrix2x4fv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC _glProgramUniformMatrix4x2fv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC _glProgramUniformMatrix3x4fv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC _glProgramUniformMatrix4x3fv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC _glProgramUniformMatrix2x3dv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC _glProgramUniformMatrix3x2dv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC _glProgramUniformMatrix2x4dv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC _glProgramUniformMatrix4x2dv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC _glProgramUniformMatrix3x4dv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC _glProgramUniformMatrix4x3dv = nullptr;
static PFNGLVALIDATEPROGRAMPIPELINEPROC _glValidateProgramPipeline = nullptr;
static PFNGLGETPROGRAMPIPELINEINFOLOGPROC _glGetProgramPipelineInfoLog = nullptr;

//reused functions from ARB_vertex_attrib_64bit
static PFNGLVERTEXATTRIBL1DPROC _glVertexAttribL1d = nullptr;
static PFNGLVERTEXATTRIBL2DPROC _glVertexAttribL2d = nullptr;
static PFNGLVERTEXATTRIBL3DPROC _glVertexAttribL3d = nullptr;
static PFNGLVERTEXATTRIBL4DPROC _glVertexAttribL4d = nullptr;
static PFNGLVERTEXATTRIBL1DVPROC _glVertexAttribL1dv = nullptr;
static PFNGLVERTEXATTRIBL2DVPROC _glVertexAttribL2dv = nullptr;
static PFNGLVERTEXATTRIBL3DVPROC _glVertexAttribL3dv = nullptr;
static PFNGLVERTEXATTRIBL4DVPROC _glVertexAttribL4dv = nullptr;
static PFNGLVERTEXATTRIBLPOINTERPROC _glVertexAttribLPointer = nullptr;
static PFNGLGETVERTEXATTRIBLDVPROC _glGetVertexAttribLdv = nullptr;

//reused functions from ARB_viewport_array
static PFNGLVIEWPORTARRAYVPROC _glViewportArrayv = nullptr;
static PFNGLVIEWPORTINDEXEDFPROC _glViewportIndexedf = nullptr;
static PFNGLVIEWPORTINDEXEDFVPROC _glViewportIndexedfv = nullptr;
static PFNGLSCISSORARRAYVPROC _glScissorArrayv = nullptr;
static PFNGLSCISSORINDEXEDPROC _glScissorIndexed = nullptr;
static PFNGLSCISSORINDEXEDVPROC _glScissorIndexedv = nullptr;
static PFNGLDEPTHRANGEARRAYVPROC _glDepthRangeArrayv = nullptr;
static PFNGLDEPTHRANGEINDEXEDPROC _glDepthRangeIndexed = nullptr;
static PFNGLGETFLOATI_VPROC _glGetFloati_v = nullptr;
static PFNGLGETDOUBLEI_VPROC _glGetDoublei_v = nullptr;
#endif //GL_VERSION_4_1

#if defined(GL_VERSION_4_2)
//reused functions from ARB_base_instance
static PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC _glDrawArraysInstancedBaseInstance = nullptr;
static PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC _glDrawElementsInstancedBaseInstance = nullptr;
static PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC _glDrawElementsInstancedBaseVertexBaseInstance = nullptr;

//reused functions from ARB_transform_feedback_instanced
static PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC _glDrawTransformFeedbackInstanced = nullptr;
static PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC _glDrawTransformFeedbackStreamInstanced = nullptr;

//reused functions from ARB_internalformat_query
static PFNGLGETINTERNALFORMATIVPROC _glGetInternalformativ = nullptr;

//reused functions from ARB_shader_atomic_counters
static PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC _glGetActiveAtomicCounterBufferiv = nullptr;

//reused functions from ARB_shader_image_load_store
static PFNGLBINDIMAGETEXTUREPROC _glBindImageTexture = nullptr;
static PFNGLMEMORYBARRIERPROC _glMemoryBarrier = nullptr;

//reused functions from ARB_texture_storage
static PFNGLTEXSTORAGE1DPROC _glTexStorage1D = nullptr;
static PFNGLTEXSTORAGE2DPROC _glTexStorage2D = nullptr;
static PFNGLTEXSTORAGE3DPROC _glTexStorage3D = nullptr;
static PFNGLTEXTURESTORAGE1DEXTPROC _glTextureStorage1DEXT = nullptr;
static PFNGLTEXTURESTORAGE2DEXTPROC _glTextureStorage2DEXT = nullptr;
static PFNGLTEXTURESTORAGE3DEXTPROC _glTextureStorage3DEXT = nullptr;
#endif //GL_VERSION_4_2

#if defined(GL_VERSION_4_3)
//functions reused from ARB_clear_buffer_object
static PFNGLCLEARBUFFERDATAPROC _glClearBufferData = nullptr;
static PFNGLCLEARBUFFERSUBDATAPROC _glClearBufferSubData = nullptr;
static PFNGLCLEARNAMEDBUFFERDATAEXTPROC _glClearNamedBufferDataEXT = nullptr;
static PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC _glClearNamedBufferSubDataEXT = nullptr;

//functions reused from ARB_compute_shader
static PFNGLDISPATCHCOMPUTEPROC _glDispatchCompute = nullptr;
static PFNGLDISPATCHCOMPUTEINDIRECTPROC _glDispatchComputeIndirect = nullptr;

//functions reused from ARB_copy_image
static PFNGLCOPYIMAGESUBDATAPROC _glCopyImageSubData = nullptr;

//functions reused from KHR_debug
static PFNGLDEBUGMESSAGECONTROLPROC _glDebugMessageControl = nullptr;
static PFNGLDEBUGMESSAGEINSERTPROC _glDebugMessageInsert = nullptr;
static PFNGLDEBUGMESSAGECALLBACKPROC _glDebugMessageCallback = nullptr;
static PFNGLGETDEBUGMESSAGELOGPROC _glGetDebugMessageLog = nullptr;
static PFNGLPUSHDEBUGGROUPPROC _glPushDebugGroup = nullptr;
static PFNGLPOPDEBUGGROUPPROC _glPopDebugGroup = nullptr;
static PFNGLOBJECTLABELPROC _glObjectLabel = nullptr;
static PFNGLGETOBJECTLABELPROC _glGetObjectLabel = nullptr;
static PFNGLOBJECTPTRLABELPROC _glObjectPtrLabel = nullptr;
static PFNGLGETOBJECTPTRLABELPROC _glGetObjectPtrLabel = nullptr;

//reused functions from ARB_framebuffer_no_attackments
static PFNGLFRAMEBUFFERPARAMETERIPROC _glFramebufferParameteri = nullptr;
static PFNGLGETFRAMEBUFFERPARAMETERIVPROC _glGetFramebufferParameteriv = nullptr;

#if defined(GL_EXT_direct_state_access)
static PFNGLNAMEDFRAMEBUFFERPARAMETERIEXTPROC _glNamedFramebufferParameteriEXT = nullptr;
static PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVEXTPROC _glGetNamedFramebufferParameterivEXT = nullptr;
#endif

//reused functions from ARB_internalformat_query2
static PFNGLGETINTERNALFORMATI64VPROC _glGetInternalformati64v = nullptr;

//reused functions from ARB_invalidate_subdata
static PFNGLINVALIDATETEXSUBIMAGEPROC _glInvalidateTexSubImage = nullptr;
static PFNGLINVALIDATETEXIMAGEPROC _glInvalidateTexImage = nullptr;
static PFNGLINVALIDATEBUFFERSUBDATAPROC _glInvalidateBufferSubData = nullptr;
static PFNGLINVALIDATEBUFFERDATAPROC _glInvalidateBufferData = nullptr;
static PFNGLINVALIDATEFRAMEBUFFERPROC _glInvalidateFramebuffer = nullptr;
static PFNGLINVALIDATESUBFRAMEBUFFERPROC _glInvalidateSubFramebuffer = nullptr;

//reused functions from ARB_multi_draw_indirect
static PFNGLMULTIDRAWARRAYSINDIRECTPROC _glMultiDrawArraysIndirect = nullptr;
static PFNGLMULTIDRAWELEMENTSINDIRECTPROC _glMultiDrawElementsIndirect = nullptr;

//reused functions from ARB_program_interface_query
static PFNGLGETPROGRAMINTERFACEIVPROC _glGetProgramInterfaceiv = nullptr;
static PFNGLGETPROGRAMRESOURCEINDEXPROC _glGetProgramResourceIndex = nullptr;
static PFNGLGETPROGRAMRESOURCENAMEPROC _glGetProgramResourceName = nullptr;
static PFNGLGETPROGRAMRESOURCEIVPROC _glGetProgramResourceiv = nullptr;
static PFNGLGETPROGRAMRESOURCELOCATIONPROC _glGetProgramResourceLocation = nullptr;
static PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC _glGetProgramResourceLocationIndex = nullptr;

//reused functions from ARB_shader_storage_buffer_object
static PFNGLSHADERSTORAGEBLOCKBINDINGPROC _glShaderStorageBlockBinding = nullptr;

//reused functions from ARB_texture_buffer_range
static PFNGLTEXBUFFERRANGEPROC _glTexBufferRange = nullptr;
static PFNGLTEXTUREBUFFERRANGEEXTPROC _glTextureBufferRangeEXT = nullptr;

//reused functions from ARB_texture_storage_multisample
static PFNGLTEXSTORAGE2DMULTISAMPLEPROC _glTexStorage2DMultisample = nullptr;
static PFNGLTEXSTORAGE3DMULTISAMPLEPROC _glTexStorage3DMultisample = nullptr;
#if defined(GL_EXT_direct_state_access)
static PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC _glTextureStorage2DMultisampleEXT = nullptr;
static PFNGLTEXTURESTORAGE3DMULTISAMPLEEXTPROC _glTextureStorage3DMultisampleEXT = nullptr;
#endif

//reused functions from ARB_texture_view
static PFNGLTEXTUREVIEWPROC _glTextureView = nullptr;

//reused functions from ARB_vertex_attrib_binding
static PFNGLBINDVERTEXBUFFERPROC _glBindVertexBuffer = nullptr;
static PFNGLVERTEXATTRIBFORMATPROC _glVertexAttribFormat = nullptr;
static PFNGLVERTEXATTRIBIFORMATPROC _glVertexAttribIFormat = nullptr;
static PFNGLVERTEXATTRIBLFORMATPROC _glVertexAttribLFormat = nullptr;
static PFNGLVERTEXATTRIBBINDINGPROC _glVertexAttribBinding = nullptr;
static PFNGLVERTEXBINDINGDIVISORPROC _glVertexBindingDivisor = nullptr;
#endif //GL_VERSION_4_3

#if defined(GL_VERSION_4_4)
//reused function from ARB_buffer_storage
static PFNGLBUFFERSTORAGEPROC _glBufferStorage = nullptr;

//reused functions from ARB_clear_texture
static PFNGLCLEARTEXIMAGEPROC _glClearTexImage = nullptr;
static PFNGLCLEARTEXSUBIMAGEPROC _glClearTexSubImage = nullptr;

//reused functions from ARB_multi_bind
static PFNGLBINDBUFFERSBASEPROC _glBindBuffersBase = nullptr;
static PFNGLBINDBUFFERSRANGEPROC _glBindBuffersRange = nullptr;
static PFNGLBINDTEXTURESPROC _glBindTextures = nullptr;
static PFNGLBINDSAMPLERSPROC _glBindSamplers = nullptr;
static PFNGLBINDIMAGETEXTURESPROC _glBindImageTextures = nullptr;
static PFNGLBINDVERTEXBUFFERSPROC _glBindVertexBuffers = nullptr;
#endif //GL_VERSION_4_4

#if defined(GEL_MSWINDOWS)
#pragma endregion
#endif

#define Version(mjr,mnr) (gel::major > mjr || (gel::major == mjr && gel::minor >= mnr))
#define GelLoadFunction(funcName) if(_##funcName == nullptr) {_##funcName = (decltype(_##funcName))gel::getProcAddress(#funcName); /*if(_##funcName == nullptr) throw new gel::FunctionNotFoundException(#funcName);*/}

#if defined(GEL_MSWINDOWS)
#pragma region Functions
#endif

#if defined(GL_VERSION_1_2) && defined(GEL_MSWINDOWS)
void glBlendColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
{
	if(Version(1,2))
	{
		GelLoadFunction(glBlendColor);
		_glBlendColor(r,g,b,a);
	}
}
void glBlendEquation(GLenum mode)
{
	if(Version(1,2))
	{
		GelLoadFunction(glBlendEquation);
		_glBlendEquation(mode);
	}
}
void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, GLvoid const * indices)
{
	if(Version(1,2))
	{
		GelLoadFunction(glDrawRangeElements);
		_glDrawRangeElements(mode,start,end,count,type,indices);
	}
}
void glTexImage3D(GLenum target, GLint level,GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, GLvoid const * pixels)
{
	if(Version(1,2))
	{
		GelLoadFunction(glTexImage3D);
		_glTexImage3D(target,level,internalformat,width,height,depth,border,format,type,pixels);
	}
}
void glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLvoid const * pixels)
{
	if(Version(1,2))
	{
		GelLoadFunction(glTexSubImage3D);
		_glTexSubImage3D(target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels);
	}
}
void glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	if(Version(1,2))
	{
		GelLoadFunction(glCopyTexSubImage3D);
		_glCopyTexSubImage3D(target,level,xoffset,yoffset,zoffset,x,y,width,height);
	}
}
#endif

#if defined(GL_VERSION_1_3) && defined(GEL_MSWINDOWS)
void glActiveTexture(GLenum texture)
{
	if(Version(1,3))
	{
		GelLoadFunction(glActiveTexture);
		_glActiveTexture(texture);
	}
}
void glSampleCoverage(GLclampf value, GLboolean invert)
{
	if(Version(1,3))
	{
		GelLoadFunction(glSampleCoverage);
		_glSampleCoverage(value,invert);
	}
}
void glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imagesize, GLvoid const * data)
{
	if(Version(1,3))
	{
		GelLoadFunction(glCompressedTexImage3D);
		_glCompressedTexImage3D(target,level,internalformat,width,height,depth,border,imagesize,data);
	}
}
void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imagesize, GLvoid const * data)
{
	if(Version(1,3))
	{
		GelLoadFunction(glCompressedTexImage2D);
		_glCompressedTexImage2D(target,level,internalformat,width,height,border,imagesize,data);
	}
}
void glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imagesize, GLvoid const * data)
{
	if(Version(1,3))
	{
		GelLoadFunction(glCompressedTexImage1D);
		_glCompressedTexImage1D(target,level,internalformat,width,border,imagesize,data);
	}
}
void glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imagesize, GLvoid const * data)
{
	if(Version(1,3))
	{
		GelLoadFunction(glCompressedTexSubImage3D);
		_glCompressedTexSubImage3D(target,level,xoffset,yoffset,zoffset,width,height,depth,format,imagesize,data);
	}
}
void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imagesize, GLvoid const * data)
{
	if(Version(1,3))
	{
		GelLoadFunction(glCompressedTexSubImage2D);
		_glCompressedTexSubImage2D(target,level,xoffset,yoffset,width,height,format,imagesize,data);
	}
}
void glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imagesize, GLvoid const * data)
{
	if(Version(1,3))
	{
		GelLoadFunction(glCompressedTexSubImage1D);
		_glCompressedTexSubImage1D(target,level,xoffset,width,format,imagesize,data);
	}
}
void glGetCompressedTexImage(GLenum target, GLint level, GLvoid * img)
{
	if(Version(1,3))
	{
		GelLoadFunction(glGetCompressedTexImage);
		_glGetCompressedTexImage(target,level,img);
	}
}
#endif

#if defined(GL_VERSION_1_4)
void glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
	if(Version(1,4))
	{
		GelLoadFunction(glBlendFuncSeparate);
		_glBlendFuncSeparate(sfactorRGB,dfactorRGB,sfactorAlpha,dfactorAlpha);
	}
}
void glMultiDrawArrays(GLenum mode, GLint const * first, GLsizei const * count, GLsizei primcount)
{
	if(Version(1,4))
	{
		GelLoadFunction(glMultiDrawArrays);
		_glMultiDrawArrays(mode,first,count,primcount);
	}
}
void glMultiDrawElements(GLenum mode, GLsizei const * count, GLenum type, GLvoid const ** indices, GLsizei primcount)
{
	if(Version(1,4))
	{
		GelLoadFunction(glMultiDrawElements);
		_glMultiDrawElements(mode,count,type,indices,primcount);
	}
}
void glPointParameterf(GLenum pname, GLfloat param)
{
	if(Version(1,4))
	{
		GelLoadFunction(glPointParameterf);
		_glPointParameterf(pname,param);
	}
}
void glPointParameterfv(GLenum pname, GLfloat const * params)
{
	if(Version(1,4))
	{
		GelLoadFunction(glPointParameterfv);
		_glPointParameterfv(pname,params);
	}
}
void glPointParameteri(GLenum pname, GLint param)
{
	if(Version(1,4))
	{
		GelLoadFunction(glPointParameteri);
		_glPointParameteri(pname,param);
	}
}
void glPointParameteriv(GLenum pname, GLint const * params)
{
	if(Version(1,4))
	{
		GelLoadFunction(glPointParameteriv);
		_glPointParameteriv(pname,params);
	}
}
#endif

#if defined(GL_VERSION_1_5)
void glGenQueries(GLsizei n, GLuint * ids)
{
	if(Version(1,5))
	{
		GelLoadFunction(glGenQueries);
		_glGenQueries(n,ids);
	}
}
void glDeleteQueries(GLsizei n, GLuint * ids)
{
	if(Version(1,5))
	{
		GelLoadFunction(glDeleteQueries);
		_glDeleteQueries(n,ids);
	}
}
GLboolean glIsQuery(GLuint id)
{
	if(Version(1,5))
	{
		GelLoadFunction(glIsQuery);
		return _glIsQuery(id);
	}
	return GL_FALSE;
}
void glBeginQuery(GLenum target, GLuint id)
{
	if(Version(1,5))
	{
		GelLoadFunction(glBeginQuery);
		_glBeginQuery(target,id);
	}
}
void glEndQuery(GLenum target)
{
	if(Version(1,5))
	{
		GelLoadFunction(glEndQuery);
		_glEndQuery(target);
	}
}
void glGetQueryiv(GLenum target, GLenum pname, GLint * params)
{
	if(Version(1,5))
	{
		GelLoadFunction(glGetQueryiv);
		_glGetQueryiv(target,pname,params);
	}
}
void glGetQueryObjectiv(GLuint id, GLenum pname, GLint * params)
{
	if(Version(1,5))
	{
		GelLoadFunction(glGetQueryObjectiv);
		_glGetQueryObjectiv(id,pname,params);
	}
}
void glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params)
{
	if(Version(1,5))
	{
		GelLoadFunction(glGetQueryObjectuiv);
		_glGetQueryObjectuiv(id,pname,params);
	}
}
void glBindBuffer(GLenum target, GLuint buffer)
{
	if(Version(1,5))
	{
		GelLoadFunction(glBindBuffer);
		_glBindBuffer(target,buffer);
	}
}
void glDeleteBuffers(GLsizei n, GLuint const * buffers)
{
	if(Version(1,5))
	{
		GelLoadFunction(glDeleteBuffers);
		_glDeleteBuffers(n,buffers);
	}
}
void glGenBuffers(GLsizei n, GLuint * buffers)
{
	if(Version(1,5))
	{
		GelLoadFunction(glGenBuffers);
		_glGenBuffers(n,buffers);
	}
}
GLboolean glIsBuffer(GLuint buffer)
{
	if(Version(1,5))
	{
		GelLoadFunction(glIsBuffer);
		return _glIsBuffer(buffer);
	}
	return GL_FALSE;
}
void glBufferData(GLenum target, GLsizeiptr size, GLvoid const * data, GLenum usage)
{
	if(Version(1,5))
	{
		GelLoadFunction(glBufferData);
		_glBufferData(target,size,data,usage);
	}
}
void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid const * data)
{
	if(Version(1,5))
	{
		GelLoadFunction(glBufferSubData);
		_glBufferSubData(target,offset,size,data);
	}
}
void glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid * data)
{
	if(Version(1,5))
	{
		GelLoadFunction(glGetBufferSubData);
		_glGetBufferSubData(target,offset,size,data);
	}
}
GLvoid * glMapBuffer(GLenum target, GLenum access)
{
	if(Version(1,5))
	{
		GelLoadFunction(glMapBuffer);
		return _glMapBuffer(target,access);
	}
	return nullptr;
}
GLboolean glUnmapBuffer(GLenum target)
{
	if(Version(1,5))
	{
		GelLoadFunction(glUnmapBuffer);
		return _glUnmapBuffer(target);
	}
	return GL_FALSE;
}
void glGetBufferParameteriv(GLenum target, GLenum pname, GLint * params)
{
	if(Version(1,5))
	{
		GelLoadFunction(glGetBufferParameteriv);
		_glGetBufferParameteriv(target,pname,params);
	}
}
void glGetBufferPointerv(GLenum target, GLenum pname, GLvoid ** params)
{
	if(Version(1,5))
	{
		GelLoadFunction(glGetBufferPointerv);
		_glGetBufferPointerv(target,pname,params);
	}
}
#endif

#if defined(GL_VERSION_2_0)
void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	if(Version(2,0))
	{
		GelLoadFunction(glBlendEquationSeparate);
		_glBlendEquationSeparate(modeRGB,modeAlpha);
	}
}
void glDrawBuffers(GLsizei n, GLenum const * bufs)
{
	if(Version(2,0))
	{
		GelLoadFunction(glDrawBuffers);
		_glDrawBuffers(n,bufs);
	}
}
void glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
{
	if(Version(2,0))
	{
		GelLoadFunction(glStencilOpSeparate);
		_glStencilOpSeparate(face,sfail,dpfail,dppass);
	}
}
void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
	if(Version(2,0))
	{
		GelLoadFunction(glStencilFuncSeparate);
		_glStencilFuncSeparate(face,func,ref,mask);
	}
}
void glStencilMaskSeparate(GLenum face, GLuint mask)
{
	if(Version(2,0))
	{
		GelLoadFunction(glStencilMaskSeparate);
		_glStencilMaskSeparate(face,mask);
	}
}
void glAttachShader(GLuint program, GLuint shader)
{
	if(Version(2,0))
	{
		GelLoadFunction(glAttachShader);
		_glAttachShader(program,shader);
	}
}
void glBindAttribLocation(GLuint program, GLuint index, GLchar const * name)
{
	if(Version(2,0))
	{
		GelLoadFunction(glBindAttribLocation);
		_glBindAttribLocation(program,index,name);
	}
}
void glCompileShader(GLuint shader)
{
	if(Version(2,0))
	{
		GelLoadFunction(glCompileShader);
		_glCompileShader(shader);
	}
}
GLuint glCreateProgram()
{
	if(Version(2,0))
	{
		GelLoadFunction(glCreateProgram);
		return _glCreateProgram();
	}
	return 0;
}
GLuint glCreateShader(GLenum type)
{
	if(Version(2,0))
	{
		GelLoadFunction(glCreateShader);
		return _glCreateShader(type);
	}
	return 0;
}
void glDeleteProgram(GLuint program)
{
	if(Version(2,0))
	{
		GelLoadFunction(glDeleteProgram);
		_glDeleteProgram(program);
	}
}
void glDeleteShader(GLuint shader)
{
	if(Version(2,0))
	{
		GelLoadFunction(glDeleteShader);
		_glDeleteShader(shader);
	}
}
void glDetachShader(GLuint program, GLuint shader)
{
	if(Version(2,0))
	{
		GelLoadFunction(glDetachShader);
		_glDetachShader(program,shader);
	}
}
void glDisableVertexAttribArray(GLuint index)
{
	if(Version(2,0))
	{
		GelLoadFunction(glDisableVertexAttribArray);
		_glDisableVertexAttribArray(index);
	}
}
void glEnableVertexAttribArray(GLuint index)
{
	if(Version(2,0))
	{
		GelLoadFunction(glEnableVertexAttribArray);
		_glEnableVertexAttribArray(index);
	}
}
void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
{
	if(Version(2,0))
	{
		GelLoadFunction(glGetActiveAttrib);
		_glGetActiveAttrib(program,index,bufSize,length,size,type,name);
	}
}
void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
{
	if(Version(2,0))
	{
		GelLoadFunction(glGetActiveUniform);
		_glGetActiveUniform(program,index,bufSize,length,size,type,name);
	}
}
void glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders)
{
	if(Version(2,0))
	{
		GelLoadFunction(glGetAttachedShaders);
		_glGetAttachedShaders(program,maxCount,count,shaders);
	}
}
GLint glGetAttribLocation(GLuint program, GLchar const * name)
{
	if(Version(2,0))
	{
		GelLoadFunction(glGetAttribLocation);
		return _glGetAttribLocation(program,name);
	}
	return 0;
}
void glGetProgramiv(GLuint program, GLenum pname, GLint * params)
{
	if(Version(2,0))
	{
		GelLoadFunction(glGetProgramiv);
		_glGetProgramiv(program,pname,params);
	}
}
void glGetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei * length, GLchar * infoLog)
{
	if(Version(2,0))
	{
		GelLoadFunction(glGetProgramInfoLog);
		_glGetProgramInfoLog(program,maxLength,length,infoLog);
	}
}
void glGetShaderiv(GLuint shader, GLenum pname, GLint * params)
{
	if(Version(2,0))
	{
		GelLoadFunction(glGetShaderiv);
		_glGetShaderiv(shader,pname,params);
	}
}
void glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei * length, GLchar * infoLog)
{
	if(Version(2,0))
	{
		GelLoadFunction(glGetShaderInfoLog);
		_glGetShaderInfoLog(shader,maxLength,length,infoLog);
	}
}
void glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source)
{
	if(Version(2,0))
	{
		GelLoadFunction(glGetShaderSource);
		_glGetShaderSource(shader,bufSize,length,source);
	}
}
GLint glGetUniformLocation(GLuint program, GLchar const * name)
{
	if(Version(2,0))
	{
		GelLoadFunction(glGetUniformLocation);
		return _glGetUniformLocation(program,name);
	}
	return 0;
}
void glGetUniformfv(GLuint program, GLint location, GLfloat * params)
{
	if(Version(2,0))
	{
		GelLoadFunction(glGetUniformfv);
		_glGetUniformfv(program,location,params);
	}
}
void glGetUniformiv(GLuint program, GLint location, GLint * params)
{
	if(Version(2,0))
	{
		GelLoadFunction(glGetUniformiv);
		_glGetUniformiv(program,location,params);
	}
}
void glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params)
{
	if(Version(2,0))
	{
		GelLoadFunction(glGetVertexAttribdv);
		_glGetVertexAttribdv(index,pname,params);
	}
}
void glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params)
{
	if(Version(2,0))
	{
		GelLoadFunction(glGetVertexAttribfv);
		glGetVertexAttribfv(index,pname,params);
	}
}
void glGetVertexAttribiv(GLuint index, GLenum pname, GLint * params)
{
	if(Version(2,0))
	{
		GelLoadFunction(glGetVertexAttribiv);
		_glGetVertexAttribiv(index,pname,params);
	}
}
void glGetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid ** pointer)
{
	if(Version(2,0))
	{
		GelLoadFunction(glGetVertexAttribPointerv);
		glGetVertexAttribPointerv(index,pname,pointer);
	}
}
GLboolean glIsProgram(GLuint program)
{
	if(Version(2,0))
	{
		GelLoadFunction(glIsProgram);
		return _glIsProgram(program);
	}
	return GL_FALSE;
}
GLboolean glIsShader(GLuint shader)
{
	if(Version(2,0))
	{
		GelLoadFunction(glIsShader);
		return _glIsShader(shader);
	}
	return GL_FALSE;
}
void glLinkProgram(GLuint program)
{
	if(Version(2,0))
	{
		GelLoadFunction(glLinkProgram);
		_glLinkProgram(program);
	}
}
void glShaderSource(GLuint shader, GLsizei count, GLchar const ** string, const GLint * length)
{
	if(Version(2,0))
	{
		GelLoadFunction(glShaderSource);
		_glShaderSource(shader,count,string,length);
	}
}
void glUseProgram(GLuint program)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUseProgram);
		_glUseProgram(program);
	}
}
void glUniform1f(GLint location, GLfloat v0)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniform1f);
		_glUniform1f(location,v0);
	}
}
void glUniform2f(GLint location, GLfloat v0, GLfloat v1)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniform2f);
		_glUniform2f(location,v0,v1);
	}
}
void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniform3f);
		_glUniform3f(location,v0,v1,v2);
	}
}
void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniform4f);
		_glUniform4f(location,v0,v1,v2,v3);
	}
}
void glUniform1i(GLint location, GLint v0)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniform1i);
		_glUniform1i(location,v0);
	}
}
void glUniform2i(GLint location, GLint v0, GLint v1)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniform2i);
		_glUniform2i(location,v0,v1);
	}
}
void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniform3i);
		_glUniform3i(location,v0,v1,v2);
	}
}
void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniform4i);
		_glUniform4i(location,v0,v1,v2,v3);
	}
}
void glUniform1fv(GLint location, GLsizei size, GLfloat const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniform1fv);
		_glUniform1fv(location,size,v);
	}
}
void glUniform2fv(GLint location, GLsizei size, GLfloat const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniform2fv);
		_glUniform2fv(location,size,v);
	}
}
void glUniform3fv(GLint location, GLsizei size, GLfloat const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniform3fv);
		_glUniform3fv(location,size,v);
	}
}
void glUniform4fv(GLint location, GLsizei size, GLfloat const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniform4fv);
		_glUniform4fv(location,size,v);
	}
}
void glUniform1iv(GLint location, GLsizei size, GLint const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniform1iv);
		_glUniform1iv(location,size,v);
	}
}
void glUniform2iv(GLint location, GLsizei size, GLint const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniform2iv);
		_glUniform2iv(location,size,v);
	}
}
void glUniform3iv(GLint location, GLsizei size, GLint const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniform3iv);
		_glUniform3iv(location,size,v);
	}
}
void glUniform4iv(GLint location, GLsizei size, GLint const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniform4iv);
		_glUniform4iv(location,size,v);
	}
}
void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniformMatrix2fv);
		_glUniformMatrix2fv(location,count,transpose,value);
	}
}
void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniformMatrix3fv);
		_glUniformMatrix3fv(location,count,transpose,value);
	}
}
void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	if(Version(2,0))
	{
		GelLoadFunction(glUniformMatrix4fv);
		_glUniformMatrix4fv(location,count,transpose,value);
	}
}
void glValidateProgram(GLuint program)
{
	if(Version(2,0))
	{
		GelLoadFunction(glValidateProgram);
		_glValidateProgram(program);
	}
}
void glVertexAttrib1d(GLuint index, GLdouble v0)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib1d);
		_glVertexAttrib1d(index,v0);
	}
}
void glVertexAttrib1dv(GLuint index, GLdouble const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib1dv);
		_glVertexAttrib1dv(index,v);
	}
}
void glVertexAttrib1f(GLuint index, GLfloat v0)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib1f);
		_glVertexAttrib1f(index,v0);
	}
}
void glVertexAttrib1fv(GLuint index, GLfloat const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib1fv);
		_glVertexAttrib1fv(index,v);
	}
}
void glVertexAttrib1s(GLuint index, GLshort v0)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib1s);
		_glVertexAttrib1s(index,v0);
	}
}
void glVertexAttrib1sv(GLuint index, GLshort const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib1sv);
		_glVertexAttrib1sv(index,v);
	}
}
void glVertexAttrib2d(GLuint index, GLdouble v0, GLdouble v1)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib2d);
		_glVertexAttrib2d(index,v0,v1);
	}
}
void glVertexAttrib2dv(GLuint index, GLdouble const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib2dv);
		_glVertexAttrib2dv(index,v);
	}
}
void glVertexAttrib2f(GLuint index, GLfloat v0, GLfloat v1)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib2f);
		_glVertexAttrib2f(index,v0,v1);
	}
}
void glVertexAttrib2fv(GLuint index, GLfloat const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib2fv);
		_glVertexAttrib2fv(index,v);
	}
}
void glVertexAttrib2s(GLuint index, GLshort v0, GLshort v1)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib2s);
		_glVertexAttrib2s(index,v0,v1);
	}
}
void glVertexAttrib2sv(GLuint index, GLshort const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib2sv);
		_glVertexAttrib2sv(index,v);
	}
}
void glVertexAttrib3d(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib3d);
		_glVertexAttrib3d(index,v0,v1,v2);
	}
}
void glVertexAttrib3dv(GLuint index, GLdouble const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib3dv);
		_glVertexAttrib3dv(index,v);
	}
}
void glVertexAttrib3f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib3f);
		_glVertexAttrib3f(index,v0,v1,v2);
	}
}
void glVertexAttrib3fv(GLuint index, GLfloat const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib3fv);
		_glVertexAttrib3fv(index,v);
	}
}
void glVertexAttrib3s(GLuint index, GLshort v0, GLshort v1, GLshort v2)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib3s);
		_glVertexAttrib3s(index,v0,v1,v2);
	}
}
void glVertexAttrib3sv(GLuint index, GLshort const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib3sv);
		_glVertexAttrib3sv(index,v);
	}
}
void glVertexAttrib4Nbv(GLuint index, GLbyte const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib4Nbv);
		_glVertexAttrib4Nbv(index,v);
	}
}
void glVertexAttrib4Niv(GLuint index, GLint const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib4Niv);
		_glVertexAttrib4Niv(index,v);
	}
}
void glVertexAttrib4Nsv(GLuint index, GLshort const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib4Nsv);
		_glVertexAttrib4Nsv(index,v);
	}
}
void glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib4Nub);
		_glVertexAttrib4Nub(index,x,y,z,w);
	}
}
void glVertexAttrib4Nubv(GLuint index, GLubyte const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib4Nubv);
		_glVertexAttrib4Nubv(index,v);
	}
}
void glVertexAttrib4Nuiv(GLuint index, GLuint const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib4Nuiv);
		_glVertexAttrib4Nuiv(index,v);
	}
}
void glVertexAttrib4Nusv(GLuint index, GLushort const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib4Nusv);
		_glVertexAttrib4Nusv(index,v);
	}
}
void glVertexAttrib4bv(GLuint index, GLbyte const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib4bv);
		_glVertexAttrib4bv(index,v);
	}
}
void glVertexAttrib4d(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib4d);
		_glVertexAttrib4d(index,v0,v1,v2,v3);
	}
}
void glVertexAttrib4dv(GLuint index, GLdouble const * v)
{
	if(Version(2,0))
	{
		GelLoadFunction(glVertexAttrib4dv);
		_glVertexAttrib4dv(index,v);
	}
}
void glVertexAttrib4f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    if(Version(2,0))
    {
        GelLoadFunction(glVertexAttrib4f);
        _glVertexAttrib4f(index,v0,v1,v2,v3);
    }
}
void glVertexAttrib4fv(GLuint index, GLfloat const  *v)
{
    if(Version(2,0))
    {
        GelLoadFunction(glVertexAttrib4fv);
        _glVertexAttrib4fv(index,v);
    }
}
void glVertexAttrib4iv(GLuint index, GLint const * v)
{
    if(Version(2,0))
    {
        GelLoadFunction(glVertexAttrib4iv);
        _glVertexAttrib4iv(index,v);
    }
}
void glVertexAttrib4s(GLuint index, GLshort v0, GLshort v1, GLshort v2, GLshort v3)
{
    if(Version(2,0))
    {
        GelLoadFunction(glVertexAttrib4s);
        _glVertexAttrib4s(index,v0,v1,v2,v3);
    }
}
void glVertexAttrib4sv(GLuint index, GLshort const * v)
{
    if(Version(2,0))
    {
        GelLoadFunction(glVertexAttrib4sv);
        _glVertexAttrib4sv(index,v);
    }
}
void glVertexAttrib4ubv(GLuint index, GLubyte const * v)
{
    if(Version(2,0))
    {
        GelLoadFunction(glVertexAttrib4ubv);
        _glVertexAttrib4ubv(index,v);
    }
}
void glVertexAttrib4uiv(GLuint index, GLuint const * v)
{
    if(Version(2,0))
    {
        GelLoadFunction(glVertexAttrib4uiv);
        _glVertexAttrib4uiv(index,v);
    }
}
void glVertexAttrib4usv(GLuint index, GLushort const * v)
{
    if(Version(2,0))
    {
        GelLoadFunction(glVertexAttrib4usv);
        _glVertexAttrib4usv(index,v);
    }
}
void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid const * pointer)
{
    if(Version(2,0))
    {
        GelLoadFunction(glVertexAttribPointer);
        _glVertexAttribPointer(index,size,type,normalized,stride,pointer);
    }
}
#endif

#if defined(GL_VERSION_2_1)
void glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
    if(Version(2,1))
    {
        GelLoadFunction(glUniformMatrix2x3fv);
        _glUniformMatrix2x3fv(location,count,transpose,value);
    }
}
void glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
    if(Version(2,1))
    {
        GelLoadFunction(glUniformMatrix3x2fv);
        _glUniformMatrix3x2fv(location,count,transpose,value);
    }
}
void glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
    if(Version(2,1))
    {
        GelLoadFunction(glUniformMatrix2x4fv);
        _glUniformMatrix2x4fv(location,count,transpose,value);
    }
}
void glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
    if(Version(2,1))
    {
        GelLoadFunction(glUniformMatrix4x2fv);
        _glUniformMatrix4x2fv(location,count,transpose,value);
    }
}
void glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
    if(Version(2,1))
    {
        GelLoadFunction(glUniformMatrix3x4fv);
        _glUniformMatrix3x4fv(location,count,transpose,value);
    }
}
void glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
    if(Version(2,1))
    {
        GelLoadFunction(glUniformMatrix4x3fv);
        _glUniformMatrix4x3fv(location,count,transpose,value);
    }
}
#endif

#if defined(GL_VERSION_3_0)
//reused functions from ARB_framebuffer_object
GLboolean glIsRenderbuffer(GLuint renderbuffer)
{
    if(Version(3,0))
    {
        GelLoadFunction(glIsRenderbuffer);
        return _glIsRenderbuffer(renderbuffer);
    }
	return GL_FALSE;
}
void glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
    if(Version(3,0))
    {
        GelLoadFunction(glBindRenderbuffer);
        _glBindRenderbuffer(target,renderbuffer);
    }
}
void glDeleteRenderbuffers(GLsizei n, GLuint const * renderbuffers)
{
    if(Version(3,0))
    {
        GelLoadFunction(glDeleteRenderbuffers);
        _glDeleteRenderbuffers(n,renderbuffers);
    }
}
void glGenRenderbuffers(GLsizei n, GLuint * renderbuffers)
{
    if(Version(3,0))
    {
        GelLoadFunction(glGenRenderbuffers);
        _glGenRenderbuffers(n,renderbuffers);
    }
}
void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
    if(Version(3,0))
    {
        GelLoadFunction(glRenderbufferStorage);
        _glRenderbufferStorage(target,internalformat,width,height);
    }
}
void glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params)
{
    if(Version(3,0))
    {
        GelLoadFunction(glGetRenderbufferParameteriv);
        _glGetRenderbufferParameteriv(target,pname,params);
    }
}
GLboolean glIsFramebuffer(GLuint framebuffer)
{
    if(Version(3,0))
    {
        GelLoadFunction(glIsFramebuffer);
        return _glIsFramebuffer(framebuffer);
    }
	return GL_FALSE;
}
void glBindFramebuffer(GLenum target, GLuint framebuffer)
{
    if(Version(3,0))
    {
        GelLoadFunction(glBindFramebuffer);
        _glBindFramebuffer(target,framebuffer);
    }
}
void glDeleteFramebuffers(GLsizei n, GLuint const * framebuffers)
{
    if(Version(3,0))
    {
        GelLoadFunction(glDeleteFramebuffers);
        _glDeleteFramebuffers(n,framebuffers);
    }
}
void glGenFramebuffers(GLsizei n, GLuint * framebuffers)
{
    if(Version(3,0))
    {
        GelLoadFunction(glGenFramebuffers);
        _glGenFramebuffers(n,framebuffers);
    }
}
GLenum glCheckFramebufferStatus(GLenum target)
{
    if(Version(3,0))
    {
        GelLoadFunction(glCheckFramebufferStatus);
        return _glCheckFramebufferStatus(target);
    }
	return 0;
}
void glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    if(Version(3,0))
    {
        GelLoadFunction(glFramebufferTexture1D);
        _glFramebufferTexture1D(target,attachment,textarget,texture,level);
    }
}
void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    if(Version(3,0))
    {
        GelLoadFunction(glFramebufferTexture2D);
        _glFramebufferTexture2D(target,attachment,textarget,texture,level);
    }
}
void glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
{
    if(Version(3,0))
    {
        GelLoadFunction(glFramebufferTexture3D);
        _glFramebufferTexture3D(target,attachment,textarget,texture,level,zoffset);
    }
}
void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
    if(Version(3,0))
    {
        GelLoadFunction(glFramebufferRenderbuffer);
        _glFramebufferRenderbuffer(target,attachment,renderbuffertarget,renderbuffer);
    }
}
void glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params)
{
    if(Version(3,0))
    {
        GelLoadFunction(glGetFramebufferAttachmentParameteriv);
        _glGetFramebufferAttachmentParameteriv(target,attachment,pname,params);
    }
}
void glGenerateMipmap(GLenum target)
{
    if(Version(3,0))
    {
        GelLoadFunction(glGenerateMipmap);
        _glGenerateMipmap(target);
    }
}
void glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
    if(Version(3,0))
    {
        GelLoadFunction(glBlitFramebuffer);
        _glBlitFramebuffer(srcX0,srcY0,srcX1,srcY1,dstX0,dstY0,dstX1,dstY1,mask,filter);
    }
}
void glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
    if(Version(3,0))
    {
        GelLoadFunction(glRenderbufferStorageMultisample);
        _glRenderbufferStorageMultisample(target,samples,internalformat,width,height);
    }
}
void glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
    if(Version(3,0))
    {
        GelLoadFunction(glFramebufferTextureLayer);
        _glFramebufferTextureLayer(target,attachment,texture,level,layer);
    }
}

//reused functions from ARB_map_buffer_range
GLvoid * glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
	if(Version(3,0))
	{
		GelLoadFunction(glMapBufferRange);
		return _glMapBufferRange(target,offset,length,access);
	}
	return nullptr;
}
void glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length)
{
	if(Version(3,0))
	{
		GelLoadFunction(glFlushMappedBufferRange);
		_glFlushMappedBufferRange(target,offset,length);
	}
}

//reused functions from ARB_vertex_array_object
void glBindVertexArray(GLuint array)
{
	if(Version(3,0))
	{
		GelLoadFunction(glBindVertexArray);
		_glBindVertexArray(array);
	}
}
void glDeleteVertexArrays(GLsizei n, GLuint const * arrays)
{
	if(Version(3,0))
	{
		GelLoadFunction(glDeleteVertexArrays);
		_glDeleteVertexArrays(n,arrays);
	}
}
void glGenVertexArrays(GLsizei n, GLuint * arrays)
{
	if(Version(3,0))
	{
		GelLoadFunction(glGenVertexArrays);
		_glGenVertexArrays(n,arrays);
	}
}
GLboolean glIsVertexArray(GLuint array)
{
	if(Version(3,0))
	{
		GelLoadFunction(glIsVertexArray);
		return _glIsVertexArray(array);
	}
	return GL_FALSE;
}

//functions introduced in OpenGL 3.0
void glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
{
	if(Version(3,0))
	{
		GelLoadFunction(glColorMaski);
		_glColorMaski(index,r,g,b,a);
	}
}
void glGetBooleani_v(GLenum target, GLuint index, GLboolean * data)
{
	if(Version(3,0))
	{
		GelLoadFunction(glGetBooleani_v);
		_glGetBooleani_v(target,index,data);
	}
}
void glGetIntegeri_v(GLenum target, GLuint index, GLint * data)
{
	if(Version(3,0))
	{
		GelLoadFunction(glGetIntegeri_v);
		_glGetIntegeri_v(target,index,data);
	}
}
void glEnablei(GLenum target, GLuint index)
{
	if(Version(3,0))
	{
		GelLoadFunction(glEnablei);
		_glEnablei(target,index);
	}
}
void glDisablei(GLenum target, GLuint index)
{
	if(Version(3,0))
	{
		GelLoadFunction(glDisablei);
		_glDisablei(target,index);
	}
}
GLboolean glIsEnabledi(GLenum target, GLuint index)
{
	if(Version(3,0))
	{
		GelLoadFunction(glIsEnabledi);
		return _glIsEnabledi(target,index);
	}
	return GL_FALSE;
}
void glBeginTransformFeedback(GLenum primitiveMode)
{
	if(Version(3,0))
	{
		GelLoadFunction(glBeginTransformFeedback);
		_glBeginTransformFeedback(primitiveMode);
	}
}
void glEndTransformFeedback()
{
	if(Version(3,0))
	{
		GelLoadFunction(glEndTransformFeedback);
		_glEndTransformFeedback();
	}
}
void glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
	if(Version(3,0))
	{
		GelLoadFunction(glBindBufferRange);
		_glBindBufferRange(target,index,buffer,offset,size);
	}
}
void glBindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
	if(Version(3,0))
	{
		GelLoadFunction(glBindBufferBase);
		_glBindBufferBase(target,index,buffer);
	}
}
void glTransformFeedbackVaryings(GLuint program, GLsizei count, GLchar const * const * varyings, GLenum bufferMode)
{
	if(Version(3,0))
	{
		GelLoadFunction(glTransformFeedbackVaryings);
		_glTransformFeedbackVaryings(program,count,varyings,bufferMode);
	}
}
void glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name)
{
	if(Version(3,0))
	{
		GelLoadFunction(glGetTransformFeedbackVarying);
		_glGetTransformFeedbackVarying(program,index,bufSize,length,size,type,name);
	}
}
void glClampColor(GLenum target, GLenum clamp)
{
	if(Version(3,0))
	{
		GelLoadFunction(glClampColor);
		_glClampColor(target,clamp);
	}
}
void glBeginConditionalRender(GLuint id, GLenum mode)
{
	if(Version(3,0))
	{
		GelLoadFunction(glBeginConditionalRender);
		_glBeginConditionalRender(id,mode);
	}
}
void glEndConditionalRender()
{
	if(Version(3,0))
	{
		GelLoadFunction(glEndConditionalRender);
		_glEndConditionalRender();
	}
}
void glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, GLvoid const * pointer)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribIPointer);
		_glVertexAttribIPointer(index,size,type,stride,pointer);
	}
}
void glGetVertexAttribIiv(GLuint index, GLenum pname, GLint * params)
{
	if(Version(3,0))
	{
		GelLoadFunction(glGetVertexAttribIiv);
		_glGetVertexAttribIiv(index,pname,params);
	}
}
void glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params)
{
	if(Version(3,0))
	{
		GelLoadFunction(glGetVertexAttribIuiv);
		_glGetVertexAttribIuiv(index,pname,params);
	}
}
void glVertexAttribI1i(GLuint index, GLint x)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI1i);
		_glVertexAttribI1i(index,x);
	}
}
void glVertexAttribI2i(GLuint index, GLint x, GLint y)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI2i);
		_glVertexAttribI2i(index,x,y);
	}
}
void glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI3i);
		_glVertexAttribI3i(index,x,y,z);
	}
}
void glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI4i);
		_glVertexAttribI4i(index,x,y,z,w);
	}
}
void glVertexAttribI1ui(GLuint index, GLuint x)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI1ui);
		_glVertexAttribI1ui(index,x);
	}
}
void glVertexAttribI2ui(GLuint index, GLuint x, GLuint y)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI2ui);
		_glVertexAttribI2ui(index,x,y);
	}
}
void glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI3ui);
		_glVertexAttribI3ui(index,x,y,z);
	}
}
void glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI4ui);
		_glVertexAttribI4ui(index,x,y,z,w);
	}
}
void glVertexAttribI1iv(GLuint index, GLint const * v)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI1iv);
		_glVertexAttribI1iv(index,v);
	}
}
void glVertexAttribI2iv(GLuint index, GLint const * v)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI2iv);
		_glVertexAttribI2iv(index,v);
	}
}
void glVertexAttribI3iv(GLuint index, GLint const * v)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI3iv);
		_glVertexAttribI3iv(index,v);
	}
}
void glVertexAttribI4iv(GLuint index, GLint const * v)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI4iv);
		_glVertexAttribI4iv(index,v);
	}
}
void glVertexAttribI1uiv(GLuint index, GLuint const * v)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI1uiv);
		_glVertexAttribI1uiv(index,v);
	}
}
void glVertexAttribI2uiv(GLuint index, GLuint const * v)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI2uiv);
		_glVertexAttribI2uiv(index,v);
	}
}
void glVertexAttribI3uiv(GLuint index, GLuint const * v)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI3uiv);
		_glVertexAttribI3uiv(index,v);
	}
}
void glVertexAttribI4uiv(GLuint index, GLuint const * v)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI4uiv);
		_glVertexAttribI4uiv(index,v);
	}
}
void glVertexAttribI4bv(GLuint index, GLbyte const * v)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI4bv);
		_glVertexAttribI4bv(index,v);
	}
}
void glVertexAttribI4sv(GLuint index, GLshort const * v)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI4sv);
		_glVertexAttribI4sv(index,v);
	}
}
void glVertexAttribI4ubv(GLuint index, GLubyte const * v)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI4ubv);
		_glVertexAttribI4ubv(index,v);
	}
}
void glVertexAttribI4usv(GLuint index, GLushort const * v)
{
	if(Version(3,0))
	{
		GelLoadFunction(glVertexAttribI4usv);
		_glVertexAttribI4usv(index,v);
	}
}
void glGetUniformuiv(GLuint program, GLint location, GLuint * params)
{
	if(Version(3,0))
	{
		GelLoadFunction(glGetUniformuiv);
		_glGetUniformuiv(program,location,params);
	}
}
void glBindFragDataLocation(GLuint program, GLuint color, GLchar const * name)
{
	if(Version(3,0))
	{
		GelLoadFunction(glBindFragDataLocation);
		_glBindFragDataLocation(program,color,name);
	}
}
GLint glGetFragDataLocation(GLuint program, GLchar const * name)
{
	if(Version(3,0))
	{
		GelLoadFunction(glGetFragDataLocation);
		return _glGetFragDataLocation(program,name);
	}
	return 0;
}
void glUniform1ui(GLint location, GLuint v0)
{
	if(Version(3,0))
	{
		GelLoadFunction(glUniform1ui);
		_glUniform1ui(location,v0);
	}
}
void glUniform2ui(GLint location, GLuint v0, GLuint v1)
{
	if(Version(3,0))
	{
		GelLoadFunction(glUniform2ui);
		_glUniform2ui(location,v0,v1);
	}
}
void glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
{
	if(Version(3,0))
	{
		GelLoadFunction(glUniform3ui);
		_glUniform3ui(location,v0,v1,v2);
	}
}
void glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	if(Version(3,0))
	{
		GelLoadFunction(glUniform4ui);
		_glUniform4ui(location,v0,v1,v2,v3);
	}
}
void glUniform1uiv(GLint location, GLsizei count, GLuint const * value)
{
	if(Version(3,0))
	{
		GelLoadFunction(glUniform1uiv);
		_glUniform1uiv(location,count,value);
	}
}
void glUniform2uiv(GLint location, GLsizei count, GLuint const * value)
{
	if(Version(3,0))
	{
		GelLoadFunction(glUniform2uiv);
		_glUniform2uiv(location,count,value);
	}
}
void glUniform3uiv(GLint location, GLsizei count, GLuint const * value)
{
	if(Version(3,0))
	{
		GelLoadFunction(glUniform3uiv);
		_glUniform3uiv(location,count,value);
	}
}
void glUniform4uiv(GLint location, GLsizei count, GLuint const * value)
{
	if(Version(3,0))
	{
		GelLoadFunction(glUniform4uiv);
		_glUniform4uiv(location,count,value);
	}
}
void glTexParameterIiv(GLenum target, GLenum pname, GLint const * params)
{
	if(Version(3,0))
	{
		GelLoadFunction(glTexParameterIiv);
		_glTexParameterIiv(target,pname,params);
	}
}
void glTexParameterIuiv(GLenum target, GLenum pname, GLuint const * params)
{
	if(Version(3,0))
	{
		GelLoadFunction(glTexParameterIuiv);
		_glTexParameterIuiv(target,pname,params);
	}
}
void glGetTexParameterIiv(GLenum target, GLenum pname, GLint * params)
{
	if(Version(3,0))
	{
		GelLoadFunction(glGetTexParameterIiv);
		_glGetTexParameterIiv(target,pname,params);
	}
}
void glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params)
{
	if(Version(3,0))
	{
		GelLoadFunction(glGetTexParameterIuiv);
		_glGetTexParameterIuiv(target,pname,params);
	}
}
void glClearBufferiv(GLenum buffer, GLint drawbuffer, GLint const * value)
{
	if(Version(3,0))
	{
		GelLoadFunction(glClearBufferiv);
		_glClearBufferiv(buffer,drawbuffer,value);
	}
}
void glClearBufferuiv(GLenum buffer, GLint drawbuffer, GLuint const * value)
{
	if(Version(3,0))
	{
		GelLoadFunction(glClearBufferuiv);
		_glClearBufferuiv(buffer,drawbuffer,value);
	}
}
void glClearBufferfv(GLenum buffer, GLint drawbuffer, GLfloat const * value)
{
	if(Version(3,0))
	{
		GelLoadFunction(glClearBufferfv);
		_glClearBufferfv(buffer,drawbuffer,value);
	}
}
void glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
{
	if(Version(3,0))
	{
		GelLoadFunction(glClearBufferfi);
		_glClearBufferfi(buffer,drawbuffer,depth,stencil);
	}
}
GLubyte const * glGetStringi(GLenum name, GLuint index)
{
	if(Version(3,0))
	{
		GelLoadFunction(glGetStringi);
		return _glGetStringi(name,index);
	}
	return nullptr;
}
#endif

#if defined(GL_VERSION_3_1)
//reused functions from ARB_copy_buffer
void glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
	if(Version(3,1))
	{
		GelLoadFunction(glCopyBufferSubData);
		_glCopyBufferSubData(readTarget,writeTarget,readOffset,writeOffset,size);
	}
}

//reused functions from ARB_uniform_buffer_object
void glGetUniformIndices(GLuint program, GLsizei uniformCount, GLchar const * const * uniformNames, GLuint * uniformIndices)
{
	if(Version(3,1))
	{
		GelLoadFunction(glGetUniformIndices);
		_glGetUniformIndices(program,uniformCount,uniformNames,uniformIndices);
	}
}
void glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, GLuint const * uniformIndices, GLenum pname, GLint * params)
{
	if(Version(3,1))
	{
		GelLoadFunction(glGetActiveUniformsiv);
		_glGetActiveUniformsiv(program,uniformCount,uniformIndices,pname,params);
	}
}
void glGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName)
{
	if(Version(3,1))
	{
		GelLoadFunction(glGetActiveUniformName);
		_glGetActiveUniformName(program,uniformIndex,bufSize,length,uniformName);
	}
}
GLuint glGetUniformBlockIndex(GLuint program, GLchar const * uniformBlockName)
{
	if(Version(3,1))
	{
		GelLoadFunction(glGetUniformBlockIndex);
		return _glGetUniformBlockIndex(program,uniformBlockName);
	}
	return 0;
}
void glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params)
{
	if(Version(3,1))
	{
		GelLoadFunction(glGetActiveUniformBlockiv);
		_glGetActiveUniformBlockiv(program,uniformBlockIndex,pname,params);
	}
}
void glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName)
{
	if(Version(3,1))
	{
		GelLoadFunction(glGetActiveUniformBlockName);
		_glGetActiveUniformBlockName(program,uniformBlockIndex,bufSize,length,uniformBlockName);
	}
}
void glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
{
	if(Version(3,1))
	{
		GelLoadFunction(glUniformBlockBinding);
		_glUniformBlockBinding(program,uniformBlockIndex,uniformBlockBinding);
	}
}

//functions introduced in OpenGL 3.1
void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)
{
	if(Version(3,1))
	{
		GelLoadFunction(glDrawArraysInstanced);
		_glDrawArraysInstanced(mode,first,count,instancecount);
	}
}
void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, GLvoid const * indices, GLsizei instancecount)
{
	if(Version(3,1))
	{
		GelLoadFunction(glDrawElementsInstanced);
		_glDrawElementsInstanced(mode,count,type,indices,instancecount);
	}
}
void glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer)
{
	if(Version(3,1))
	{
		GelLoadFunction(glTexBuffer);
		_glTexBuffer(target,internalformat,buffer);
	}
}
void glPrimitiveRestartIndex(GLuint index)
{
	if(Version(3,1))
	{
		GelLoadFunction(glPrimitiveRestartIndex);
		_glPrimitiveRestartIndex(index);
	}
}
#endif

#if defined(GL_VERSION_3_2)
//reused functions from ARB_draw_elements_base_vertex
void glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, GLvoid const * indices, GLint basevertex)
{
	if(Version(3,2))
	{
		GelLoadFunction(glDrawElementsBaseVertex);
		_glDrawElementsBaseVertex(mode,count,type,indices,basevertex);
	}
}
void glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, GLvoid const * indices, GLint basevertex)
{
	if(Version(3,2))
	{
		GelLoadFunction(glDrawRangeElementsBaseVertex);
		_glDrawRangeElementsBaseVertex(mode,start,end,count,type,indices,basevertex);
	}
}
void glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, GLvoid const * indices, GLsizei primcount, GLint basevertex)
{
	if(Version(3,2))
	{
		GelLoadFunction(glDrawElementsInstancedBaseVertex);
		_glDrawElementsInstancedBaseVertex(mode,count,type,indices,primcount,basevertex);
	}
}
void glMultiDrawElementsBaseVertex(GLenum mode, GLsizei const * count, GLenum type, GLvoid const * const * indices, GLsizei primcount, GLint const * basevertex)
{
	if(Version(3,2))
	{
		GelLoadFunction(glMultiDrawElementsBaseVertex);
		_glMultiDrawElementsBaseVertex(mode,count,type,indices,primcount,basevertex);
	}
}

//reused functions from ARB_provoking_vertex
void glProvokingVertex(GLenum provokeMode)
{
	if(Version(3,2))
	{
		GelLoadFunction(glProvokingVertex);
		_glProvokingVertex(provokeMode);
	}
}

//reused functions from ARB_sync
GLsync glFenceSync(GLenum condition, GLbitfield flags)
{
	if(Version(3,2))
	{
		GelLoadFunction(glFenceSync);
		return _glFenceSync(condition,flags);
	}
	return nullptr;
}
GLboolean glIsSync(GLsync sync)
{
	if(Version(3,2))
	{
		GelLoadFunction(glIsSync);
		return _glIsSync(sync);
	}
	return GL_FALSE;
}
void glDeleteSync(GLsync sync)
{
	if(Version(3,2))
	{
		GelLoadFunction(glDeleteSync);
		_glDeleteSync(sync);
	}
}
GLenum glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
	if(Version(3,2))
	{
		GelLoadFunction(glClientWaitSync);
		return _glClientWaitSync(sync,flags,timeout);
	}
	return 0;
}
void glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
	if(Version(3,2))
	{
		GelLoadFunction(glWaitSync);
		_glWaitSync(sync,flags,timeout);
	}
}
void glGetInteger64v(GLenum pname, GLint64 * params)
{
	if(Version(3,2))
	{
		GelLoadFunction(glGetInteger64v);
		_glGetInteger64v(pname,params);
	}
}
void glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values)
{
	if(Version(3,2))
	{
		GelLoadFunction(glGetSynciv);
		_glGetSynciv(sync,pname,bufSize,length,values);
	}
}

//reused functions from ARB_texture_multisample
void glTexImage2DMultisample(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	if(Version(3,2))
	{
		GelLoadFunction(glTexImage2DMultisample);
		_glTexImage2DMultisample(target,samples,internalformat,width,height,fixedsamplelocations);
	}
}
void glTexImage3DMultisample(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	if(Version(3,2))
	{
		GelLoadFunction(glTexImage3DMultisample);
		_glTexImage3DMultisample(target,samples,internalformat,width,height,depth,fixedsamplelocations);
	}
}
void glGetMultisamplefv(GLenum pname, GLuint index, GLfloat * val)
{
	if(Version(3,2))
	{
		GelLoadFunction(glGetMultisamplefv);
		_glGetMultisamplefv(pname,index,val);
	}
}
void glSampleMaski(GLuint index, GLbitfield mask)
{
	if(Version(3,2))
	{
		GelLoadFunction(glSampleMaski);
		_glSampleMaski(index,mask);
	}
}

//functions introduced in OpenGL 3.2
void glGetInteger64i_v(GLenum target, GLuint index, GLint64 * data)
{
	if(Version(3,2))
	{
		GelLoadFunction(glGetInteger64i_v);
		_glGetInteger64i_v(target,index,data);
	}
}
void glGetBufferParameteri64v(GLenum target, GLenum value, GLint64 * data)
{
	if(Version(3,2))
	{
		GelLoadFunction(glGetBufferParameteri64v);
		_glGetBufferParameteri64v(target,value,data);
	}
}
void glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
{
	if(Version(3,2))
	{
		GelLoadFunction(glFramebufferTexture);
		_glFramebufferTexture(target,attachment,texture,level);
	}
}
#endif

#if defined(GL_VERSION_3_3)
//reused functions from ARB_blend_func_extended
void glBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, GLchar const * name)
{
    if(Version(3,3))
    {
        GelLoadFunction(glBindFragDataLocationIndexed);
        _glBindFragDataLocationIndexed(program,colorNumber,index,name);
    }
}
GLint glGetFragDataIndex(GLuint program, GLchar const * name)
{
    if(Version(3,3))
    {
        GelLoadFunction(glGetFragDataIndex);
        return _glGetFragDataIndex(program,name);
    }
    return 0;
}

//reused functions from ARB_sampler_objects
void glGenSamplers(GLsizei n, GLuint * samplers)
{
    if(Version(3,3))
    {
        GelLoadFunction(glGenSamplers);
        _glGenSamplers(n,samplers);
    }
}
void glDeleteSamplers(GLsizei n, GLuint const * samplers)
{
    if(Version(3,3))
    {
        GelLoadFunction(glDeleteSamplers);
        _glDeleteSamplers(n,samplers);
    }
}
GLboolean glIsSampler(GLuint id)
{
    if(Version(3,3))
    {
        GelLoadFunction(glIsSampler);
        return _glIsSampler(id);
    }
    return GL_FALSE;
}
void glBindSampler(GLuint unit, GLuint sampler)
{
    if(Version(3,3))
    {
        GelLoadFunction(glBindSampler);
        _glBindSampler(unit,sampler);
    }
}
void glSamplerParameteri(GLuint sampler, GLenum pname, GLint param)
{
    if(Version(3,3))
    {
        GelLoadFunction(glSamplerParameteri);
        _glSamplerParameteri(sampler,pname,param);
    }
}
void glSamplerParameteriv(GLuint sampler, GLenum pname, GLint const * params)
{
    if(Version(3,3))
    {
        GelLoadFunction(glSamplerParameteriv);
        _glSamplerParameteriv(sampler,pname,params);
    }
}
void glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param)
{
    if(Version(3,3))
    {
        GelLoadFunction(glSamplerParameterf);
		_glSamplerParameterf(sampler,pname,param);
    }
}
void glSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat const * params)
{
	if(Version(3,3))
	{
		GelLoadFunction(glSamplerParameterfv);
		_glSamplerParameterfv(sampler,pname,params);
	}
}
void glSamplerParameterIiv(GLuint sampler, GLenum pname, GLint const * params)
{
	if(Version(3,3))
	{
		GelLoadFunction(glSamplerParameterIiv);
		_glSamplerParameterIiv(sampler,pname,params);
	}
}
void glSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint const * params)
{
	if(Version(3,3))
	{
		GelLoadFunction(glSamplerParameterIuiv);
		_glSamplerParameterIuiv(sampler,pname,params);
	}
}
void glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint * params)
{
	if(Version(3,3))
	{
		GelLoadFunction(glGetSamplerParameteriv);
		_glGetSamplerParameteriv(sampler,pname,params);
	}
}
void glGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint * params)
{
	if(Version(3,3))
	{
		GelLoadFunction(glGetSamplerParameterIiv);
		_glGetSamplerParameterIiv(sampler,pname,params);
	}
}
void glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat * params)
{
	if(Version(3,3))
	{
		GelLoadFunction(glGetSamplerParameterfv);
		_glGetSamplerParameterfv(sampler,pname,params);
	}
}
void glGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint * params)
{
	if(Version(3,3))
	{
		GelLoadFunction(glGetSamplerParameterIuiv);
		_glGetSamplerParameterIuiv(sampler,pname,params);
	}
}

//reused functions from ARB_timer_query
void glQueryCounter(GLuint id, GLenum target)
{
	if(Version(3,3))
	{
		GelLoadFunction(glQueryCounter);
		_glQueryCounter(id,target);
	}
}
void glGetQueryObjecti64v(GLuint id, GLenum pname, GLint64 * params)
{
	if(Version(3,3))
	{
		GelLoadFunction(glGetQueryObjecti64v);
		_glGetQueryObjecti64v(id,pname,params);
	}
}
void glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 * params)
{
	if(Version(3,3))
	{
		GelLoadFunction(glGetQueryObjectui64v);
		_glGetQueryObjectui64v(id,pname,params);
	}
}

//reused functions from ARB_vertex_type_2_10_10_10_rev
//removed fixed-function rendering functions
void glVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	if(Version(3,3))
	{
		GelLoadFunction(glVertexAttribP1ui);
		_glVertexAttribP1ui(index,type,normalized,value);
	}
}
void glVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	if(Version(3,3))
	{
		GelLoadFunction(glVertexAttribP2ui);
		_glVertexAttribP2ui(index,type,normalized,value);
	}
}
void glVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	if(Version(3,3))
	{
		GelLoadFunction(glVertexAttribP3ui);
		_glVertexAttribP3ui(index,type,normalized,value);
	}
}
void glVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	if(Version(3,3))
	{
		GelLoadFunction(glVertexAttribP4ui);
		_glVertexAttribP4ui(index,type,normalized,value);
	}
}

//functions introduced in OpenGL 3.3
void glVertexAttribDivisor(GLuint index, GLuint divisor)
{
	if(Version(3,3))
	{
		GelLoadFunction(glVertexAttribDivisor);
		_glVertexAttribDivisor(index,divisor);
	}
}
#endif

#if defined(GL_VERSION_4_0)
//reused functions from ARB_draw_indirect
void glDrawArraysIndirect(GLenum mode, GLvoid const * indirect)
{
	if(Version(4,0))
	{
		GelLoadFunction(glDrawArraysIndirect);
		_glDrawArraysIndirect(mode,indirect);
	}
}
void glDrawElementsIndirect(GLenum mode, GLenum type, GLvoid const * indirect)
{
	if(Version(4,0))
	{
		GelLoadFunction(glDrawElementsIndirect);
		_glDrawElementsIndirect(mode,type,indirect);
	}
}

//reused functions from ARB_gpu_shader_fp64
void glUniform1d(GLint location, GLdouble x)
{
	if(Version(4,0))
	{
		GelLoadFunction(glUniform1d);
		_glUniform1d(location,x);
	}
}
void glUniform2d(GLint location, GLdouble x, GLdouble y)
{
	if(Version(4,0))
	{
		GelLoadFunction(glUniform2d);
		_glUniform2d(location,x,y);
	}
}
void glUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z)
{
	if(Version(4,0))
	{
		GelLoadFunction(glUniform3d);
		_glUniform3d(location,x,y,z);
	}
}
void glUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	if(Version(4,0))
	{
		GelLoadFunction(glUniform4d);
		_glUniform4d(location,x,y,z,w);
	}
}
void glUniform1dv(GLint location, GLsizei count, GLdouble const * value)
{
	if(Version(4,0))
	{
		GelLoadFunction(glUniform1dv);
		_glUniform1dv(location,count,value);
	}
}
void glUniform2dv(GLint location, GLsizei count, GLdouble const * value)
{
	if(Version(4,0))
	{
		GelLoadFunction(glUniform2dv);
		_glUniform2dv(location,count,value);
	}
}
void glUniform3dv(GLint location, GLsizei count, GLdouble const * value)
{
	if(Version(4,0))
	{
		GelLoadFunction(glUniform3dv);
		_glUniform3dv(location,count,value);
	}
}
void glUniform4dv(GLint location, GLsizei count, GLdouble const * value)
{
	if(Version(4,0))
	{
		GelLoadFunction(glUniform4dv);
		_glUniform4dv(location,count,value);
	}
}
void glUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	if(Version(4,0))
	{
		GelLoadFunction(glUniformMatrix2dv);
		_glUniformMatrix2dv(location,count,transpose,value);
	}
}
void glUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	if(Version(4,0))
	{
		GelLoadFunction(glUniformMatrix3dv);
		_glUniformMatrix3dv(location,count,transpose,value);
	}
}
void glUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	if(Version(4,0))
	{
		GelLoadFunction(glUniformMatrix4dv);
		_glUniformMatrix4dv(location,count,transpose,value);
	}
}
void glUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	if(Version(4,0))
	{
		GelLoadFunction(glUniformMatrix2x3dv);
		_glUniformMatrix2x3dv(location,count,transpose,value);
	}
}
void glUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	if(Version(4,0))
	{
		GelLoadFunction(glUniformMatrix2x4dv);
		_glUniformMatrix2x4dv(location,count,transpose,value);
	}
}
void glUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	if(Version(4,0))
	{
		GelLoadFunction(glUniformMatrix3x2dv);
		_glUniformMatrix3x2dv(location,count,transpose,value);
	}
}
void glUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	if(Version(4,0))
	{
		GelLoadFunction(glUniformMatrix3x4dv);
		_glUniformMatrix3x4dv(location,count,transpose,value);
	}
}
void glUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	if(Version(4,0))
	{
		GelLoadFunction(glUniformMatrix4x2dv);
		_glUniformMatrix4x2dv(location,count,transpose,value);
	}
}
void glUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	if(Version(4,0))
	{
		GelLoadFunction(glUniformMatrix4x3dv);
		_glUniformMatrix4x3dv(location,count,transpose,value);
	}
}
void glGetUniformdv(GLuint program, GLint location, GLdouble * params)
{
	if(Version(4,0))
	{
		GelLoadFunction(glGetUniformdv);
		_glGetUniformdv(program,location,params);
	}
}

//reused functions from ARB_shader_subroutine
GLint glGetSubroutineUniformLocation(GLuint program, GLenum shadertype, GLchar const * name)
{
	if(Version(4,0))
	{
		GelLoadFunction(glGetSubroutineUniformLocation);
		return _glGetSubroutineUniformLocation(program,shadertype,name);
	}
	return -1;
}
GLuint glGetSubroutineIndex(GLuint program, GLenum shadertype, GLchar const * name)
{
	if(Version(4,0))
	{
		GelLoadFunction(glGetSubroutineIndex);
		return _glGetSubroutineIndex(program,shadertype,name);
	}
	return 0;
}
void glGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values)
{
	if(Version(4,0))
	{
		GelLoadFunction(glGetActiveSubroutineUniformiv);
		_glGetActiveSubroutineUniformiv(program,shadertype,index,pname,values);
	}
}
void glGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name)
{
	if(Version(4,0))
	{
		GelLoadFunction(glGetActiveSubroutineUniformName);
		_glGetActiveSubroutineUniformName(program,shadertype,index,bufsize,length,name);
	}
}
void glGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name)
{
	if(Version(4,0))
	{
		GelLoadFunction(glGetActiveSubroutineName);
		_glGetActiveSubroutineName(program,shadertype,index,bufsize,length,name);
	}
}
void glUniformSubroutinesuiv(GLenum shadertype, GLsizei count, GLuint const * indices)
{
	if(Version(4,0))
	{
		GelLoadFunction(glUniformSubroutinesuiv);
		_glUniformSubroutinesuiv(shadertype,count,indices);
	}
}
void glGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint * params)
{
	if(Version(4,0))
	{
		GelLoadFunction(glGetUniformSubroutineuiv);
		_glGetUniformSubroutineuiv(shadertype,location,params);
	}
}
void glGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint * values)
{
	if(Version(4,0))
	{
		GelLoadFunction(glGetProgramStageiv);
		_glGetProgramStageiv(program,shadertype,pname,values);
	}
}

//reused functions from ARB_tessellation_shader
void glPatchParameteri(GLenum pname, GLint value)
{
	if(Version(4,0))
	{
		GelLoadFunction(glPatchParameteri);
		_glPatchParameteri(pname,value);
	}
}
void glPatchParameterfv(GLenum pname, GLfloat const * values)
{
	if(Version(4,0))
	{
		GelLoadFunction(glPatchParameterfv);
		_glPatchParameterfv(pname,values);
	}
}

//reused functions from ARB_transform_feedback2
void glBindTransformFeedback(GLenum target, GLuint id)
{
	if(Version(4,0))
	{
		GelLoadFunction(glBindTransformFeedback);
		_glBindTransformFeedback(target,id);
	}
}
void glDeleteTransformFeedbacks(GLsizei n, GLuint const * ids)
{
	if(Version(4,0))
	{
		GelLoadFunction(glDeleteTransformFeedbacks);
		_glDeleteTransformFeedbacks(n,ids);
	}
}
void glGenTransformFeedbacks(GLsizei n, GLuint * ids)
{
	if(Version(4,0))
	{
		GelLoadFunction(glGenTransformFeedbacks);
		_glGenTransformFeedbacks(n,ids);
	}
}
GLboolean glIsTransformFeedback(GLuint id)
{
	if(Version(4,0))
	{
		GelLoadFunction(glIsTransformFeedback);
		return _glIsTransformFeedback(id);
	}
	return GL_FALSE;
}
void glPauseTransformFeedback()
{
	if(Version(4,0))
	{
		GelLoadFunction(glPauseTransformFeedback);
		_glPauseTransformFeedback();
	}
}
void glResumeTransformFeedback()
{
	if(Version(4,0))
	{
		GelLoadFunction(glResumeTransformFeedback);
		_glResumeTransformFeedback();
	}
}
void glDrawTransformFeedback(GLenum mode, GLuint id)
{
	if(Version(4,0))
	{
		GelLoadFunction(glDrawTransformFeedback);
		_glDrawTransformFeedback(mode,id);
	}
}

//reused functions from ARB_transform_feedback3
void glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream)
{
	if(Version(4,0))
	{
		GelLoadFunction(glDrawTransformFeedbackStream);
		_glDrawTransformFeedbackStream(mode,id,stream);
	}
}
void glBeginQueryIndexed(GLenum target, GLuint index, GLuint id)
{
	if(Version(4,0))
	{
		GelLoadFunction(glBeginQueryIndexed);
		_glBeginQueryIndexed(target,index,id);
	}
}
void glEndQueryIndexed(GLenum target, GLuint index)
{
	if(Version(4,0))
	{
		GelLoadFunction(glEndQueryIndexed);
		_glEndQueryIndexed(target,index);
	}
}
void glGetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint * params)
{
	if(Version(4,0))
	{
		GelLoadFunction(glGetQueryIndexediv);
		_glGetQueryIndexediv(target,index,pname,params);
	}
}

//functions introduced in OpenGL 4.0
void glMinSampleShading(GLfloat value)
{
	if(Version(4,0))
	{
		GelLoadFunction(glMinSampleShading);
		_glMinSampleShading(value);
	}
}
void glBlendEquationi(GLuint buf, GLenum mode)
{
	if(Version(4,0))
	{
		GelLoadFunction(glBlendEquationi);
		_glBlendEquationi(buf,mode);
	}
}
void glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
{
	if(Version(4,0))
	{
		GelLoadFunction(glBlendEquationSeparatei);
		_glBlendEquationSeparatei(buf,modeRGB,modeAlpha);
	}
}
void glBlendFunci(GLuint buf, GLenum src, GLenum dst)
{
	if(Version(4,0))
	{
		GelLoadFunction(glBlendFunci);
		_glBlendFunci(buf,src,dst);
	}
}
void glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	if(Version(4,0))
	{
		GelLoadFunction(glBlendFuncSeparatei);
		_glBlendFuncSeparatei(buf,srcRGB,dstRGB,srcAlpha,dstAlpha);
	}
}
#endif

#if defined(GL_VERSION_4_1)
//functions reused from ARB_ES2_compatibility
void glReleaseShaderCompiler()
{
	if(Version(4,1))
	{
		GelLoadFunction(glReleaseShaderCompiler);
		_glReleaseShaderCompiler();
	}
}
void glShaderBinary(GLsizei count, GLuint const * shaders, GLenum binaryformat, GLvoid const * binary, GLsizei length)
{
	if(Version(4,1))
	{
		GelLoadFunction(glShaderBinary);
		_glShaderBinary(count,shaders,binaryformat,binary,length);
	}
}
void glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision)
{
	if(Version(4,1))
	{
		GelLoadFunction(glGetShaderPrecisionFormat);
		_glGetShaderPrecisionFormat(shadertype,precisiontype,range,precision);
	}
}
void glDepthRangef(GLfloat n, GLfloat f)
{
	if(Version(4,1))
	{
		GelLoadFunction(glDepthRangef);
		_glDepthRangef(n,f);
	}
}
void glClearDepthf(GLfloat d)
{
	if(Version(4,1))
	{
		GelLoadFunction(glClearDepthf);
		_glClearDepthf(d);
	}
}

//functions reused from ARB_get_program_binary
void glGetProgramBinary(GLuint program, GLsizei bufsize, GLsizei * length, GLenum * binaryFormat,GLvoid * binary)
{
	if(Version(4,1))
	{
		GelLoadFunction(glGetProgramBinary);
		_glGetProgramBinary(program,bufsize,length,binaryFormat,binary);
	}
}
void glProgramBinary(GLuint program, GLenum binaryformat, GLvoid const * binary, GLsizei length)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramBinary);
		_glProgramBinary(program,binaryformat,binary,length);
	}
}
void glProgramParameteri(GLuint program, GLenum pname, GLint value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramParameteri);
		_glProgramParameteri(program,pname,value);
	}
}

//functions reused from ARB_separate_shader_objects
void glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program)
{
	if(Version(4,1))
	{
		GelLoadFunction(glUseProgramStages);
		_glUseProgramStages(pipeline,stages,program);
	}
}
void glActiveShaderProgram(GLuint pipeline, GLuint program)
{
	if(Version(4,1))
	{
		GelLoadFunction(glActiveShaderProgram);
		_glActiveShaderProgram(pipeline,program);
	}
}
GLuint glCreateShaderProgramv(GLenum type, GLsizei count, GLchar const * const * strings)
{
	if(Version(4,1))
	{
		GelLoadFunction(glCreateShaderProgramv);
		return _glCreateShaderProgramv(type,count,strings);
	}
	return 0;
}
void glBindProgramPipeline(GLuint pipeline)
{
	if(Version(4,1))
	{
		GelLoadFunction(glBindProgramPipeline);
		_glBindProgramPipeline(pipeline);
	}
}
void glDeleteProgramPipelines(GLsizei n, GLuint const * pipelines)
{
	if(Version(4,1))
	{
		GelLoadFunction(glDeleteProgramPipelines);
		_glDeleteProgramPipelines(n,pipelines);
	}
}
void glGenProgramPipelines(GLsizei n, GLuint * pipelines)
{
	if(Version(4,1))
	{
		GelLoadFunction(glGenProgramPipelines);
		_glGenProgramPipelines(n,pipelines);
	}
}
GLboolean glIsProgramPipeline(GLuint pipeline)
{
	if(Version(4,1))
	{
		GelLoadFunction(glIsProgramPipeline);
		return _glIsProgramPipeline(pipeline);
	}
	return GL_FALSE;
}
void glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint * params)
{
	if(Version(4,1))
	{
		GelLoadFunction(glGetProgramPipelineiv);
		_glGetProgramPipelineiv(pipeline,pname,params);
	}
}
void glProgramUniform1i(GLuint program, GLint location, GLint v0)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform1i);
		_glProgramUniform1i(program,location,v0);
	}
}
void glProgramUniform1iv(GLuint program, GLint location, GLsizei count, GLint const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform1iv);
		_glProgramUniform1iv(program,location,count,value);
	}
}
void glProgramUniform1f(GLuint program, GLint location, GLfloat v0)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform1f);
		_glProgramUniform1f(program,location,v0);
	}
}
void glProgramUniform1fv(GLuint program, GLint location, GLsizei count, GLfloat const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform1fv);
		_glProgramUniform1fv(program,location,count,value);
	}
}
void glProgramUniform1d(GLuint program, GLint location, GLdouble v0)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform1d);
		_glProgramUniform1d(program,location,v0);
	}
}
void glProgramUniform1dv(GLuint program, GLint location, GLsizei count, GLdouble const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform1dv);
		_glProgramUniform1dv(program,location,count,value);
	}
}
void glProgramUniform1ui(GLuint program, GLint location, GLuint v0)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform1ui);
		_glProgramUniform1ui(program,location,v0);
	}
}
void glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, GLuint const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform1uiv);
		_glProgramUniform1uiv(program,location,count,value);
	}
}
void glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform2i);
		_glProgramUniform2i(program,location,v0,v1);
	}
}
void glProgramUniform2iv(GLuint program, GLint location, GLsizei count, GLint const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform2iv);
		_glProgramUniform2iv(program,location,count,value);
	}
}
void glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform2f);
		_glProgramUniform2f(program,location,v0,v1);
	}
}
void glProgramUniform2fv(GLuint program, GLint location, GLsizei count, GLfloat const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform2fv);
		_glProgramUniform2fv(program,location,count,value);
	}
}
void glProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform2d);
		_glProgramUniform2d(program,location,v0,v1);
	}
}
void glProgramUniform2dv(GLuint program, GLint location, GLsizei count, GLdouble const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform2dv);
		_glProgramUniform2dv(program,location,count,value);
	}
}
void glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform2ui);
		_glProgramUniform2ui(program,location,v0,v1);
	}
}
void glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, GLuint const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform2uiv);
		_glProgramUniform2uiv(program,location,count,value);
	}
}
void glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform3i);
		_glProgramUniform3i(program,location,v0,v1,v2);
	}
}
void glProgramUniform3iv(GLuint program, GLint location, GLsizei count, GLint const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform3iv);
		_glProgramUniform3iv(program,location,count,value);
	}
}
void glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform3f);
		_glProgramUniform3f(program,location,v0,v1,v2);
	}
}
void glProgramUniform3fv(GLuint program, GLint location, GLsizei count, GLfloat const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform3fv);
		_glProgramUniform3fv(program,location,count,value);
	}
}
void glProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform3d);
		_glProgramUniform3d(program,location,v0,v1,v2);
	}
}
void glProgramUniform3dv(GLuint program, GLint location, GLsizei count, GLdouble const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform3dv);
		_glProgramUniform3dv(program,location,count,value);
	}
}
void glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform3ui);
		_glProgramUniform3ui(program,location,v0,v1,v2);
	}
}
void glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, GLuint const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform3uiv);
		_glProgramUniform3uiv(program,location,count,value);
	}
}
void glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform4i);
		_glProgramUniform4i(program,location,v0,v1,v2,v3);
	}
}
void glProgramUniform4iv(GLuint program, GLint location, GLsizei count, GLint const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform4iv);
		_glProgramUniform4iv(program,location,count,value);
	}
}
void glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform4f);
		_glProgramUniform4f(program,location,v0,v1,v2,v3);
	}
}
void glProgramUniform4fv(GLuint program, GLint location, GLsizei count, GLfloat const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform4fv);
		_glProgramUniform4fv(program,location,count,value);
	}
}
void glProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform4d);
		_glProgramUniform4d(program,location,v0,v1,v2,v3);
	}
}
void glProgramUniform4dv(GLuint program, GLint location, GLsizei count, GLdouble const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform4dv);
		_glProgramUniform4dv(program,location,count,value);
	}
}
void glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform4ui);
		_glProgramUniform4ui(program,location,v0,v1,v2,v3);
	}
}
void glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, GLuint const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniform4uiv);
		_glProgramUniform4uiv(program,location,count,value);
	}
}
void glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniformMatrix2fv);
		_glProgramUniformMatrix2fv(program,location,count,transpose,value);
	}
}
void glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniformMatrix3fv);
		_glProgramUniformMatrix3fv(program,location,count,transpose,value);
	}
}
void glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniformMatrix4fv);
		_glProgramUniformMatrix4fv(program,location,count,transpose,value);
	}
}
void glProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniformMatrix2dv);
		_glProgramUniformMatrix2dv(program,location,count,transpose,value);
	}
}
void glProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniformMatrix3dv);
		_glProgramUniformMatrix3dv(program,location,count,transpose,value);
	}
}
void glProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniformMatrix4dv);
		_glProgramUniformMatrix4dv(program,location,count,transpose,value);
	}
}
void glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniformMatrix2x3fv);
		_glProgramUniformMatrix2x3fv(program,location,count,transpose,value);
	}
}
void glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniformMatrix3x2fv);
		_glProgramUniformMatrix3x2fv(program,location,count,transpose,value);
	}
}
void glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniformMatrix2x4fv);
		_glProgramUniformMatrix2x4fv(program,location,count,transpose,value);
	}
}
void glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniformMatrix4x2fv);
		_glProgramUniformMatrix4x2fv(program,location,count,transpose,value);
	}
}
void glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniformMatrix3x4fv);
		_glProgramUniformMatrix3x4fv(program,location,count,transpose,value);
	}
}
void glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniformMatrix4x3fv);
		_glProgramUniformMatrix4x3fv(program,location,count,transpose,value);
	}
}
void glProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniformMatrix2x3dv);
		_glProgramUniformMatrix2x3dv(program,location,count,transpose,value);
	}
}
void glProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniformMatrix3x2dv);
		_glProgramUniformMatrix3x2dv(program,location,count,transpose,value);
	}
}
void glProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniformMatrix2x4dv);
		_glProgramUniformMatrix2x4dv(program,location,count,transpose,value);
	}
}
void glProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniformMatrix4x2dv);
		_glProgramUniformMatrix4x2dv(program,location,count,transpose,value);
	}
}
void glProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniformMatrix3x4dv);
		_glProgramUniformMatrix3x4dv(program,location,count,transpose,value);
	}
}
void glProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	if(Version(4,1))
	{
		GelLoadFunction(glProgramUniformMatrix4x3dv);
		_glProgramUniformMatrix4x3dv(program,location,count,transpose,value);
	}
}
void glValidateProgramPipeline(GLuint pipeline)
{
	if(Version(4,1))
	{
		GelLoadFunction(glValidateProgramPipeline);
		_glValidateProgramPipeline(pipeline);
	}
}
void glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
{
	if(Version(4,1))
	{
		GelLoadFunction(glGetProgramPipelineInfoLog);
		_glGetProgramPipelineInfoLog(pipeline,bufSize,length,infoLog);
	}
}

//reused functions from ARB_vertex_attrib_64bit
void glVertexAttribL1d(GLuint index, GLdouble x)
{
	if(Version(4,1))
	{
		GelLoadFunction(glVertexAttribL1d);
		_glVertexAttribL1d(index,x);
	}
}
void glVertexAttribL2d(GLuint index, GLdouble x, GLdouble y)
{
	if(Version(4,1))
	{
		GelLoadFunction(glVertexAttribL2d);
		_glVertexAttribL2d(index,x,y);
	}
}
void glVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
	if(Version(4,1))
	{
		GelLoadFunction(glVertexAttribL3d);
		_glVertexAttribL3d(index,x,y,z);
	}
}
void glVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	if(Version(4,1))
	{
		GelLoadFunction(glVertexAttribL4d);
		_glVertexAttribL4d(index,x,y,z,w);
	}
}
void glVertexAttribL1dv(GLuint index, GLdouble const * v)
{
	if(Version(4,1))
	{
		GelLoadFunction(glVertexAttribL1dv);
		_glVertexAttribL1dv(index,v);
	}
}
void glVertexAttribL2dv(GLuint index, GLdouble const * v)
{
	if(Version(4,1))
	{
		GelLoadFunction(glVertexAttribL2dv);
		_glVertexAttribL2dv(index,v);
	}
}
void glVertexAttribL3dv(GLuint index, GLdouble const * v)
{
	if(Version(4,1))
	{
		GelLoadFunction(glVertexAttribL3dv);
		_glVertexAttribL3dv(index,v);
	}
}
void glVertexAttribL4dv(GLuint index, GLdouble const * v)
{
	if(Version(4,1))
	{
		GelLoadFunction(glVertexAttribL4dv);
		_glVertexAttribL4dv(index,v);
	}
}
void glVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, GLvoid const * pointer)
{
	if(Version(4,1))
	{
		GelLoadFunction(glVertexAttribLPointer);
		_glVertexAttribLPointer(index,size,type,stride,pointer);
	}
}
void glGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble * params)
{
	if(Version(4,1))
	{
		GelLoadFunction(glGetVertexAttribLdv);
		_glGetVertexAttribLdv(index,pname,params);
	}
}

//reused functions from ARB_viewport_array
void glViewportArrayv(GLuint first, GLsizei count, GLfloat const * v)
{
	if(Version(4,1))
	{
		GelLoadFunction(glViewportArrayv);
		_glViewportArrayv(first,count,v);
	}
}
void glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
	if(Version(4,1))
	{
		GelLoadFunction(glViewportIndexedf);
		_glViewportIndexedf(index,x,y,w,h);
	}
}
void glViewportIndexedfv(GLuint index, GLfloat const * v)
{
	if(Version(4,1))
	{
		GelLoadFunction(glViewportIndexedfv);
		_glViewportIndexedfv(index,v);
	}
}
void glScissorArrayv(GLuint first, GLsizei count, GLint const * v)
{
	if(Version(4,1))
	{
		GelLoadFunction(glScissorArrayv);
		_glScissorArrayv(first,count,v);
	}
}
void glScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height)
{
	if(Version(4,1))
	{
		GelLoadFunction(glScissorIndexed);
		_glScissorIndexed(index,left,bottom,width,height);
	}
}
void glScissorIndexedv(GLuint index, GLint const * v)
{
	if(Version(4,1))
	{
		GelLoadFunction(glScissorIndexedv);
		_glScissorIndexedv(index,v);
	}
}
void glDepthRangeArrayv(GLuint first, GLsizei count, GLdouble const * v)
{
	if(Version(4,1))
	{
		GelLoadFunction(glDepthRangeArrayv);
		_glDepthRangeArrayv(first,count,v);
	}
}
void glDepthRangeIndexed(GLuint index, GLdouble n, GLdouble f)
{
	if(Version(4,1))
	{
		GelLoadFunction(glDepthRangeIndexed);
		_glDepthRangeIndexed(index,n,f);
	}
}
void glGetFloati_v(GLenum target, GLuint index, GLfloat * data)
{
	if(Version(4,1))
	{
		GelLoadFunction(glGetFloati_v);
		_glGetFloati_v(target,index,data);
	}
}
void glGetDoublei_v(GLenum target, GLuint index, GLdouble * data)
{
	if(Version(4,1))
	{
		GelLoadFunction(glGetDoublei_v);
		_glGetDoublei_v(target,index,data);
	}
}
#endif

#if defined(GL_VERSION_4_2)
//reused functions from ARB_base_instance
void glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance)
{
	if(Version(4,2))
	{
		GelLoadFunction(glDrawArraysInstancedBaseInstance);
		_glDrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance);
	}
}
void glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, void const * indices, GLsizei instancecount, GLuint baseinstance)
{
	if(Version(4,2))
	{
		GelLoadFunction(glDrawElementsInstancedBaseInstance);
		_glDrawElementsInstancedBaseInstance(mode,count,type,indices,instancecount,baseinstance);
	}
}
void GEL_API glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, void const * indices, GLsizei instancecount,  GLint basevertex, GLuint baseinstance)
{
	if(Version(4,2))
	{
		GelLoadFunction(glDrawElementsInstancedBaseVertexBaseInstance);
		_glDrawElementsInstancedBaseVertexBaseInstance(mode,count,type,indices,instancecount,basevertex,baseinstance);
	}
}

//reused functions from ARB_transform_feedback_instanced
void GEL_API glDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount)
{
	if(Version(4,2))
	{
		GelLoadFunction(glDrawTransformFeedbackInstanced);
		_glDrawTransformFeedbackInstanced(mode,id,instancecount);
	}
}
void GEL_API glDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount)
{
	if(Version(4,2))
	{
		GelLoadFunction(glDrawTransformFeedbackStreamInstanced);
		_glDrawTransformFeedbackStreamInstanced(mode,id,stream,instancecount);
	}
}

//reused functions from ARB_internalformat_query
void GEL_API glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint * params)
{
	if(Version(4,2))
	{
		GelLoadFunction(glGetInternalformativ);
		_glGetInternalformativ(target, internalformat,pname,bufSize,params);
	}
}

//reused functions from ARB_shader_atomic_counters
void GEL_API glGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params)
{
	if(Version(4,2))
	{
		GelLoadFunction(glGetActiveAtomicCounterBufferiv);
		_glGetActiveAtomicCounterBufferiv(program,bufferIndex,pname,params);
	}
}

//reused functions from ARB_shader_image_load_store
void GEL_API glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format)
{
	if(Version(4,2))
	{
		GelLoadFunction(glBindImageTexture);
		_glBindImageTexture(unit,texture,level,layered,layer,access,format);
	}
}
void GEL_API glMemoryBarrier(GLbitfield barriers)
{
	if(Version(4,2))
	{
		GelLoadFunction(glMemoryBarrier);
		_glMemoryBarrier(barriers);
	}
}

//reused functions from ARB_texture_storage
void GEL_API glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
{
	if(Version(4,2))
	{
		GelLoadFunction(glTexStorage1D);
		_glTexStorage1D(target,levels,internalformat,width);
	}
}
void GEL_API glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
	if(Version(4,2))
	{
		GelLoadFunction(glTexStorage2D);
		_glTexStorage2D(target,levels,internalformat,width,height);
	}
}
void GEL_API glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
	if(Version(4,2))
	{
		GelLoadFunction(glTexStorage3D);
		_glTexStorage3D(target,levels,internalformat,width,height,depth);
	}
}
void GEL_API glTextureStorage1DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
{
	if(Version(4,2))
	{
		GelLoadFunction(glTextureStorage1DEXT);
		_glTextureStorage1DEXT(texture,target,levels,internalformat,width);
	}
}
void GEL_API glTextureStorage2DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
	if(Version(4,2))
	{
		GelLoadFunction(glTextureStorage2DEXT);
		_glTextureStorage2DEXT(texture,target,levels,internalformat,width,height);
	}
}
void GEL_API glTextureStorage3DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
	if(Version(4,2))
	{
		GelLoadFunction(glTextureStorage3DEXT);
		_glTextureStorage3DEXT(texture,target,levels,internalformat,width,height,depth);
	}
}
#endif

#if defined(GL_VERSION_4_3)
//reused functions from ARB_clear_buffer_object
void glClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, GLvoid const * data)
{
	if(Version(4,3))
	{
		GelLoadFunction(glClearBufferData);
		_glClearBufferData(target,internalformat,format,type,data);
	}
}
void glClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, GLvoid const * data)
{
	if(Version(4,3))
	{
		GelLoadFunction(glClearBufferSubData);
		_glClearBufferSubData(target,internalformat,offset,size,format,type,data);
	}
}
void glClearNamedBufferDataEXT(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, GLvoid const * data)
{
	if(Version(4,3))
	{
		GelLoadFunction(glClearNamedBufferDataEXT);
		_glClearNamedBufferDataEXT(buffer,internalformat,format,type,data);
	}
}
void glClearNamedBufferSubDataEXT(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, GLintptr offset, GLsizeiptr size, GLvoid const * data)
{
	if(Version(4,3))
	{
		GelLoadFunction(glClearNamedBufferSubDataEXT);
		_glClearNamedBufferSubDataEXT(buffer,internalformat,format,type,offset,size,data);
	}
}

//reused functions from ARB_compute_shader
void glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z)
{
	if(Version(4,3))
	{
		GelLoadFunction(glDispatchCompute);
		_glDispatchCompute(num_groups_x,num_groups_y,num_groups_z);
	}
}
void glDispatchComputeIndirect(GLintptr indirect)
{
	if(Version(4,3))
	{
		GelLoadFunction(glDispatchComputeIndirect);
		_glDispatchComputeIndirect(indirect);
	}
}

//reused functions from ARB_copy_image
//holy parameters, Batman.
void glCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth)
{
	if(Version(4,3))
	{
		GelLoadFunction(glCopyImageSubData);
		_glCopyImageSubData(srcName,srcTarget,srcLevel,srcX,srcY,srcZ,dstName,dstTarget,dstLevel,dstX,dstY,dstZ,srcWidth,srcHeight,srcDepth);
	}
}

//reused functions from KHR_debug
void glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, GLuint const * ids, GLboolean enabled)
{
	if(Version(4,3))
	{
		GelLoadFunction(glDebugMessageControl);
		_glDebugMessageControl(source,type,severity,count,ids,enabled);
	}
}
void glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const * buf)
{
	if(Version(4,3))
	{
		GelLoadFunction(glDebugMessageInsert);
		_glDebugMessageInsert(source,type,id,severity,length,buf);
	}
}
void glDebugMessageCallback(GLDEBUGPROC callback, GLvoid const * userParam)
{
	if(Version(4,3))
	{
		GelLoadFunction(glDebugMessageCallback);
		_glDebugMessageCallback(callback,userParam);
	}
}
GLuint glGetDebugMessageLog(GLuint count, GLsizei bufsize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog)
{
	if(Version(4,3))
	{
		GelLoadFunction(glGetDebugMessageLog);
		return _glGetDebugMessageLog(count,bufsize,sources,types,ids,severities,lengths,messageLog);
	}
	return 0;
}
void glPushDebugGroup(GLenum source, GLuint id, GLsizei length, GLchar const * message)
{
	if(Version(4,3))
	{
		GelLoadFunction(glPushDebugGroup);
		_glPushDebugGroup(source,id,length,message);
	}
}
void glPopDebugGroup()
{
	if(Version(4,3))
	{
		GelLoadFunction(glPopDebugGroup);
		_glPopDebugGroup();
	}
}
void glObjectLabel(GLenum identifier, GLuint name, GLsizei length, GLchar const * label)
{
	if(Version(4,3))
	{
		GelLoadFunction(glObjectLabel);
		_glObjectLabel(identifier,name,length,label);
	}
}
void glGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label)
{
	if(Version(4,3))
	{
		GelLoadFunction(glGetObjectLabel);
		_glGetObjectLabel(identifier,name,bufSize,length,label);
	}
}
void glObjectPtrLabel(GLvoid * ptr, GLsizei length, GLchar const * label)
{
	if(Version(4,3))
	{
		GelLoadFunction(glObjectPtrLabel);
		_glObjectPtrLabel(ptr,length,label);
	}
}
void glGetObjectPtrLabel(GLvoid * ptr, GLsizei bufSize, GLsizei * length, GLchar * label)
{
	if(Version(4,3))
	{
		GelLoadFunction(glGetObjectPtrLabel);
		_glGetObjectPtrLabel(ptr,bufSize,length,label);
	}
}

//reused functions from ARB_framebuffer_no_attachments
void glFramebufferParameteri(GLenum target, GLenum pname, GLint param)
{
	if(Version(4,3))
	{
		GelLoadFunction(glFramebufferParameteri);
		_glFramebufferParameteri(target,pname,param);
	}
}
void glGetFramebufferParameteriv(GLenum target, GLenum pname, GLint * params)
{
	if(Version(4,3))
	{
		GelLoadFunction(glGetFramebufferParameteriv);
		_glGetFramebufferParameteriv(target,pname,params);
	}
}

#if defined(GL_EXT_direct_state_access)
void glNamedFramebufferParameteriEXT(GLuint framebuffer, GLenum pname, GLint param)
{
	if(Version(4,3))
	{
		GelLoadFunction(glNamedFramebufferParameteriEXT);
		_glNamedFramebufferParameteriEXT(framebuffer,pname,param);
	}
}
void glGetNamedFramebufferParameterivEXT(GLuint framebuffer, GLenum pname, GLint * params)
{
	if(Version(4,3))
	{
		GelLoadFunction(glGetNamedFramebufferParameterivEXT);
		_glGetNamedFramebufferParameterivEXT(framebuffer,pname,params);
	}
}
#endif //GL_EXT_direct_state_access

//reused functions from ARB_internalformat_query2
void glGetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 * params)
{
	if(Version(4,3))
	{
		GelLoadFunction(glGetInternalformati64v);
		_glGetInternalformati64v(target,internalformat,pname,bufSize,params);
	}
}

//reused functions from ARB_invalidate_subdata
void glInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth)
{
	if(Version(4,3))
	{
		GelLoadFunction(glInvalidateTexSubImage);
		_glInvalidateTexSubImage(texture,level,xoffset,yoffset,zoffset,width,height,depth);
	}
}
void glInvalidateTexImage(GLuint texture, GLint level)
{
	if(Version(4,3))
	{
		GelLoadFunction(glInvalidateTexImage);
		_glInvalidateTexImage(texture,level);
	}
}
void glInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length)
{
	if(Version(4,3))
	{
		GelLoadFunction(glInvalidateBufferSubData);
		_glInvalidateBufferSubData(buffer,offset,length);
	}
}
void glInvalidateBufferData(GLuint buffer)
{
	if(Version(4,3))
	{
		GelLoadFunction(glInvalidateBufferData);
		_glInvalidateBufferData(buffer);
	}
}
void glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, GLenum const * attachments)
{
	if(Version(4,3))
	{
		GelLoadFunction(glInvalidateFramebuffer);
		_glInvalidateFramebuffer(target,numAttachments,attachments);
	}
}
void glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, GLenum const * attachments, GLint x, GLint y, GLsizei width, GLsizei height)
{
	if(Version(4,3))
	{
		GelLoadFunction(glInvalidateSubFramebuffer);
		_glInvalidateSubFramebuffer(target,numAttachments,attachments,x,y,width,height);
	}
}

//reused functions from ARB_multi_draw_indirect
void glMultiDrawArraysIndirect(GLenum mode, GLvoid const * indirect, GLsizei primcount, GLsizei stride)
{
	if(Version(4,3))
	{
		GelLoadFunction(glMultiDrawArraysIndirect);
		_glMultiDrawArraysIndirect(mode,indirect,primcount,stride);
	}
}
void glMultiDrawElementsIndirect(GLenum mode, GLenum type, GLvoid const * indirect, GLsizei primcount, GLsizei stride)
{
	if(Version(4,3))
	{
		GelLoadFunction(glMultiDrawElementsIndirect);
		_glMultiDrawElementsIndirect(mode,type,indirect,primcount,stride);
	}
}

//reused functions from ARB_program_interface_query
void glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint * params)
{
	if(Version(4,3))
	{
		GelLoadFunction(glGetProgramInterfaceiv);
		_glGetProgramInterfaceiv(program,programInterface,pname,params);
	}
}
GLuint glGetProgramResourceIndex(GLuint program, GLenum programInterface, GLchar const * name)
{
	if(Version(4,3))
	{
		GelLoadFunction(glGetProgramResourceIndex);
		return _glGetProgramResourceIndex(program,programInterface,name);
	}
	return 0;
}
void glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name)
{
	if(Version(4,3))
	{
		GelLoadFunction(glGetProgramResourceName);
		_glGetProgramResourceName(program,programInterface,index,bufSize,length,name);
	}
}
void glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, GLenum const * props, GLsizei bufSize, GLsizei * length, GLint * params)
{
	if(Version(4,3))
	{
		GelLoadFunction(glGetProgramResourceiv);
		_glGetProgramResourceiv(program,programInterface,index,propCount,props,bufSize,length,params);
	}
}
GLint glGetProgramResourceLocation(GLuint program, GLenum programInterface, GLchar const * name)
{
	if(Version(4,3))
	{
		GelLoadFunction(glGetProgramResourceLocation);
		return _glGetProgramResourceLocation(program,programInterface,name);
	}
	return 0;
}
GLint glGetProgramResourceLocationIndex(GLuint program, GLenum programInterface, GLchar const * name)
{
	if(Version(4,3))
	{
		GelLoadFunction(glGetProgramResourceLocationIndex);
		return _glGetProgramResourceLocationIndex(program,programInterface,name);
	}
	return 0;
}

//reused functions from ARB_shader_storage_buffer_object
void glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding)
{
	if(Version(4,3))
	{
		GelLoadFunction(glShaderStorageBlockBinding);
		_glShaderStorageBlockBinding(program,storageBlockIndex,storageBlockBinding);
	}
}

//reused functions from ARB_texture_buffer_range
void glTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
	if(Version(4,3))
	{
		GelLoadFunction(glTexBufferRange);
		_glTexBufferRange(target,internalformat,buffer,offset,size);
	}
}
void glTextureBufferTangeEXT(GLuint texture, GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
	if(Version(4,3))
	{
		GelLoadFunction(glTextureBufferRangeEXT);
		_glTextureBufferRangeEXT(texture,target,internalformat,buffer,offset,size);
	}
}

//reused functions from ARB_texture_storage_multisample
void glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	if(Version(4,3))
	{
		GelLoadFunction(glTexStorage2DMultisample);
		_glTexStorage2DMultisample(target,samples,internalformat,width,height,fixedsamplelocations);
	}
}
void glTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	if(Version(4,3))
	{
		GelLoadFunction(glTexStorage3DMultisample);
		_glTexStorage3DMultisample(target,samples,internalformat,width,height,depth,fixedsamplelocations);
	}
}
#if defined(GL_EXT_direct_state_access)
void glTextureStorage2DMultisampleEXT(GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	if(Version(4,3))
	{
		GelLoadFunction(glTextureStorage2DMultisampleEXT);
		_glTextureStorage2DMultisampleEXT(texture,target,samples,internalformat,width,height,fixedsamplelocations);
	}
}
void glTextureStorage3DMultisampleEXT(GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	if(Version(4,3))
	{
		GelLoadFunction(glTextureStorage3DMultisampleEXT);
		_glTextureStorage3DMultisampleEXT(texture,target,samples,internalformat,width,height,depth,fixedsamplelocations);
	}
}
#endif //GL_EXT_direct_state_access

//reused functions from ARB_texture_view
void glTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers)
{
	if(Version(4,3))
	{
		GelLoadFunction(glTextureView);
		_glTextureView(texture,target,origtexture,internalformat,minlevel,numlevels,minlayer,numlayers);
	}
}

//reused functions from ARB_vertex_attrib_binding
void glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
{
	if(Version(4,3))
	{
		GelLoadFunction(glBindVertexBuffer);
		_glBindVertexBuffer(bindingindex,buffer,offset,stride);
	}
}
void glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
{
	if(Version(4,3))
	{
		GelLoadFunction(glVertexAttribFormat);
		_glVertexAttribFormat(attribindex,size,type,normalized,relativeoffset);
	}
}
void glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
	if(Version(4,3))
	{
		GelLoadFunction(glVertexAttribIFormat);
		_glVertexAttribIFormat(attribindex,size,type,relativeoffset);
	}
}
void glVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
	if(Version(4,3))
	{
		GelLoadFunction(glVertexAttribLFormat);
		_glVertexAttribLFormat(attribindex,size,type,relativeoffset);
	}
}
void glVertexAttribBinding(GLuint attribindex, GLuint bindingindex)
{
	if(Version(4,3))
	{
		GelLoadFunction(glVertexAttribBinding);
		_glVertexAttribBinding(attribindex,bindingindex);
	}
}
void glVertexBindingDivisor(GLuint bindingindex, GLuint divisor)
{
	if(Version(4,3))
	{
		GelLoadFunction(glVertexBindingDivisor);
		_glVertexBindingDivisor(bindingindex,divisor);
	}
}
#endif

#if defined(GL_VERSION_4_4)
//reused function from ARB_buffer_storage
void glBufferStorage(GLenum target, GLsizeiptr size, const void *data, GLbitfield flags)
{
	if(Version(4,4))
	{
		GelLoadFunction(glBufferStorage);
		_glBufferStorage(target,size,data,flags);
	}
}

//reused functions from ARB_clear_texture
void glClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void *data)
{
	if(Version(4,4))
	{
		GelLoadFunction(glClearTexImage);
		_glClearTexImage(texture,level,format,type,data);
	}
}
void glClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data)
{
	if(Version(4,4))
	{
		GelLoadFunction(glClearTexSubImage);
		_glClearTexSubImage(texture,level,xoffset,yoffset,zoffset,width,height,depth,format,type,data);
	}
}

//reused functions from ARB_multi_bind
void glBindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint *buffers)
{
	if(Version(4,4))
	{
		GelLoadFunction(glBindBuffersBase);
		_glBindBuffersBase(target,first,count,buffers);
	}
}
void glBindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes)
{
	if(Version(4,4))
	{
		GelLoadFunction(glBindBuffersRange);
		_glBindBuffersRange(target,first,count,buffers,offsets,sizes);
	}
}
void glBindTextures(GLuint first, GLsizei count, const GLuint *textures)
{
	if(Version(4,4))
	{
		GelLoadFunction(glBindTextures);
		_glBindTextures(first,count,textures);
	}
}
void glBindSamplers(GLuint first, GLsizei count, const GLuint *samplers)
{
	if(Version(4,4))
	{
		GelLoadFunction(glBindSamplers);
		_glBindSamplers(first,count,samplers);
	}
}
void glBindImageTextures(GLuint first, GLsizei count, const GLuint *textures)
{
	if(Version(4,4))
	{
		GelLoadFunction(glBindImageTextures);
		_glBindImageTextures(first,count,textures);
	}
}
void glBindVertexBuffers(GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides)
{
	if(Version(4,4))
	{
		GelLoadFunction(glBindVertexBuffers);
		_glBindVertexBuffers(first,count,buffers,offsets,strides);
	}
}
#endif

#if defined(GEL_MSWINDOWS)
#pragma endregion
#endif

namespace gel
{
#if defined(GEL_MACOSX)
	//so far as I know, Macs are limited to OpenGL 3.2
	//before Lion, they only have 2.1
	static void * OGLdylib;
#endif

	void (*getProcAddress(char const* procName))()
	{
#if defined(GEL_MSWINDOWS)
		return (void(*)())wglGetProcAddress(procName);
#elif defined(GEL_LINUX)
		return (void(*)())glXGetProcAddress(reinterpret_cast<GLubyte const*>(procName));
#elif defined(GEL_MACOSX)
		return (void(*)())dlsym(OGLdylib,procName);
#endif
	}
	bool init(unsigned short major, unsigned short minor, bool loadNow)
	{
#if defined(GEL_MACOSX)
		OGLdylib = dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL",RTLD_LAZY);
		if(!OGLdylib) return false;
#endif
		gel::major = major;
		gel::minor = minor;

		if(loadNow)
		{
			//load all functions available for major.minor.

			//only load 1.2 and 1.3 on Windows
			//stop at 2.1 on Macs pre-Lion
			//stop at 3.2 on Macs post-Lion
		}
		return true;
	}
}

//#endif
