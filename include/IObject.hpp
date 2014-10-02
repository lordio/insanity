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
		//Reports whether the object should be tracked internally,
		//	by a GarbageCollector.
		//Objects created by Insanity should return true,
		//	while application-side creations should return false.
		//=================================================
		virtual bool ShouldBeTracked() const = 0;

		//=================================================
		//Is the object currently being tracked by an Insanity
		//	Garbage Collector?
		//If ShouldBeTracked() returns false, this should always
		//	also be false.
		//=================================================
		virtual bool IsBeingTracked() const = 0;

		//=================================================
		//Tell the object its new tracking state.
		//Should only be called by GarbageCollector's Track
		//	and Untrack methods.
		//=================================================
		virtual void SetIsTracked(bool track) = 0;
		
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
