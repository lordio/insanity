#define INSANITY_BUILDING_LIBRARY

#include "CWindowsWin32EventPumpTask.hpp"

#if defined(PLATFORM_MSWINDOWS)

#include <IThread.hpp>
#include <IGarbageCollector.hpp>
#include <IApplication.hpp>

#include "CWindowsWin32Window.hpp"

namespace Insanity
{
	CWindowsWin32EventPumpTask::CWindowsWin32EventPumpTask() : Default::Task{}
	{
	}
	CWindowsWin32EventPumpTask::~CWindowsWin32EventPumpTask()
	{
	}

	//=====================================================
	//Implementation-specific
	//=====================================================

	//=====================================================
	//Interface: ITask
	//=====================================================
	void CWindowsWin32EventPumpTask::Perform()
	{
		//So um... I realized that, between all of the various implementations I've written to handle events,
		//	the simplest answer is perhaps a basic message loop, at least here.
		//	X11 can still use the registration system, as that's basically emulating Win32's setup anyway.
		MSG msg;
		ZeroMemory(&msg,sizeof(msg));

		while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if(msg.message == WM_QUIT) IApplication::GetInstance()->End();
		}
	}
	bool CWindowsWin32EventPumpTask::ShouldRequeue()
	{
		return CWindowsWin32Window::GetWindowCount() != 0;
	}
}

#endif