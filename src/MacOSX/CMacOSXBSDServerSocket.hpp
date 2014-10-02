#ifndef INSANITY_IMPLEMENTATION_MACOSX_BSD_SERVER_SOCKET
#define INSANITY_IMPLEMENTATION_MACOSX_BSD_SERVER_SOCKET

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

#include <IServerSocket.hpp>
#include "../Generic/CGenericObject.hpp"

namespace Insanity
{
	class CMacOSXBSDServerSocket final : public IServerSocket, public CGenericObject
    {
		int _sock{};
    public:
        CMacOSXBSDServerSocket(u16 port);
        ~CMacOSXBSDServerSocket();
        
        //===================================================
        //Interface: IServerSocket
        //===================================================
        bool Listen(u16 port) override;
        bool Close() override;
        IStreamSocket * Accept() override;
        bool IsOpen() const override;
    };
}

#endif

#endif