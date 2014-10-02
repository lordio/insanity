#ifndef INSANITY_IMPLEMENTATION_LINUX_APPLICATION
#define INSANITY_IMPLEMENTATION_LINUX_APPLICATION

#include <Constants.hpp>

#if defined(PLATFORM_LINUX)

#include <IApplication.hpp>
#include <Ptr.hpp>
#include <vector>
#include <memory>

namespace Insanity
{
	class IGarbageCollector;
	class ITask;

	class CLinuxApplication final : public IApplication
	{
	private:
		std::vector<Ptr<ITask>> _taskList{};
		std::unique_ptr<IGarbageCollector> _gc;
		mutable u64 _ref{0};
		bool _running{true};
		u8 _gcTicker{0};
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
		bool ShouldBeTracked() const override;
	};
}

#endif

#endif
