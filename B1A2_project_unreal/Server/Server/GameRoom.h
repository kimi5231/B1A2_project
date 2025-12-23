#pragma once
class GameRoom
{
public:
	GameRoom();
	~GameRoom();

public:
	void Update();

public:
	void SetGameRoomType(GameRoomType type) { _type = type; }
	GameRoomType GetGameRoomType() { return _type; }
	void SetPos(Vector pos) { _pos = pos; }
	Vector GetPos() { return _pos; }
	void SetSize(Vector size) { _size = size; }
	Vector GetSize() { return _size; }

private:
	GameRoomType _type;
	Vector _pos;
	Vector _size;
};