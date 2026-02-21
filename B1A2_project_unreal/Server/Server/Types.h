#pragma once

using uint = unsigned int;

//------------------Enums------------------
enum class ObjectType
{
	Player,
	Monster,
	Item,
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

enum Difficulty 
{
	Easy,
	Normal,
	Hard,

	DifficultyCount,
};

enum TileState : short
{
	Impassable = 0b00, // 갈 수 없음 + 물체 없음
	Passable = 0b01, // 갈 수 있음 + 물체 없음
	Wall = 0b10, // 갈 수 없음 + 물체 있음 == 벽
	Occupied = 0b11  // 갈 수 있음 + 물체 있음
};

enum ItemType
{
	CardboardBox,

	ItemTypeCount,
};

enum Floor
{
	B2 = -2,
	B1 = -1,
	F1 = 0,
	F2 = 1,
	F3 = 2,
};

//------------------Struct------------------
// unordered map에 pair를 쓰기 위해 필요한 구조체
struct PairHash
{
	size_t operator()(const std::pair<int, int>& p) const noexcept 
	{
		// 두 값을 섞어서 Hash 생성
		return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
	}
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
	//std::unordered_map<Dir, Vector> leftTopPos;
	bool isCreateItem;
	bool isCreateExit;
	std::unordered_map<Difficulty, uint> minCreateCount;
	std::unordered_map<Difficulty, uint> maxCreateCount;
	std::unordered_map<Difficulty, float> spawnChance;
	std::pair<uint, uint> f1DoorCount;
	std::pair<uint, uint> f2DoorCount;
	std::vector<Vector> f1DoorPos;
	std::vector<Vector> f2DoorPos;
	//std::unordered_map<Dir, std::vector<Vector>> f1DoorPos;
	//std::unordered_map<Dir, std::vector<Vector>> f2DoorPos;
	std::vector<Dir> doorDir;
	int enterDistance;
};

struct GameRoomConditionInfo
{
	uint totalGameRoomCount;
	std::pair<uint, uint> createItemCount;
	std::pair<uint, uint> createExitCount;
	std::pair<uint, uint> exitPos;
	std::pair<uint, uint> floor;
};