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
	C_InteractDoor,
	C_Emotion,
	C_UseLantern,
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
	S_SpawnParticle,
	S_InteractDoorNotify,
	S_TurnOnLantern,
	S_TurnOffLantern,
	S_StartStage,
	S_EndStage,
	S_UpdateHp,
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
	int playerID;
	bool isTool;
	int itemID;
};

struct C_DropItem_Packet
{
	int playerID;
	bool isTool;
	int itemID;
};

struct C_ChangeTool_Packet
{
	int playerID;
	int toolID;
};

struct C_UseTool_Packet
{
	int playerID;
	int toolID;
	Rotation playerRotation;
};

struct C_UseKey_Packet
{
	int playerID;
	int toolID;
	int doorID;
};

struct C_InteractDoor_Packet
{
	int playerID;
	int doorID;
};

struct C_Emotion_Packet
{
	float angry;
	float disgust;
	float fear;
	float happy;
	float sad;
	float surprise;
	float neutral;
};

struct C_UseLantern_Packet
{
	int lanternID;
	int playerID;
};

struct C_StartStage_Packet
{
	bool result;
};

struct C_EndStage_Packet
{
	bool result;
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