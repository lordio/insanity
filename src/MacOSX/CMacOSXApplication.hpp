#ifndef INSANITY_IMPLEMENTATION_MACOSX_APPLICATION
#define INSANITY_IMPLEMENTATION_MACOSX_APPLICATION

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

#include <IApplication.hpp>
#include <Ptr.hpp>
#include <list>
#include <memory>

@class OMacOSXCocoaApplicationDelegate;

namespace Insanity
{
	class IGarbageCollector;
	class ITask;

	class CMacOSXApplication final : public IApplication
	{
	private:
		std::list<Ptr<ITask>> _taskList{};
		std::unique_ptr<IGarbageCollector> _gc;
		mutable u64 _ref{0};
		bool _running{true};
		u8 _gcTicker{0};
        
        //NSApplication doesn't retain the delegate for whatever reason, so create a static reference to it.
        OMacOSXCocoaApplicationDelegate * _appDelegate;
	public:
		CMacOSXApplication();
		~CMacOSXApplication();

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

		//=================================================
		//Interface: IObject
		//=================================================
		void Retain() const override;
		void Release() const override;
		u64 GetReferenceCount() const override;
		void Delete() override;
	};
}

#endif

#endif
