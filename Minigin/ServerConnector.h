#pragma once
#include "Singleton.h"

namespace dae
{
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

		void CloseConnection();

		Connection GetConnection() const;
	private:
		Connection m_Connection{};
	};
}

