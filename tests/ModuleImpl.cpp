#include "ConformanceTestMod.hpp"
#include <Default/Mod.hpp>

class ModuleImpl final : public ConformanceTestMod, public Insanity::Default::Mod
{
public:
	ModuleImpl() {}

	char const * GetValue() override { return "Deathmole"; }
};

extern "C" ATTRIBUTE_EXPORT Insanity::IMod * InitMod()
{
	return new ModuleImpl();
}