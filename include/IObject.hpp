#ifndef INSANITY_INTERFACE_OBJECT
#define INSANITY_INTERFACE_OBJECT

#include "Constants.hpp"

namespace Insanity
{
	class INSANITY_API IObject
	{
	public:
		//=================================================
		//Increments the reference count for the object.
		//Modifies mutable reference count.
		//=================================================
		virtual void Retain() const = 0;
		
		//=================================================
		//Decrements the reference count for the object.
		//If the reference count goes to zero,
		//	the garbage collector will destroy it on its next cycle.
		//Modifies mutable reference count.
		//=================================================
		virtual void Release() const = 0;
		
		//=================================================
		//Get the current reference count.
		//Not intended for use outside the library.
		//=================================================
		virtual u64 GetReferenceCount() const = 0;
		
		//=================================================
		//Deletes the object.
		//Not intended for use outside the library.
		//=================================================
		virtual void Delete() = 0;
		
		//=================================================
		//Casts the object to the specified interface,
		//	if it is supported. Nullptr otherwise.
		//=================================================
		template<class _type>
		inline _type * As()
		{
			return dynamic_cast<_type * const>(this);
		}
		
		//=================================================
		//Retain const-qualification if present.
		//=================================================
		template<class _type>
		inline _type const * As() const
		{
			return dynamic_cast<_type const * const>(this);
		}
		
		//=================================================
		//Check interface support.
		//=================================================
		template<class _type>
		inline bool Is() const
		{
			return dynamic_cast<_type const * const>(this) != nullptr;
		}
	};
}

#endif
