#pragma once

enum
{
	TEST = 1,
	EnterRoom = 2,
	Add_Player = 3,
};

class Player;

class Room
{
public:
	Room();
	virtual ~Room();

	void Update();

public:
	void AddPlayer();

public:
	// temp. 추후 전용 클래스 생성 예정.
	void SendAddPlayerPacket(std::shared_ptr<Player> player);

public:
	std::vector<SOCKET> _clients;

private:
	std::unordered_map<int, std::shared_ptr<Player>> _players;

	// temp
	int _playerID = 1;
};