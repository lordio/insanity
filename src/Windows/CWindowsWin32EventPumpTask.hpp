#ifndef INSANITY_IMPLEMENTATION_WINDOWS_WIN32_EVENT_PUMP_TASK
#define INSANITY_IMPLEMENTATION_WINDOWS_WIN32_EVENT_PUMP_TASK

#include <Constants.hpp>

#if defined(PLATFORM_MSWINDOWS)

#include <ITask.hpp>
#include <map>
#include <functional>

#include <Windows.h>

#include <Default.hpp>

namespace Insanity
{
	//should only ever be added to the Application.

	class CWindowsWin32EventPumpTask final : public Default::Task
	{
	public:
		CWindowsWin32EventPumpTask();
		~CWindowsWin32EventPumpTask();

		//=================================================
		//Implementation-specific
		//=================================================

		//=================================================
		//Interface: ITask
		//=================================================
		void Perform() override;
		bool ShouldRequeue() override;
	};
}

#endif

#endif