#pragma once
#include "BoundingBox.h"

class Door;

class Cube
{
public:
	Cube(Vector pos, Dir dir, CubeInfo info);
	~Cube();

public:
	void Update();

public:
	std::vector<Door*> CreateDoors();
	bool CheckCollision(BoundingBox other) { return _box.CheckCollision(other.GetBounds()); };
	bool CheckInclude(BoundingBox other) { return _box.CheckInclude(other.GetBounds()); }

	void AddConnectedRoom(CubeRef gameRoom) { _connetedCube.push_back(gameRoom); }
	void AddDoor(int doorID) { _doors.push_back(doorID); }

public:
	void SetCubeInfo(CubeInfo info) { _info = info; }
	CubeInfo GetCubeInfo() { return _info; }
	void SetCubeType(CubeType type) { _info.type = type; }
	CubeType GetCubeType() { return _info.type; }
	void SetSize(Vector size) { _info.size = size; }
	Vector GetSize() { return _info.size; }
	void SetPos(Vector pos) { _pos = pos; }
	Vector GetPos() { return _pos; }
	void SetDir(Dir dir) { _dir = dir; }
	Dir GetDir() { return _dir; }
	BoundingBox GetBoundingBox() { return _box; }
	void SetID(int id) { _id = id; }
	int GetID() { return _id; }
	std::vector<int>& GetDoors() { return _doors; }
	std::vector<CubeRef>& GetConnectedCubes() { return _connetedCube; }

private:
	CubeInfo _info{};
	int _id{};
	Vector _pos{};
	Dir _dir{};
	BoundingBox _box;
	std::vector<int> _doors;
	std::vector<CubeRef> _connetedCube;
};