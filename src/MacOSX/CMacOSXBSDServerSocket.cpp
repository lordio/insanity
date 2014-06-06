#define INSANITY_BUILDING_LIBRARY

#include "CMacOSXBSDServerSocket.hpp"

#if defined(PLATFORM_MACOSX)

//Linux pulls in IThread and IGarbageCollector; why?
#include "CMacOSXBSDStreamSocket.hpp"
#include <Ptr.hpp>

#include <string>
#include <cstring>
#include <cstdio>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

namespace Insanity
{
    IServerSocket * IServerSocket::Create(u16 port)
    {
		return new CMacOSXBSDServerSocket{port};
    }
    
	CMacOSXBSDServerSocket::CMacOSXBSDServerSocket(u16 port) : _sock{}
    {
        Listen(port);
    }
    CMacOSXBSDServerSocket::~CMacOSXBSDServerSocket()
    {
        if(_sock != 0) Close();
    }
    
    //=====================================================
    //Interface: IServerSocket
    //=====================================================
    bool CMacOSXBSDServerSocket::Listen(u16 port)
    {
		if(_sock != 0) Close();
        
        addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_flags = AI_PASSIVE;
        hints.ai_socktype = SOCK_STREAM;
		hints.ai_family = AF_UNSPEC;

		addrinfo * list{};
		addrinfo * ptr{};

		std::string cport{std::to_string(port)};
        
        getaddrinfo(nullptr, cport.c_str(), &hints, &list);
        
        ptr = list;
        
        while(_sock == 0 && ptr != nullptr)
        {
            if((_sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) == -1)
            {
                _sock = 0;
                ptr = ptr->ai_next;
            }
            else if(bind(_sock, ptr->ai_addr, ptr->ai_addrlen) == -1)
            {
                _sock = 0;
                ptr = ptr->ai_next;
            }
            else if(listen(_sock, 20) == -1)
            {
                _sock = 0;
                ptr = ptr->ai_next;
            }
        }
        
        freeaddrinfo(list);
        
        if(_sock == 0) return false;
        
        return true;
    }
    bool CMacOSXBSDServerSocket::Close()
    {
        if(_sock == 0) return false;
        
        close(_sock);
        _sock = 0;
        return true;
    }
    
    IStreamSocket * CMacOSXBSDServerSocket::Accept()
	{
		timeval tv{};

		fd_set fd;
		FD_ZERO(&fd);
		FD_SET(_sock, &fd);

		if(select(_sock+1, &fd, nullptr, nullptr, &tv) == -1) return nullptr;

		if(FD_ISSET(_sock, &fd));
		{
			sockaddr_storage unused1;
			socklen_t unused2{sizeof(unused1)};

			int accepted{accept(_sock, reinterpret_cast<sockaddr*>(&unused1),&unused2)};
			WeakPtr<CMacOSXBSDStreamSocket> acc{new CMacOSXBSDStreamSocket{accepted}};
			return acc;
		}
        return nullptr;
    }
    bool CMacOSXBSDServerSocket::IsOpen() const
    {
        return (_sock != 0);
    }
}

#endif