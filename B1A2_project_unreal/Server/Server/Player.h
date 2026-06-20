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
	virtual void Init();
	virtual void Update();

public:
	bool AddItemToInventory(bool isTool, int id);
	bool RemoveItemFromInventory(bool isTool, int id);
	bool ExistItem(bool isTool, int id);

	void Attack(Room* room);
	void Respawn();

	void AddFearCount() { _fearCount++; }

public:
	virtual bool SetState(ObjectState state, bool isSend = true);
	int GetCurrentTool() { return _currentTool; }
	void SetCurrentTool(int toolID) { _currentTool = toolID; }
	Emotion GetCurrentEmotion() { return _currentEmotion; }
	void SetCurrentEmotion(Emotion emotion) { _currentEmotion = emotion; }
	Session* GetClient() { return _client; }
	void SetClient(Session* client) { _client = client; }
	int GetLookRange() { return _lookRange; }
	int GetLookHeight() { return _lookHeight; }
	float GetLookAngle() { return _lookAngle; }
	bool GetIsCanMove() { return _isCanMove; }
	void SetIsCanMove(bool isCanMove) { _isCanMove = isCanMove; }
	int GetFearCount() { return _fearCount; }

private:
	Session* _client;
	Inventory* _inventory{};
	int _currentTool{};
	Emotion _currentEmotion{};
	int _fearCount{};

	int _lookRange;
	int _lookHeight;
	float _lookAngle;

	bool _isCanMove;
};