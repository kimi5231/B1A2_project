#pragma once

class Room;

struct Client
{
	int id;
	SOCKET socket;
	PlayerRef player;
};

template <class T>
struct SendEvent
{
	bool isComplete = false;
	bool isBroadcast;
	SOCKET clientSocket;
	PacketID packetID;
	T packetData;
};

class ServerFramework
{
public:
	ServerFramework();
	~ServerFramework();

public:
	void Update();
	void ProcessRecv(ClientRef client);

	template <class T>
	void ProcessSend(PacketID id, const T& packetData, SOCKET clientSocket);

	template <class T>
	std::vector<char> CreatePakcet(PacketID id, const T& packetData);

public:
	// Send
	void SendAddObjectPacket(GameObjectRef object, bool broadcast, SOCKET client = 0);
	void SendMovePacket(GameObjectRef object, bool broadcast, SOCKET client = 0);

	template <class T>
	void Broadcast(PacketID id, const T& packetData);

public:
	// Recv
	void ProcessAccept(SOCKET clientSocket);
	void ProcessDisconnect(ClientRef client);
	void ProcessMovePacket(C_Move_Packet packet);

private:
	fd_set _readSet{};
	fd_set _writeSet{};

	SOCKET _listenSocket{};
	std::vector<ClientRef> _clients;
	std::vector<ClientRef> _removeClients;

	std::vector<EventType> _sendEvents;

private:
	Room* _room{};
};