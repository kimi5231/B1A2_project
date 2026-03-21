#pragma once
#include "Item.h"

class Tool : public Item
{
public:
	Tool(ItemType itemType);
	virtual ~Tool();

public:
	virtual void Update();
	void UseTool();
};