#ifndef INSANITY_IMPLEMENTATION_WINDOWS_WINSOCK_TRACKER
#define INSANITY_IMPLEMENTATION_WINDOWS_WINSOCK_TRACKER

#include <Constants.hpp>

namespace Insanity
{
	//static class for keeping track of existing references to Winsock.
	class CWindowsWinsockTracker final
	{
	private:
		//Should not be instantiated, ctor and dtor made private.
		CWindowsWinsockTracker();
		~CWindowsWinsockTracker();
	
		static u64 s_ref;
	public:
		static void Retain();
		static void Release();
	};
}

#endif
