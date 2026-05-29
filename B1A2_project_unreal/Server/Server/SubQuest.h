#pragma once
#include "Quest.h"

class SubQuest : public Quest
{
public:
	SubQuest(int currentStage);
	virtual ~SubQuest();

public:
	void ChangeQuest(int currentStage);

private:
	int _startStage;
	int _deadLine;
};