#pragma once
#include "ResourceBase.h"

struct Line
{
	std::wstring speakerName;
	int32 speakerID;
	int32 state;
	int32 dir;
	std::wstring type;
	std::wstring cutScene;
	Vec2 moveDistance;
	std::wstring speech;
};

class Dialogue : public ResourceBase
{
public:
	Dialogue();
	virtual ~Dialogue() override;

public:
	virtual void LoadFile(const std::wstring& path) override;

public:
	std::vector<Line>& GetEvent(const std::wstring& key) { return _events[key]; }

private:
	std::unordered_map<std::wstring, std::vector<Line>> _events;
};