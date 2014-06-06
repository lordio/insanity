#ifndef INSANITY_COM_POINTER
#define INSANITY_COM_POINTER

//"Kiss Me" Klingon

#include "Constants.hpp"

namespace Insanity
{
	//okay for use internally, but not for methods, interface statics, or Default classes.
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

		inline operator _comtype*()
		{
			return _ptr;
		}
		inline operator _comtype*() const
		{
			return _ptr;
		}
		inline _comtype * operator->()
		{
			return _ptr;
		}
		inline _comtype * operator->() const
		{
			return _ptr;
		}
		inline _comtype * operator=(_comtype * ptr)
		{
			if(_strong && _ptr) _ptr->Release();
			_ptr = ptr;
			if(_strong && _ptr) _ptr->Retain();

			return _ptr;
		}
		template<bool strong>
		inline _comtype * operator=(Ptr<_comtype,strong> const & ptr)
		{
			if(_strong && _ptr) _ptr->Release();
			_ptr = (_comtype*)ptr;
			if(_strong && _ptr) _ptr->Retain();

			return _ptr;
		}
		inline bool operator==(_comtype const * ptr) const
		{
			return _ptr == ptr;
		}
		template<bool strong>
		inline bool operator==(Ptr<_comtype,strong> const & ptr) const
		{
			return _ptr == (_comtype*)ptr;
		}

		inline _comtype * Get() const
		{
			return _ptr;
		}
	};

	template<typename _comtype> using WeakPtr = Ptr<_comtype,false>;
}

#endif