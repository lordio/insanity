#ifndef INSANITY_IMPLEMENTATION_MACOSX_OPENGL_SHADER_PROGRAM
#define INSANITY_IMPLEMENTATION_MACOSX_OPENGL_SHADER_PROGRAM

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

#include <IShaderProgram.hpp>
#include <default/Object.hpp>

#include <OpenGL/GL3.h>

namespace Insanity
{
    class CMacOSXOpenGLShaderProgram final : public IShaderProgram, public Default::Object
    {
        GLuint _programName;
		bool _linked;
    public:
        CMacOSXOpenGLShaderProgram();
        ~CMacOSXOpenGLShaderProgram();
        
        GLuint GetProgramName() const;
        
        //=============================================
        //Interface: IShaderProgram
        //=============================================
        bool AddShader(EShaderType type, char const * filename) override;
        bool Link() override;
        
        void SetAttribute(u64 location, float value) override;
        void SetAttribute(u64 location, TVector<float, 2> const& value) override;
        void SetAttribute(u64 location, TVector<float, 3> const& value) override;
        void SetAttribute(u64 location, TVector<float, 4> const& value) override;
        void SetAttribute(char const * name, float value) override;
        void SetAttribute(char const * name, TVector<float, 2> const& value) override;
        void SetAttribute(char const * name, TVector<float, 3> const& value) override;
        void SetAttribute(char const * name, TVector<float, 4> const& value) override;
        
        void SetUniform(char const * name, bool value) override;
        void SetUniform(char const * name, int value) override;
        void SetUniform(char const * name, float value) override;
        void SetUniform(char const * name, TVector<float, 2> const& value) override;
        void SetUniform(char const * name, TVector<float, 3> const& value) override;
        void SetUniform(char const * name, TVector<float, 4> const& value) override;
        void SetUniform(char const * name, TMatrix<float, 2> const& value) override;
        void SetUniform(char const * name, TMatrix<float, 3> const& value) override;
        void SetUniform(char const * name, TMatrix<float, 4> const& value) override;
    };
}

#endif

#endif