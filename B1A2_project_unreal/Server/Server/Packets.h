#pragma once
#include "Types.h"
#include <vector>

enum PacketID
{
	// Client
	C_UpdateObjectState,
	C_Move,
	C_GetItem,

	//Server
	S_AddObject,
	S_AddItem,
	S_RemoveObject,
	S_UpdateObjectState,
	S_Move,
	S_CreateGameRoom,
	S_AddItemToInventory
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
	int objectID;
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

struct C_ChangeTool_Packet
{
	int playerID;
	int toolID;
};

struct C_UseTool_Pacekt
{
	int playerID;
	int toolID;
};

struct C_DropItem_Packet
{
	int playerID;
	bool isTool;
	int itemID;
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
	ObjectType objectType;
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

struct S_CreateGameRoom_Packet
{
	std::vector<GameRoomDTO> gameRooms;
	std::vector<WallDTO> walls;
};

struct S_AddItemToInventory_Packet
{
	bool isTool;
	ItemType itemType;
	int itemID;
	float itemWeight;
};