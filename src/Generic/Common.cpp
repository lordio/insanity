#define INSANITY_BUILDING_LIBRARY

#include <Common.hpp>
#include <IThread.hpp>

namespace Insanity
{
	IGarbageCollector * GetCurrentGC()
	{
		return IThread::Current()->GetGarbageCollector();
	}
}