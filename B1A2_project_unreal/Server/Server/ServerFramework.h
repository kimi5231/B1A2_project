#pragma once

#include "Packets.h"

class Room;

struct Client
{
	int id;
	SOCKET socket;
	PlayerRef player;
};

struct SendEvent
{
	bool isComplete = false;
	bool isBroadcast;
	SOCKET clientSocket;
	PacketID packetID;
	std::vector<char> serializedPacketData;
};

class ServerFramework
{
public:
	ServerFramework();
	~ServerFramework();

public:
	void Update();
	void ProcessRecv(ClientRef client);
	void ProcessSend(PacketID id, const std::vector<char>& packetData, SOCKET clientSocket);
	std::vector<char> CreatePakcet(PacketID id, const std::vector<char>& packetData);

private:
	template <class T >
	std::vector<char> SerializePOD(const T& pod);

	template <class T >
	std::vector<char> SerializeVector(const std::vector<T>& vector);
	
	template <class T>
	std::vector<T> DeserializeVector(const std::vector<char>& data);

public:
	// Send
	void SendAddObjectPacket(GameObjectRef object, bool broadcast, SOCKET client = 0);
	void SendAddItemPacket(ItemRef item, bool isTool, bool broadcast, SOCKET client = 0);
	void SendRemoveObjectPacket(ObjectType objectType, uint objectID, bool broadcast, SOCKET client = 0);
	void SendUpdateObjectStatePacket(GameObjectRef object, bool broadcast, SOCKET client = 0);
	void SendMovePacket(GameObjectRef object, bool broadcast, SOCKET client = 0);
	void SendCreateCubesPacket(const std::vector<CubeRef>& cubes, bool broadcast, SOCKET client = 0);
	void SendAddItemToInventoryPacket(ItemRef item, bool isTool, bool broadcast, SOCKET client = 0);
	void SendItemPickupNotifyPacket(ItemRef item, uint playerID, bool isTool, bool broadcast, SOCKET client = 0);
	void SendDropItemPacket(ItemRef item, PlayerRef player, bool isTool, bool broadcast, SOCKET client = 0);
	void SendUpdateCurrentToolPacket(uint playerID, uint itemID, ItemType type, bool broadcast, SOCKET client = 0);
	void SendUseToolPacket(uint playerID, ItemType type, bool broadcast, SOCKET client = 0);
	void SendSpawnParticlePacket(Vector pos, bool broadcast, SOCKET client = 0);
	void Broadcast(PacketID id, const std::vector<char>& packetData);

public:
	// Recv
	void ProcessAccept(SOCKET clientSocket);
	void ProcessDisconnect(ClientRef client);
	void ProcessUpdateObjectStatePacket(C_UpdateObjectState_Packet packet);
	void ProcessMovePacket(C_Move_Packet packet);
	void ProcessGetItemPacket(SOCKET clientSocket, C_GetItem_Packet packet);
	void ProcessDropItemPacket(C_DropItem_Packet packet);
	void ProcessChangeToolPacket(C_ChangeTool_Packet packet);
	void ProcessUseToolPacket(C_UseTool_Packet packet);

public:
	Room* GetRoom() { return _room; }

private:
	fd_set _readSet{};
	fd_set _writeSet{};

	SOCKET _listenSocket{};
	std::vector<ClientRef> _clients;
	std::vector<ClientRef> _removeClients;

	std::vector<SendEventRef> _sendEvents;

private:
	Room* _room{};
};