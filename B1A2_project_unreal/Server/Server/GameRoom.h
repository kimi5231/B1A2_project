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
	void SetPos(Vector pos) { pos = pos; }
	Vector GetPos() { return _pos; }
	void SetSize(Vector size) { _info.size = size; }
	Vector GetSize() { return _info.size; }

private:
	GameRoomInfo _info{};
	Vector _pos{};

	std::vector<DoorRef> _doors;
};