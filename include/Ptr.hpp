#ifndef INSANITY_COM_POINTER
#define INSANITY_COM_POINTER

#include "Constants.hpp"
#include "Common.hpp"
#include "IGarbageCollector.hpp"

namespace Insanity
{
	//okay for use internally, but not for methods, interface statics, or Default classes.
	template<typename _comtype, bool _strong = true>
	class Ptr
	{
	private:
		inline void _retain()
		{
			if (_ptr)
			{
				if (_ptr->ShouldBeTracked() && !_ptr->IsBeingTracked()) GetCurrentGC()->Track(_ptr);
				if (_strong) _ptr->Retain();
			}
		}
		inline void _release()
		{
			if (_strong && _ptr)
			{
				_ptr->Release();

				//if _ptr should not be tracked, delete it if its reference count goes to 0.
				if (!_ptr->ShouldBeTracked() && _ptr->GetReferenceCount() == 0) delete _ptr;
			}
		}
	protected:
		_comtype * _ptr;
	public:
		Ptr(_comtype * ptr = nullptr) : _ptr(ptr)
		{
			_retain();
		}
		//why isn't this templated?
		Ptr(Ptr<_comtype,_strong> const & rval) : _ptr((_comtype*)rval)
		{
			_retain();
		}
		Ptr(Ptr<_comtype,!_strong> const & rval) : _ptr((_comtype*)rval)
		{
			_retain();
		}
		template<bool strong>
		Ptr(Ptr<_comtype, strong> && rval) : _ptr((_comtype*)rval)
		{
			_retain();
			rval = nullptr;
		}
		virtual ~Ptr()
		{
			_release();
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
			_release();
			_ptr = ptr;
			_retain();

			return _ptr;
		}
		template<bool strong>
		inline _comtype * operator=(Ptr<_comtype,strong> const & ptr)
		{
			_release();
			_ptr = (_comtype*)ptr;
			_retain();

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