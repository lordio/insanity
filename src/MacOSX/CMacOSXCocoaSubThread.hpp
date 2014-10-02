#ifndef INSANITY_IMPLEMENTATION_MACOSX_COCOA_SUB_THREAD
#define INSANITY_IMPLEMENTATION_MACOSX_COCOA_SUB_THREAD

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

#include <ISubThread.hpp>
#include "../Generic/CGenericObject.hpp"
#include <ITask.hpp>
#include <Ptr.hpp>

#include <list>
#include <memory>

@class OMacOSXCocoaThread;

namespace Insanity
{
	class IGarbageCollector;
	class ITask;
	
	class CMacOSXCocoaSubThread final : public ISubThread, public CGenericObject
	{
	private:
		enum class ThreadState : u8
		{
			Waiting,
			Running,
			Returning,
			Returned
		};
		std::list<Ptr<ITask>> _tasks{};
		std::unique_ptr<IGarbageCollector> _gc;
		WeakPtr<ISubThread> _ext;
		OMacOSXCocoaThread * _thrd{nil}; //ARC pointer.
		ThreadState _condition{ThreadState::Waiting};
		u8 _gcTicker{0};
	public:
		CMacOSXCocoaSubThread(ISubThread * ext, bool start);
		~CMacOSXCocoaSubThread();
		
		static IThread * _Current();

		//=================================================
		//Public because OMacOSXCocoaThread needs to call it.
		//=================================================
		void _ThreadBoilerplate();

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
