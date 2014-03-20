#ifndef INSANITY_IMPLEMENTATION_MACOSX_BSD_STREAM_SOCKET
#define INSANITY_IMPLEMENTATION_MACOSX_BSD_STREAM_SOCKET

#include <Constants.hpp>

#if defined(PLATFORM_MACOSX)

#include <IStreamSocket.hpp>
#include <default/Object.hpp>

namespace Insanity
{
    class CMacOSXBSDStreamSocket final : public IStreamSocket, public Default::Object
    {
        int _sock;
    public:
        CMacOSXBSDStreamSocket(char const * host, u16 port);
        CMacOSXBSDStreamSocket(int accepted);
        ~CMacOSXBSDStreamSocket();
        
        //====================================================
        //Interface: IStreamSocket
        //====================================================
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