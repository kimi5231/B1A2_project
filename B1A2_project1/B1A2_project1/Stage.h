#pragma once
#include "ResourceBase.h"

struct StageInfo
{
	int32 id;	// A
	Dir dir;	// B
	Vec2 spawnPos;	// C, D
	float movingDistance;	// E
	Vec2 movementLimit;	// F, G
};

class Stage : public ResourceBase
{
public:
	Stage();
	virtual ~Stage() override;

public:
	virtual void LoadFile(const std::wstring& path) override;

public:
	std::vector<StageInfo>& GetInfos() { return _infos; }

private:
	std::vector<StageInfo> _infos;
};