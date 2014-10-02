#define INSANITY_BUILDING_LIBRARY

#include "CWindowsWinsockServerSocket.hpp"

#if defined(PLATFORM_MSWINDOWS)

#include <WS2tcpip.h>
#include "CWindowsWinsockStreamSocket.hpp"
#include "CWindowsWinsockTracker.hpp"

#include <IThread.hpp>
#include <IGarbageCollector.hpp>
#include <Ptr.hpp>

#include <iostream>
#include <cassert>
#include <string>

namespace Insanity
{
	IServerSocket * IServerSocket::Create(u16 port)
	{
		return new CWindowsWinsockServerSocket{ port };
	}

	CWindowsWinsockServerSocket::CWindowsWinsockServerSocket(u16 port) :
		CGenericObject{}
	{
		CWindowsWinsockTracker::Retain();
		Listen(port);
	}
	CWindowsWinsockServerSocket::~CWindowsWinsockServerSocket()
	{
		if(_sock) Close();

		CWindowsWinsockTracker::Release();
	}

	//=====================================================
	//Interface: IServerSocket
	//=====================================================
	bool CWindowsWinsockServerSocket::Listen(u16 port)
	{
		if (_sock) Close();

		std::wstring wport{ std::to_wstring(port) };

		ADDRINFOW hints;
		ZeroMemory(&hints,sizeof(hints));
		hints.ai_flags = AI_PASSIVE;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_family = AF_UNSPEC;

		//hold onto the list head for the freeaddrinfo call
		ADDRINFOW * list{};

		//pointer for iterating over the list
		ADDRINFOW * ptr{};

		GetAddrInfoW(nullptr,wport.c_str(),&hints,&list);

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
		FreeAddrInfoW(list);

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
		timeval tv{};

		fd_set fd;
		FD_ZERO(&fd);
		FD_SET(_sock,&fd);

		select(0,&fd,nullptr,nullptr,&tv);

		if(FD_ISSET(_sock,&fd))
		{
			sockaddr_storage unused1;
			int unused2{ sizeof(unused1) };
			SOCKET accepted{ accept(_sock, reinterpret_cast<sockaddr*>(&unused1), &unused2) };
			WeakPtr<CWindowsWinsockStreamSocket> acc{ new CWindowsWinsockStreamSocket{ accepted } };
			return acc;
		}

		return nullptr;
	}
	bool CWindowsWinsockServerSocket::IsOpen() const
	{
		return (_sock != 0);
	}
}

#endif
