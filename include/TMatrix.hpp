#ifndef INSANITY_TEMPLATE_MATRIX
#define INSANITY_TEMPLATE_MATRIX

#include "Constants.hpp"

namespace Insanity
{
	template<typename _elemType, u8 _rows, u8 _columns = _rows>
	class TMatrix final
	{
		_elemType _elems[_rows][_columns];
	public:
		TMatrix()
		{
			for (u8 i = 0; i < _rows; i++)
				for (u8 j = 0; j < _columns; j++)
					_elems[i][j] = (_elemType) 0;
		}
		TMatrix(_elemType init[_rows][_columns]) : _elems(init)
		{
		}
		~TMatrix()
		{
		}

		_elemType& At(u8 row, u8 column)
		{
			return _elems[row][column];
		}
		const _elemType& At(u8 row, u8 column) const
		{
			return _elems[row][column];
		}
		operator _elemType*()
		{
			return &_elems[0][0];
		}
		operator _elemType const*() const
		{
			return &_elems[0][0];
		}
		TMatrix<_elemType, _rows, _columns> operator+(TMatrix<_elemType, _rows, _columns> const & rval) const
		{
			TMatrix<_elemType, _rows, _columns> ret;
			for (u8 i = 0; i < _rows; i++)
				for (u8 j = 0; j < _columns; j++)
					ret.At(i, j) = At(i, j) + rval.At(i, j);
			return ret;
		}
		TMatrix<_elemType, _rows, _columns> operator-(TMatrix<_elemType, _rows, _columns> const & rval) const
		{
			TMatrix<_elemType, _rows, _columns> ret;
			for (u8 i = 0; i < _rows; i++)
				for (u8 j = 0; j < _columns; j++)
					ret.At(i, j) = At(i, j) - rval.At(i, j);
			return ret;
		}
		//rval's rows are enforced to be the same as lval's columns.
		//This should work correctly; TMatrix<float,4,3> should be multiplyable by TMatrix<float,3,2>, and produce a TMatrix<float,4,2>.
		template<u8 _rcolumns>
		TMatrix<_elemType, _rows, _rcolumns> operator*(TMatrix<_elemType, _columns, _rcolumns> const & rval) const
		{
			TMatrix<_elemType, _rows, _rcolumns> ret;
			for (u8 i = 0; i < _rows; i++)
				for (u8 j = 0; j < _rcolumns; j++)
					for (u8 k = 0; k < _columns; k++) 
						ret.At(i, j) += At(i, k) * rval.At(k, j);
			return ret;
		}
		u8 Size() const
		{
			return _columns * _rows;
		}
		u8 Width() const
		{
			return _columns;
		}
		u8 Height() const
		{
			return _rows;
		}
	};
}

#endif