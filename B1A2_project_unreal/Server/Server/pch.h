#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <array>
#include <variant>
#include <random>

#pragma comment(lib, "ws2_32")

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

enum MoveState
{
	MOVE_STATE_IDLE,
	MOVE_STATE_RUN,
	MOVE_STATE_JUMP,
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
	std::vector<GameRoomInfo> gameRooms;
};

struct SendEvent;
using SendEventRef = std::shared_ptr<SendEvent>;

using ClientRef = std::shared_ptr<class Client>;
using RoomRef = std::shared_ptr<class Room>;

using GameRoomRef = std::shared_ptr<class GameRoom>;
using GameObjectRef = std::shared_ptr<class GameObject>;
using PlayerRef = std::shared_ptr<class Player>;