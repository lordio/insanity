#ifndef INSANITY_IMPLEMENTATION_LINUX_BSD_SERVER_SOCKET
#define INSANITY_IMPLEMENTATION_LINUX_BSD_SERVER_SOCKET

#include <Constants.hpp>

#if defined(PLATFORM_LINUX)

#include <IServerSocket.hpp>

#include <Default.hpp>

namespace Insanity
{
	class CLinuxBSDServerSocket final : public IServerSocket, public Default::Object
	{
		//int used instead of s32 because it's the name Unix uses.
		int _sock;
		//u64 _ref;
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

		//==================================================
		//Interface: IObject
		//==================================================
		/*void Retain() override;
		void Release() override;
		u64 GetReferenceCount() const override;
		void Delete() override;*/
	};
}

#endif

#endif
