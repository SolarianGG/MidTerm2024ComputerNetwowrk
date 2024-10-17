#pragma once

#include <string>

namespace network {

	class ConnectionHandler
	{
	private:
		int port_ = 5150;

		std::string ip_ = "192.168.192.1";

		unsigned __int64 s = 0;

	public:
		ConnectionHandler() {}

		ConnectionHandler(int port, std::string ip) 
			: port_(port), ip_(ip)
		{}

		bool Initialize();

		bool Connect();

		bool Disconect();

		~ConnectionHandler() {}
	};
}