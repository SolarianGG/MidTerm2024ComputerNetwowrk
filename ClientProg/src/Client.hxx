#pragma once

#include <string>

namespace network {

	class ConnectionHandler
	{
	private:
		int port_;

		std::string ip_;

		unsigned __int64 s;

	public:
		ConnectionHandler(int port = 5150, std::string ip = "192.168.192.1", unsigned __int64 s_ = 0)
			: port_(port), ip_(ip), s(s_)
		{}

		bool Initialize();

		bool Connect();

		bool SendData(const char* data, size_t data_size) const;

		bool ReceiveData(char* data, size_t data_size) const;

		bool Disconect();

		void SetServerIP(const std::string& ip) { ip_ = ip; }

		void SetServerPort(int port) { port_ = port; }

		~ConnectionHandler() { }

		// Removing default copy constructor and operator= to avoid copying

		ConnectionHandler(const ConnectionHandler& other) = delete;

		ConnectionHandler& operator=(const ConnectionHandler& other) = delete;
	};
}