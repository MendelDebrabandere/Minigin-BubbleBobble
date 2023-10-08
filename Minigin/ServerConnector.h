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
		void Init();

		void SetAsServer();
		void SetAsClient();

		void SendInputPacket(const std::string& inputPacket) const;
	private:
		void ReceiveInputPackets();

		Connection m_Connection{};

		SOCKET m_Socket{};
	};
}

