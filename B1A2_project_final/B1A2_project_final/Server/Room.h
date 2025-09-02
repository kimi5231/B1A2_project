#pragma once

class Player;

class Room
{
public:
	Room();
	virtual ~Room();

	void Update();

public:
	void AddPlayer();

private:
	std::unordered_map<int, std::shared_ptr<Player>> _players;
};