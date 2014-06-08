#define INSANITY_BUILDING_LIBRARY

#include "CLinuxSubThread.hpp"

#if defined(PLATFORM_LINUX)

#include <IApplication.hpp>
#include <IGarbageCollector.hpp>
#include <ITask.hpp>
#include <algorithm>

//Linux stores current thread pointer as CLinuxSubThread*.

namespace Insanity
{
	pthread_key_t CLinuxSubThread::s_curThreadKey{};
	bool CLinuxSubThread::s_threadInit{};

	ISubThread * ISubThread::Create(ISubThread * ext, bool start)
	{
		return new CLinuxSubThread{ext,start};
	}

	IThread * IThread::Current()
	{
		return CLinuxSubThread::_Current();
	}
	IThread * CLinuxSubThread::_Current()
	{
		//if the TLS for current threads hasn't been initialized, then we must be running on the main thread.
		if(!s_threadInit) return IApplication::GetInstance();

		//pthread_getspecific is guaranteed to return nullptr if it hasn't had a value set yet.
		void * spec{pthread_getspecific(s_curThreadKey)};
		
		//if no value for this thread, then it's the main thread, as the Application doesn't know if there is a Thread class.
		if(spec == nullptr) return IApplication::GetInstance();

		WeakPtr<CLinuxSubThread> ret{reinterpret_cast<CLinuxSubThread*>(spec)};
		return (ret->_ext ? ret->_ext.Get() : ret.Get());
		//if the key has been initialized, then return the extension, if available (should be).
	}
	void CLinuxSubThread::_TLSInit()
	{
		if(s_threadInit) return;

		pthread_key_create(&s_curThreadKey,nullptr);
		s_threadInit = true;
	}
	void * CLinuxSubThread::_ThreadBoilerplate(void * params)
	{
		//NOTE: This function is being called by the thread represented by params.

		//startup phase
		pthread_setspecific(s_curThreadKey,params);

		WeakPtr<CLinuxSubThread> self{reinterpret_cast<CLinuxSubThread*>(params)};

		//execute the requested thread function
		self->Main();

		//cleanup phase
		self->_condition = ThreadState::Returned;
		self->Release();

		return nullptr;
	}

	//A thread should be managed by its parent thread's garbage collector.
	CLinuxSubThread::CLinuxSubThread(ISubThread * ext, bool start) :
		_taskList{},
		_gc{IGarbageCollector::Create()},
		_ext{ext},
		_condition{ThreadState::Waiting},
		_gcTicker{}
	{
		//NOTE: This ctor is being called in the parent thread.

		//Ensure the thread-local storage key is initialized.
		_TLSInit();

		Retain();

		if(start) Start();
	}
	CLinuxSubThread::~CLinuxSubThread()
	{
	}

	//=====================================================
	//Interface: ISubThread
	//=====================================================
	void CLinuxSubThread::Start()
	{
		//if the thread is already running or completed, don't start it again.
		if(_condition != ThreadState::Waiting) return;

		_condition = ThreadState::Waiting;

		//apparently the first param is needed, but we don't use it
		pthread_t unused;
		pthread_create(&unused,nullptr,_ThreadBoilerplate,this);
	}
	void CLinuxSubThread::Main()
	{
		if(_ext) _ext->Main();
	}

	//=====================================================
	//Interface: IThread
	//=====================================================
	bool CLinuxSubThread::Update()
	{
		if(_condition != ThreadState::Running) return false;

		for(auto iter = _taskList.begin(); iter != _taskList.end();)
		{
			(*iter)->Perform();
			
			if(!(*iter)->ShouldRequeue())
			{
				(*iter)->Dequeue();
				iter = _taskList.erase(iter);
			}
			else iter++;
		}

		if(++_gcTicker == 60)
		{
			_gc->Collect();
			_gcTicker = 0;
		}

		return _condition == ThreadState::Running;
	}
	void CLinuxSubThread::End()
	{
		_condition = ThreadState::Returning;
	}
	IGarbageCollector * CLinuxSubThread::GetGarbageCollector() const
	{
		return _gc.get();
	}
	void CLinuxSubThread::Yield() const
	{
		if(IsCurrentThread()) pthread_yield();
	}
	void CLinuxSubThread::RegisterTask(ITask * task)
	{
		_taskList.push_back(task);
	}
	void CLinuxSubThread::Transfer(IObject * obj)
	{
		IThread::Current()->GetGarbageCollector()->Untrack(obj);
		_gc->Track(obj);
	}
	bool CLinuxSubThread::IsCurrentThread() const
	{
		return IThread::Current() == (IThread*)this;
	}
}

#endif
