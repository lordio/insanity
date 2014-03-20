#define INSANITY_BUILDING_LIBRARY

#include "CMacOSXOpenGLShaderProgram.hpp"

#if defined(PLATFORM_MACOSX)

#include <IString.hpp>
#include <TVector.hpp>

#include <iostream>
#include <fstream>

namespace
{
    GLenum translate(Insanity::EShaderType type)
    {
        switch(type)
        {
            case Insanity::EShaderType::Compute:
                return 0; //Compute shaders were made core in 4.3. Mac 10.9 supports 3.3 or 4.1 (depending on graphics hardware)
            case Insanity::EShaderType::Fragment:
                return GL_FRAGMENT_SHADER;
            case Insanity::EShaderType::Geometry:
                return GL_GEOMETRY_SHADER;
            case Insanity::EShaderType::TessellationControl:
                return GL_TESS_CONTROL_SHADER;
            case Insanity::EShaderType::TessellationEvaluate:
                return GL_TESS_EVALUATION_SHADER;
            case Insanity::EShaderType::Vertex:
                return GL_VERTEX_SHADER;
        }
    }
}

namespace Insanity
{
	CMacOSXOpenGLShaderProgram::CMacOSXOpenGLShaderProgram() :
		_programName(glCreateProgram()), _linked(false)
	{
	}
	CMacOSXOpenGLShaderProgram::~CMacOSXOpenGLShaderProgram()
	{
		glDeleteProgram(_programName);
	}
	
	GLuint CMacOSXOpenGLShaderProgram::GetProgramName() const
	{
		return _programName;
	}
	
	//=====================================================
	//Interface: IShaderProgram
	//=====================================================
	bool CMacOSXOpenGLShaderProgram::AddShader(EShaderType type, char const * filename)
	{
		if (_linked) return false;

		IString<char> * shader = IString<char>::Create();
		shader->Retain();

		//add some more checks that, if failed, will return false

		//ensure the file was loaded
		std::ifstream shaderFile(filename);

		char holder = 0;
		while (shaderFile.get(holder)) shader->Append(holder);

		GLuint shaderName = glCreateShader(translate(type));

		char const * shaderCArray = shader->Array();

		//ensure compilation worked.
		glShaderSource(shaderName, 1, &shaderCArray, nullptr);
		glCompileShader(shaderName);
		
		GLint status = 0;
		glGetShaderiv(shaderName,GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint loglen = 0;
			glGetShaderiv(shaderName,GL_INFO_LOG_LENGTH,&loglen);
			
			char * log = new char[loglen];
			glGetShaderInfoLog(shaderName, loglen, &loglen, log);
			
			std::cout << log << std::endl;
			delete [] log;

			return false;
		}

		glAttachShader(_programName, shaderName);

		glDeleteShader(shaderName);

		shader->Release();

		return true;
	}
	bool CMacOSXOpenGLShaderProgram::Link()
	{
		if(_linked) return true;
		
		glLinkProgram(_programName);
		
		GLint status = 0;
		glGetProgramiv(_programName, GL_LINK_STATUS, &status);
		
		if(status == GL_FALSE)
		{
			int len = 0;
			glGetProgramiv(_programName, GL_INFO_LOG_LENGTH, &len);
			
			char * log = new char[len];
			glGetProgramInfoLog(_programName, len, &len, log);
			
			std::cout << log << std::endl;
			
			delete [] log;
			return false;
		}
		
#if defined(CONFIGURE_DEBUG)
		glValidateProgram(_programName);
		glGetProgramiv(_programName, GL_VALIDATE_STATUS, &status);
		if (status == GL_FALSE)
		{
			int len = 0;
			glGetProgramiv(_programName, GL_INFO_LOG_LENGTH, &len);

			char * log = new char[len];

			glGetProgramInfoLog(_programName, len, &len, log);
			std::cout << log << std::endl;

			delete [] log;

			return false;
		}
#endif //CONFIGURE_DEBUG

		_linked = true;
		
		return true;
	}

