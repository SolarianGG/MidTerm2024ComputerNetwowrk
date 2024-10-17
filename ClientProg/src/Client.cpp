#include <winsock2.h>
#include <stdio.h>
#include <iostream>
#include "Client.hxx"

#pragma comment(lib, "ws2_32.lib")

namespace network {
	bool ConnectionHandler::Initialize()
	{
		WSADATA              wsaData;
		int                  Ret;

		if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
		{
			// NOTE: Since Winsock failed to load we cannot use WSAGetLastError 
			// to determine the error code as is normally done when a Winsock 
			// API fails. We have to report the return status of the function.

			std::cerr << "WSAStartup failed with error " << Ret << std::endl;
			return false;
		}

		if ((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
			== INVALID_SOCKET)
		{
			std::cerr << "socket failed with error " << WSAGetLastError() << std::endl;
			WSACleanup();
			return false;
		}

		return true;
	}

	bool ConnectionHandler::Connect()
	{
		SOCKADDR_IN          ServerAddr;
		ServerAddr.sin_family = AF_INET;
		ServerAddr.sin_port = htons(port_);
		ServerAddr.sin_addr.s_addr = inet_addr(ip_.c_str());

		// Make a connection to the server with socket s.

		printf("We are trying to connect to %s:%d...\n",
			inet_ntoa(ServerAddr.sin_addr), htons(ServerAddr.sin_port));

		if (connect(s, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr))
			== SOCKET_ERROR)
		{
			std::cerr << "socket failed with error " << WSAGetLastError() << std::endl;
			closesocket(s);
			WSACleanup();
			return false;
		}
		std::cout << "Our connection succeeded.\n";

		return true;
	}

	bool ConnectionHandler::Disconect()
	{
		std::cout << "We are closing the connection.\n";
		closesocket(s);
		WSACleanup();
		return true;
	}
}