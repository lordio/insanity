#ifndef INSANITY_INTERFACE_TASK
#define INSANITY_INTERFACE_TASK

#include "Constants.hpp"
#include "IObject.hpp"

namespace Insanity
{
	class INSANITY_API ITask : public virtual IObject
	{
	public:
		//=================================================
		//Code to perform on thread update.
		//=================================================
		virtual void Perform() = 0;

		//=================================================
		//Ask the Task if it should stay in the task queue.
		//=================================================
		virtual bool ShouldRequeue() = 0;

		//=================================================
		//Tell the task it is being removed from the queue.
		//=================================================
		virtual void Dequeue() = 0;
	};
}

#endif