#define INSANITY_BUILDING_LIBRARY

#include "CLinuxApplication.hpp"

#if defined(PLATFORM_LINUX)

#include <IGarbageCollector.hpp>
#include <ITask.hpp>
#include <IMod.hpp>

#include <pthread.h>
#include <algorithm>

namespace Insanity
{
	IApplication * IApplication::s_app{};

	IApplication * IApplication::GetInstance()
	{
		if(s_app) return s_app;
		
		return s_app = new CLinuxApplication{};
	}
	
	CLinuxApplication::CLinuxApplication() :
		_gc{IGarbageCollector::Create()}
	{
	}
	CLinuxApplication::~CLinuxApplication()
	{
		//Let go of all mods, to ensure proper cleanup.
		IMod::ClearCache();

		s_app = nullptr;
	}
	
	//=====================================================
	//Interface: IThread
	//=====================================================
	bool CLinuxApplication::Update()
	{
		//check once so garbage collection isn't run if it's not necessary.
		//	The Application dtor will empty out the garbage collector anyway.
		if(!_running) return false;
		
		//some sort of taskmaster setup?
		//	I.E., objects register tasks to be run on update.
		//	Perhaps not built in?
		for(auto iter = _taskList.begin(); iter < _taskList.end();)
		{
			(*iter)->Perform();
			
			if(!(*iter)->ShouldRequeue())
			{
				(*iter)->Dequeue();
				iter = _taskList.erase(iter);
			}
			else iter++;
		}
		
		//Can play with this for different effects.
		//Could do a pass every time _gcTicker equals _gc's count of objects.
		if(++_gcTicker == 60)
		{
			_gc->Collect();
			_gcTicker = 0;
		}
		
		//in case collecting an object requested application end.
		return _running;
	}
	void CLinuxApplication::End()
	{
		_running = false;
	}
	IGarbageCollector * CLinuxApplication::GetGarbageCollector() const
	{
		return _gc.get();
	}
	void CLinuxApplication::Yield() const
	{
		if(IsCurrentThread()) pthread_yield();
	}
	void CLinuxApplication::RegisterTask(ITask * task)
	{
		_taskList.push_back(task);
	}
	void CLinuxApplication::Transfer(IObject * obj)
	{
		IThread::Current()->GetGarbageCollector()->Untrack(obj);
		_gc->Track(obj);
	}
	bool CLinuxApplication::IsCurrentThread() const
	{
		return IThread::Current() == (IThread*)this;
	}

	//=====================================================
	//Interface: IObject
	//=====================================================
	void CLinuxApplication::Retain() const
	{
		++_ref;
	}
	void CLinuxApplication::Release() const
	{
		if(_ref == 0) return;
		if(--_ref == 0) delete this; //since the Application is not managed by a GarbageCollector, it should delete itself.

		//If a COMPtr is used (as expected), Release will be called on exit from main.
		//Principle of least astonishment dictates the Application should behave like any other object.
	}
	u64 CLinuxApplication::GetReferenceCount() const
	{
		return _ref;
	}
	void CLinuxApplication::Delete()
	{
		delete this;
	}
	bool CLinuxApplication::ShouldBeTracked() const
	{
		return false;
	}
}

#endif
