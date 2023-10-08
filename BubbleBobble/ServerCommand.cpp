#include "ServerCommand.h"
#include <thread>
#include "ServerConnector.h"

void ServerCommand::Execute()
{
	// Create a new thread to handle the server connection
	std::thread clientThread(&dae::ServerConnector::SetAsServer, &dae::ServerConnector::GetInstance());
	clientThread.detach();
}
