#ifndef GEL
#define GEL

//Windows OpenGL headers need certain tokens defined before GL.h is included.

//deprecated functions are not included

#if (defined(__APPLE__) || defined(__MACH__))
#error Gel is unnecessary on Macs, as all available OpenGL functions are natively exported.
#endif

#if defined(_WIN32)
#	define GEL_MSWINDOWS
//only two supported processor architectures
//note: These defines are all MSVC2012-dependent.
#	if defined(_M_IX86)
#		define _X86_
#	endif //_M_IX86
#	if defined(_M_AMD64)
#		define _AMD64_
#	endif //_M_AMD64
#	include <minwindef.h>
#	ifndef WINGDIAPI
#		define WINGDIAPI __declspec(dllimport)
#	endif //WINGDIAPI
#	ifndef APIENTRY
#		define APIENTRY WINAPI
#	endif //APIENTRY
#	if defined(GEL_BUILDING_LIBRARY)
#		define GEL_API _declspec(dllexport)
#	else
#		define GEL_API _declspec(dllimport)
#	endif //GEL_BUILDING_LIBRARY
#elif defined(__linux__) || defined(__linux)
#	define GEL_LINUX
#	if defined(GEL_BUILDING_LIBRARY)
#		define GEL_API __attribute__((visibility("default")))
#	else
#		define GEL_API
#	endif //defined(__linux__) || defined(__linux)
#endif //_WIN32

#include <GL/gl.h>

//glext function declarations
#include <GL/glext.h>

#if defined(GL_VERSION_1_2) && defined(GEL_MSWINDOWS)
void GEL_API glBlendColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
void GEL_API glBlendEquation(GLenum mode);
void GEL_API glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, GLvoid const * indices);
void GEL_API glTexImage3D(GLenum target, GLint level,GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, GLvoid const * pixels);
void GEL_API glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLvoid const * pixels);
void GEL_API glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
#endif //GL_VERSION_1_2 && GEL_MSWINDOWS

#if defined(GL_VERSION_1_3) && defined(GEL_MSWINDOWS)
void GEL_API glActiveTexture(GLenum texture);
void GEL_API glSampleCoverage(GLclampf value, GLboolean invert);
void GEL_API glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imagesize, GLvoid const * data);
void GEL_API glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imagesize, GLvoid const * data);
void GEL_API glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imagesize, GLvoid const * data);
void GEL_API glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imagesize, GLvoid const * data);
void GEL_API glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imagesize, GLvoid const * data);
void GEL_API glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imagesize, GLvoid const * data);
void GEL_API glGetCompressedTexImage(GLenum target, GLint level, GLvoid * img);
#endif //GL_VERSION_1_3 && GEL_MSWINDOWS

#if defined(GL_VERSION_1_4)
void GEL_API glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
void GEL_API glMultiDrawArrays(GLenum mode, GLint const * first, GLsizei const * count, GLsizei primcount);
void GEL_API glMultiDrawElements(GLenum mode, GLsizei const * count, GLenum type, GLvoid const ** indices, GLsizei primcount);
void GEL_API glPointParameterf(GLenum pname, GLfloat param);
void GEL_API glPointParameterfv(GLenum pname, GLfloat const * params);
void GEL_API glPointParameteri(GLenum pname, GLint param);
void GEL_API glPointParameteriv(GLenum pname, GLint const * params);
#endif //GL_VERSION_1_4

#if defined(GL_VERSION_1_5)
void GEL_API glGenQueries(GLsizei n, GLuint * ids);
void GEL_API glDeleteQueries(GLsizei n, GLuint * ids);
GLboolean GEL_API glIsQuery(GLuint id);
void GEL_API glBeginQuery(GLenum target, GLuint id);
void GEL_API glEndQuery(GLenum target);
void GEL_API glGetQueryiv(GLenum target, GLenum pname, GLint * params);
void GEL_API glGetQueryObjectiv(GLuint id, GLenum pname, GLint * params);
void GEL_API glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params);
void GEL_API glBindBuffer(GLenum target, GLuint buffer);
void GEL_API glDeleteBuffers(GLsizei n, GLuint const * buffers);
void GEL_API glGenBuffers(GLsizei n, GLuint * buffers);
GLboolean GEL_API glIsBuffer(GLuint buffer);
void GEL_API glBufferData(GLenum target, GLsizeiptr size, GLvoid const * data, GLenum usage);
void GEL_API glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid const * data);
void GEL_API glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid * data);
GEL_API GLvoid * glMapBuffer(GLenum target, GLenum access);
GLboolean GEL_API glUnmapBuffer(GLenum target);
void GEL_API glGetBufferParameteriv(GLenum target, GLenum pname, GLint * params);
void GEL_API glGetBufferPointerv(GLenum target, GLenum pname, GLvoid ** params);
#endif //GL_VERSION_1_5

