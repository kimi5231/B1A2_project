#pragma once
#include "Types.h"
#include <vector>

enum PacketID
{
	// Client
	C_UpdateObjectState,
	C_Move,

	//Server
	S_AddObject,
	S_UpdateObjectState,
	S_Move,
	S_CreateGameRoom,
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

// Client
struct C_UpdateObjectState_Packet
{
	int objectID;
	ObjectType type;
	ObjectState state;
};

struct C_Move_Packet
{
	int objectID;
	Vector pos;
	Rotation rotation;
	ObjectState state;
};

// Server
struct S_AddObject_Packet
{
	ObjectType type;
	int objectID;
	Vector pos;
	Rotation rotaion;
};

struct S_RemoveObject_Packet
{
	int objectID;
	Vector pos;
	Rotation rotaion;
};

struct S_UpdateObjectState_Packet
{
	int objectID;
	ObjectType type;
	ObjectState state;
};

struct S_Move_Packet
{
	int objectID;
	Vector pos;
	Rotation rotation;
	ObjectState state;
};

struct S_CreateGameRoom_Packet
{
	std::vector<GameRoomDTO> gameRooms;
};