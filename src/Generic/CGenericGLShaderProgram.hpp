#ifndef INSANITY_IMPLEMENTATION_GENERIC_GL_SHADER_PROGRAM
#define INSANITY_IMPLEMENTATION_GENERIC_GL_SHADER_PROGRAM

#include <Constants.hpp>

#if !defined(PLATFORM_MACOSX)

#include <IShaderProgram.hpp>
#include <default/Object.hpp>
#include "IOpenGLShaderProgram.hpp"

#include "../../gel/gel.hpp"

namespace Insanity
{
	//Windows and Linux use the Generic shader program objects.
	//Mac uses its own, which are tailored for the Mac versions available.
	
	//This object should work with the most basic supported shader program API, from OpenGL 3.1 onward.
	//A separate object should use 4.1, which allows glProgramUniform methods.
	//SetUniform calls should only be made on the active shader program.
	//	Route them through the Renderer, since that maintains a pointer to the active shader program?
	class CGenericGLShaderProgram final : public IOpenGLShaderProgram, public virtual IShaderProgram, public Default::Object
	{
		GLuint _programName;
		bool _linked;
	public:
		CGenericGLShaderProgram();
		~CGenericGLShaderProgram();
		
		//=================================================
		//Returns the OpenGL shader program name.
		//=================================================
		GLuint GetProgramName() const override;

		//=================================================
		//Interface: IShaderProgram
		//=================================================
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

#endif //!defined(PLATFORM_MACOSX)

#endif //INSANITY_IMPLEMENTATION_GENERIC_GL_SHADER_PROGRAM