#if defined(GL_VERSION_2_0)
void GEL_API glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
void GEL_API glDrawBuffers(GLsizei n, GLenum const * bufs);
void GEL_API glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
void GEL_API glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
void GEL_API glStencilMaskSeparate(GLenum face, GLuint mask);
void GEL_API glAttachShader(GLuint program, GLuint shader);
void GEL_API glBindAttribLocation(GLuint program, GLuint index, GLchar const * name);
void GEL_API glCompileShader(GLuint shader);
GLuint GEL_API glCreateProgram();
GLuint GEL_API glCreateShader(GLenum type);
void GEL_API glDeleteProgram(GLuint program);
void GEL_API glDeleteShader(GLuint shader);
void GEL_API glDetachShader(GLuint program, GLuint shader);
void GEL_API glDisableVertexAttribArray(GLuint index);
void GEL_API glEnableVertexAttribArray(GLuint index);
void GEL_API glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
void GEL_API glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
void GEL_API glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders);
GLint GEL_API glGetAttribLocation(GLuint program, GLchar const * name);
void GEL_API glGetProgramiv(GLuint program, GLenum pname, GLint * params);
void GEL_API glGetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei * length, GLchar * infoLog);
void GEL_API glGetShaderiv(GLuint shader, GLenum pname, GLint * params);
void GEL_API glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei * length, GLchar * infoLog);
void GEL_API glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source);
GLint GEL_API glGetUniformLocation(GLuint program, GLchar const * name);
void GEL_API glGetUniformfv(GLuint program, GLint location, GLfloat * params);
void GEL_API glGetUniformiv(GLuint program, GLint location, GLint * params);
void GEL_API glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params);
void GEL_API glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params);
void GEL_API glGetVertexAttribiv(GLuint index, GLenum pname, GLint * params);
void GEL_API glGetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid ** pointer);
GLboolean GEL_API glIsProgram(GLuint program);
GLboolean GEL_API glIsShader(GLuint shader);
void GEL_API glLinkProgram(GLuint program);
void GEL_API glShaderSource(GLuint shader, GLsizei count, GLchar const ** string, const GLint * length);
void GEL_API glUseProgram(GLuint program);
void GEL_API glUniform1f(GLint location, GLfloat v0);
void GEL_API glUniform2f(GLint location, GLfloat v0, GLfloat v1);
void GEL_API glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
void GEL_API glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
void GEL_API glUniform1i(GLint location, GLint v0);
void GEL_API glUniform2i(GLint location, GLint v0, GLint v1);
void GEL_API glUniform3i(GLint location, GLint v0, GLint v1, GLint v2);
void GEL_API glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
void GEL_API glUniform1fv(GLint location, GLsizei size, GLfloat const * v);
void GEL_API glUniform2fv(GLint location, GLsizei size, GLfloat const * v);
void GEL_API glUniform3fv(GLint location, GLsizei size, GLfloat const * v);
void GEL_API glUniform4fv(GLint location, GLsizei size, GLfloat const * v);
void GEL_API glUniform1iv(GLint location, GLsizei size, GLint const * v);
void GEL_API glUniform2iv(GLint location, GLsizei size, GLint const * v);
void GEL_API glUniform3iv(GLint location, GLsizei size, GLint const * v);
void GEL_API glUniform4iv(GLint location, GLsizei size, GLint const * v);
void GEL_API glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
void GEL_API glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
void GEL_API glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
void GEL_API glValidateProgram(GLuint program);
void GEL_API glVertexAttrib1d(GLuint index, GLdouble v0);
void GEL_API glVertexAttrib1dv(GLuint index, GLdouble const * v);
void GEL_API glVertexAttrib1f(GLuint index, GLfloat v0);
void GEL_API glVertexAttrib1fv(GLuint index, GLfloat const * v);
void GEL_API glVertexAttrib1s(GLuint index, GLshort v0);
void GEL_API glVertexAttrib1sv(GLuint index, GLshort const * v);
void GEL_API glVertexAttrib2d(GLuint index, GLdouble v0, GLdouble v1);
void GEL_API glVertexAttrib2dv(GLuint index, GLdouble const * v);
void GEL_API glVertexAttrib2f(GLuint index, GLfloat v0, GLfloat v1);
void GEL_API glVertexAttrib2fv(GLuint index, GLfloat const * v);
void GEL_API glVertexAttrib2s(GLuint index, GLshort v0, GLshort v1);
void GEL_API glVertexAttrib2sv(GLuint index, GLshort const * v);
void GEL_API glVertexAttrib3d(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2);
void GEL_API glVertexAttrib3dv(GLuint index, GLdouble const * v);
void GEL_API glVertexAttrib3f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2);
void GEL_API glVertexAttrib3fv(GLuint index, GLfloat const * v);
void GEL_API glVertexAttrib3s(GLuint index, GLshort v0, GLshort v1, GLshort v2);
void GEL_API glVertexAttrib3sv(GLuint index, GLshort const * v);
void GEL_API glVertexAttrib4Nbv(GLuint index, GLbyte const * v);
void GEL_API glVertexAttrib4Niv(GLuint index, GLint const * v);
void GEL_API glVertexAttrib4Nsv(GLuint index, GLshort const * v);
void GEL_API glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
void GEL_API glVertexAttrib4Nubv(GLuint index, GLubyte const * v);
void GEL_API glVertexAttrib4Nuiv(GLuint index, GLuint const * v);
void GEL_API glVertexAttrib4Nusv(GLuint index, GLushort const * v);
void GEL_API glVertexAttrib4bv(GLuint index, GLbyte const * v);
void GEL_API glVertexAttrib4d(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
void GEL_API glVertexAttrib4dv(GLuint index, GLdouble const * v);
void GEL_API glVertexAttrib4f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
void GEL_API glVertexAttrib4fv(GLuint index, GLfloat const  *v);
void GEL_API glVertexAttrib4iv(GLuint index, GLint const * v);
void GEL_API glVertexAttrib4s(GLuint index, GLshort v0, GLshort v1, GLshort v2, GLshort v3);
void GEL_API glVertexAttrib4sv(GLuint index, GLshort const * v);
void GEL_API glVertexAttrib4ubv(GLuint index, GLubyte const * v);
void GEL_API glVertexAttrib4uiv(GLuint index, GLuint const * v);
void GEL_API glVertexAttrib4usv(GLuint index, GLushort const * v);
void GEL_API glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid const * pointer);
#endif //GL_VERSION_2_0

