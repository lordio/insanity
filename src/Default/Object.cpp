#define INSANITY_BUILDING_LIBRARY

#include <Default/Object.hpp>
#include <IThread.hpp>
#include <IGarbageCollector.hpp>

namespace Insanity
{
	namespace Default
	{
		Object::Object()
		{
			//Application does not inherit Default::Object.
			//For all other objects, should be suitable GC.

			//Actually, this is well and good for Insanity-side implementation objects, but not other Default objects.
			//Currently, Default objects are created in the executable, and deleted in the DLL. It hasn't been a problem, but it could become one.
			//Default objects should not be added to a collector, and should not be deleted using the IObject Delete method.
			//In fact, they probably shouldn't participate in Insanity-side reference counting at all.
			//On the other hand, many parts of the code assume Default objects inherit from IObject.
			IThread::Current()->GetGarbageCollector()->Track(this);
		}
		Object::~Object()
		{
		}

		void Object::Retain() const
		{
			//ref is marked mutable, so okay to change in const methods.
			++ref;
		}
		void Object::Release() const
		{
			if(ref == 0) return;
			--ref;
		}
		u64 Object::GetReferenceCount() const
		{
			return ref;
		}
		void Object::Delete()
		{
			delete this;
		}

		bool Object::ShouldBeTracked() const
		{
			//simpler to return false in case applications inherit from Default::Object.
			return false;
		}
	}
}
