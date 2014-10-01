#ifndef INSANITY_TEMPLATE_RECTANGLE
#define INSANITY_TEMPLATE_RECTANGLE

#include "Constants.hpp"
#include <cmath>

namespace Insanity
{
	//can specify the type for x and y separately from width and height, defaults to the same.
	template<typename _xytype, typename _whtype = _xytype>
	class TRectangle final
	{
	private:
		_xytype _x;
		_xytype _y;
		_whtype _width;
		_whtype _height;

		template<typename etype> bool isWithin(etype left, etype middle, etype right) const
		{
			return left <= middle &&
				middle <= right;
		}
	public:
		TRectangle() :
			_x{}, _y{}, _width{}, _height{}
		{
		}
		TRectangle(_xytype x, _xytype y, _whtype width, _whtype height) :
			_x(x), _y(y), _width(width), _height(height)
		{
		}
		TRectangle(TRectangle const & rval) = default;
		~TRectangle()
		{
		}
		TRectangle & operator=(TRectangle const & rval)
		{
			_x = rval._x;
			_y = rval._y;
			_width = rval._width;
			_height = rval._height;
		}
		TRectangle & operator=(TRectangle && rval)
		{
			_x = rval._x;
			_y = rval._y;
			_width = rval._width;
			_height = rval._height;
		}
		_xytype GetX() const {return _x;}
		_xytype GetY() const {return _y;}
		_whtype GetWidth() const {return _width;}
		_whtype GetHeight() const {return _height;}

		_xytype GetLeft() const {return _x;}
		_xytype GetTop() const {return _y;}
		_whtype GetRight() const {return _x + _width;}
		_whtype GetBottom() const {return _y + _height;}

		//=================================================
		//Does any part of other overlap the calling Rectangle?
		//=================================================
		bool Intersects(TRectangle<_xytype,_whtype> const * other) const
		{
			//this function will report intersections for rectangles that are touching but not necessarily overlapping.
			//is it too restrictive to only allow Rectangles of the same types to be checked for intersections?
			//	could be templated if so.
			_xytype cx = _x + (_width / 2);
			_xytype cy = _y + (_height / 2);
			_xytype ocx = other->_x + (other->_width / 2);
			_xytype ocy = other->_y + (other->_height / 2);

			return ((std::abs(cx - ocx) * 2) <= (_width + other->_width)) &&
				((std::abs(cy - ocy) * 2) <= (_height + other->_height));
		}
		
		//=================================================
		//Does the calling Rectangle entirely contain other?
		//=================================================
		bool Contains(TRectangle<_xytype,_whtype> const * other) const
		{
			return  isWithin(GetLeft(), other->GetLeft(),   GetRight())  &&
					isWithin(GetLeft(), other->GetRight(),  GetRight())  &&
					isWithin(GetTop(),  other->GetTop(),    GetBottom()) &&
					isWithin(GetTop(),  other->GetBottom(), GetBottom());
		}

		void SetX(_xytype value) {_x = value;}
		void SetY(_xytype value) {_y = value;}
		void SetWidth(_whtype value) {_width = value;}
		void SetHeight(_whtype value) {_height = value;}
	};
}

#endif
