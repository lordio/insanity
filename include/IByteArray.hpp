#ifndef INSANITY_INTERFACE_BYTE_ARRAY
#define INSANITY_INTERFACE_BYTE_ARRAY

#include "Constants.hpp"
#include "IObject.hpp"

namespace Insanity
{
	template<typename _ctype> class IString;

	class INSANITY_API IByteArray : public virtual IObject
	{
	public:
		//=================================================
		//Returns a new, empty byte array.
		//=================================================
		static IByteArray * Create();

		//=================================================
		//Writes an unsigned integer value to the array.
		//NOTE: All writes are made to the end of the array.
		//=================================================
		virtual void Write(u8 val) = 0;
		virtual void Write(u16 val) = 0;
		virtual void Write(u32 val) = 0;
		virtual void Write(u64 val) = 0;

		//=================================================
		//Writes a signed integer value to the array.
		//NOTE: The s8 version is also used for chars.
		//=================================================
		virtual void Write(s8 val) = 0;
		virtual void Write(s16 val) = 0;
		virtual void Write(s32 val) = 0;
		virtual void Write(s64 val) = 0;

		//=================================================
		//Writes a simple representation of a bool to the array.
		//=================================================
		virtual void Write(bool val) = 0;

		//=================================================
		//Writes a floating-point number value to the array.
		//NOTE: Avoid using long doubles.
		//=================================================
		virtual void Write(float val) = 0;
		virtual void Write(double val) = 0;
		virtual void Write(long double val) = 0;

		//=================================================
		//Copy another ByteArray into this one.
		//=================================================
		virtual void Write(IByteArray const * val) = 0;

		//=================================================
		//Copy a raw byte array into this array.
		//For safety's sake, use this for character arrays.
		//=================================================
		virtual void Write(u8 const * val, u64 length) = 0;

		//=================================================
		//Read an unsigned integer value from the array.
		//NOTE: All reads start at an offset from the beginning of the array.
		//	Reads increment the offset based on their size.
		//=================================================
		virtual void Read(u8 & val) = 0;
		virtual void Read(u16 & val) = 0;
		virtual void Read(u32 & val) = 0;
		virtual void Read(u64 & val) = 0;

		//=================================================
		//Read a signed integer value from the array.
		//=================================================
		virtual void Read(s8 & val) = 0;
		virtual void Read(s16 & val) = 0;
		virtual void Read(s32 & val) = 0;
		virtual void Read(s64 & val) = 0;

		//=================================================
		//Reads a boolean value from the array.
		//=================================================
		virtual void Read(bool & val) = 0;

		//=================================================
		//Read a floating-point number from the array.
		//Avoid using long doubles.
		//=================================================
		virtual void Read(float & val) = 0;
		virtual void Read(double & val) = 0;
		virtual void Read(long double & val) = 0;

		//=================================================
		//Reads a raw chunk of data from an array.
		//=================================================
		virtual void Read(u8 * val, u64 length) = 0;

		//=================================================
		//Returns a pointer to the internal raw array.
		//=================================================
		virtual u8 const * Array() const = 0;

		//=================================================
		//Returns the number of bytes in the array.
		//=================================================
		virtual u64 Size() const = 0;

		//=================================================
		//Removes all bytes at indices [0,offset)
		//	Resets offset to 0 after removal.
		//=================================================
		virtual void Clip() = 0;

		//=================================================
		//Empties the entire array.
		//	Resets offset to 0.
		//=================================================
		virtual void Clear() = 0;
	};
}

#endif