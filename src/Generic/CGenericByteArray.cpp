#define INSANITY_BUILDING_LIBRARY

#include "CGenericByteArray.hpp"

#include <string>

namespace Insanity
{
	namespace
	{
		inline void _write_bytes(std::vector<u8> & vec, u8 const * bytes, u64 count)
		{
			for(s64 i = count - 1; i >= 0; i--) vec.push_back(bytes[i]);
		}
		inline void _read_bytes(std::vector<u8> & vec, u64 & offset, u8 * bytes, u64 count)
		{
			for(s64 i = count - 1; i >= 0; i--, offset++) bytes[i] = vec[offset];
		}
	}

	IByteArray * IByteArray::Create()
	{
		return new CGenericByteArray{};
	}

	CGenericByteArray::CGenericByteArray() :
		CGenericObject{}
	{
	}
	CGenericByteArray::~CGenericByteArray()
	{
	}

	//=====================================================
	//Interface: IByteArray
	//=====================================================
	void CGenericByteArray::Write(u8 val)
	{
		_vec.push_back(val);
	}
	void CGenericByteArray::Write(u16 val)
	{
		_write_bytes(_vec,reinterpret_cast<u8*>(&val),sizeof(val));
	}
	void CGenericByteArray::Write(u32 val)
	{
		_write_bytes(_vec,reinterpret_cast<u8*>(&val),sizeof(val));
	}
	void CGenericByteArray::Write(u64 val)
	{
		_write_bytes(_vec,reinterpret_cast<u8*>(&val),sizeof(val));
	}
	void CGenericByteArray::Write(s8 val)
	{
		_vec.push_back(static_cast<u8>(val));
	}
	void CGenericByteArray::Write(s16 val)
	{
		_write_bytes(_vec,reinterpret_cast<u8*>(&val),sizeof(val));
	}
	void CGenericByteArray::Write(s32 val)
	{
		_write_bytes(_vec,reinterpret_cast<u8*>(&val),sizeof(val));
	}
	void CGenericByteArray::Write(s64 val)
	{
		_write_bytes(_vec,reinterpret_cast<u8*>(&val),sizeof(val));
	}
	void CGenericByteArray::Write(bool val)
	{
		_vec.push_back(val ? (u8)1 : (u8)0);
	}
	void CGenericByteArray::Write(float val)
	{
		//naive implementation for floating-point types
		_write_bytes(_vec,reinterpret_cast<u8*>(&val),sizeof(val));
	}
	void CGenericByteArray::Write(double val)
	{
		_write_bytes(_vec,reinterpret_cast<u8*>(&val),sizeof(val));
	}
	void CGenericByteArray::Write(long double ATTRIBUTE_UNUSED val)
	{
		//not always ten bytes, so if not, pad to it
		//since value might be ten bytes, always read and write at end of ten-byte zone
		//fine for writes, reads will need to do some munging
		//for(u8 i = 0; i < 10 - sizeof(val); i++) _vec.push_back((u8)0);

		//_write_bytes(&_vec,reinterpret_cast<u8*>(&val),sizeof(val));
	}
	void CGenericByteArray::Write(IByteArray const * val)
	{
		Write(val->Array(),val->Size());
	}
	void CGenericByteArray::Write(u8 const * val, u64 length)
	{
		//write forward
		for(u64 i = 0; i < length; i++) _vec.push_back(val[i]);
		
		//This will write the array into _vec backward.
		//_write_bytes(&_vec,val,length);
	}

	//TODO: Add checks to ensure read isn't attempted if _offset is >= _vec.size()
	void CGenericByteArray::Read(u8 & val)
	{
		val = _vec[_offset];
		_offset++;
	}
	void CGenericByteArray::Read(u16 & val)
	{
		_read_bytes(_vec,_offset,reinterpret_cast<u8*>(&val),sizeof(val));
	}
	void CGenericByteArray::Read(u32 & val)
	{
		_read_bytes(_vec,_offset,reinterpret_cast<u8*>(&val),sizeof(val));
	}
	void CGenericByteArray::Read(u64 & val)
	{
		_read_bytes(_vec,_offset,reinterpret_cast<u8*>(&val),sizeof(val));
	}
	void CGenericByteArray::Read(s8 & val)
	{
		val = (s8)_vec[_offset];
		_offset++;
	}
	void CGenericByteArray::Read(s16 & val)
	{
		_read_bytes(_vec,_offset,reinterpret_cast<u8*>(&val),sizeof(val));
	}
	void CGenericByteArray::Read(s32 & val)
	{
		_read_bytes(_vec,_offset,reinterpret_cast<u8*>(&val),sizeof(val));
	}
	void CGenericByteArray::Read(s64 & val)
	{
		_read_bytes(_vec,_offset,reinterpret_cast<u8*>(&val),sizeof(val));
	}
	void CGenericByteArray::Read(bool & val)
	{
		val = _vec[_offset] == 1;
		_offset++;
	}
	void CGenericByteArray::Read(float & val)
	{
		_read_bytes(_vec,_offset,reinterpret_cast<u8*>(&val),sizeof(val));
	}
	void CGenericByteArray::Read(double & val)
	{
		_read_bytes(_vec,_offset,reinterpret_cast<u8*>(&val),sizeof(val));
	}
	void CGenericByteArray::Read(long double & val)
	{
		_read_bytes(_vec,_offset,reinterpret_cast<u8*>(&val),sizeof(val));
		//cheat the offset ahead if on a nonstandard compiler
		_offset += 10 - sizeof(long double);
	}
	void CGenericByteArray::Read(u8 * val, u64 length)
	{
		for(u64 i = 0; i < length; i++, _offset++) val[i] = _vec[_offset];

		//reads backward
		//_read_bytes(&_vec,_offset,val,length);
	}
	
	u8 const * CGenericByteArray::Array() const
	{
		//returns the whole array, regardless of offset
		return _vec.data();
	}
	u64 CGenericByteArray::Size() const
	{
		return _vec.size();
	}
	void CGenericByteArray::Clip()
	{
		auto iter = _vec.begin();
		for(u64 i = 0; iter < _vec.end() && i < _offset; iter++, i++);
		_vec.erase(_vec.begin(),iter); //should be [first,last)
		_offset = 0;
	}
	void CGenericByteArray::Clear()
	{
		_vec.clear();
		_offset = 0;
	}
}
