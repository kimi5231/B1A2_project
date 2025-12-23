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
struct C_Move_Packet
{
	int objectID;
	Vector pos;
	Rotation rotation;
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
	Rotation rotaion;
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
};

template <class T>
struct SendEvent;
template <class T>
using SendEventRef = std::shared_ptr<SendEvent<T>>;

using EventType = std::variant<SendEventRef<S_AddObject_Packet>, SendEventRef<S_RemoveObject_Packet>,
					SendEventRef<S_Move_Packet>, SendEventRef<S_CreateGameRoom_Packet>>;


using ClientRef = std::shared_ptr<class Client>;
using RoomRef = std::shared_ptr<class Room>;

using GameRoomRef = std::shared_ptr<class GameRoom>;
using GameObjectRef = std::shared_ptr<class GameObject>;
using PlayerRef = std::shared_ptr<class Player>;