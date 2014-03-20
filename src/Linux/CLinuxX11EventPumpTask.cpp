#define INSANITY_BUILDING_LIBRARY

#include "CLinuxX11EventPumpTask.hpp"

#if defined(PLATFORM_LINUX)

#include <stdexcept>

namespace Insanity
{
	CLinuxX11EventPumpTask::CLinuxX11EventPumpTask(Display * dpy) : 
		_dpy(dpy)
	{
	}
	CLinuxX11EventPumpTask::~CLinuxX11EventPumpTask()
	{
	}

	//=====================================================
	//Implementation-specific
	//=====================================================
	void CLinuxX11EventPumpTask::RegisterProc(Window win,ProcType proc)
	{
		_procmap[win] = proc;
	}
	void CLinuxX11EventPumpTask::Clear(Window win)
	{
		_procmap.erase(win);
	}

	//=====================================================
	//Interface: ITask
	//=====================================================
	void CLinuxX11EventPumpTask::Perform()
	{
		XEvent xe;
		while(XPending(_dpy))
		{
			XNextEvent(_dpy, &xe);
			try
			{
				_procmap.at(xe.xany.window)(&xe);
			}
			catch(std::out_of_range oor)
			{
			}
		}
	}
	bool CLinuxX11EventPumpTask::ShouldRequeue()
	{
		return _procmap.size() != 0;
	}
}

#endif
