#pragma once

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

struct GameRoomInfo
{
	GameRoomType type;
	Vector pos;
	Vector size;
};