#if defined(GL_VERSION_2_1)
void GEL_API glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
void GEL_API glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
void GEL_API glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
void GEL_API glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
void GEL_API glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
void GEL_API glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
#endif //GL_VERSION_2_1

#if defined(GL_VERSION_3_0)
//reused functions from ARB_framebuffer_object
GLboolean GEL_API glIsRenderbuffer(GLuint renderbuffer);
void GEL_API glBindRenderbuffer(GLenum target, GLuint renderbuffer);
void GEL_API glDeleteRenderbuffers(GLsizei n, GLuint const * renderbuffers);
void GEL_API glGenRenderbuffers(GLsizei n, GLuint * renderbuffers);
void GEL_API glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
void GEL_API glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params);
GLboolean GEL_API glIsFramebuffer(GLuint framebuffer);
void GEL_API glBindFramebuffer(GLenum target, GLuint framebuffer);
void GEL_API glDeleteFramebuffers(GLsizei n, GLuint const * framebuffers);
void GEL_API glGenFramebuffers(GLsizei n, GLuint * framebuffers);
GLenum GEL_API glCheckFramebufferStatus(GLenum target);
void GEL_API glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
void GEL_API glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
void GEL_API glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
void GEL_API glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
void GEL_API glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params);
void GEL_API glGenerateMipmap(GLenum target);
void GEL_API glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
void GEL_API glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
void GEL_API glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);

//reused functions from ARB_map_buffer_range
GEL_API GLvoid * glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
void GEL_API glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length);

//reused functions from ARB_vertex_array_object
void GEL_API glBindVertexArray(GLuint array);
void GEL_API glDeleteVertexArrays(GLsizei n, GLuint const * arrays);
void GEL_API glGenVertexArrays(GLsizei n, GLuint * arrays);
GLboolean GEL_API glIsVertexArray(GLuint array);

