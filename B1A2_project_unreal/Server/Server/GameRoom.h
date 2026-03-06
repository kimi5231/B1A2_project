#pragma once
#include "BoundingBox.h"

class Door;

class GameRoom
{
public:
	GameRoom(Vector pos, Dir dir, GameRoomInfo info);
	~GameRoom();

public:
	void Update();

public:
	std::vector<DoorRef>& CreateDoors();
	bool CheckCollision(BoundingBox other) { return _box.CheckCollision(other.GetBounds()); };
	bool CheckInclude(BoundingBox other) { return _box.CheckInclude(other.GetBounds()); }

	void AddConnectedRoom(GameRoomRef gameRoom) { _connetedRoom.push_back(gameRoom); }

public:
	void SetGameRoomInfo(GameRoomInfo info) { _info = info; }
	GameRoomInfo GetGameRoomInfo() { return _info; }
	void SetGameRoomType(GameRoomType type) { _info.type = type; }
	GameRoomType GetGameRoomType() { return _info.type; }
	void SetSize(Vector size) { _info.size = size; }
	Vector GetSize() { return _info.size; }
	void SetPos(Vector pos) { _pos = pos; }
	Vector GetPos() { return _pos; }
	void SetDir(Dir dir) { _dir = dir; }
	Dir GetDir() { return _dir; }
	BoundingBox GetBoundingBox() { return _box; }
	std::vector<DoorRef>& GetWalls() { return _walls; }
	void SetID(uint id) { _id = id; }

private:
	GameRoomInfo _info{};
	uint _id{};
	Vector _pos{};
	Dir _dir{};
	BoundingBox _box;

	// 순환참조 방지
	std::vector<std::weak_ptr<GameRoom>> _connetedRoom;
	std::vector<DoorRef> _doors;
	std::vector<DoorRef> _walls;
};