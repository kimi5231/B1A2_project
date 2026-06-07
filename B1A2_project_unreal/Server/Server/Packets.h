#pragma once
#include "Types.h"
#include <vector>

enum PacketID : char
{
	// Client
	C_Login,
	C_Logout,
	C_CreateRoom,
	C_EnterRoom,
	C_ExitRoom,
	C_Move,
	C_UpdateObjectState,
	C_GetItem,
	C_DropItem,
	C_DropItemToSellingMachine,
	C_ChangeTool,
	C_UseTool,
	C_UseKey,
	C_UseLantern,
	C_InteractDoor,
	C_SellItem,
	C_BuyItem,
	C_ChangeEmotion,
	C_EmotionResult,
	C_StartStage,
	C_EndStage,
	C_SubmitItem,
	C_RequestQuestReward,
	C_VoiceData,

	//Server
	S_LoginResult,
	S_CurrentRoomList,
	S_CreateRoomResult,
	S_AddPlayer,
	S_AddMonster,
	S_AddItem,
	S_AddObstacle,
	S_RemoveObject,
	S_Move,
	S_UpdateObjectState,
	S_CreateCubes,
	S_AddItemToInventory,
	S_RemoveItemFromInventory,
	S_ItemPickupNotify,
	S_DropItem,
	S_UpdateCurrentTool,
	S_UseTool,
	S_TurnOnLantern,
	S_TurnOffLantern,
	S_InteractDoorNotify,
	S_SellItemResult,
	S_BuyItemResult,
	S_UpdateHp,
	S_EmotionGameResult,
	S_SpawnParticle,
	S_StartStage,
	S_EndStage,
	S_UpdateQuest,
	S_UpdateQuestProgress,
	S_UpdateCredit,
	S_VoiceData,
};

#pragma pack(push, 1)
struct RoomDTO
{
	unsigned char playerCount;
	unsigned char roomID;
	RoomState roomState;
	std::vector<char> roomTitle;
};

struct CubeDTO
{
	CubeType type;
	Vector pos;
	Dir dir;
};

struct DoorDTO
{
	unsigned char id;
	Vector pos;
	Dir dir;
	ObjectState state;
	DoorType doorType;
};

struct SellingMachineDTO
{
	unsigned char id;
	Vector pos;
	Dir dir;
	ObjectState state;
	unsigned char creditLimit;
};

// Client
struct C_Login_Packet
{
	unsigned char size;
	PacketID packetID;
	std::vector<char> id;
};

struct C_Logout_Packet
{
	unsigned char size;
	PacketID packetID;
};

struct C_CreateRoom_Packet
{
	unsigned char size;
	PacketID packetID;
};

struct C_EnterRoom_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned char roomID;
};

struct C_ExitRoom_Packet
{
	unsigned char size;
	PacketID packetID;
};

struct C_Move_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned char id;
	Vector pos;
	Rotation rotation;
	ObjectType type;
	ObjectState state;
};

struct C_UpdateObjectState_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned char id;
	ObjectType type;
	ObjectState state;
};

struct C_GetItem_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned char itemID;
	unsigned char playerID;
	bool isTool;
};

struct C_DropItem_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned char itemID;
	unsigned char playerID;
	bool isTool;
};

struct C_DropItemToSellingMachine_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned char sellingMachineID;
	unsigned char itemID;
	unsigned char playerID;
};

struct C_ChangeTool_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned char toolID;
	unsigned char playerID;
};

struct C_UseTool_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned char toolID;
	unsigned char playerID;
	Rotation playerRotation;
};

struct C_UseKey_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned char toolID;
	unsigned char doorID;
	unsigned char playerID;
};

struct C_UseLantern_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned char lanternID;
	unsigned char playerID;
};

struct C_InteractDoor_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned char doorID;
	unsigned char playerID;
};

struct C_SellItem_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned char sellingMachineID;
	unsigned char playerID;
};

struct C_BuyItem_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned char playerID;
	ItemType itemType;
	unsigned char itemCount;
};

struct C_ChangeEmotion_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned char playerID;
	Emotion emotion;
};

struct C_EmotionResult_Packet
{
	unsigned char size;
	PacketID packetID;
	float angryTime;
	float disgustTime;
	float fearTime;
	float happyTime;
	float sadTime;
	float surpriseTime;
	float neutralTime;
};

struct C_StartStage_Packet
{
	unsigned char size;
	PacketID packetID;
};

struct C_EndStage_Packet
{
	unsigned char size;
	PacketID packetID;
};

