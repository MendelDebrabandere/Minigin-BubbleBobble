#include "ServerConnector.h"

#include <chrono>
#include <iostream>
#include <WS2tcpip.h>
#include <tchar.h>
#include <document.h>
#include <writer.h>
#include <stringbuffer.h>
#include "InputManager.h"
#include "Minigin.h"
#include "Timer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "error/en.h" // For error parsing

using namespace dae;

ServerConnector::~ServerConnector()
{
    if (m_Connection != Connection::None)
    {
        std::cout << "\n=== Closing Socket ===\n";
        WSACleanup();
    }
}

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



    //Set seed to random
    unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    //sending seed over
    SendPacket(PacketTypes::RANDOM_SEED, std::to_string(seed));
    Minigin::AddTask([=]() {Minigin::SetRandomSeed(seed); });
    // add set seed as task to the main thread, (randomseed value is thread-local)
    std::cout << "RANDOM MULTIPLAYER SEED = " << seed << '\n';



    //Launch a thread to listen for packets from the client
    std::thread inputThread(&ServerConnector::ReceivePacket, this);
    inputThread.detach();  // Detach the thread so it runs independently and does not need to be joined back.


    //Launch a thread to send gamestate to the client 
    std::thread gamestateThread(&ServerConnector::SendGameStatePackets, this);
    gamestateThread.detach();  // Detach the thread so it runs independently and does not need to be joined back.


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
    
    //Launch a thread to listen for packets from the server
    std::thread receiveThread(&ServerConnector::ReceivePacket, this);
    receiveThread.detach();  // Detach the thread so it runs independently and does not need to be joined back.

}

void ServerConnector::SendGameStatePackets()
{
    float previousTime = Time::GetInstance().GetTotal();

    while (true)
    {
        float currTotalTime = Time::GetInstance().GetTotal();
        float deltaTime = currTotalTime - previousTime;

        if (deltaTime >= m_GameStateSendingFrequency)
        {
            //Update previousTime
            previousTime = currTotalTime;

	        //send gamestate
            //std::cout << "GAMESTATE SENDING\n";

            rapidjson::Document doc = SceneManager::GetInstance().GetActiveScene()->SerializeScene();
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            doc.Accept(writer);
            std::string jsonString = buffer.GetString();

            Minigin::LockMutex();
            SendPacket(PacketTypes::GAME_STATE, jsonString);
            Minigin::UnlockMutex();
        }
        else
        {
            float sleepDuration{ m_GameStateSendingFrequency - deltaTime};
            std::this_thread::sleep_for(std::chrono::duration<float>(sleepDuration));
        }
    }
}

void ServerConnector::SendPacket(PacketTypes type, const std::string& payload)
{
    PacketHeader header;
    header.packetType = static_cast<uint16_t>(type);
    header.packetSize = static_cast<uint32_t>(payload.size());

    //Lock mutex so that packages don't accidentally get sent at exactly the same time.
    m_SendingMutex.lock();

    // Send header
    send(m_Socket, reinterpret_cast<char*>(&header), sizeof(header), 0);

    //std::cout << payload << '\n';
    // Send payload
    send(m_Socket, payload.c_str(), static_cast<int>(payload.size()), 0);

    m_SendingMutex.unlock();
}

void ServerConnector::ReceivePacket()
{
    while (true)
    {
        PacketHeader header;

        // Receive header
        int receivedBytes = recv(m_Socket, reinterpret_cast<char*>(&header), sizeof(header), 0);
        if (receivedBytes <= 0)
        {
            // Handle disconnect or error
            return;
        }

        // Now that we know the size from the header, receive the payload
        std::vector<char> payloadBuffer(header.packetSize);
        receivedBytes = recv(m_Socket, payloadBuffer.data(), header.packetSize, 0);

        if (receivedBytes != static_cast<int>(header.packetSize))
        {
            std::cerr << "Incomplete packet received. Expected " << header.packetSize << " bytes but got " << receivedBytes << " bytes." << std::endl;
            continue;  // I had a lot of errors due to this, best option is to continue and go to next loop
        }

        // Handle packet based on type
        switch (static_cast<PacketTypes>(header.packetType))
        {
        case PacketTypes::GAME_STATE:
        {
            // Deserialize and process game state
            Minigin::LockMutex();

            payloadBuffer.push_back('\0');

            rapidjson::Document doc;
            doc.Parse(payloadBuffer.data());

            if (doc.HasParseError())
            {
                std::cerr << "Malformed JSON: " << payloadBuffer.data() << std::endl;

                std::cerr << "JSON parse error: " << rapidjson::GetParseError_En(doc.GetParseError())
                    << " (" << doc.GetErrorOffset() << ")" << std::endl;
                return;  // or handle error as needed
            }

            SceneManager::GetInstance().GetActiveScene()->Deserialize(doc);

            Minigin::UnlockMutex();
            break;
        }
        case PacketTypes::PLAYER_INPUT:
        {
            // Process player input
            Minigin::LockMutex();
            InputManager::GetInstance().ReceiveInputMultiplayer(std::string(payloadBuffer.data()));
            Minigin::UnlockMutex();
            break;
        }
        case PacketTypes::RANDOM_SEED:
        {
            payloadBuffer.push_back('\0');
            std::string payload{ payloadBuffer.data() };

            // Set your RNG with the received seed
            std::cout << "RANDOM MULTIPLAYER SEED = " << payload << '\n';
            // add set seed as task to the main thread, (randomseed value is thread-local)
            int seedNumber{ std::stoi(payload) };
            Minigin::AddTask([=]() {Minigin::SetRandomSeed(static_cast<unsigned int>(seedNumber)); });
            break;
        }
        }
    }
}
