#ifndef INSANITY_IMPLEMENTATION_WINDOWS_APPLICATION
#define INSANITY_IMPLEMENTATION_WINDOWS_APPLICATION

#include <Constants.hpp>

#if defined(PLATFORM_MSWINDOWS)

#include <IApplication.hpp>
#include <Ptr.hpp>
#include <list>
#include <memory>

namespace Insanity
{
	class IGarbageCollector;
	class ITask;

	class CWindowsApplication final : public IApplication
	{
	private:
		std::list<Ptr<ITask>> _taskList{};
		std::unique_ptr<IGarbageCollector> _gc; //is not reference counted, so manage with unique_ptr
		mutable u64 _ref{ 0 };
		bool _running{ true };
		u8 _gcTicker{ 0 };
	public:
		CWindowsApplication();
		~CWindowsApplication();

		//=================================================
		//Interface: IThread
		//=================================================
		bool Update() override;
		void End() override;
		IGarbageCollector * GetGarbageCollector() const override;
		void Yield() const override;
		void RegisterTask(ITask * task) override;
		void Transfer(IObject * obj) override;
		bool IsCurrentThread() const override;

		//=================================================
		//Interface: IObject
		//=================================================
		void Retain() const override;
		void Release() const override;
		u64 GetReferenceCount() const override;
		void Delete() override;
		bool ShouldBeTracked() const override;
		bool IsBeingTracked() const override;
		void SetIsTracked(bool) override;
	};
}

#endif

#endif
