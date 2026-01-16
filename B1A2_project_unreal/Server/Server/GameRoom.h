#pragma once
class GameRoom
{
public:
	GameRoom();
	~GameRoom();

public:
	void Update();

public:
	void SetGameRoomInfo(GameRoomInfo info) { _info = info; }
	GameRoomInfo GetGameRoomInfo() { return _info; }
	void SetGameRoomType(GameRoomType type) { _info.type = type; }
	GameRoomType GetGameRoomType() { return _info.type; }
	void SetPos(Vector pos) { _info.pos = pos; }
	Vector GetPos() { return _info.pos; }
	void SetSize(Vector size) { _info.size = size; }
	Vector GetSize() { return _info.size; }

private:
	GameRoomInfo _info{};
};