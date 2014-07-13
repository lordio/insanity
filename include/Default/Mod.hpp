#ifndef INSANITY_DEFAULT_MOD
#define INSANITY_DEFAULT_MOD

//NOTE! Do not inherit this class when defining a mod interface!
//Mod interfaces should inherit from IMod.
//Mod implementations may inherit from Default::Mod.

#include "../Constants.hpp"
#include "../IMod.hpp"

namespace Insanity
{
	namespace Default
	{
		class INSANITY_API Mod : public virtual IMod
		{
			mutable u64 _ref{ 0 };
		public:
			Mod();
			virtual ~Mod();
			
			virtual void Retain() const override;
			virtual void Release() const override;
			virtual u64 GetReferenceCount() const override;
			virtual void Delete() override;
		};
	}
}

#endif
