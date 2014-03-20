#ifndef INSANITY_IMPLEMENTATION_WINDOWS_WIN32_THREAD
#define INSANITY_IMPLEMENTATION_WINDOWS_WIN32_THREAD

#include <Constants.hpp>

#if defined(PLATFORM_MSWINDOWS)

#include <ISubThread.hpp>
#include <Windows.h>
#include <vector>

#include <default/Object.hpp>

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
		static DWORD s_tls;
		static bool s_tlsInitialized; //since initialization can only occur on main thread.

		std::vector<ITask*> _taskList;
		IGarbageCollector * _gc;
		ISubThread * _ext;
		u8 _condition;
		u8 _gcTicker;

		static const u8 THREAD_WAITING = 0x01;
		static const u8 THREAD_RUNNING = 0x02;
		static const u8 THREAD_RETURNED = 0x04;

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