struct C_SubmitItem_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned char itemID;
	unsigned char playerID;
};

struct C_RequestQuestReward_Packet
{
	unsigned char size;
	PacketID packetID;
	bool isMain;
};

struct C_VoiceData_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned short clientID;
	unsigned char playerID;
	unsigned int sequenceNumber;
	std::vector<char> audioData;
};

// Server
struct S_LoginResult_Packet
{
	unsigned short size;
	PacketID packetID;
	LoginResult result;
};

struct S_CurrentRoomList_Packet
{
	unsigned short size;
	PacketID packetID;
	std::vector<RoomDTO> roomList;
};

struct S_CreateRoomResult_Packet
{
	unsigned short size;
	PacketID packetID;
	bool result;
	unsigned char roomID;
};

struct S_AddPlayer_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char id;
	Vector pos;
	Rotation rotation;
};

struct S_AddMonster_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char id;
	Vector pos;
	Rotation rotation;
	MonsterType monsterType;
	ObjectState state;
};

struct S_AddItem_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char id;
	bool isTool;
	Vector pos;
	ItemType itemType;
	unsigned char cost;
};

struct S_AddObstacle_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char id;
	Vector pos;
	Rotation rotation;
	ObstacleType obstacleType;
};

struct S_RemoveObject_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char id;
	ObjectType type;
};

struct S_Move_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char id;
	Vector pos;
	Rotation rotation;
	ObjectType type;
	ObjectState state;
};

struct S_UpdateObjectState_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char id;
	ObjectType type;
	ObjectState state;
};

struct S_CreateCubes_Packet
{
	unsigned short size;
	PacketID packetID;
	std::vector<CubeDTO> cubes;
	std::vector<DoorDTO> doors;
	std::vector<SellingMachineDTO> sellingMachines;
};

struct S_AddItemToInventory_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char id;
	bool isTool;
	ItemType itemType;
	float weight;
};

struct S_RemoveItemFromInventory_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char id;
	bool isTool;
	ItemType itemType;
};

struct S_ItemPickupNotify_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char itemID;
	unsigned char playerID;
	bool isTool;
	ItemType itemType;
};

struct S_DropItem_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char itemID;
	unsigned char playerID;
	bool isTool;
	bool isToSellingMachine;
	ItemType itemType;
	Vector itemPos;
	unsigned char cost;
	unsigned char laternBattery;
};

struct S_UpdateCurrentTool_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char itemID;
	unsigned char playerID;
	ItemType itemType;
};

struct S_UseTool_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char playerID;
	ItemType toolType;
};

struct S_TurnOnLantern_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char lanternID;
	unsigned char playerID;
	unsigned char laternBattery;
	unsigned char laternRange;
	float laternAngle;
};

struct S_TurnOffLantern_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char lanternID;
	unsigned char playerID;
	unsigned char laternBattery;
};

struct S_InteractDoorNotify_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char doorID;
	unsigned char playerID;
	ObjectState doorState;
};

struct S_SellItemResult_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char sellingMachineID;
	unsigned char playerID;
	unsigned short remainCredit;
	unsigned short collectCredit;
	unsigned short currentCredit;
	ObjectState sellingMachineState;
	std::vector<char> itemIDs;
};

struct S_BuyItemResult_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned short currentCredit;
};

struct S_UpdateHp_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char playerID;
	unsigned char hp;
};

struct S_EmotionGameResult_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char monsterID;
	unsigned char playerID;
	unsigned char playerHP;
	Emotion monsterEmotion;
	EmotionGameResult result;
};

struct S_SpawnParticle_Packet
{
	unsigned short size;
	PacketID packetID;
	Vector pos;
};

struct S_StartStage_Packet
{
	unsigned short size;
	PacketID packetID;
};

struct S_EndStage_Packet
{
	unsigned short size;
	PacketID packetID;
};

struct S_UpdateQuest_Packet
{
	unsigned short size;
	PacketID packetID;
	bool isMain;
	unsigned char questID;
	unsigned char goalCount;
	unsigned char deadLine;
	ItemType itemType;
};

struct S_UpdateQuestProgress_Packet
{
	unsigned short size;
	PacketID packetID;
	bool isMain;
	unsigned char currentCount;
	unsigned char deadLine;
};

struct S_UpdateCredit_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned short goalCredit;
	unsigned short collectCredit;
	unsigned short currentCredit;
};

struct S_VoiceData_Packet
{
	unsigned short size;
	PacketID packetID;
	unsigned char playerID;
	unsigned int sequenceNumber;
	std::vector<char> audioData;
};
#pragma pack(pop)