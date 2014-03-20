#define INSANITY_BUILDING_LIBRARY

#include "CMacOSXBSDStreamSocket.hpp"

#if defined(PLATFORM_MACOSX)

#include <IByteArray.hpp>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <cstring>
#include <cstdio>

namespace Insanity
{
	IStreamSocket * IStreamSocket::Create(char const * host, u16 port)
	{
		return new CMacOSXBSDStreamSocket(host,port);
	}

	CMacOSXBSDStreamSocket::CMacOSXBSDStreamSocket(char const * host, u16 port) : 
		_sock(0)
	{
		Connect(host, port);
	}
	CMacOSXBSDStreamSocket::CMacOSXBSDStreamSocket(int sock) : 
		_sock(sock)
	{
	}
	CMacOSXBSDStreamSocket::~CMacOSXBSDStreamSocket()
	{
		if(_sock) Close();
	}

	//=====================================================
	//Interface: IStreamSocket
	//=====================================================
	bool CMacOSXBSDStreamSocket::Connect(char const * host, u16 port)
	{
		if(_sock) Close();

		addrinfo hints;
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;

		addrinfo * ret = nullptr;
		addrinfo * ptr = nullptr;

		char cport[6] = "";
		snprintf(cport, 6, "%d", port);

		getaddrinfo(host, cport, &hints, &ret);

		ptr = ret;

		while(_sock == 0 && ptr != nullptr)
		{
			if((_sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) == -1)
			{
				_sock = 0;
				ptr = ptr->ai_next;
			}
			else if(connect(_sock, ptr->ai_addr, ptr->ai_addrlen) == -1)
			{
				_sock = 0;
				ptr = ptr->ai_next;
			}
		}
		freeaddrinfo(ret);

		if(_sock == 0) return false;

		return true;
	}
	bool CMacOSXBSDStreamSocket::Close()
	{
		if(_sock == 0) return false;

		close(_sock);
		_sock = 0;

		return true;
	}

	void CMacOSXBSDStreamSocket::Send(IByteArray const * arr)
	{
		u64 size = arr->Size();
		send(_sock, reinterpret_cast<char*>(&size), sizeof(u64), 0);
		send(_sock, reinterpret_cast<char const*>(arr->Array()), static_cast<int>(size), 0);
	}
	void CMacOSXBSDStreamSocket::Receive(IByteArray * arr)
	{
		u64 size = 0;
		recv(_sock, reinterpret_cast<char*>(&size), sizeof(u64), 0);

		u8 * buffer = new u8[size];
		recv(_sock, reinterpret_cast<char*>(buffer), static_cast<int>(size), 0);

		arr->Write(buffer, size);

		delete[] buffer;
	}

	bool CMacOSXBSDStreamSocket::HasPendingData() const
	{
		timeval tv;
		tv.tv_usec = 0;
		tv.tv_sec = 0;

		fd_set set;
		FD_ZERO(&set);
		FD_SET(_sock, &set);

		select(_sock + 1, &set, nullptr, nullptr, &tv);

		if(FD_ISSET(_sock, &set)) return true;
		else return false;
	}
	bool CMacOSXBSDStreamSocket::IsConnected() const
	{
		return (_sock != 0);
	}
}

#endif