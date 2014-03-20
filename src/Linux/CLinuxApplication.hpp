#ifndef INSANITY_IMPLEMENTATION_LINUX_APPLICATION
#define INSANITY_IMPLEMENTATION_LINUX_APPLICATION

#include <Constants.hpp>

#if defined(PLATFORM_LINUX)

#include <IApplication.hpp>
#include <vector>

namespace Insanity
{
	class IGarbageCollector;
	class ITask;

	class CLinuxApplication final : public IApplication
	{
	private:
		std::vector<ITask*> _taskList;
		IGarbageCollector * _gc;
		mutable u64 _ref;
		bool _running;
		u8 _gcTicker;
	public:
		CLinuxApplication();
		~CLinuxApplication();
		
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
	};
}

#endif

#endif