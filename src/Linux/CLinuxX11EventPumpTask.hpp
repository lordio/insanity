#ifndef INSANITY_IMPLEMENTATION_LINUX_X11_EVENT_PUMP_TASK
#define INSANITY_IMPLEMENTATION_LINUX_X11_EVENT_PUMP_TASK

#include <Constants.hpp>

#if defined(PLATFORM_LINUX)

#include <Default/Task.hpp>

#include <map>
#include <functional>

#include <X11/Xlib.h>

namespace Insanity
{
	class CLinuxX11EventPumpTask final : public Default::Task
	{
		typedef std::function<void(XEvent*)> ProcType;
		std::map<Window,ProcType> _procmap;
		Display * _dpy;
	public:
		CLinuxX11EventPumpTask(Display * dpy);
		~CLinuxX11EventPumpTask();

		//=================================================
		//Implementation-specific
		//=================================================
		void RegisterProc(Window wnd, ProcType proc);
		void Clear(Window wnd);

		//=================================================
		//Interface: ITask
		//=================================================
		void Perform() override;
		bool ShouldRequeue() override;
	};
}

#endif

#endif
