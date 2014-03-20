#ifndef INSANITY_IMPLEMENTATION_LINUX_THREAD
#define INSANITY_IMPLEMENTATION_LINUX_THREAD

#include <Constants.hpp>

#if defined(PLATFORM_LINUX)

#include <ISubThread.hpp>
#include <pthread.h>
#include <vector>

#include <default/Object.hpp>

namespace Insanity
{
	class IGarbageCollector;
	class ITask;
	
	class CLinuxSubThread final : public ISubThread, public Default::Object
	{
		static pthread_key_t s_curThreadKey;
		static bool s_threadInit;

		std::vector<ITask*> _taskList;
		IGarbageCollector * _gc;
		ISubThread * _ext;
		u8 _condition;
		u8 _gcTicker;

		//Thread states:
		//Running is mutually exclusive with waiting and returned states.
		//It is possible no condition applies (a thread has started and not yet returned, and something has requested its execution end).

		//Thread has not yet started execution.
		static const u8 THREAD_WAITING = 0x01;
		
		//Thread execution has completed.
		static const u8 THREAD_RETURNED = 0x02;

		//Thread should keep running.
		static const u8 THREAD_RUNNING = 0x04;

		struct _BoilerplateParams;

		static void _TLSInit();
		static void * _ThreadBoilerplate(void * params);
	public:
		//=================================================
		//Interface: CLinuxSubThread
		//=================================================
		static IThread * _Current();

		CLinuxSubThread(ISubThread*,bool);
		~CLinuxSubThread();

		//=================================================
		//Interface: ISubThread
		//=================================================
		void Start() override;
		void Main() override;

		//=================================================
		//Interface: IThread
		//=================================================
		bool Update() override;
		void End() override;
		IGarbageCollector * GetGarbageCollector() const override;
		void Yield() const override;
		void RegisterTask(ITask * task) override;
		void Transfer(IObject * obj) override;
		bool IsCurrentThread() const override;
	};
}

#endif

#endif
