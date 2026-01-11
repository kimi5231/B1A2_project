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
	C_UpdateObjectState,
	C_Move,

	//Server
	S_AddObject,
	S_UpdateObjectState,
	S_Move,
	S_CreateGameRoom,
};

enum MoveState
{
	MOVE_STATE_IDLE,
	MOVE_STATE_RUN,
	MOVE_STATE_JUMP,
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
	Rotation rotation;
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
	GameRoomInfo room1;
	GameRoomInfo room2;
	GameRoomInfo room3;
	GameRoomInfo room4;
	GameRoomInfo room5;
};