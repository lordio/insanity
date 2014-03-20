#ifndef INSANITY_IMPLEMENTATION_MACOSX_COCOA_EVENT_PUMP_TASK
#define INSANITY_IMPLEMENTATION_MACOSX_COCOA_EVENT_PUMP_TASK

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

#include <default/Task.hpp>
#include <functional>
#include <map>

@class NSEvent;
@class NSWindow;

namespace Insanity
{
	class CMacOSXCocoaEventPumpTask final : public Default::Task
	{
		typedef std::function<void(NSEvent*)> ProcType;
		std::map<NSWindow*,ProcType> _procmap;
	public:
		CMacOSXCocoaEventPumpTask();
		~CMacOSXCocoaEventPumpTask();

		//=================================================
		//Implementation-specific
		//=================================================
		void RegisterProc(NSWindow * wnd, ProcType proc);
		void Clear(NSWindow * wnd);

		//=================================================
		//Interface: ITask
		//=================================================
		void Perform() override;
		bool ShouldRequeue() override;
	};
}

#endif

#endif