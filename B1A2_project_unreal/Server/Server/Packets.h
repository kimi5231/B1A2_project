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
	Vector size;
};

// Client
struct C_UpdateObjectState_Packet
{
	int objectID;
	ObjectType type;
	MoveState state;
};

struct C_Move_Packet
{
	int objectID;
	Vector pos;
	Rotation rotation;
	MoveState state;
};

// Server
struct S_AddObject_Packet
{
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
	MoveState state;
};

struct S_Move_Packet
{
	int objectID;
	Vector pos;
	Rotation rotation;
	MoveState state;
};

struct S_CreateGameRoom_Packet
{
	std::vector<GameRoomDTO> gameRooms;
};