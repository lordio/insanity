#define INSANITY_BUILDING_LIBRARY

#include "CWindowsWinsockTracker.hpp"
#include <WinSock2.h>

namespace Insanity
{
	u64 CWindowsWinsockTracker::s_ref{};
	
	void CWindowsWinsockTracker::Retain()
	{
		//if s_ref is 1 after increment
		if(++s_ref == 1)
		{
			WSADATA unused;
			WSAStartup(MAKEWORD(2,2), &unused);
		}
	}
	void CWindowsWinsockTracker::Release()
	{
		//if s_ref is already 0, don't underflow.
		if(s_ref == 0) return;
		
		//if s_ref is 0 after decrement
		if(--s_ref == 0) WSACleanup();
	}
}
