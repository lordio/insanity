#ifndef INSANITY_TEMPLATE_RECTANGLE
#define INSANITY_TEMPLATE_RECTANGLE

#include "Constants.hpp"
#include "Default/Object.hpp"
#include "IClonable.hpp"

namespace Insanity
{
	//can specify the type for x and y separately from width and height, defaults to the same.
	//how necessary is it that this inherit from Object?
	template<typename _xytype, typename _whtype = _xytype>
	class TRectangle : public IClonable<TRectangle<_xytype,_whtype>>, public Default::Object
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
		TRectangle(_xytype x, _xytype y, _whtype width, _whtype height) :
			_x(x), _y(y), _width(width), _height(height)
		{
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

			if(Contains(other)) return true;
			if(other->Contains(this)) return true;

			//other checks
			
			//top left corner of other is within this
			if(isWithin(GetLeft(), other->GetLeft(), GetRight()) &&
				isWithin(GetTop(),other->GetTop(), GetBottom())) return true;

			//top right corner of other is within this
			else if(isWithin(GetLeft(), other->GetRight(), GetRight()) &&
				isWithin(GetTop(), other->GetTop(), GetBottom())) return true;

			//bottom left corner is within this
			else if(isWithin(GetLeft(), other->GetLeft(), GetRight()) &&
				isWithin(GetTop(), other->GetBottom(), GetBottom())) return true;

			//bottom right corner is within this
			else if(isWithin(GetLeft(), other->GetRight(), GetRight()) &&
				isWithin(GetTop(), other->GetBottom(), GetBottom())) return true;

			//no corners are within the other rectangle.
			//do any sides traverse the other?
			else if((GetLeft() < other->GetLeft() && GetRight() > other->GetRight()) &&
				(isWithin(other->GetTop(), GetTop(), other->GetBottom()) || 
				isWithin(other->GetTop(), GetBottom(), other->GetBottom())))
				return true;
			else if((GetTop() < other->GetTop() && GetBottom() > other->GetBottom()) &&
				(isWithin(other->GetLeft(), GetLeft(), other->GetRight()) ||
				isWithin(other->GetLeft(), GetRight(), other->GetRight())))
				return true;

			else return false;
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
		
		//=================================================
		//Interface: IClonable
		//=================================================
		TRectangle<_xytype,_whtype> * Clone() const override
		{
			return new TRectangle<_xytype,_whtype>(_x,_y,_width,_height);
		}
	};
}

#endif
