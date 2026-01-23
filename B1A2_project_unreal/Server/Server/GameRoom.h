#pragma once

class Door;

class GameRoom
{
public:
	GameRoom();
	~GameRoom();

public:
	void Update();

public:
	std::vector<DoorRef>& CreateDoors();

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

private:
	GameRoomInfo _info{};
	Vector _pos{};
	Dir _dir{};

	std::vector<DoorRef> _doors;
};