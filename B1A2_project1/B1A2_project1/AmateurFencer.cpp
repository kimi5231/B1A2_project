#include "pch.h"
#include "AmateurFencer.h"
#include "BehaviorTree.h"
#include "Player.h"

AmateurFencer::AmateurFencer()
{
}

AmateurFencer::~AmateurFencer()
{
}

void AmateurFencer::BeginPlay()
{
	// Idle Sequence
	Condition* c1 = new Condition("is cur state Idle?", [&]() {return is_cur_state_Idle(); });
	Action* a1 = new Action("Idle", [&]() {return Idle(); });
	Sequence* IdleSequence = new Sequence();
	IdleSequence->addChild(c1);
	IdleSequence->addChild(a1);

	// Hit Sequence
	Condition* c2 = new Condition("is cur state Hit?", [&]() {return is_cur_state_hit(); });
	Action* a2 = new Action("Hit", [&]() {return Hit(); });
	Sequence* HitSequence = new Sequence();
	HitSequence->addChild(c2);
	HitSequence->addChild(a2);

	// Chase Sequence
	Condition* c3 = new Condition("is cur State Chase?", [&]() {return is_cur_state_chase(); });
	Action* a3 = new Action("Chase", [&]() {return Chase(); });
	Sequence* ChaseSequence = new Sequence();
	ChaseSequence->addChild(c3);
	ChaseSequence->addChild(a3);

	// Attack Selector
	// Close Atk Sequence
	Condition* c4 = new Condition("is cur State CloseAtk?", [&]() {return is_cur_state_close_atk(); });
	Action* a4 = new Action("CloseAtk", [&]() {return Close_atk(); });
	Sequence* CloseAtkSequence = new Sequence();
	CloseAtkSequence->addChild(c4);
	CloseAtkSequence->addChild(a4);
	// Long Atk Sequence
	Condition* c5 = new Condition("is cur State LongAtk?", [&]() {return is_cur_state_long_atk(); });
	Action* a5 = new Action("CloseAtk", [&]() {return Long_atk(); });
	// Dash Sequence
	Condition* c6 = new Condition("is cur State Dash?", [&]() {return is_cur_state_dash(); });
	Action* a6 = new Action("Dash", [&]() {return Dash(); });
	Sequence* DashSequence = new Sequence();
	DashSequence->addChild(c4);
	DashSequence->addChild(a4);
	
	Sequence* LongAtkSequence = new Sequence();
	LongAtkSequence->addChild(c5);
	LongAtkSequence->addChild(a5);
	LongAtkSequence->addChild(DashSequence);

	Selector* AttackSelector = new Selector();
	AttackSelector->addChild(CloseAtkSequence);
	AttackSelector->addChild(LongAtkSequence);
}

void AmateurFencer::Tick()
{
}

void AmateurFencer::Render(HDC hdc)
{
}

BehaviorState AmateurFencer::is_cur_state_Idle()
{
	if (_state == ObjectState::Idle)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState AmateurFencer::Idle()
{
	// �ø��� ����
	// ...

	float distance;	// �÷��̾���� �Ÿ� - ���� �ʿ�!!!

	if (distance <= 320)
	{
		_state = ObjectState::LongAttack;
		return BehaviorState::SUCCESS;
	}

	return BehaviorState::RUNNING;
}

BehaviorState AmateurFencer::is_cur_state_hit()
{
	if (_state == ObjectState::Hit)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState AmateurFencer::Hit()
{
	// �ø��� ����
	// ...

	//if (attacked �ø����� ����)
	//{
	//	if (_commonStat.hp <= 0)
	//	{
	//		_state = ObjectState::Dead;
	//		// �״� �ִϸ��̼� �ø��� 1�� ��� ��
	//		// �Ҹ��Ű��
	//	}
	//	_state = ObjectState::Idle;
	//	return BehaviorState::SUCCESS;
	//}
	//else
	//	return BehaviorState::RUNNING;

	return BehaviorState();
}

BehaviorState AmateurFencer::is_cur_state_chase()
{
	if (_state == ObjectState::Chase)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState AmateurFencer::Chase()
{
	int distance;

	if (distance > 120 && distance <= 320)
	{
		// �Ѿư��� �ڵ�
		return BehaviorState::RUNNING;
	}
	else if (distance <= 120)
	{
		_state = ObjectState::CloseAttack;
		return BehaviorState::SUCCESS;
	}
	/*else if (std::abs(distance - ��.��.��) > std::abs(distance - ��.��.��))
	{
		_state = ObjectState::LongAttack;
		return BehaviorState::SUCCESS;
	}*/
}

BehaviorState AmateurFencer::is_cur_state_close_atk()
{
	if (_state == ObjectState::CloseAttack)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState AmateurFencer::Close_atk()
{
	int distance;

	if (distance <= 120)
	{
		// �ٰŸ� ���� �ڵ�
		return BehaviorState::RUNNING;
	}
	else if (distance > 120 && distance <= 320)
	{
		_state = ObjectState::CloseAttack;
		return BehaviorState::SUCCESS;
	}
	/*else if (std::abs(distance - ��.��.��) > std::abs(distance - ��.��.��))
	{
		_state = ObjectState::LongAttack;
		return BehaviorState::SUCCESS;
	}*/
}

BehaviorState AmateurFencer::is_cur_state_long_atk()
{
	if (_state == ObjectState::LongAttack)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState AmateurFencer::Long_atk()
{
	int distance;

	//if (std::abs(distance - ��.��.��) > std::abs(distance - ��.��.��))
	//{
	//	���Ÿ� ���� �ڵ�	
	//	return BehaviorState::RUNNING;
	//}
	if (distance <= 120)
	{
		_state = ObjectState::CloseAttack;
		return BehaviorState::SUCCESS;
	}
	else if (distance > 120 && distance <= 320)
	{
		_state = ObjectState::Chase;
		return BehaviorState::SUCCESS;
	}

}

BehaviorState AmateurFencer::is_cur_state_dash()
{
	if (_state == ObjectState::Dash)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState AmateurFencer::Dash()
{
	// Dash �ִϸ��̼� �� �� ��� ��

	_state = ObjectState::Chase;	// ������ ����!?
}
