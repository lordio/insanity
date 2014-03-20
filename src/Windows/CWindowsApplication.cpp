#define INSANITY_BUILDING_LIBRARY

#include "CWindowsApplication.hpp"

#if defined(PLATFORM_MSWINDOWS)

#include <IGarbageCollector.hpp>
#include <IMod.hpp>
#include <ITask.hpp>
#include <Windows.h>

#ifdef Yield
#undef Yield
#endif

namespace Insanity
{
	IApplication * IApplication::s_app = nullptr;

	IApplication * IApplication::GetInstance()
	{
		if(s_app) return s_app;

		return s_app = new CWindowsApplication();
	}

	CWindowsApplication::CWindowsApplication() :
		_gc(IGarbageCollector::Create()), _ref(0), _running(true)
	{
	}
	CWindowsApplication::~CWindowsApplication()
	{
		IMod::ClearCache();

		_gc->Clean();
		delete _gc;

		s_app = nullptr;
	}

	//========================================================
	//Interface: IThread
	//========================================================
	bool CWindowsApplication::Update()
	{
		//If we're about to stop anyway, don't run the GC. It'll be cleaned on Application deletion.
		if(!_running) return false;

		//Run all waiting tasks.
		for (auto iter = _taskList.begin(); iter < _taskList.end();)
		{
			(*iter)->Perform();

			if (!(*iter)->ShouldRequeue())
			{
				(*iter)->Dequeue();
				(*iter)->Release();
				iter = _taskList.erase(iter); //erase returns a valid iterator pointing to the element after the erased one
			}
			else iter++;
		}

		//Has it been long enough to do a garbage pass?
		//Could make this configurable
		//	Not if IConfigFile is garbage collected, I can't.
		//	No, I can totally make this configurable. Have it default to, say, 60, then allow the config file to override it.
		if(++_gcTicker == 60)
		{
			_gc->Collect();
			_gcTicker = 0;
		}

		return _running;
	}
	void CWindowsApplication::End()
	{
		_running = false;
	}
	IGarbageCollector * CWindowsApplication::GetGarbageCollector() const
	{
		return _gc;
	}
	void CWindowsApplication::Yield() const
	{
		if(IsCurrentThread()) Sleep(0);
	}
	void CWindowsApplication::RegisterTask(ITask * task)
	{
		_taskList.push_back(task);
		task->Retain(); //tasklist keeps tasks with strong pointers.
	}
	void CWindowsApplication::Transfer(IObject * obj)
	{
		//mostly just prettying up garbage collector untrack/track
		IThread::Current()->GetGarbageCollector()->Untrack(obj);
		_gc->Track(obj);
	}
	bool CWindowsApplication::IsCurrentThread() const
	{
		return IThread::Current() == (IThread*)this;
	}

	//=====================================================
	//Interface: IObject
	//=====================================================
	void CWindowsApplication::Retain() const
	{
		_ref++;
	}
	void CWindowsApplication::Release() const
	{
		//since Application is not GC'ed, delete if reference count goes to 0.
		if(_ref == 0) return;
		if(--_ref == 0) delete this;
	}
	u64 CWindowsApplication::GetReferenceCount() const
	{
		return _ref;
	}
	void CWindowsApplication::Delete()
	{
		delete this;
	}
}

#endif
