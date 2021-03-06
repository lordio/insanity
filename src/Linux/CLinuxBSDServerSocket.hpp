#ifndef INSANITY_IMPLEMENTATION_LINUX_BSD_SERVER_SOCKET
#define INSANITY_IMPLEMENTATION_LINUX_BSD_SERVER_SOCKET

#include <Constants.hpp>

#if defined(PLATFORM_LINUX)

#include <IServerSocket.hpp>
#include "../Generic/CGenericObject.hpp"

namespace Insanity
{
	class CLinuxBSDServerSocket final : public IServerSocket, public CGenericObject
	{
		//int used instead of s32 because it's the name Unix uses.
		int _sock{};
	public:
		CLinuxBSDServerSocket(u16 port);
		~CLinuxBSDServerSocket();

		//==================================================
		//Interface: IServerSocket
		//==================================================
		bool Listen(u16 port) override;
		bool Close() override;

		IStreamSocket * Accept() override;
		bool IsOpen() const override;
	};
}

#endif

#endif
