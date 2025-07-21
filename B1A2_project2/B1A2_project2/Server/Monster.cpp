#include "pch.h"
#include "Monster.h"

Monster::Monster()
{

}

Monster::~Monster()
{

}

void Monster::Update()
{
	switch (_objectInfo.state())
	{
	case IDLE:
		UpdateIdle();
		break;
	case LONG_ATTACK:
		UpdateLongAttack();
		break;
	}
}