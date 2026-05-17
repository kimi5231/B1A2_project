#pragma once
#include "Types.h"
#include <vector>

enum PacketID : char
{
	// Client
	C_Move,
	C_UpdateObjectState,
	C_GetItem,
	C_DropItem,
	C_ChangeTool,
	C_UseTool,
	C_UseKey,
	C_UseLantern,
	C_InteractDoor,
	C_ChangeEmotion,
	C_EmotionResult,
	C_StartStage,
	C_EndStage,

	//Server
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
	S_UpdateHp,
	S_EmotionGameResult,
	S_SpawnParticle,
	S_StartStage,
	S_EndStage,
};

#pragma pack(push, 1)
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

// Client
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
	unsigned int itemID;
	unsigned int playerID;
	bool isTool;
};

struct C_DropItem_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned int itemID;
	unsigned int playerID;
	bool isTool;
};

struct C_ChangeTool_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned int toolID;
	unsigned int playerID;
};

struct C_UseTool_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned int toolID;
	unsigned int playerID;
	Rotation playerRotation;
};

struct C_UseKey_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned int toolID;
	unsigned int doorID;
	unsigned int playerID;
};

struct C_UseLantern_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned int lanternID;
	unsigned int playerID;
};

struct C_InteractDoor_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned int doorID;
	unsigned int playerID;
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

// Server
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
	ItemType itemType;
	Vector itemPos;
	// 임시로 배터리 추가 예정
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
#pragma pack(pop)