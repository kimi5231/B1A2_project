#pragma once
#include "Quest.h"

class MainQuest : public Quest
{
public:
	MainQuest();
	virtual ~MainQuest();

public:
	void ChangeNextQuest();
};