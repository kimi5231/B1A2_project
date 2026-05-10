#pragma once
#include "Types.h"
#include <vector>

enum PacketID
{
	// Client
	C_UpdateObjectState,
	C_Move,
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
	S_AddObject,
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
	S_GetDamage,
	S_StartStage,
	S_EndStage,
};

struct Header
{
	PacketID id;
	int dataSize;
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
struct C_UpdateObjectState_Packet
{
	uint objectID;
	ObjectType type;
	ObjectState state;
};

struct C_Move_Packet
{
	ObjectType type;
	int objectID;
	Vector pos;
	Rotation rotation;
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
struct S_AddObject_Packet
{
	ObjectType type;
	int objectID;
	Vector pos;
	Rotation rotation;
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
	ObjectType objectType;
	int objectID;
};

struct S_UpdateObjectState_Packet
{
	int objectID;
	ObjectType type;
	ObjectState state;
};

struct S_Move_Packet
{
	ObjectType type;
	int objectID;
	Vector pos;
	Rotation rotation;
	ObjectState state;
};

struct S_CreateCubes_Packet
{
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

struct S_GetDamage_Packet
{
	int playerID;
	unsigned char damage;
};

struct S_StartStage_Packet
{
	bool result;
};

struct S_EndStage_Packet
{
	bool result;
};