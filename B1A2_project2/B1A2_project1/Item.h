#pragma once
#include "ResourceBase.h"

struct ItemInfo
{
	int32 ID;	
	std::wstring name;
	std::wstring explain;
	bool acquiredByFKey;
	int32 droppingMonsterPersonalID;
	Vec2 spawnPos;	// 스폰 위치 (spawnXpos, spawnYpos)
};

class Item : public ResourceBase
{
public:
	Item();
	virtual ~Item() override;

public:
	virtual void LoadFile(const std::wstring& path) override;
	std::unordered_map<int32, ItemInfo*> GetItems() const { return _items; }

private:
	std::unordered_map<int32, ItemInfo*> _items;	
};