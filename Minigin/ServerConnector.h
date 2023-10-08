#pragma once
#include <string>
#include <winsock2.h>

#include "Singleton.h"

namespace dae
{
	class GameObject;

	enum class Connection
	{
		None,
		Server,
		Client
	};

	class ServerConnector final : public Singleton<ServerConnector>
	{
	public:
		ServerConnector() = default;
		~ServerConnector() override;

		ServerConnector(const ServerConnector& other) = delete;
		ServerConnector(ServerConnector&& other) = delete;
		ServerConnector& operator=(const ServerConnector& other) = delete;
		ServerConnector& operator=(ServerConnector&& other) = delete;

		void Init();

		void SetAsServer();
		void SetAsClient();

		void SendInputPacket(const std::string& inputPacket) const;

	private:
		void ReceiveInputPackets();

		void SendGameStatePackets();
		void ReceiveGameStatePackets();

		Connection m_Connection{};

		SOCKET m_Socket{};
	};
}

