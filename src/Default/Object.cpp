#define INSANITY_BUILDING_LIBRARY

#include <Default/Object.hpp>
#include <IThread.hpp>
#include <IGarbageCollector.hpp>

namespace Insanity
{
	namespace Default
	{
		Object::Object() : ref(0)
		{
			//Application does not inherit Default::Object.
			//For all other objects, should be suitable GC.
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
	}
}
