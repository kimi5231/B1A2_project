#pragma once
#include "Quest.h"

class SubQuest : public Quest
{
public:
	SubQuest(int currentStage);
	virtual ~SubQuest();

public:
	virtual void UpdateQuest(int currentStage) override;

	bool IsEnd(int currentStage);

public:
	virtual int GetDeadLine() override { return _deadLine; }

private:
	int _startStage;
	int _deadLine;
};