//functions introduced in OpenGL 3.0
void GEL_API glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
void GEL_API glGetBooleani_v(GLenum target, GLuint index, GLboolean * data);
void GEL_API glGetIntegeri_v(GLenum target, GLuint index, GLint * data);
void GEL_API glEnablei(GLenum target, GLuint index);
void GEL_API glDisablei(GLenum target, GLuint index);
GLboolean GEL_API glIsEnabledi(GLenum target, GLuint index);
void GEL_API glBeginTransformFeedback(GLenum primitiveMode);
void GEL_API glEndTransformFeedback();
void GEL_API glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
void GEL_API glBindBufferBase(GLenum target, GLuint index, GLuint buffer);
void GEL_API glTransformFeedbackVaryings(GLuint program, GLsizei count, GLchar const * const * varyings, GLenum bufferMode);
void GEL_API glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name);
void GEL_API glClampColor(GLenum target, GLenum clamp);
void GEL_API glBeginConditionalRender(GLuint id, GLenum mode);
void GEL_API glEndConditionalRender();
void GEL_API glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, GLvoid const * pointer);
void GEL_API glGetVertexAttribIiv(GLuint index, GLenum pname, GLint * params);
void GEL_API glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params);
void GEL_API glVertexAttribI1i(GLuint index, GLint x);
void GEL_API glVertexAttribI2i(GLuint index, GLint x, GLint y);
void GEL_API glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z);
void GEL_API glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w);
void GEL_API glVertexAttribI1ui(GLuint index, GLuint x);
void GEL_API glVertexAttribI2ui(GLuint index, GLuint x, GLuint y);
void GEL_API glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z);
void GEL_API glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
void GEL_API glVertexAttribI1iv(GLuint index, GLint const * v);
void GEL_API glVertexAttribI2iv(GLuint index, GLint const * v);
void GEL_API glVertexAttribI3iv(GLuint index, GLint const * v);
void GEL_API glVertexAttribI4iv(GLuint index, GLint const * v);
void GEL_API glVertexAttribI1uiv(GLuint index, GLuint const * v);
void GEL_API glVertexAttribI2uiv(GLuint index, GLuint const * v);
void GEL_API glVertexAttribI3uiv(GLuint index, GLuint const * v);
void GEL_API glVertexAttribI4uiv(GLuint index, GLuint const * v);
void GEL_API glVertexAttribI4bv(GLuint index, GLbyte const * v);
void GEL_API glVertexAttribI4sv(GLuint index, GLshort const * v);
void GEL_API glVertexAttribI4ubv(GLuint index, GLubyte const * v);
void GEL_API glVertexAttribI4usv(GLuint index, GLushort const * v);
void GEL_API glGetUniformuiv(GLuint program, GLint location, GLuint * params);
void GEL_API glBindFragDataLocation(GLuint program, GLuint color, GLchar const * name);
GLint GEL_API glGetFragDataLocation(GLuint program, GLchar const * name);
void GEL_API glUniform1ui(GLint location, GLuint v0);
void GEL_API glUniform2ui(GLint location, GLuint v0, GLuint v1);
void GEL_API glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2);
void GEL_API glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
void GEL_API glUniform1uiv(GLint location, GLsizei count, GLuint const * value);
void GEL_API glUniform2uiv(GLint location, GLsizei count, GLuint const * value);
void GEL_API glUniform3uiv(GLint location, GLsizei count, GLuint const * value);
void GEL_API glUniform4uiv(GLint location, GLsizei count, GLuint const * value);
void GEL_API glTexParameterIiv(GLenum target, GLenum pname, GLint const * params);
void GEL_API glTexParameterIuiv(GLenum target, GLenum pname, GLuint const * params);
void GEL_API glGetTexParameterIiv(GLenum target, GLenum pname, GLint * params);
void GEL_API glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params);
void GEL_API glClearBufferiv(GLenum buffer, GLint drawbuffer, GLint const * value);
void GEL_API glClearBufferuiv(GLenum buffer, GLint drawbuffer, GLuint const * value);
void GEL_API glClearBufferfv(GLenum buffer, GLint drawbuffer, GLfloat const * value);
void GEL_API glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
GEL_API GLubyte const * glGetStringi(GLenum name, GLuint index);
#endif //GL_VERSION_3_0

#if defined(GL_VERSION_3_1)
//reused functions from ARB_copy_buffer
void GEL_API glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);

//reused functions from ARB_uniform_buffer_object
void GEL_API glGetUniformIndices(GLuint program, GLsizei uniformCount, GLchar const * const * uniformNames, GLuint * uniformIndices);
void GEL_API glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, GLuint const * uniformIndices, GLenum pname, GLint * params);
void GEL_API glGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName);
GLuint GEL_API glGetUniformBlockIndex(GLuint program, GLchar const * uniformBlockName);
void GEL_API glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params);
void GEL_API glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName);
void GEL_API glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);

//functions introduced in OpenGL 3.1
void GEL_API glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
void GEL_API glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, GLvoid const * indices, GLsizei instancecount);
void GEL_API glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer);
void GEL_API glPrimitiveRestartIndex(GLuint index);
#endif //GL_VERSION_3_1

#if defined(GL_VERSION_3_2)
//reused functions from ARB_draw_elements_base_vertex
void GEL_API glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, GLvoid const * indices, GLint basevertex);
void GEL_API glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, GLvoid const * indices, GLint basevertex);
void GEL_API glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, GLvoid const * indices, GLsizei primcount, GLint basevertex);
void GEL_API glMultiDrawElementsBaseVertex(GLenum mode, GLsizei const * count, GLenum type, GLvoid const * const * indices, GLsizei primcount, GLint const * basevertex);

//reused functions from ARB_provoking_vertex
void GEL_API glProvokingVertex(GLenum provokeMode);

