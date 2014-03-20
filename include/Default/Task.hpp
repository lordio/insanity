#ifndef INSANITY_IMPLEMENTATION_DEFAULT_TASK
#define INSANITY_IMPLEMENTATION_DEFAULT_TASK

#include <Constants.hpp>

#include <ITask.hpp>
#include "Object.hpp"

namespace Insanity
{
	namespace Default
	{
		class INSANITY_API Task : public ITask, public Object
		{
		public:
			Task();
			virtual ~Task();

			virtual void Perform();
			virtual bool ShouldRequeue();
			virtual void Dequeue();
		};
	}
}

#endif