#ifndef INSANITY_IMPLEMENTATION_MACOSX_COCOA_SUB_THREAD
#define INSANITY_IMPLEMENTATION_MACOSX_COCOA_SUB_THREAD

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

#include <ISubThread.hpp>
#include <default/Object.hpp>
#include <ITask.hpp>
#include <Ptr.hpp>

#include <list>
#include <memory>

@class OMacOSXCocoaThread;

namespace Insanity
{
	class IGarbageCollector;
	class ITask;
	
	class CMacOSXCocoaSubThread final : public ISubThread, public Default::Object
	{
	private:
		enum class ThreadState : u8
		{
			Waiting,
			Running,
			Returning,
			Returned
		};
		std::list<Ptr<ITask>> _tasks;
		std::unique_ptr<IGarbageCollector> _gc;
		WeakPtr<ISubThread> _ext;
		OMacOSXCocoaThread * _thrd; //ARC pointer.
		ThreadState _condition;
		u8 _gcTicker;
	public:
		CMacOSXCocoaSubThread(ISubThread * ext, bool start);
		~CMacOSXCocoaSubThread();
		
		static IThread * _Current();

		//=================================================
		//Public because MacObjCThreadWrapper needs to call it.
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