//reused functions from ARB_sync
GLsync GEL_API glFenceSync(GLenum condition, GLbitfield flags);
GLboolean GEL_API glIsSync(GLsync sync);
void GEL_API glDeleteSync(GLsync sync);
GLenum GEL_API glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout);
void GEL_API glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout);
void GEL_API glGetInteger64v(GLenum pname, GLint64 * params);
void GEL_API glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values);

//reused functions from ARB_texture_multisample
void GEL_API glTexImage2DMultisample(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
void GEL_API glTexImage3DMultisample(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
void GEL_API glGetMultisamplefv(GLenum pname, GLuint index, GLfloat * val);
void GEL_API glSampleMaski(GLuint index, GLbitfield mask);

//functions introduced in OpenGL 3.2
void GEL_API glGetInteger64i_v(GLenum target, GLuint index, GLint64 * data);
void GEL_API glGetBufferParameteri64v(GLenum target, GLenum value, GLint64 * data);
void GEL_API glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level);
#endif //GL_VERSION_3_2

#if defined(GL_VERSION_3_3)
//reused functions from ARB_blend_func_extended
void GEL_API glBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, GLchar const * name);
GLint GEL_API glGetFragDataIndex(GLuint program, GLchar const * name);

//reused functions from ARB_sampler_objects
void GEL_API glGenSamplers(GLsizei n, GLuint * samplers);
void GEL_API glDeleteSamplers(GLsizei n, GLuint const * samplers);
GLboolean GEL_API glIsSampler(GLuint id);
void GEL_API glBindSampler(GLuint unit, GLuint sampler);
void GEL_API glSamplerParameteri(GLuint sampler, GLenum pname, GLint param);
void GEL_API glSamplerParameteriv(GLuint sampler, GLenum pname, GLint const * params);
void GEL_API glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param);
void GEL_API glSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat const * params);
void GEL_API glSamplerParameterIiv(GLuint sampler, GLenum pname, GLint const * params);
void GEL_API glSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint const * params);
void GEL_API glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint * params);
void GEL_API glGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint * params);
void GEL_API glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat * params);
void GEL_API glGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint * params);

//reused functions from ARB_timer_query
void GEL_API glQueryCounter(GLuint id, GLenum target);
void GEL_API glGetQueryObjecti64v(GLuint id, GLenum pname, GLint64 * params);
void GEL_API glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 * params);

//reused functions from ARB_vertex_type_2_10_10_10_rev
//removed fixed-function rendering functions
void GEL_API glVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value);
void GEL_API glVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value);
void GEL_API glVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value);
void GEL_API glVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value);

//functions introduced in OpenGL 3.3
void GEL_API glVertexAttribDivisor(GLuint index, GLuint divisor);
#endif //GL_VERSION_3_3

#if defined(GL_VERSION_4_0)
//reused functions from ARB_draw_indirect
void GEL_API glDrawArraysIndirect(GLenum mode, GLvoid const * indirect);
void GEL_API glDrawElementsIndirect(GLenum mode, GLenum type, GLvoid const * indirect);

//reused functions from ARB_gpu_shader_fp64
void GEL_API glUniform1d(GLint location, GLdouble x);
void GEL_API glUniform2d(GLint location, GLdouble x, GLdouble y);
void GEL_API glUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z);
void GEL_API glUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
void GEL_API glUniform1dv(GLint location, GLsizei count, GLdouble const * value);
void GEL_API glUniform2dv(GLint location, GLsizei count, GLdouble const * value);
void GEL_API glUniform3dv(GLint location, GLsizei count, GLdouble const * value);
void GEL_API glUniform4dv(GLint location, GLsizei count, GLdouble const * value);
void GEL_API glUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value);
void GEL_API glUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value);
void GEL_API glUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value);
void GEL_API glUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value);
void GEL_API glUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value);
void GEL_API glUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value);
void GEL_API glUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value);
void GEL_API glUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value);
void GEL_API glUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value);
void GEL_API glGetUniformdv(GLuint program, GLint location, GLdouble * params);

//reused functions from ARB_shader_subroutine
GLint GEL_API glGetSubroutineUniformLocation(GLuint program, GLenum shadertype, GLchar const * name);
GLuint GEL_API glGetSubroutineIndex(GLuint program, GLenum shadertype, GLchar const * name);
void GEL_API glGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values);
void GEL_API glGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name);
void GEL_API glGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name);
void GEL_API glUniformSubroutinesuiv(GLenum shadertype, GLsizei count, GLuint const * indices);
void GEL_API glGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint * params);
void GEL_API glGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint * values);

//reused functions from ARB_tessellation_shader
void GEL_API glPatchParameteri(GLenum pname, GLint value);
void GEL_API glPatchParameterfv(GLenum pname, GLfloat const * values);

