#define INSANITY_BUILDING_LIBRARY

#include "CGenericOpenGL41ShaderProgram.hpp"

#if !defined(PLATFORM_MACOSX)

#include <TVector.hpp>
#include <TMatrix.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <memory>

namespace
{
	GLenum translate(Insanity::EShaderType shaderType)
	{
		GLenum ret = 0;
		switch (shaderType)
		{
		case Insanity::EShaderType::Compute:
			ret = GL_COMPUTE_SHADER; break;
		case Insanity::EShaderType::Fragment:
			ret = GL_FRAGMENT_SHADER; break;
		case Insanity::EShaderType::Geometry:
			ret = GL_GEOMETRY_SHADER; break;
		case Insanity::EShaderType::TessellationControl:
			ret = GL_TESS_CONTROL_SHADER; break;
		case Insanity::EShaderType::TessellationEvaluate:
			ret = GL_TESS_EVALUATION_SHADER; break;
		case Insanity::EShaderType::Vertex:
			ret = GL_VERTEX_SHADER; break;
		}
		return ret;
	}
}

namespace Insanity
{
	CGenericOpenGL41ShaderProgram::CGenericOpenGL41ShaderProgram() :
		_programName{ glCreateProgram() }, _linked{ false }
	{
	}
	CGenericOpenGL41ShaderProgram::~CGenericOpenGL41ShaderProgram()
	{
		glDeleteProgram(_programName);
	}
	
	GLuint CGenericOpenGL41ShaderProgram::GetProgramName() const
	{
		return _programName;
	}
	
	//=====================================================
	//Interface: IShaderProgram
	//=====================================================
	bool CGenericOpenGL41ShaderProgram::AddShader(EShaderType type, char const * filename)
	{
		assert(!_linked);

		//add some more checks that, if failed, will return false

		std::ifstream shaderFile{ filename };
		assert(shaderFile);

		std::string shader{};
		char holder{};
		while (shaderFile.get(holder)) shader += holder;

		GLuint shaderName{ glCreateShader(translate(type)) };

		char const * shaderCArray{ shader.c_str() };

		//ensure compilation worked.
		glShaderSource(shaderName, 1, &shaderCArray, nullptr);
		glCompileShader(shaderName);

		GLint status{};
		glGetShaderiv(shaderName,GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint loglen{};
			glGetShaderiv(shaderName, GL_INFO_LOG_LENGTH, &loglen);

			std::unique_ptr<char []> log{ new char[loglen] };
			glGetShaderInfoLog(shaderName, loglen, &loglen, log.get());
			
			std::cerr << log.get() << std::endl;

			return false;
		}

		glAttachShader(_programName, shaderName);

		glDeleteShader(shaderName);

		return true;
	}
	bool CGenericOpenGL41ShaderProgram::Link()
	{
		if(_linked) return true;
		
		glLinkProgram(_programName);

		GLint status{};
		glGetProgramiv(_programName, GL_LINK_STATUS, &status);
		
		if(status == GL_FALSE)
		{
			GLint len{};
			glGetProgramiv(_programName, GL_INFO_LOG_LENGTH, &len);

			std::unique_ptr<char []> log{ new char[len] };
			glGetProgramInfoLog(_programName, len, &len, log.get());
			
			std::cerr << log.get() << std::endl;
			
			return false;
		}
		
#if defined(CONFIGURE_DEBUG)
		glValidateProgram(_programName);
		glGetProgramiv(_programName, GL_VALIDATE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint len{};
			glGetProgramiv(_programName, GL_INFO_LOG_LENGTH, &len);

			std::unique_ptr<char []> log{ new char[len] };

			glGetProgramInfoLog(_programName, len, &len, log.get());
			std::cerr << log.get() << std::endl;

			return false;
		}
#endif //CONFIGURE_DEBUG

		_linked = true;
		
		return true;
	}
	void CGenericOpenGL41ShaderProgram::SetAttribute(u64 location, float value)
	{
		glVertexAttrib1f(static_cast<GLuint>(location), value);
	}
	void CGenericOpenGL41ShaderProgram::SetAttribute(u64 location, TVector<float, 2> const& value)
	{
		glVertexAttrib2fv(static_cast<GLuint>(location), value);
	}
	void CGenericOpenGL41ShaderProgram::SetAttribute(u64 location, TVector<float, 3> const& value)
	{
		glVertexAttrib3fv(static_cast<GLuint>(location), value);
	}
	void CGenericOpenGL41ShaderProgram::SetAttribute(u64 location, TVector<float, 4> const& value)
	{
		glVertexAttrib4fv(static_cast<GLuint>(location), value);
	}
	void CGenericOpenGL41ShaderProgram::SetAttribute(char const * name, float value)
	{
		glVertexAttrib1f(glGetAttribLocation(_programName, name), value);
	}
	void CGenericOpenGL41ShaderProgram::SetAttribute(char const * name, TVector<float, 2> const& value)
	{
		glVertexAttrib2fv(glGetAttribLocation(_programName, name), value);
	}
	void CGenericOpenGL41ShaderProgram::SetAttribute(char const * name, TVector<float, 3> const& value)
	{
		glVertexAttrib3fv(glGetAttribLocation(_programName, name), value);
	}
	void CGenericOpenGL41ShaderProgram::SetAttribute(char const * name, TVector<float, 4> const& value)
	{
		glVertexAttrib4fv(glGetAttribLocation(_programName, name), value);
	}
	
	void CGenericOpenGL41ShaderProgram::SetUniform(char const * name, bool value)
	{
		glProgramUniform1i(_programName, glGetUniformLocation(_programName, name), (value ? 1 : 0));
	}
	void CGenericOpenGL41ShaderProgram::SetUniform(char const * name, int value)
	{
		glProgramUniform1i(_programName, glGetUniformLocation(_programName, name), value);
	}
	void CGenericOpenGL41ShaderProgram::SetUniform(char const * name, float value)
	{
		glProgramUniform1f(_programName, glGetUniformLocation(_programName, name), value);
	}
	void CGenericOpenGL41ShaderProgram::SetUniform(char const * name, TVector<float, 2> const& value)
	{
		glProgramUniform2fv(_programName, glGetUniformLocation(_programName, name), 1, value);
	}
	void CGenericOpenGL41ShaderProgram::SetUniform(char const * name, TVector<float, 3> const& value)
	{
		glProgramUniform3fv(_programName, glGetUniformLocation(_programName, name), 1, value);
	}
	void CGenericOpenGL41ShaderProgram::SetUniform(char const * name, TVector<float, 4> const& value)
	{
		glProgramUniform4fv(_programName, glGetUniformLocation(_programName, name), 1, value);
	}
	void CGenericOpenGL41ShaderProgram::SetUniform(char const * name, TMatrix<float, 2> const& value)
	{
		glProgramUniformMatrix2fv(_programName, glGetUniformLocation(_programName, name), 1, GL_TRUE, value);
	}
	void CGenericOpenGL41ShaderProgram::SetUniform(char const * name, TMatrix<float, 3> const& value)
	{
		glProgramUniformMatrix3fv(_programName, glGetUniformLocation(_programName, name), 1, GL_TRUE, value);
	}
	void CGenericOpenGL41ShaderProgram::SetUniform(char const * name, TMatrix<float, 4> const& value)
	{
		glProgramUniformMatrix4fv(_programName, glGetUniformLocation(_programName, name), 1, GL_TRUE, value);
	}
}

#endif
