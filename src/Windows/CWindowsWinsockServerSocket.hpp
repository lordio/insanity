#ifndef INSANITY_IMPLEMENTATION_WINDOWS_WINSOCK_SERVER_SOCKET
#define INSANITY_IMPLEMENTATION_WINDOWS_WINSOCK_SERVER_SOCKET

#include <Constants.hpp>

#if defined(PLATFORM_MSWINDOWS)

#include <IServerSocket.hpp>
#include <WinSock2.h>

#include "../Generic/CGenericObject.hpp"

namespace Insanity
{
	class CWindowsWinsockServerSocket final : public IServerSocket, public CGenericObject
	{
		SOCKET _sock{};
	public:
		CWindowsWinsockServerSocket(u16 port);
		~CWindowsWinsockServerSocket();

		//=================================================
		//Interface: IServerSocket
		//=================================================
		bool Listen(u16 port) override;
		bool Close() override;
		IStreamSocket * Accept() override;
		bool IsOpen() const override;
	};
}

#endif

#endif