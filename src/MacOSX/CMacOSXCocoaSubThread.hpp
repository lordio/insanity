#ifndef INSANITY_IMPLEMENTATION_MACOSX_COCOA_SUB_THREAD
#define INSANITY_IMPLEMENTATION_MACOSX_COCOA_SUB_THREAD

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

#include <ISubThread.hpp>
#include <default/Object.hpp>

#include <vector>

@class OMacOSXCocoaThread;

namespace Insanity
{
	class IGarbageCollector;
	class ITask;
	
	class CMacOSXCocoaSubThread final : public ISubThread, public Default::Object
	{
	private:
		std::vector<ITask*> _tasks;
		IGarbageCollector * _gc;
		ISubThread * _ext;
		OMacOSXCocoaThread * _thrd;
		u8 _condition;
		u8 _gcTicker;
		
		enum ThreadState
		{
			ThreadWaiting = 0x01,	//thread has not yet started running
			ThreadRunning = 0x02,	//thread is active (not necessarily running right now, but hasn't been ended)
			ThreadReturned = 0x04	//thread has finished execution
		};
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