//reused functions from ARB_transform_feedback2
void GEL_API glBindTransformFeedback(GLenum target, GLuint id);
void GEL_API glDeleteTransformFeedbacks(GLsizei n, GLuint const * ids);
void GEL_API glGenTransformFeedbacks(GLsizei n, GLuint * ids);
GLboolean GEL_API glIsTransformFeedback(GLuint id);
void GEL_API glPauseTransformFeedback();
void GEL_API glResumeTransformFeedback();
void GEL_API glDrawTransformFeedback(GLenum mode, GLuint id);

//reused functions from ARB_transform_feedback3
void GEL_API glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream);
void GEL_API glBeginQueryIndexed(GLenum target, GLuint index, GLuint id);
void GEL_API glEndQueryIndexed(GLenum target, GLuint index);
void GEL_API glGetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint * params);

//functions introduced in OpenGL 4.0
void GEL_API glMinSampleShading(GLfloat value);
void GEL_API glBlendEquationi(GLuint buf, GLenum mode);
void GEL_API glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
void GEL_API glBlendFunci(GLuint buf, GLenum src, GLenum dst);
void GEL_API glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#endif //GL_VERSION_4_0

#if defined(GL_VERSION_4_1)
//functions reused from ARB_ES2_compatibility
void GEL_API glReleaseShaderCompiler();
void GEL_API glShaderBinary(GLsizei count, GLuint const * shaders, GLenum binaryformat, GLvoid const * binary, GLsizei length);
void GEL_API glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision);
void GEL_API glDepthRangef(GLfloat n, GLfloat f);
void GEL_API glClearDepthf(GLfloat d);

//functions reused from ARB_get_program_binary
void GEL_API glGetProgramBinary(GLuint program, GLsizei bufsize, GLsizei * length, GLenum * binaryFormat,GLvoid * binary);
void GEL_API glProgramBinary(GLuint program, GLenum binaryformat, GLvoid const * binary, GLsizei length);
void GEL_API glProgramParameteri(GLuint program, GLenum pname, GLint value);

//functions reused from ARB_separate_shader_objects
void GEL_API glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program);
void GEL_API glActiveShaderProgram(GLuint pipeline, GLuint program);
GLuint GEL_API glCreateShaderProgramv(GLenum type, GLsizei count, GLchar const * const * strings);
void GEL_API glBindProgramPipeline(GLuint pipeline);
void GEL_API glDeleteProgramPipelines(GLsizei n, GLuint const * pipelines);
void GEL_API glGenProgramPipelines(GLsizei n, GLuint * pipelines);
GLboolean GEL_API glIsProgramPipeline(GLuint pipeline);
void GEL_API glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint * params);
void GEL_API glProgramUniform1i(GLuint program, GLint location, GLint v0);
void GEL_API glProgramUniform1iv(GLuint program, GLint location, GLsizei count, GLint const * value);
void GEL_API glProgramUniform1f(GLuint program, GLint location, GLfloat v0);
void GEL_API glProgramUniform1fv(GLuint program, GLint location, GLsizei count, GLfloat const * value);
void GEL_API glProgramUniform1d(GLuint program, GLint location, GLdouble v0);
void GEL_API glProgramUniform1dv(GLuint program, GLint location, GLsizei count, GLdouble const * value);
void GEL_API glProgramUniform1ui(GLuint program, GLint location, GLuint v0);
void GEL_API glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, GLuint const * value);
void GEL_API glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1);
void GEL_API glProgramUniform2iv(GLuint program, GLint location, GLsizei count, GLint const * value);
void GEL_API glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1);
void GEL_API glProgramUniform2fv(GLuint program, GLint location, GLsizei count, GLfloat const * value);
void GEL_API glProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1);
void GEL_API glProgramUniform2dv(GLuint program, GLint location, GLsizei count, GLdouble const * value);
void GEL_API glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1);
void GEL_API glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, GLuint const * value);
void GEL_API glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
void GEL_API glProgramUniform3iv(GLuint program, GLint location, GLsizei count, GLint const * value);
void GEL_API glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
void GEL_API glProgramUniform3fv(GLuint program, GLint location, GLsizei count, GLfloat const * value);
void GEL_API glProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
void GEL_API glProgramUniform3dv(GLuint program, GLint location, GLsizei count, GLdouble const * value);
void GEL_API glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
void GEL_API glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, GLuint const * value);
void GEL_API glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
void GEL_API glProgramUniform4iv(GLuint program, GLint location, GLsizei count, GLint const * value);
void GEL_API glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
void GEL_API glProgramUniform4fv(GLuint program, GLint location, GLsizei count, GLfloat const * value);
void GEL_API glProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
void GEL_API glProgramUniform4dv(GLuint program, GLint location, GLsizei count, GLdouble const * value);
void GEL_API glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
void GEL_API glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, GLuint const * value);
void GEL_API glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
void GEL_API glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
void GEL_API glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
void GEL_API glProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value);
void GEL_API glProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value);
void GEL_API glProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value);
void GEL_API glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
void GEL_API glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
void GEL_API glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
void GEL_API glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
void GEL_API glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
void GEL_API glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
void GEL_API glProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value);
void GEL_API glProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value);
void GEL_API glProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value);
void GEL_API glProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value);
void GEL_API glProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value);
void GEL_API glProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value);
void GEL_API glValidateProgramPipeline(GLuint pipeline);
void GEL_API glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog);

