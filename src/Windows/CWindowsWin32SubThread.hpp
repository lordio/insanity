#ifndef INSANITY_IMPLEMENTATION_WINDOWS_WIN32_THREAD
#define INSANITY_IMPLEMENTATION_WINDOWS_WIN32_THREAD

#include <Constants.hpp>

#if defined(PLATFORM_MSWINDOWS)

#include <ISubThread.hpp>
#include <Ptr.hpp>
#include <Windows.h>
#include <list>

#include <default/Object.hpp>
#include <memory>

//wtf Windows?
#ifdef Yield
#undef Yield
#endif

namespace Insanity
{
	class IGarbageCollector;
	class ITask;

	class CWindowsWin32SubThread final : public ISubThread, public Default::Object
	{
		enum class ThreadState : u8
		{
			Waiting,
			Running,
			Returning,
			Returned
		};
		static DWORD s_tls;
		static bool s_tlsInitialized; //since initialization can only occur on main thread.

		std::list<Ptr<ITask>> _taskList{ {} };
		std::unique_ptr<IGarbageCollector> _gc;
		WeakPtr<ISubThread> _ext;
		ThreadState _condition{ ThreadState::Waiting };
		u8 _gcTicker{ 0 };

		static void _TLSInit();
		static DWORD CALLBACK _ThreadBoilerplate(void * params);
	public:
		static IThread * _Current();

		CWindowsWin32SubThread(ISubThread * ext, bool start);
		~CWindowsWin32SubThread();

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
