#ifndef INSANITY_IMPLEMENTATION_LINUX_THREAD
#define INSANITY_IMPLEMENTATION_LINUX_THREAD

#include <Constants.hpp>

#if defined(PLATFORM_LINUX)

#include <ISubThread.hpp>
#include <Ptr.hpp>
#include <pthread.h>
#include <list>
#include <memory>

#include <Default/Object.hpp>

namespace Insanity
{
	class IGarbageCollector;
	class ITask;
	
	class CLinuxSubThread final : public ISubThread, public Default::Object
	{
		enum class ThreadState : u8
		{
			Waiting,
			Running,
			Returning,
			Returned
		};

		static pthread_key_t s_curThreadKey;
		static bool s_threadInit;

		std::list<Ptr<ITask>> _taskList;
		std::unique_ptr<IGarbageCollector> _gc;
		WeakPtr<ISubThread> _ext;
		ThreadState _condition;
		u8 _gcTicker;

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
