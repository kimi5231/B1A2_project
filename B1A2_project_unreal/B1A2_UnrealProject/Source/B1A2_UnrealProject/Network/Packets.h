#pragma once

#include <vector>

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
	Monster,
	Item,
};

enum class GameRoomType
{
	MainEntranceRoom,

	GapRoom,
	ApparatusRoom,
	ServerRoom,
	CabinetRoom,
	StorageRoom_Rect,
	StorageRoom_Corner,
	StorageRoom_Step,
	YellowOfficeRoom,
	FactoryRoom,

	RailCatwalk,
	PipedHallways_Line,
	PipedHallways_Grid,

	Staircase,
};

enum Dir
{
	Front,
	Right,
	Back,
	Left,

	DirCount
};

struct GameRoomDTO
{
	GameRoomType type;
	Vector pos;
	Dir dir;
};

enum PacketID
{
	// Client
	C_UpdateObjectState,
	C_Move,

	//Server
	S_AddObject,
	S_AddItem,
	S_UpdateObjectState,
	S_Move,
	S_CreateGameRoom,
};

enum ObjectState
{
	IDLE,
	RUN,
	JUMP,
};

enum ItemType
{
	CardboardBox,

	ItemTypeCount,
};

// 언리얼 전용
UENUM(BlueprintType)
enum class EMoveState : uint8
{
	MOVE_STATE_IDLE UMETA(DisplayName = "Idle"),
	MOVE_STATE_RUN  UMETA(DisplayName = "Run"),
	MOVE_STATE_JUMP UMETA(DisplayName = "Jump")
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
	ObjectType type;
	int objectID;
	Vector pos;
	Rotation rotation;
	ObjectState state;
};

struct S_CreateGameRoom_Packet
{
	std::vector<GameRoomDTO> gameRooms;
};