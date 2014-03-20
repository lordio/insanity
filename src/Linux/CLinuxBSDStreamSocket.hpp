#ifndef INSANITY_IMPLEMENTATION_LINUX_BSD_STREAM_SOCKET
#define INSANITY_IMPLEMENTATION_LINUX_BSD_STREAM_SOCKET

#include <Constants.hpp>

#if defined(PLATFORM_LINUX)

#include <IStreamSocket.hpp>
#include <default/Object.hpp>

namespace Insanity
{
	class CLinuxBSDStreamSocket final : public IStreamSocket, public Default::Object
	{
		int _sock;
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

		//=================================================
		//Interface: IObject
		//=================================================
		/*void Retain() override;
		void Release() override;
		u64 GetReferenceCount() const override;
		void Delete () override;*/
	};
}

#endif

#endif
