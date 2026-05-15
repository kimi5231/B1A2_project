#pragma once
#include "Types.h"
#include <vector>

#define PORT 7777
#define BufferSize 5000

enum PacketID
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
	S_AddItem,
	S_RemoveObject,
	S_UpdateObjectState,
	S_Move,
	S_CreateCubes,
	S_AddItemToInventory,
	S_RemoveItemFromInventory,
	S_ItemPickupNotify,
	S_DropItem,
	S_UpdateCurrentTool,
	S_UseTool,
	S_SpawnParticle,
	S_InteractDoorNotify,
	S_SpawnMonster,
	S_TurnOnLantern,
	S_TurnOffLantern,
	S_StartStage,
	S_EndStage,
	S_SpawnObstacle,
	S_UpdateHp,
};

struct CubeDTO
{
	CubeType type;
	Vector pos;
	Dir dir;
};

struct DoorDTO
{
	int id;
	Vector pos;
	Dir dir;
	ObjectState state;
	DoorType doorType;
};

// Client
#pragma pack(push, 1)
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
	uint playerID;
	uint doorID;
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
	unsigned char size;
	PacketID packetID;
	unsigned char id;
	Vector pos;
	Rotation rotation;
};

struct S_AddMonster_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned char id;
	Vector pos;
	Rotation rotation;
	MonsterType type;
	ObjectState state;
};

struct S_AddItem_Packet
{
	bool isTool;
	ItemType itemType;
	int objectID;
	Vector pos;
	Rotation rotation;
};

struct S_RemoveObject_Packet
{
	unsigned char size;
	PacketID packetID;
	ObjectType objectType;
	int objectID;
};

struct S_Move_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned char id;
	Vector pos;
	Rotation rotation;
	ObjectType type;
	ObjectState state;
};

struct S_UpdateObjectState_Packet
{
	unsigned char size;
	PacketID packetID;
	unsigned char id;
	ObjectType type;
	ObjectState state;
};

struct S_CreateCubes_Packet
{
	/*unsigned char size;
	PacketID packetID;*/
	std::vector<CubeDTO> cubes;
	std::vector<DoorDTO> doors;
};

struct S_AddItemToInventory_Packet
{
	bool isTool;
	ItemType itemType;
	int itemID;
	float itemWeight;
};

struct S_RemoveItemFromInventory_Packet
{
	bool isTool;
	ItemType itemType;
	int itemID;
};

struct S_ItemPickupNotify_Packet
{
	bool isTool;
	ItemType itemType;
	int itemID;
	int playerID;
};

struct S_DropItem_Packet
{
	int playerID;
	bool isTool;
	ItemType itemType;
	int itemID;
	Vector itemPos;
};

struct S_UpdateCurrentTool_Packet
{
	int playerID;
	int itemID;
	ItemType itemType;
};

struct S_SpawnParticle_Packet
{
	Vector pos;
};

struct S_InteractDoorNotify_Packet
{
	int playerID;
	int doorID;
	ObjectState doorState;
};

struct S_UseTool_Packet
{
	int playerID;
	ItemType toolType;
};

struct S_SpawnMonster_Packet
{
	int id;
	MonsterType type;
	ObjectState state;
	Vector pos;
	Rotation rotation;
};

struct S_TurnOnLantern_Packet
{
	int lanternID;
	int playerID;
	unsigned char laternBattery;
	unsigned char laternRange;
	float laternAngle;
};

struct S_TurnOffLantern_Packet
{
	int lanternID;
	int playerID;
	unsigned char laternBattery;
};

struct S_StartStage_Packet
{
	bool result;
};

struct S_EndStage_Packet
{
	bool result;
};

struct S_SpawnObstacle_Packet
{
	int id;
	ObstacleType type;
	Vector pos;
};

struct S_UpdateHp_Packet
{
	int playerID;
	unsigned char hp;
};
#pragma pack(pop)