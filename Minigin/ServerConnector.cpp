#include "ServerConnector.h"
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <tchar.h>

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

    SOCKET serverSocket, acceptSocket;
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

    acceptSocket = accept(serverSocket, NULL, NULL);
    if (acceptSocket == INVALID_SOCKET)
    {
        std::cout << "accept failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        m_Connection = Connection::None;
        return;
    }
    std::cout << "Accepted connection\n";


    ////************* STEP 6 CHAT TO THE CLIENT *************
    //std::cout << "\n=== Step 6 - Chat to the client ===\n";

    //constexpr int buffLen{ 200 };
    //char buffer[buffLen];

    //std::string message;

    //while (true)
    //{
    //    //Check if it receives messages from the client
    //    int byteCount = recv(acceptSocket, buffer, buffLen, 0);

    //    if (byteCount > 0)
    //    {
    //        std::cout << "Message received: " << buffer << std::endl;

    //        if (strcmp(buffer, "SHUTDOWN") == 0)
    //        {
    //            std::cout << "SHUTDOWN command received. Closing the connection.\n";
    //            break;
    //        }
    //    }
    //    else
    //    {
    //        std::cout << "Error: No message has been received.\n";
    //        WSACleanup();
    //        break;
    //    }
    //}


    ////************* STEP 7 CLOSE SOCKET *************
    //std::cout << "\n=== Step 7 - Close Socket ===\n";

    //system("pause");
    //WSACleanup();
    
}

void ServerConnector::SetAsClient()
{
	if (m_Connection != Connection::None)
		return;

    std::cout << "======= Sockets =======\n";
    std::cout << "======= CLIENT =======\n";


    //************* STEP 1 SET UP DLL *************
    std::cout << "\n=== Step 1 - Set up DLL ===\n";

    SOCKET clientSocket;
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

    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET)
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

    if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
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


    ////************* STEP 4 CHAT TO THE SERVER *************
    //std::cout << "\n=== Step 4 - Chat to the Server ===\n";
    //std::cout << "Type \"SHUTDOWN\" to end the chat.\n";
    //std::cout << "Please enter your messages to send to the Server: \n";

    //constexpr int buffLen{ 200 };
    //char buffer[buffLen];

    //while (true)
    //{
    //    std::cin.getline(buffer, buffLen);

    //    int byteCount = send(clientSocket, buffer, buffLen, 0);

    //    if (byteCount > 0)
    //    {
    //        //std::cout << "Message sent: " << buffer << std::endl;

    //        if (strcmp(buffer, "SHUTDOWN") == 0)
    //        {
    //            std::cout << "SHUTDOWN command received. Closing the connection.\n";
    //            break;
    //        }
    //    }
    //    else
    //    {
    //        std::cout << "Error: No message has been sent.\n";
    //        WSACleanup();
    //        break;
    //    }
    //}



    ////************* STEP 5 CLOSE SOCKET *************
    //std::cout << "\n=== Step 5 - Close Socket ===\n";

    //system("pause");
    //WSACleanup();
}

void ServerConnector::CloseConnection()
{
}

Connection ServerConnector::GetConnection() const
{
    return m_Connection;
}
