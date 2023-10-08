#include "ClientCommand.h"
#include <thread>
#include "ServerConnector.h"

void ClientCommand::Execute()
{
	// Create a new thread to handle the client connection
	std::thread clientThread(&dae::ServerConnector::SetAsClient, &dae::ServerConnector::GetInstance());
	clientThread.detach();
}
