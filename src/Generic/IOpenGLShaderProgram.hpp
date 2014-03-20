#ifndef INSANITY_INTERFACE_OPENGL_SHADER_PROGRAM
#define INSANITY_INTERFACE_OPENGL_SHADER_PROGRAM

#include <Constants.hpp>
#include <IShaderProgram.hpp>

#include "../../gel/gel.hpp"

namespace Insanity
{
	//Internal interface only.
	class INSANITY_API IOpenGLShaderProgram : public virtual IShaderProgram, public virtual IObject
	{
	public:
		virtual GLuint GetProgramName() const = 0;
	};
}

#endif