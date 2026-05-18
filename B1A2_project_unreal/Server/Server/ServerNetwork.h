#pragma once
#include "Packets.h"
#include "ExpOver.h"

class ServerFramework;
class Session;
class Lantern;
class EmotionGame;
class SellingMachine;
class Room;

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
	
private:
	template <class T >
	std::vector<char> SerializePOD(const T& pod);

	template <class T >
	std::vector<char> SerializeVector(const std::vector<T>& vector);

	template <class T>
	std::vector<T> DeserializeVector(const std::vector<char>& data);

public:
	// Send
	void SendLoginResultPacket(LoginResult result, Session* client);
	void SendCurrentRoomListPacket(std::array<Room*, MAX_ROOM>& rooms, Session* client);
	void SendAddPlayerPacket(Player* player, Session* client);
	void SendAddMonsterPacket(Monster* monster, Session* client);
	void SendAddItemPacket(Item* item, bool isTool, Session* client);
	void SendAddObstaclePacket(Obstacle* obstacle, Session* client);
	void SendRemoveObjectPacket(ObjectType objectType, int objectID, Session* client);
	void SendMovePacket(GameObject* object, Session* client);
	void SendUpdateObjectStatePacket(GameObject* object, Session* client);
	void SendCreateCubesPacket(const std::vector<CubeRef>& cubes, const std::vector<Door*>& doors, const std::vector<SellingMachine*>& sellingMachines, Session* client);
	void SendAddItemToInventoryPacket(Item* item, bool isTool, Session* client);
	void SendRemoveItemFromInventoryPacket(Item* item, bool isTool, Session* client);
	void SendItemPickupNotifyPacket(Item* item, int playerID, bool isTool, Session* client);
	void SendDropItemPacket(Item* item, int playerID, Vector itemPos, bool isTool, Session* client);
	void SendUpdateCurrentToolPacket(int itemID, int playerID, ItemType type, Session* client);
	void SendUseToolPacket(int playerID, ItemType type, Session* client);
	void SendTurnOnLanternPacket(Lantern* lantern, int playerID, Session* client);
	void SendTurnOffLanternPacket(Lantern* lantern, int playerID, Session* client);
	void SendInteractDoorNotifyPacket(int playerID, int doorID, ObjectState doorState, Session* client);
	void SendSellItemResultPacket(char playerID, char sellingMachineID, ObjectState sellingMachineState, char remainCredit, char currentCredit, std::vector<int>& itemIDs, Session* client);
	void SendBuyItemResultPacket(char currentCredit, Session* client);
	void SendUpdateHpPacket(int playerID, int hp, Session* client);
	void SendEmotionGameResultPacket(int playerID, int playerHP, EmotionGame* emotionGame,  Session* client);
	void SendSpawnParticlePacket(Vector pos, Session* client);
	void SendStartStagePacket(Session* client);
	void SendEndStagePacket(Session* client);
	void SendUpdateCreditPacket(char currentCredit, Session* client);
	
public:
	// Recv
	void ProcessLoginPacket(C_Login_Packet packet, int clientIndex);
	void ProcessLogoutPacket(C_Logout_Packet packet, int clientIndex);
	void ProcessCreateRoomPacket(C_CreateRoom_Packet packet, int clientIndex);
	void ProcessEnterRoomPacket(C_EnterRoom_Packet packet, int clientIndex);
	void ProcessExitRoomPacket(C_ExitRoom_Packet packet, int clientIndex);
	void ProcessMovePacket(C_Move_Packet packet, int clientIndex);
	void ProcessUpdateObjectStatePacket(C_UpdateObjectState_Packet packet, int clientIndex);
	void ProcessGetItemPacket(C_GetItem_Packet packet, int clientIndex);
	void ProcessDropItemPacket(C_DropItem_Packet packet, int clientIndex);
	void ProcessDropItemToSellingMachinePacket(C_DropItemToSellingMachine_Packet packet, int clientIndex);
	void ProcessChangeToolPacket(C_ChangeTool_Packet packet, int clientIndex);
	void ProcessUseToolPacket(C_UseTool_Packet packet, int clientIndex);
	void ProcessUseKeyPacket(C_UseKey_Packet packet, int clientIndex);
	void ProcessUseLanternPacket(C_UseLantern_Packet packet, int clientIndex);
	void ProcessInteractDoorPacket(C_InteractDoor_Packet packet, int clientIndex);
	void ProcessSellItemPacket(C_SellItem_Packet packet, int clientIndex);
	void ProcessBuyItemPacket(C_BuyItem_Packet packet, int clientIndex);
	void ProcessChangeEmotionPacket(C_ChangeEmotion_Packet packet, int clientIndex);
	void ProcessEmotionResultPacket(C_EmotionResult_Packet packet, int clientIndex);
	void ProcessStartStagePacket(C_StartStage_Packet packet, int clientIndex);
	void ProcessEndStagePacket(C_EndStage_Packet packet, int clientIndex);

private:
	SOCKET _listenSocket{};
	SOCKET _tempSocket{};
	ExpOver _acceptOver{};
	HANDLE _iocp{};
	std::array<class Session*, MAX_CLIENT> _clients;

	ServerFramework* _framework;
};