//reused functions from ARB_vertex_attrib_64bit
void GEL_API glVertexAttribL1d(GLuint index, GLdouble x);
void GEL_API glVertexAttribL2d(GLuint index, GLdouble x, GLdouble y);
void GEL_API glVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z);
void GEL_API glVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
void GEL_API glVertexAttribL1dv(GLuint index, GLdouble const * v);
void GEL_API glVertexAttribL2dv(GLuint index, GLdouble const * v);
void GEL_API glVertexAttribL3dv(GLuint index, GLdouble const * v);
void GEL_API glVertexAttribL4dv(GLuint index, GLdouble const * v);
void GEL_API glVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, GLvoid const * pointer);
void GEL_API glGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble * params);

//reused functions from ARB_viewport_array
void GEL_API glViewportArrayv(GLuint first, GLsizei count, GLfloat const * v);
void GEL_API glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
void GEL_API glViewportIndexedfv(GLuint index, GLfloat const * v);
void GEL_API glScissorArrayv(GLuint first, GLsizei count, GLint const * v);
void GEL_API glScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
void GEL_API glScissorIndexedv(GLuint index, GLint const * v);
void GEL_API glDepthRangeArrayv(GLuint first, GLsizei count, GLdouble const * v);
void GEL_API glDepthRangeIndexed(GLuint index, GLdouble n, GLdouble f);
void GEL_API glGetFloati_v(GLenum target, GLuint index, GLfloat * data);
void GEL_API glGetDoublei_v(GLenum target, GLuint index, GLdouble * data);
#endif //GL_VERSION_4_1

#if defined(GL_VERSION_4_2)
//reused functions from ARB_base_instance
void GEL_API glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
void GEL_API glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, void const * indices, GLsizei instancecount, GLuint baseinstance);
void GEL_API glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, void const * indices, GLsizei instancecount,  GLint basevertex, GLuint baseinstance);

//reused functions from ARB_transform_feedback_instanced
void GEL_API glDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount);
void GEL_API glDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount);

//reused functions from ARB_internalformat_query
void GEL_API glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint * params);

//reused functions from ARB_shader_atomic_counters
void GEL_API glGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params);

//reused functions from ARB_shader_image_load_store
void GEL_API glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
void GEL_API glMemoryBarrier(GLbitfield barriers);

//reused functions from ARB_texture_storage
void GEL_API glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
void GEL_API glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
void GEL_API glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
void GEL_API glTextureStorage1DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
void GEL_API glTextureStorage2DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
void GEL_API glTextureStorage3DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
#endif //GL_VERSION_4_2

#if defined(GL_VERSION_4_3)
//reused functions from ARB_clear_buffer_object
void GEL_API glClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, GLvoid const * data);
void GEL_API glClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, GLvoid const * data);
void GEL_API glClearNamedBufferDataEXT(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, GLvoid const * data);
void GEL_API glClearNamedBufferSubDataEXT(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, GLintptr offset, GLsizeiptr size, GLvoid const * data);

//reused functions from ARB_compute_shader
void GEL_API glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
void GEL_API glDispatchComputeIndirect(GLintptr indirect);

//reused functions from ARB_copy_image
//holy parameters, Batman.
void GEL_API glCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);

//reused functions from KHR_debug
void GEL_API glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, GLuint const * ids, GLboolean enabled);
void GEL_API glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const * buf);
void GEL_API glDebugMessageCallback(GLDEBUGPROC callback, GLvoid const * userParam);
GLuint GEL_API glGetDebugMessageLog(GLuint count, GLsizei bufsize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog);
void GEL_API glPushDebugGroup(GLenum source, GLuint id, GLsizei length, GLchar const * message);
void GEL_API glPopDebugGroup();
void GEL_API glObjectLabel(GLenum identifier, GLuint name, GLsizei length, GLchar const * label);
void GEL_API glGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label);
void GEL_API glObjectPtrLabel(GLvoid * ptr, GLsizei length, GLchar const * label);
void GEL_API glGetObjectPtrLabel(GLvoid * ptr, GLsizei bufSize, GLsizei * length, GLchar * label);