	void CMacOSXOpenGLShaderProgram::SetAttribute(u64 location, float value)
	{
		glVertexAttrib1f(static_cast<GLuint>(location), value);
	}
	void CMacOSXOpenGLShaderProgram::SetAttribute(u64 location, TVector<float, 2> const& value)
	{
		glVertexAttrib2fv(static_cast<GLuint>(location), value);
	}
	void CMacOSXOpenGLShaderProgram::SetAttribute(u64 location, TVector<float, 3> const& value)
	{
		glVertexAttrib3fv(static_cast<GLuint>(location), value);
	}
	void CMacOSXOpenGLShaderProgram::SetAttribute(u64 location, TVector<float, 4> const& value)
	{
		glVertexAttrib4fv(static_cast<GLuint>(location), value);
	}
	void CMacOSXOpenGLShaderProgram::SetAttribute(char const * name, float value)
	{
		glVertexAttrib1f(glGetAttribLocation(_programName, name), value);
	}
	void CMacOSXOpenGLShaderProgram::SetAttribute(char const * name, TVector<float, 2> const& value)
	{
		glVertexAttrib2fv(glGetAttribLocation(_programName, name), value);
	}
	void CMacOSXOpenGLShaderProgram::SetAttribute(char const * name, TVector<float, 3> const& value)
	{
		glVertexAttrib3fv(glGetAttribLocation(_programName, name), value);
	}
	void CMacOSXOpenGLShaderProgram::SetAttribute(char const * name, TVector<float, 4> const& value)
	{
		glVertexAttrib4fv(glGetAttribLocation(_programName, name), value);
	}

	void CMacOSXOpenGLShaderProgram::SetUniform(char const * name, bool value)
	{
        //despite ARB_separate_shader_objects being made core in 4.1, OS 10.9 makes it available on all supported graphics cards.
		glProgramUniform1i(_programName, glGetUniformLocation(_programName, name), (value ? 1 : 0));
	}
	void CMacOSXOpenGLShaderProgram::SetUniform(char const * name, int value)
	{
		glProgramUniform1i(_programName, glGetUniformLocation(_programName, name), value);
	}
	void CMacOSXOpenGLShaderProgram::SetUniform(char const * name, float value)
	{
		glProgramUniform1f(_programName, glGetUniformLocation(_programName, name), value);
	}
	void CMacOSXOpenGLShaderProgram::SetUniform(char const * name, TVector<float, 2> const& value)
	{
		glProgramUniform2fv(_programName, glGetUniformLocation(_programName, name), 1, value);
	}
	void CMacOSXOpenGLShaderProgram::SetUniform(char const * name, TVector<float, 3> const& value)
	{
		glProgramUniform3fv(_programName, glGetUniformLocation(_programName, name), 1, value);
	}
	void CMacOSXOpenGLShaderProgram::SetUniform(char const * name, TVector<float, 4> const& value)
	{
		glProgramUniform4fv(_programName, glGetUniformLocation(_programName, name), 1, value);
	}
	void CMacOSXOpenGLShaderProgram::SetUniform(char const * name, TMatrix<float, 2> const& value)
	{
		glProgramUniformMatrix2fv(_programName, glGetUniformLocation(_programName, name), 1, GL_TRUE, value);
	}
	void CMacOSXOpenGLShaderProgram::SetUniform(char const * name, TMatrix<float, 3> const& value)
	{
		glProgramUniformMatrix3fv(_programName, glGetUniformLocation(_programName, name), 1, GL_TRUE, value);
	}
	void CMacOSXOpenGLShaderProgram::SetUniform(char const * name, TMatrix<float, 4> const& value)
	{
		glProgramUniformMatrix4fv(_programName, glGetUniformLocation(_programName, name), 1, GL_TRUE, value);
	}
}

#endif
