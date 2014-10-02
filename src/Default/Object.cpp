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
		bool Object::IsBeingTracked() const
		{
			return _tracked;
		}
		void Object::SetIsTracked(bool track)
		{
			if (ShouldBeTracked()) _tracked = track;
		}
	}
}
