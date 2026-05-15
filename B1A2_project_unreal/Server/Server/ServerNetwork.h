#pragma once
#include "Packets.h"
#include "ExpOver.h"

class ServerFramework;
class Session;

class ServerNetwork
{
public:
	ServerNetwork(ServerFramework* framework);
	~ServerNetwork();

public:
	void Update();
	void ProcessAccept();
	void ProcessDisconnected(int clientIndex);
	void ProcessRecv(int clientIndex, int numByte, ExpOver* expOver);
	void ProcessPacket(std::vector<char>& packet, int clientIndex);
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
	void SendAddPlayerPacket(Player* player, Session* client);
	
	void SendAddItemPacket(ItemRef item, bool isTool, bool broadcast, SOCKET client = 0);
	void SendRemoveObjectPacket(ObjectType objectType, int objectID, Session* client);
	
	// GetPlayer 함수 GetObject 함수로 수정 필요
	void SendMovePacket(GameObject* object, Session* client);
	void SendUpdateObjectStatePacket(GameObject* object, Session* client);
	
	void SendCreateCubesPacket(const std::vector<CubeRef>& cubes, const std::vector<DoorRef>& doors, bool broadcast, SOCKET client = 0);
	void SendAddItemToInventoryPacket(ItemRef item, bool isTool, bool broadcast, SOCKET client = 0);
	void SendRemoveItemFromInventoryPacket(ItemRef item, bool isTool, bool broadcast, SOCKET client = 0);
	void SendItemPickupNotifyPacket(ItemRef item, uint playerID, bool isTool, bool broadcast, SOCKET client = 0);
	void SendDropItemPacket(ItemRef item, PlayerRef player, bool isTool, bool broadcast, SOCKET client = 0);
	void SendUpdateCurrentToolPacket(uint playerID, uint itemID, ItemType type, bool broadcast, SOCKET client = 0);
	void SendUseToolPacket(uint playerID, ItemType type, bool broadcast, SOCKET client = 0);
	void SendSpawnParticlePacket(Vector pos, bool broadcast, SOCKET client = 0);
	void SendInteractDoorNotifyPacket(uint playerID, uint doorID, ObjectState doorState, bool broadcast, SOCKET client = 0);
	void SendSpawnMonsterPacket(MonsterRef monster, bool broadcast, SOCKET client = 0);
	void SendSpawnObstaclePacket(ObstacleRef obstacle, bool broadcast, SOCKET client = 0);
	void SendTurnOnLanternPacket(LanternRef lantern, int playerID, bool broadcast, SOCKET client = 0);
	void SendTurnOffLanternPacket(LanternRef lantern, int playerID, bool broadcast, SOCKET client = 0);
	void SendStartStagePacket(bool broadcast, SOCKET client = 0);
	void SendEndStagePacket(bool broadcast, SOCKET client = 0);
	void SendUpdateHpPacket(int playerID, unsigned char hp, bool broadcast, SOCKET client = 0);

public:
	// Recv
	void ProcessMovePacket(C_Move_Packet packet, int clientIndex);
	void ProcessUpdateObjectStatePacket(C_UpdateObjectState_Packet packet, int clientIndex);
	
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

private:
	SOCKET _listenSocket{};
	SOCKET _tempSocket{};
	ExpOver _acceptOver{};
	HANDLE _iocp{};
	std::array<class Session*, MAX_PLAYER> _clients;

	ServerFramework* _framework;
};