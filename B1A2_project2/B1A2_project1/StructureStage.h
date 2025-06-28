#pragma once
#include "ResourceBase.h"
#include <string>

struct StructureStageInfo
{
	std::wstring name;
	Vec2 spawnPos;
	Vec2 keyPos;
	int32 wallType;
	int32 zipLineType;
	int32 zipLineRenderType;
	Vec2 zipLineStartPos;
	Vec2 zipLineEndPos;
	Vec2 zipLineButtonPos;
	Vec2 zipLineDisplayPos;
	float windowFlickeringCycle;
	float windowFlickeringDuration;
};

class StructureStage : public ResourceBase
{
public:
	StructureStage();
	virtual ~StructureStage() override;

public:
	virtual void LoadFile(const std::wstring& path) override;

public:
	std::vector<StructureStageInfo>& GetStructureStageInfos() { return _infos; }

private:
	std::vector<StructureStageInfo> _infos;
};