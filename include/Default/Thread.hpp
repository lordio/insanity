#ifndef INSANITY_IMPLEMENTATION_DEFAULT_THREAD
#define INSANITY_IMPLEMENTATION_DEFAULT_THREAD

#include "../ISubThread.hpp"
#include "Object.hpp"

//When inheriting Default::Thread, be very clear in documentation whether
//	methods are intended to be called from within the thread or from another
//	thread, or what effects differ between the two cases.

#if defined(Yield)
#undef Yield
#endif

namespace Insanity
{
	class IGarbageCollector;
	class ITask;

	namespace Default
	{
		//Because of the platform-specific nature of threading, there is no
		//	"default" implementation for backend classes.
		class INSANITY_API Thread : public ISubThread, public Object
		{
		private:
			ISubThread * _base;
		public:
			Thread();
			virtual ~Thread();

			//=============================================
			//Interface: ISubThread
			//=============================================
			void Start() override final;
			//Override with thread main method body.
			virtual void Main() override;

			//=============================================
			//Interface: IThread
			//=============================================
			bool Update() override final;
			void Yield() const override final;
			void End() override final;
			IGarbageCollector * GetGarbageCollector() const override final;
			void RegisterTask(ITask * task) override final;
			void Transfer(IObject * obj) override final;
			bool IsCurrentThread() const override final;
		};
	}
}

#endif