#pragma once
class Room
{
public:
	Room();
	~Room();

public:
	void Update();

public:
	GameObjectRef AddObject(ObjectType type);

public:
	GameObjectRef GetObject(UINT id);
	const std::unordered_map<UINT, PlayerRef>& GetPlayers() { return _players; }

private:
	UINT _generatePlayerID{};

	std::unordered_map<UINT, PlayerRef> _players;
};