#pragma once
#include "Creature.h"

class Inventory;
class Room;
class Session;

class Player : public Creature
{
public: 
	Player();
	virtual ~Player();

public:
	virtual void Update();

public:
	bool AddItemToInventory(bool isTool, int id);
	bool RemoveItemFromInventory(bool isTool, int id);
	bool ExistItem(bool isTool, int id);

	void Attack(Room* room);

public:
	int GetCurrentTool() { return _currentTool; }
	void SetCurrentTool(int toolID) { _currentTool = toolID; }
	Emotion GetCurrentEmotion() { return _currentEmotion; }
	void SetCurrentEmotion(Emotion emotion) { _currentEmotion = emotion; }
	Session* GetSession() { return _client; }

private:
	Session* _client;
	Inventory* _inventory{};
	int _currentTool{};
	Emotion _currentEmotion{};
};