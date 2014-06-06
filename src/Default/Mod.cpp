#define INSANITY_BUILDING_LIBRARY

#include <Default/Mod.hpp>

namespace Insanity
{
	namespace Default
	{
		Mod::Mod() : _ref{ 0 }
		{
		}
		Mod::~Mod()
		{
		}
		
		void Mod::Retain() const
		{
			++_ref;
		}
		void Mod::Release() const
		{
			if(_ref == 0) return;
			if(--_ref == 0) delete this;
		}
		u64 Mod::GetReferenceCount() const
		{
			return _ref;
		}
		void Mod::Delete()
		{
			delete this;
		}
	}
}
