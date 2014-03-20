#define INSANITY_BUILDING_LIBRARY

#include "CWindowsWinsockServerSocket.hpp"

#if defined(PLATFORM_MSWINDOWS)

#include <WS2tcpip.h>
#include "CWindowsWinsockStreamSocket.hpp"

#include <IThread.hpp>
#include <IGarbageCollector.hpp>

#include <iostream>

namespace Insanity
{
	IServerSocket * IServerSocket::Create(u16 port)
	{
		return new CWindowsWinsockServerSocket(port);
	}

	CWindowsWinsockServerSocket::CWindowsWinsockServerSocket(u16 port) :
		_sock(0)//, _ref(0)
	{
		{
			WSAData unused;

			//check this for return values:
			//	WSASYSNOTREADY (The only one that may be the case, but what do I do about it?)
			//	WSAVERNOTSUPPORTED (version requested not supported, no.)
			//	WSAEPROCLIM (proclimit for winsock reached, would be bullshit if this is the case)
			//	WSAEFAULT (lpwsadata not valid pointer, shouldn't be the case)
			//	0 means it worked.
			WSAStartup(MAKEWORD(2,2),&unused);
		}
		if(!Listen(port)) std::cout << "Listen Error." << std::endl;
	}
	CWindowsWinsockServerSocket::~CWindowsWinsockServerSocket()
	{
		if(_sock) Close();

		WSACleanup();
	}

	//=====================================================
	//Interface: IServerSocket
	//=====================================================
	bool CWindowsWinsockServerSocket::Listen(u16 port)
	{
		if(_sock) Close();

		char sport[6] = "";
		_itoa_s(port,sport,10);

		addrinfo hints;
		ZeroMemory(&hints,sizeof(hints));
		hints.ai_flags = AI_PASSIVE;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_family = AF_UNSPEC;

		//hold onto the list head for the freeaddrinfo call
		addrinfo * list = nullptr;

		//pointer for iterating over the list
		addrinfo * ptr = nullptr;

		getaddrinfo(nullptr,sport,&hints,&list);

		ptr = list;

		while(_sock == 0 && ptr != nullptr)
		{
			if((_sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) == INVALID_SOCKET)
			{
				_sock = 0;
				ptr = ptr->ai_next;
				continue;
			}
			if(bind(_sock,ptr->ai_addr,static_cast<int>(ptr->ai_addrlen)) == SOCKET_ERROR)
			{
				_sock = 0;
				ptr = ptr->ai_next;
				continue;
			}
			if(listen(_sock,20) == SOCKET_ERROR)
			{
				_sock = 0;
				ptr = ptr->ai_next;
			}
		}
		freeaddrinfo(list);

		if(_sock == 0) return false;

		return true;
	}
	bool CWindowsWinsockServerSocket::Close()
	{
		if(!_sock) return false;

		closesocket(_sock);
		_sock = 0;
		return true;
	}
	IStreamSocket * CWindowsWinsockServerSocket::Accept()
	{
		timeval tv;
		ZeroMemory(&tv, sizeof(tv));

		fd_set fd;
		FD_ZERO(&fd);
		FD_SET(_sock,&fd);

		select(0,&fd,nullptr,nullptr,&tv);

		if(FD_ISSET(_sock,&fd))
		{
			sockaddr_storage unused1;
			int unused2 = sizeof(unused1);
			SOCKET accepted = accept(_sock,reinterpret_cast<sockaddr*>(&unused1),&unused2);
			CWindowsWinsockStreamSocket * acc = new CWindowsWinsockStreamSocket(accepted);
			return acc;
		}

		return nullptr;
	}
	bool CWindowsWinsockServerSocket::IsOpen() const
	{
		return (_sock != 0);
	}

	//=====================================================
	//Interface: IObject
	//=====================================================
	//void CWindowsWinsockServerSocket::Retain()
	//{
	//	++_ref;
	//}
	//void CWindowsWinsockServerSocket::Release()
	//{
	//	if(_ref == 0) return;
	//	--_ref;
	//}
	//u64 CWindowsWinsockServerSocket::GetReferenceCount() const
	//{
	//	return _ref;
	//}
	//void CWindowsWinsockServerSocket::Delete()
	//{
	//	delete this;
	//}
}

#endif