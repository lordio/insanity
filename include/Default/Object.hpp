#ifndef INSANITY_IMPLEMENTATION_DEFAULT_OBJECT
#define INSANITY_IMPLEMENTATION_DEFAULT_OBJECT

#include "../Constants.hpp"

#include "../IObject.hpp"

namespace Insanity
{
	namespace Default
	{
		class INSANITY_API Object : public virtual IObject
		{
		protected:
			mutable u64 ref;
		public:
			Object();
			virtual ~Object();

			//there shouldn't be any need to override these, but the option's open anyway.
			virtual void Retain() const override;
			virtual void Release() const override;
			virtual u64 GetReferenceCount() const override;
			virtual void Delete() override;
		};
	}
}

#endif