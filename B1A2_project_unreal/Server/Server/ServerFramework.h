#pragma once
#include "Packets.h"

class Room;

class ServerFramework
{
public:
	ServerFramework();
	~ServerFramework();

public:
	void Update();
	void ProcessRecv(ClientRef client);
	
private:
	template <class T >
	std::vector<char> SerializePOD(const T& pod);

	template <class T >
	std::vector<char> SerializeVector(const std::vector<T>& vector);
	
	template <class T>
	std::vector<T> DeserializeVector(const std::vector<char>& data);

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
	void ProcessUseKeyPacket(SOCKET clientSocket, C_UseKey_Packet packet);
	void ProcessInteractDoorPacket(C_InteractDoor_Packet packet);
	void ProcessEmotionPacket(C_Emotion_Packet packet);
	void ProcessUseLanternPacket(C_UseLantern_Packet packet);
	void ProcessStartStagePacket(C_StartStage_Packet packet);
	void ProcessEndStagePacket(C_EndStage_Packet packet);

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