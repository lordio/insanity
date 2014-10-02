#ifndef INSANITY_COMMON
#define INSANITY_COMMON

#include "Constants.hpp"

namespace Insanity
{
	class IGarbageCollector;

	INSANITY_API IGarbageCollector * GetCurrentGC();
}

#endif