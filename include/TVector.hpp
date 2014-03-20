#ifndef INSANITY_TEMPLATE_VECTOR
#define INSANITY_TEMPLATE_VECTOR

#include "Constants.hpp"
#include <cmath>

namespace Insanity
{
	template<typename _elemType, u8 _elemCount>
	class TVector final
	{
		_elemType _elems[_elemCount];
	public:
		TVector()
		{
		}
		TVector(TVector<_elemType, _elemCount> const& rval)
		{
			for (u8 i = 0; i < _elemCount; i++) _elems[i] = rval[i];
		}
		~TVector()
		{
		}

		_elemType & operator[](u8 index)
		{
			return _elems[index];
		}
		_elemType const& operator[](u8 index) const
		{
			return _elems[index];
		}
		operator _elemType*()
		{
			return _elems;
		}
		operator _elemType const*() const
		{
			return _elems;
		}
		TVector<_elemType, _elemCount> operator+(TVector<_elemType, _elemCount> const& rval) const
		{
			TVector<_elemType, _elemCount> ret;
			for (u8 i = 0; i < _elemCount; i++) ret[i] = _elems[i] + rval[i];
			return ret;
		}
		TVector<_elemType, _elemCount> operator-(TVector<_elemType, _elemCount> const& rval) const
		{
			TVector<_elemType, _elemCount> ret;
			for (u8 i = 0; i < _elemCount; i++) ret[i] = _elems[i] - rval[i];
			return ret;
		}
		_elemType operator*(TVector<_elemType, _elemCount> const& rval) const
		{
			//dot product is sum of products of corresponding elements
			_elemType ret = (_elemType) 0;
			for (u8 i = 0; i < _elemCount; i++) ret += _elems[i] * rval[i];
			return ret;
		}
		u8 Size() const
		{
			return _elemCount;
		}
		void Normalize()
		{
			_elemType length = (_elemType) 0;
			for (_elemType elem : _elems) length += elem * elem;
			length = sqrt(length);
			for (_elemType & elem : _elems) elem /= length;
		}

		template<typename _type>
		static TVector<_type, 3> CrossProduct(TVector<_type, 3> const & lval, TVector<_type, 3> const & rval)
		{
			TVector<_type, 3> ret;
			ret[0] = lval[1] * rval[2] - lval[2] * rval[1];
			ret[1] = lval[2] * rval[0] - lval[0] * rval[2];
			ret[2] = lval[0] * rval[1] - lval[1] * rval[0];
			return ret;
		}
		//how would the cross product of homogenous coordinates be taken? Does that even make sense?
	};
}

#endif