//reused functions from ARB_framebuffer_no_attachments
void GEL_API glFramebufferParameteri(GLenum target, GLenum pname, GLint param);
void GEL_API glGetFramebufferParameteriv(GLenum target, GLenum pname, GLint * params);

#if defined(GL_EXT_direct_state_access)
void GEL_API glNamedFramebufferParameteriEXT(GLuint framebuffer, GLenum pname, GLint param);
void GEL_API glGetNamedFramebufferParameterivEXT(GLuint framebuffer, GLenum pname, GLint * params);
#endif //GL_EXT_direct_state_access

//reused functions from ARB_internalformat_query2
void GEL_API glGetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 * params);

//reused functions from ARB_invalidate_subdata
void GEL_API glInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
void GEL_API glInvalidateTexImage(GLuint texture, GLint level);
void GEL_API glInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length);
void GEL_API glInvalidateBufferData(GLuint buffer);
void GEL_API glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, GLenum const * attachments);
void GEL_API glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, GLenum const * attachments, GLint x, GLint y, GLsizei width, GLsizei height);

//reused functions from ARB_multi_draw_indirect
void GEL_API glMultiDrawArraysIndirect(GLenum mode, GLvoid const * indirect, GLsizei primcount, GLsizei stride);
void GEL_API glMultiDrawElementsIndirect(GLenum mode, GLenum type, GLvoid const * indirect, GLsizei primcount, GLsizei stride);

//reused functions from ARB_program_interface_query
void GEL_API glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint * params);
GLuint GEL_API glGetProgramResourceIndex(GLuint program, GLenum programInterface, GLchar const * name);
void GEL_API glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name);
void GEL_API glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, GLenum const * props, GLsizei bufSize, GLsizei * length, GLint * params);
GLint GEL_API glGetProgramResourceLocation(GLuint program, GLenum programInterface, GLchar const * name);
GLint GEL_API glGetProgramResourceLocationIndex(GLuint program, GLenum programInterface, GLchar const * name);

//reused functions from ARB_shader_storage_buffer_object
void GEL_API glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);

//reused functions from ARB_texture_buffer_range
void GEL_API glTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
void GEL_API glTextureBufferRangeEXT(GLuint texture, GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);

//reused functions from ARB_texture_storage_multisample
void GEL_API glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
void GEL_API glTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
#if defined(GL_EXT_direct_state_access)
void GEL_API glTextureStorage2DMultisampleEXT(GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
void GEL_API glTextureStorage3DMultisampleEXT(GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
#endif //GL_EXT_direct_state_access

//reused functions from ARB_texture_view
void GEL_API glTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);

//reused functions from ARB_vertex_attrib_binding
void GEL_API glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
void GEL_API glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
void GEL_API glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
void GEL_API glVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
void GEL_API glVertexAttribBinding(GLuint attribindex, GLuint bindingindex);
void GEL_API glVertexBindingDivisor(GLuint bindingindex, GLuint divisor);
#endif

#if defined(GL_VERSION_4_4)
//reused function from ARB_buffer_storage
void GEL_API glBufferStorage(GLenum target, GLsizeiptr size, const void *data, GLbitfield flags);

//reused functions from ARB_clear_texture
void GEL_API glClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void *data);
void GEL_API glClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data);

//reused functions from ARB_multi_bind
void GEL_API glBindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint *buffers);
void GEL_API glBindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes);
void GEL_API glBindTextures(GLuint first, GLsizei count, const GLuint *textures);
void GEL_API glBindSamplers(GLuint first, GLsizei count, const GLuint *samplers);
void GEL_API glBindImageTextures(GLuint first, GLsizei count, const GLuint *textures);
void GEL_API glBindVertexBuffers(GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides);
#endif


#if defined(_WIN32)
//wglext not included, nothing of particular note of use.
#endif //_WIN32
#if defined(__linux__) || defined(__linux)
//glxext function declarations
//TODO: Check to see if any glxext functions are crucial
#   include <GL/glx.h>
#	include <GL/glxext.h>
#endif //__linux__ || __linux

namespace gel
{
	void GEL_API (*getProcAddress(char const * procName))();

	//returns false if any attempt to load a function fails.
	bool GEL_API init(unsigned short major, unsigned short minor, bool loadNow = false);
}

#if defined(GEL_MSWINDOWS)
#	pragma comment(lib,"openGL32.lib")
#	if !defined(GEL_BUILDING_LIBRARY)
#		pragma comment(lib,"Gel.lib")
#	endif //!GEL_BUILDING_LIBRARY
#endif //GEL_MSWINDOWS

#endif //GEL
