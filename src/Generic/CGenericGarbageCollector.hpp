#ifndef INSANITY_IMPLEMENTATION_GENERIC_GARBAGE_COLLECTOR
#define INSANITY_IMPLEMENTATION_GENERIC_GARBAGE_COLLECTOR

#include <Constants.hpp>
#include <IGarbageCollector.hpp>
#include <IObject.hpp>
#include <list>

namespace Insanity
{
	class ATTRIBUTE_LOCAL CGenericGarbageCollector final : public IGarbageCollector
	{
		//use a std::unordered_set instead? To avoid duplication.
		std::list<IObject*> _pool;
	public:
		CGenericGarbageCollector();
		~CGenericGarbageCollector();

		//=================================================
		//Interface: IGarbageCollector
		//=================================================
		void Track(IObject * obj) override;
		void Untrack(IObject * obj) override;
		void Collect() override;
		void Clean() override;
	};
}

#endif
