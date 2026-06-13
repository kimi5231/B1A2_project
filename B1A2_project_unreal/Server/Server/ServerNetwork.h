#pragma once
#include "Packets.h"
#include "ExpOver.h"

class ServerFramework;
class Session;
class Lantern;
class EmotionGame;
class SellingMachine;
class Room;
class Quest;

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
	void ProcessUDPRecv(int numByte, ExpOver* expOver);
	void ProcessPacket(std::vector<char>& packet, int clientIndex);
	void ProcessDB(int clientIndex, ExpOver* expOver);
	
private:
	template <class T >
	std::vector<char> SerializePOD(const T& pod);

	template <class T >
	std::vector<char> SerializeVector(const std::vector<T>& vector);

	template <class T>
	std::vector<T> DeserializeVector(const std::vector<char>& data);

public:
	// Send
	void SendSignupResultPacket(SignupResult result, Session* client);
	void SendLoginResultPacket(LoginResult result, short clientID, Session* client);
	void SendCurrentRoomListPacket(Session* client);
	void SendCreateRoomResultPacket(bool result, Session* client);
	void SendEnterRoomResultPacket(bool result, Session* client);
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
	void SendDropItemPacket(Item* item, int playerID, Vector itemPos, bool isTool, bool isToSellingMachine, Session* client);
	void SendUpdateCurrentToolPacket(int itemID, int playerID, ItemType type, Session* client);
	void SendUseToolPacket(int playerID, ItemType type, Session* client);
	void SendTurnOnLanternPacket(Lantern* lantern, int playerID, Session* client);
	void SendTurnOffLanternPacket(Lantern* lantern, int playerID, Session* client);
	void SendInteractDoorNotifyPacket(int playerID, int doorID, ObjectState doorState, Session* client);
	void SendSellItemResultPacket(char playerID, char sellingMachineID, ObjectState sellingMachineState, short remainCredit, short collectCredit, short currentCredit, std::vector<int>& itemIDs, Session* client);
	void SendBuyItemResultPacket(short currentCredit, Session* client);
	void SendUpdateHpPacket(int playerID, int hp, Session* client);
	void SendEmotionGameResultPacket(int playerID, int playerHP, EmotionGame* emotionGame,  Session* client);
	void SendSpawnParticlePacket(Vector pos, Session* client);
	void SendStartStagePacket(Session* client);
	void SendEndStagePacket(Session* client);
	void SendGameOverPacket(Session* client);
	void SendUpdateQuestPacket(Quest* quest, bool isMain, Session* client);
	void SendUpdateQuestProgressPacket(Quest* quest, bool isMain, Session* client);
	void SendUpdateCreditPacket(short goalCredit, short collectCredit, short currentCredit, Session* client);
	void SendVoiceDataPacket(char playerId, int sequenceNumber, std::vector<char>& audioData, ExpOver* expOver);

public:
	// Recv
	void ProcessSignupPacket(C_Signup_Packet packet, int clientIndex);
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
	void ProcessSubmitItemPacket(C_SubmitItem_Packet packet, int clientIndex);
	void ProcessRequestQuestRewardPacket(C_RequestQuestReward_Packet packet, int clientIndex);
	void ProcessVoiceDataPacket(C_VoiceData_Packet packet);

public:
	HANDLE GetIOCP() const { return _iocp; }

private:
	SOCKET _listenSocket{};
	SOCKET _udpSocket{};
	SOCKET _tempSocket{};
	ExpOver _acceptOver{};
	HANDLE _iocp{};
	std::array<class Session*, MAX_CLIENT> _clients;

	ServerFramework* _framework;
	float _updateLobbyTime;
	std::unordered_map<int, class Session*> _lobbyClients;
};