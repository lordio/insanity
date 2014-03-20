#define INSANITY_BUILDING_LIBRARY

#include "CWindowsWin32SubThread.hpp"

#if defined(PLATFORM_MSWINDOWS)

#include <IApplication.hpp>
#include <IGarbageCollector.hpp>
#include <ITask.hpp>

//Windows stores the current thread as CWindowsWin32SubThread*.

namespace Insanity
{
	DWORD CWindowsWin32SubThread::s_tls = 0;
	bool CWindowsWin32SubThread::s_tlsInitialized = false;

	ISubThread * ISubThread::Create(ISubThread * ext, bool start)
	{
		return new CWindowsWin32SubThread(ext, start);
	}

	//since this may return either an Application or SubThread, must return common interface.
	IThread * IThread::Current()
	{
		return CWindowsWin32SubThread::_Current();
	}

	IThread * CWindowsWin32SubThread::_Current()
	{
		//If the TLS isn't initialized, must be running on only one thread.
		if(!s_tlsInitialized) return IApplication::GetInstance();

		void * thrd = TlsGetValue(s_tls);

		//The main thread's TLS is never assigned. MSDN says TLS is initialized to NULL.
		if(thrd == nullptr) return IApplication::GetInstance();
		
		//If ret has an extension (should be most common case), return that.
		CWindowsWin32SubThread * ret = reinterpret_cast<CWindowsWin32SubThread*>(thrd);
		return (ret->_ext ? ret->_ext : ret);
	}

	void CWindowsWin32SubThread::_TLSInit()
	{
		//will always immediately return if not on main thread
		//If main thread, first run sets static bool to true, all further calls are skipped
		if(s_tlsInitialized) return;

		s_tls = TlsAlloc();
		s_tlsInitialized = true;
	}

	DWORD CALLBACK CWindowsWin32SubThread::_ThreadBoilerplate(void * params)
	{
		//the reference given in the ctor is assumed here
		//params->self->Retain();
		TlsSetValue(s_tls,params);

		CWindowsWin32SubThread * self = reinterpret_cast<CWindowsWin32SubThread*>(params);

		self->Main();

		self->_condition &= ~THREAD_RUNNING;
		self->_condition |= THREAD_RETURNED;
		self->_gc->Clean();
		self->Release();

		return 0;
	}

	CWindowsWin32SubThread::CWindowsWin32SubThread(ISubThread * ext, bool start) :
		_gc(IGarbageCollector::Create()), _ext(ext), _condition(0)
	{
		_TLSInit();

		//Cheat to ensure Thread is not GC'ed prematurely.
		Retain();

		if(start) Start();
		else _condition |= THREAD_WAITING;
	}
	CWindowsWin32SubThread::~CWindowsWin32SubThread()
	{
		//what should happen is, thread exits. backend object is cleaned up.
		//Frontend Thread object sticks around to have its fields referenced.
	}

	//=====================================================
	//Interface: ISubThread
	//=====================================================
	void CWindowsWin32SubThread::Main()
	{
		if(_ext) _ext->Main();
	}

	void CWindowsWin32SubThread::Start()
	{
		if(_condition & THREAD_RUNNING ||
			_condition & THREAD_RETURNED) return;

		//bool wasWaiting = _condition & THREAD_WAITING;

		_condition |= THREAD_RUNNING;
		_condition &= ~THREAD_WAITING;

		CreateThread(nullptr,1024,_ThreadBoilerplate,this,0,nullptr);
	}

	//=====================================================
	//Interface: IThread
	//=====================================================
	bool CWindowsWin32SubThread::Update()
	{
		if(!(_condition & THREAD_RUNNING)) return false;

		for(auto iter = _taskList.begin(); iter < _taskList.end();)
		{
			(*iter)->Perform();
			
			if(!(*iter)->ShouldRequeue())
			{
				(*iter)->Dequeue();
				(*iter)->Release();
				iter = _taskList.erase(iter);
			}
			else iter++;
		}

		if(++_gcTicker == 60)
		{
			_gc->Collect();
			_gcTicker = 0;
		}

		return (_condition & THREAD_RUNNING) == THREAD_RUNNING;
	}
	void CWindowsWin32SubThread::End()
	{
		_condition &= ~THREAD_RUNNING;
	}
	IGarbageCollector * CWindowsWin32SubThread::GetGarbageCollector() const
	{
		return _gc;
	}
	void CWindowsWin32SubThread::Yield() const
	{
		if(IsCurrentThread()) Sleep(0);
	}
	void CWindowsWin32SubThread::RegisterTask(ITask * task)
	{
		_taskList.push_back(task);
		task->Retain();
	}
	void CWindowsWin32SubThread::Transfer(IObject * obj)
	{
		IThread::Current()->GetGarbageCollector()->Untrack(obj);
		_gc->Track(obj);
	}
	bool CWindowsWin32SubThread::IsCurrentThread() const
	{
		return IThread::Current() == (IThread*)this;
	}
}

#endif
