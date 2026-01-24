#pragma once

using uint = unsigned int;

enum class ObjectType
{
	Player,
};

enum ObjectState
{
	IDLE,
	RUN,
	JUMP,
};

enum Dir
{
	Front,
	Right,
	Back,
	Left,

	DirCount
};

enum class GameRoomType
{
	MainEntranceRoom,

	GapRoom,
	Staircase,
	RailCatwalk,
	ApparatusRoom,
	ServerRoom,
	CabinetRoom,
	StorageRoom_Rect,
	StorageRoom_Corner,
	StorageRoom_Step,
	YellowOfficeRoom,
	PipedHallways_Line,
	PipedHallways_Grid,
	FactoryRoom,
};

enum Difficulty 
{
	Easy,
	Normal,
	Hard,

	DifficultyCount,
};

struct Vector
{
	float x;
	float y;
	float z;

	Vector operator+(const Vector& other) const
	{
		return {other.x + x, other.y + y, other.z + z};
	}
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
	Vector size;
	std::unordered_map<Dir, Vector> leftTopPos;
	bool isCreateItem;
	bool isCreateExit;
	std::unordered_map<Difficulty, uint> minCreateCount;
	std::unordered_map<Difficulty, uint> maxCreateCount;
	std::unordered_map<Difficulty, float> spawnChance;
	std::pair<uint, uint> doorCount;
	std::unordered_map<Dir, std::vector<Vector>> doorPos;
	std::vector<Dir> doorDir;
};

struct GameRoomConditionInfo
{
	uint totalGameRoomCount;
	std::pair<uint, uint> createItemCount;
	std::pair<uint, uint> createExitCount;
	std::pair<uint, uint> exitPos;
	std::pair<uint, uint> floor;
};