#pragma once
#include <string>
#include <winsock2.h>

#include "Singleton.h"

namespace dae
{
	class Scene;
	class GameObject;

	enum class Connection
	{
		None,
		Server,
		Client
	};

	struct PacketHeader {
		uint16_t packetType; // Enum value representing the type of packet
		uint32_t packetSize; // Size of the packet's payload (not including the header)
	};

	enum class PacketTypes : uint16_t
	{
		GAME_STATE,
		PLAYER_INPUT,
		RANDOM_SEED
		//ADD MORE IF NEEDED
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

		void SendPacket(PacketTypes type, const std::string& payload);
	private:
		void SendGameStatePackets();

		void ReceivePacket();



		Connection m_Connection{};

		SOCKET m_Socket{};
	};
}

