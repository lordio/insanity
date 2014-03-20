#ifndef INSANITY_INTERFACE_GARBAGE_COLLECTOR
#define INSANITY_INTERFACE_GARBAGE_COLLECTOR

#include "Constants.hpp"

namespace Insanity
{
	class IObject;

	//Garbage Collectors are not themselves garbage collected.
	//	(Who collects the collectors?)
	class INSANITY_API IGarbageCollector
	{
	public:
		//=================================================
		//Define virtual dtor, so that thread dtors can
		//	simply delete their garbage collectors.
		//=================================================
		virtual ~IGarbageCollector() {}

		//=================================================
		//Creates a new garbage collector.
		//Not intended for use outside the library.
		//=================================================
		static IGarbageCollector * Create();

		//=================================================
		//Register an object for garbage collection.
		//=================================================
		virtual void Track(IObject * obj) = 0;

		//=================================================
		//Stop tracking an object.
		//=================================================
		virtual void Untrack(IObject * obj) = 0;

		//=================================================
		//Run a garbage collection pass.
		//=================================================
		virtual void Collect() = 0;

		//=================================================
		//Destroy all objects tracked by this collector.
		//Used when a thread is ending.
		//=================================================
		virtual void Clean() = 0;
	};
}

#endif