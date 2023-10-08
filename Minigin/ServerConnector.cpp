#include "ServerConnector.h"

#include <chrono>
#include <iostream>
#include <WS2tcpip.h>
#include <tchar.h>

#include "InputManager.h"
#include "Scene.h"
#include "SceneManager.h"

using namespace dae;

void ServerConnector::Init()
{
	m_Connection = Connection::None;
}

void ServerConnector::SetAsServer()
{
	if (m_Connection != Connection::None)
		return;

	std::cout << "Set as server\n";
	m_Connection = Connection::Server;

    std::cout << "======= Sockets =======\n";
    std::cout << "======= SERVER =======\n";


    //************* STEP 1 SET UP DLL *************
    std::cout << "\n=== Step 1 - Set up DLL ===\n";

    SOCKET serverSocket;
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);

    int wsaerr = WSAStartup(wVersionRequested, &wsaData);

    if (wsaerr != 0)
    {
        std::cout << "The Winsock dll is not found!\n";
        m_Connection = Connection::None;
        return;
    }
    else
    {
        std::cout << "TheWinsock dll has been found!\n";
        std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
    }

    //************* STEP 2 SET UP SERVER SOCKET *************
    std::cout << "\n=== Step 2 - Set up Server Socket ===\n";

    serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET)
    {
        std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        m_Connection = Connection::None;
        return;
    }
    else
    {
        std::cout << "socket() is OK!\n";
    }

    //************* STEP 3 BIND SOCKET *************
    std::cout << "\n=== Step 3 - Bind Socket ===\n";

    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
    {
        std::cout << "bind() failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        m_Connection = Connection::None;
        return;
    }
    else
    {
        std::cout << "bind() is OK!\n";
    }

    //************* STEP 4 INITIATE LISTEN *************
    std::cout << "\n=== Step 4 - Initiate Listen ===\n";

    if (listen(serverSocket, 1) == SOCKET_ERROR)
        std::cout << "listen(): Error Listening on socket: " << WSAGetLastError() << std::endl;
    else
        std::cout << "listen() is OK, waiting for connections...\n";


    //************* STEP 5 ACCEPT CONNECTION *************
    std::cout << "\n=== Step 5 - Accept Connection ===\n";

    m_Socket = accept(serverSocket, NULL, NULL);
    if (m_Socket == INVALID_SOCKET)
    {
        std::cout << "accept failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        m_Connection = Connection::None;
        return;
    }
    std::cout << "Accepted connection\n";


    //Launch a thread to listen for inputPackets from the client
    std::thread receiveThread(&ServerConnector::ReceiveInputPackets, this);
    receiveThread.detach();  // Detach the thread so it runs independently and does not need to be joined back.

}

void ServerConnector::SetAsClient()
{
	if (m_Connection != Connection::None)
		return;

    std::cout << "======= Sockets =======\n";
    std::cout << "======= CLIENT =======\n";
    m_Connection = Connection::Client;

    //************* STEP 1 SET UP DLL *************
    std::cout << "\n=== Step 1 - Set up DLL ===\n";

    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);

    int wsaerr = WSAStartup(wVersionRequested, &wsaData);

    if (wsaerr != 0)
    {
        std::cout << "The Winsock dll is not found!\n";
        m_Connection = Connection::None;
        return;
    }
    else
    {
        std::cout << "TheWinsock dll has been found!\n";
        std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
    }


    //************* STEP 2 SET UP CLIENT SOCKET *************
    std::cout << "\n=== Step 2 - Set up Client Socket ===\n";

    m_Socket = INVALID_SOCKET;
    m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_Socket == INVALID_SOCKET)
    {
        std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        m_Connection = Connection::None;
        return;
    }
    else
    {
        std::cout << "socket() is OK!\n";
    }


    //************* STEP 3 CONNECT WITH SERVER *************
    std::cout << "\n=== Step 3 - Connect with Server ===\n";

    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);

    if (connect(m_Socket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
    {
        std::cout << "Client: connect() - Failed to connect." << std::endl;
        WSACleanup();
        m_Connection = Connection::None;
        return;
    }
    else
    {
        std::cout << "Client: connect() is OK.\n";
        std::cout << "Client: Can start sending and receiving data...\n";
    }
}

void ServerConnector::CloseConnection()
{
}

Connection ServerConnector::GetConnection() const
{
    return m_Connection;
}

void ServerConnector::SendInputPacket(const std::string& inputPacket) const
{
    //only send over inputs when you are the client
    if (m_Connection != Connection::Client)
        return;

    int byteCount = send(m_Socket, inputPacket.c_str(), static_cast<int>(inputPacket.size()), 0);

    if (byteCount == 0)
        std::cout << "Error sending inputPacket.\n";
    else
        std::cout << "Successfully sent inputPacket.\n";
}

void ServerConnector::ReceiveInputPackets()
{
    char recvbuf[512]{};  // Can change buffersize if required
    int bytesReceived;
    while (true)
    {
        bytesReceived = recv(m_Socket, recvbuf, sizeof(recvbuf), 0);
        if (bytesReceived > 0)
        {
            // Data received
            // Process the received data here.
            // Deserialize and handle the input packet.
            std::cout << "Received Input: " << std::string(recvbuf) << std::endl;
            InputManager::GetInstance().ReceiveInputFromClient(std::string(recvbuf));
        }
        else if (bytesReceived == 0)
        {
            std::cout << "Connection closed.\n";
            m_Connection = Connection::None;
            break;
        }
        else
        {
            std::cout << "recv failed: " << WSAGetLastError() << "\n";
            break;
        }
    }
}
