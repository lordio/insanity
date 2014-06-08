#define INSANITY_BUILDING_LIBRARY

#include <Default/Thread.hpp>

namespace Insanity
{
	namespace Default
	{
		Thread::Thread() : _base{ ISubThread::Create(this, false) }, Object{}
		{
			//need a way to override IThread::Current to return this instead of _base.

			//If it's known that IThread implementations may have an extension, it can do
			//	if(curr->ext ? curr->ext : curr)

			_base->Retain();
		}
		Thread::~Thread()
		{
			_base->Release();
		}

		//=================================================
		//Interface: ISubThread
		//=================================================
		void Thread::Main()
		{
			//does nothing by default. Override with actual method.

			//_base->Main() calls this.
		}
		void Thread::Start()
		{
			_base->Start();
		}

		//=================================================
		//Interface: IThread
		//=================================================
		bool Thread::Update()
		{
			return _base->Update();
		}
		void Thread::Yield() const
		{
			_base->Yield();
		}
		void Thread::End()
		{
			_base->End();
		}
		IGarbageCollector * Thread::GetGarbageCollector() const
		{
			return _base->GetGarbageCollector();
		}
		void Thread::RegisterTask(ITask * task)
		{
			_base->RegisterTask(task);
		}
		void Thread::Transfer(IObject * obj)
		{
			_base->Transfer(obj);
		}
		bool Thread::IsCurrentThread() const
		{
			return _base->IsCurrentThread();
		}

		//Default::Object ensures this object manages reference counting, not _base.
	}
}