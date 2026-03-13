#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public: 
	Player();
	virtual ~Player();

public:
	virtual void Update();

public:
	void AddItemToInventory(ItemRef item, bool isTool);

private:

};