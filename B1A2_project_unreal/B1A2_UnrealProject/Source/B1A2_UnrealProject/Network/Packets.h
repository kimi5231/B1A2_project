#pragma once

struct Vector
{
	float x;
	float y;
	float z;
};

struct Rotation
{
	float pitch;
	float yaw;
	float roll;
};

enum class ObjectType
{
	Player,
};

enum class GameRoomType
{
	MainEntranceRoom,
	GapRoom,

	Staircase,
	CorridorCatwalk,

	ApparatusRoom,
	ServerRoom,
	LockerRoom,
	StorageRoom,

	None,
};

struct GameRoomInfo
{
	GameRoomType type;
	Vector pos;
	Vector size;
};

enum PacketID
{
	// Client
	C_Move,

	//Server
	S_AddObject,
	S_Move,
	S_CreateGameRoom,
};

struct Header
{
	PacketID id;
	int dataSize;
};

// Client
enum MoveState
{
	MOVE_STATE_IDLE,
	MOVE_STATE_RUN,
	MOVE_STATE_JUMP,
};

struct C_Move_Packet
{
	int objectID;
	Vector pos;
	Rotation rotation;
	MoveState state;
};

// Server
struct S_CreateGameRoom_Packet
{
	GameRoomInfo room1;
	GameRoomInfo room2;
	GameRoomInfo room3;
	GameRoomInfo room4;
	GameRoomInfo room5;
};

struct S_AddObject_Packet
{
	int objectID;
	Vector pos;
	Rotation rotation;
};

struct S_RemoveObject_Packet
{
	int objectID;
	Vector pos;
	Rotation rotaion;
};

struct S_Move_Packet
{
	int objectID;
	Vector pos;
	Rotation rotation;
	MoveState state;
};