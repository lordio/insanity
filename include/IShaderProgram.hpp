#ifndef INSANITY_INTERFACE_SHADER_PROGRAM
#define INSANITY_INTERFACE_SHADER_PROGRAM

#include "Constants.hpp"
#include "IObject.hpp"
#include "TMatrix.hpp"

namespace Insanity
{
	template<typename _ctype>
	class IString;

	template<typename _elemType, u8 _elemCount>
	class TVector;

	enum class EShaderType
	{
		Vertex,
		Fragment,
		TessellationControl,
		TessellationEvaluate,
		Geometry,
		Compute
	};

	class INSANITY_API IShaderProgram : public virtual IObject
	{
	public:
		//=================================================
		//Load, compile, and add the shader to the program.
		//Returns bool: Was compilation successful?
		//=================================================
		virtual bool AddShader(EShaderType type, char const * filename) = 0;
		
		//=================================================
		//Links the program.
		//	Returns true if has been successfully linked,
		//	whether by this call, or a prior one.
		//	Returns false if linking failed.
		//=================================================
		virtual bool Link() = 0;

		//Uniforms and other program state.
		virtual void SetAttribute(u64 location, float value) = 0;
		virtual void SetAttribute(u64 location, TVector<float, 2> const& value) = 0;
		virtual void SetAttribute(u64 location, TVector<float, 3> const& value) = 0;
		virtual void SetAttribute(u64 location, TVector<float, 4> const& value) = 0;
		virtual void SetAttribute(char const * name, float value) = 0;
		virtual void SetAttribute(char const * name, TVector<float, 2> const& value) = 0;
		virtual void SetAttribute(char const * name, TVector<float, 3> const& value) = 0;
		virtual void SetAttribute(char const * name, TVector<float, 4> const& value) = 0;

		//=================================================
		//Must only be called on the active shader program.
		//=================================================
		virtual void SetUniform(char const * name, bool value) = 0;
		virtual void SetUniform(char const * name, int value) = 0;
		virtual void SetUniform(char const * name, float value) = 0;
		virtual void SetUniform(char const * name, TVector<float, 2> const& value) = 0;
		virtual void SetUniform(char const * name, TVector<float, 3> const& value) = 0;
		virtual void SetUniform(char const * name, TVector<float, 4> const& value) = 0;
		virtual void SetUniform(char const * name, TMatrix<float, 2> const& value) = 0;
		virtual void SetUniform(char const * name, TMatrix<float, 3> const& value) = 0;
		virtual void SetUniform(char const * name, TMatrix<float, 4> const& value) = 0;
	};
}

#endif
