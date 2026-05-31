#pragma once
#include "Quest.h"

class SubQuest : public Quest
{
public:
	SubQuest();
	virtual ~SubQuest();

public:
	virtual void UpdateQuest() override;
	void MinusDeadLine() { _deadLine--; }

public:
	virtual int GetDeadLine() override { return _deadLine; }

private:
	int _deadLine;
};