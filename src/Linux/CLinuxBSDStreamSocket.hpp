#ifndef INSANITY_IMPLEMENTATION_LINUX_BSD_STREAM_SOCKET
#define INSANITY_IMPLEMENTATION_LINUX_BSD_STREAM_SOCKET

#include <Constants.hpp>

#if defined(PLATFORM_LINUX)

#include <IStreamSocket.hpp>
#include <Default/Object.hpp>

namespace Insanity
{
	class CLinuxBSDStreamSocket final : public IStreamSocket, public Default::Object
	{
		int _sock; //no in-class initializer; ctors will set different values
	public:
		CLinuxBSDStreamSocket(char const * host, u16 port);
		CLinuxBSDStreamSocket(int accepted);
		~CLinuxBSDStreamSocket();

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
