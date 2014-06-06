#define INSANITY_BUILDING_LIBRARY

#include <Default/Task.hpp>

namespace Insanity
{
	namespace Default
	{
		Task::Task() : Object{}
		{
		}
		Task::~Task()
		{
		}

		void Task::Perform()
		{
			//really shouldn't make Tasks without implementing Perform.
		}
		bool Task::ShouldRequeue()
		{
			return false;
		}
		void Task::Dequeue()
		{
		}

		//Object methods already implemented.
	}
}
