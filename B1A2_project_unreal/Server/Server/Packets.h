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

	//Server
	S_AddObject,
	S_AddItem,
	S_RemoveObject,
	S_UpdateObjectState,
	S_Move,
	S_CreateGameRoom,
	S_AddItemToInventory,
	S_ItemPickupNotify,
	S_DropItem,
	S_UpdateCurrentTool,
	S_UseTool,
};

struct Header
{
	PacketID id;
	int dataSize;
};

struct GameRoomDTO
{
	GameRoomType type;
	Vector pos;
	Dir dir;
};

struct WallDTO
{
	Vector pos;
	Dir dir;
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
	uint objectID;
	Vector pos;
	Rotation rotation;
	ObjectState state;
};

struct C_GetItem_Packet
{
	uint playerID;
	bool isTool;
	uint itemID;
};

struct C_DropItem_Packet
{
	uint playerID;
	bool isTool;
	uint itemID;
};

struct C_ChangeTool_Packet
{
	uint playerID;
	uint toolID;
};

struct C_UseTool_Packet
{
	uint playerID;
	uint toolID;
	Rotation playerRotation;
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

// Server
struct S_AddObject_Packet
{
	ObjectType type;
	uint objectID;
	Vector pos;
	Rotation rotation;
};

struct S_AddItem_Packet
{
	bool isTool;
	ItemType itemType;
	uint objectID;
	Vector pos;
	Rotation rotation;
};

struct S_RemoveObject_Packet
{
	ObjectType objectType;
	uint objectID;
};

struct S_UpdateObjectState_Packet
{
	uint objectID;
	ObjectType type;
	ObjectState state;
};

struct S_Move_Packet
{
	ObjectType type;
	uint objectID;
	Vector pos;
	Rotation rotation;
	ObjectState state;
};

struct S_CreateGameRoom_Packet
{
	std::vector<GameRoomDTO> gameRooms;
	std::vector<WallDTO> walls;
};

struct S_AddItemToInventory_Packet
{
	bool isTool;
	ItemType itemType;
	uint itemID;
	float itemWeight;
};

struct S_ItemPickupNotify_Packet
{
	bool isTool;
	ItemType itemType;
	uint itemID;
	uint playerID;
};

struct S_DropItem_Packet
{
	uint playerID;
	bool isTool;
	ItemType itemType;
	uint itemID;
	Vector itemPos;
};

struct S_UpdateCurrentTool_Packet
{
	uint playerID;
	uint itemID;
	ItemType itemType;
};

struct S_SpawnParticle_Packet
{
	Vector pos;
};

struct S_InteractDoorNotify_Packet
{
	uint playerID;
	uint doorID;
	ObjectState doorState;
};

struct S_UseTool_Packet
{
	uint playerID;
	ItemType toolType;
};