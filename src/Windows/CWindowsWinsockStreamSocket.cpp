#define INSANITY_BUILDING_LIBRARY

#include "CWindowsWinsockStreamSocket.hpp"

#if defined(PLATFORM_MSWINDOWS)

#include <WS2tcpip.h>
#include <IByteArray.hpp>
#include "CWindowsWinsockTracker.hpp"

#include <IThread.hpp>
#include <IGarbageCollector.hpp>

#pragma comment(lib, "Ws2_32.lib")

namespace Insanity
{
	IStreamSocket * IStreamSocket::Create(char const * host, u16 port)
	{
		return new CWindowsWinsockStreamSocket(host,port);
	}

	CWindowsWinsockStreamSocket::CWindowsWinsockStreamSocket(char const * host, u16 port) :
		_sock(0)
	{
		CWindowsWinsockTracker::Retain();
		Connect(host,port);
	}
	CWindowsWinsockStreamSocket::CWindowsWinsockStreamSocket(SOCKET accepted) :
		_sock(accepted)
	{
		CWindowsWinsockTracker::Retain();
	}
	CWindowsWinsockStreamSocket::~CWindowsWinsockStreamSocket()
	{
		if(_sock) Close();

		CWindowsWinsockTracker::Release();
	}

	//=====================================================
	//Interface: IStreamSocket
	//=====================================================
	void CWindowsWinsockStreamSocket::Send(IByteArray const * buf)
	{
		u64 size = buf->Size();
		send(_sock,reinterpret_cast<char*>(&size),sizeof(u64),0);
		send(_sock,reinterpret_cast<char const*>(buf->Array()),static_cast<int>(size),0);
	}
	void CWindowsWinsockStreamSocket::Receive(IByteArray * buf)
	{
		u64 size = 0;
		recv(_sock,reinterpret_cast<char*>(&size),sizeof(u64),0);
		
		u8 * buffer = new u8[size];
		recv(_sock,reinterpret_cast<char*>(buffer),static_cast<int>(size),0);

		buf->Write(buffer,size);

		delete [] buffer;
	}

	bool CWindowsWinsockStreamSocket::Connect(char const * host, u16 port)
	{
		if(_sock) Close();

		ADDRINFO hints;
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;

		ADDRINFO * ret = nullptr;
		ADDRINFO * ptr = nullptr;

		char cport[6] = "";
		_itoa_s(port,cport,10);

		GetAddrInfo(host,cport,&hints,&ret);

		ptr = ret;

		while(_sock == 0 && ptr != nullptr)
		{
			if ((_sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) == -1)
			{
				_sock = 0;
				ptr = ptr->ai_next;
			}

			if(connect(_sock, ptr->ai_addr, static_cast<int>(ptr->ai_addrlen)) == -1)
			{
				_sock = 0;
				ptr = ptr->ai_next;
			}
		}

		FreeAddrInfo(ret);

		if(_sock == 0) return false;

		return true;
	}
	bool CWindowsWinsockStreamSocket::Close()
	{
		if(_sock == 0) return false;

		closesocket(_sock);
		_sock = 0;

		return true;
	}
	bool CWindowsWinsockStreamSocket::HasPendingData() const
	{
		timeval tv;
		ZeroMemory(&tv, sizeof(tv));

		fd_set set;
		FD_ZERO(&set);
		FD_SET(_sock,&set);

		select(0,&set,nullptr,nullptr,&tv);

		if(FD_ISSET(_sock,&set)) return true;
		else return false;
	}
	bool CWindowsWinsockStreamSocket::IsConnected() const
	{
		return (_sock != 0);
	}
}

#endif
