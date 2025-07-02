#pragma once
#include "ResourceBase.h"

struct ItemStageInfo
{
	int32 id;
	bool acquiredByFKey;
	int32 droppingMonsterPersonalID;
	Vec2 spawnPos;
};

class ItemStage : public ResourceBase
{
public:
	ItemStage();
	virtual ~ItemStage() override;

public:
	virtual void LoadFile(const std::wstring& path) override;

public:
	std::vector<ItemStageInfo>& GetItemStageInfos() { return _infos; }

private:
	std::vector<ItemStageInfo> _infos;
};