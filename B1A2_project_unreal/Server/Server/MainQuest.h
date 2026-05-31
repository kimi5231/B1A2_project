#pragma once
#include "Quest.h"

class MainQuest : public Quest
{
public:
	MainQuest();
	virtual ~MainQuest();

public:
	virtual void UpdateQuest(int currentStage) override;
};