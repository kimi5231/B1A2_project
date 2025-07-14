#pragma once
#include "Monster.h"
#include "Stat.h"

class BrokenCopyMachine : public Monster
{
public:
	BrokenCopyMachine();
	virtual ~BrokenCopyMachine();

public:
	void SetBrokenCopyMachineStat(BrokenCopyMachineStat* stat) { _stat = stat; }

private:
	BrokenCopyMachineStat* _stat;
};