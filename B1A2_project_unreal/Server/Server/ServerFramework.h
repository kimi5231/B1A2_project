#pragma once

class Room;

class ServerFramework
{
public:
	ServerFramework();
	~ServerFramework();

public:
	void Update();
	void ProcessRecv(SOCKET client);

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
	void ProcessMovePacket(C_Move_Packet packet);

private:
	fd_set _readSet{};
	fd_set _writeSet{};

	SOCKET _listenSocket{};
	std::vector<SOCKET> _clients;

private:
	Room* _room{};
};