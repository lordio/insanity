#ifndef INSANITY_IMPLEMENTATION_WINDOWS_WINSOCK_STREAM_SOCKET
#define INSANITY_IMPLEMENTATION_WINDOWS_WINSOCK_STREAM_SOCKET

#include <Constants.hpp>

#if defined(PLATFORM_MSWINDOWS)

#include <IStreamSocket.hpp>
#include <WinSock2.h>

#include "../Generic/CGenericObject.hpp"

namespace Insanity
{
	class CWindowsWinsockStreamSocket final : public IStreamSocket, public CGenericObject
	{
		SOCKET _sock;
	public:
		CWindowsWinsockStreamSocket(char const * host, u16 port);
		CWindowsWinsockStreamSocket(SOCKET accepted);
		~CWindowsWinsockStreamSocket();

		//=================================================
		//Interface: IStreamSocket
		//=================================================
		void Send(IByteArray const * buf) override;
		void Receive(IByteArray * buf) override;

		bool Connect(char const * host, u16 port) override;
		bool Close() override;

		bool HasPendingData() const override;
		bool IsConnected() const override;
	};
}

#endif

#endif