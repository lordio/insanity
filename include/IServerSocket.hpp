#ifndef INSANITY_INTERFACE_SERVER_SOCKET
#define INSANITY_INTERFACE_SERVER_SOCKET

#include "Constants.hpp"
#include "IObject.hpp"

namespace Insanity
{
	class IStreamSocket;

	class INSANITY_API IServerSocket : public virtual IObject
	{
		//<property>
		//u16 port
		//</property>
	public:
		//=================================================
		//Creates a new server socket on port.
		//=================================================
		static IServerSocket * Create(u16 port);

		//Returns false if operation could not complete, true otherwise
		//Will call Close if the socket is already open.
		//starts listening for TCP/IP connections on port
		virtual bool Listen(u16 port) = 0;

		//Returns false if the socket is already closed, true otherwise
		//Stops listening on open socket
		virtual bool Close() = 0;

		//Returns a new stream socket if a connection is waiting, nullptr otherwise
		virtual IStreamSocket * Accept() = 0;

		virtual bool IsOpen() const = 0;
	};
}

#endif