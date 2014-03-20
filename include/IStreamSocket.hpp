#ifndef INSANITY_INTERFACE_STREAM_SOCKET
#define INSANITY_INTERFACE_STREAM_SOCKET

#include "Constants.hpp"
#include "IObject.hpp"

namespace Insanity
{
	class IByteArray;

	class INSANITY_API IStreamSocket : public virtual IObject
	{
	public:
		//=================================================
		//Create a new StreamSocket
		//	Attempts to connect to host, at port.
		//	Will return an unconnected IStreamSocket if connection fails.
		//=================================================
		static IStreamSocket * Create(char const * host, u16 port);

		//=================================================
		//Communicate with remote peer.
		//	Silently ignores request if unconnected.
		//=================================================
		virtual void Send(IByteArray const * arr) = 0;
		virtual void Receive(IByteArray * arr) = 0;

		//=================================================
		//Attempt to connect to host, at port.
		//	Returns false if the connection fails, true otherwise.
		//	Will Close() the socket if it is open.
		//=================================================
		virtual bool Connect(const char * host, u16 port) = 0;

		//=================================================
		//Stops communications on the socket.
		//	Returns false if socket was already not open, true otherwise.
		//=================================================
		virtual bool Close() = 0;

		//=================================================
		//Returns false if the socket is not open, or if there is no pending data.
		//	True otherwise.
		//=================================================
		virtual bool HasPendingData() const = 0;

		//=================================================
		//Returns true if the socket is connected to a server
		//	false otherwise.
		//=================================================
		virtual bool IsConnected() const = 0;
	};
}

#endif