#ifndef INSANITY_COM_POINTER
#define INSANITY_COM_POINTER

//"First of May" ASL
//"Kiss Me" Klingon

#include "Constants.hpp"

namespace Insanity
{
	template<typename _comtype, bool _strong = true>
	class Ptr
	{
	protected:
		_comtype * _ptr;
	public:
		Ptr(_comtype * ptr = nullptr) : _ptr(ptr)
		{
			if(_strong && _ptr) _ptr->Retain();
		}
		Ptr(Ptr<_comtype,_strong> const & rval) : _ptr((_comtype*)rval)
		{
			if(_strong && _ptr) _ptr->Retain();
		}
		Ptr(Ptr<_comtype,!_strong> const & rval) : _ptr((_comtype*)rval)
		{
			if(_strong && _ptr) _ptr->Retain();
		}
		virtual ~Ptr()
		{
			if(_strong && _ptr) _ptr->Release();
		}

		operator _comtype*()
		{
			return _ptr;
		}
		operator _comtype*() const
		{
			return _ptr;
		}
		_comtype * operator->()
		{
			return _ptr;
		}
		_comtype * operator->() const
		{
			return _ptr;
		}
		_comtype * operator=(_comtype * ptr)
		{
			if(_strong && _ptr) _ptr->Release();
			_ptr = ptr;
			if(_strong && _ptr) _ptr->Retain();

			return _ptr;
		}
		template<bool strong>
		_comtype * operator=(Ptr<_comtype,strong> const & ptr)
		{
			if(_strong && _ptr) _ptr->Release();
			_ptr = (_comtype*)ptr;
			if(_strong && _ptr) _ptr->Retain();

			return _ptr;
		}
		bool operator==(_comtype const * ptr) const
		{
			return _ptr == ptr;
		}
		template<bool strong>
		bool operator==(Ptr<_comtype,strong> const & ptr) const
		{
			return _ptr == (_comtype*)ptr;
		}
	};

	template<typename _comtype> using WeakPtr = Ptr<_comtype,false>;
}

#endif