#include "pch.h"
#include "Creature.h"
#include "Global.h"
#include "Room.h"

Creature::Creature()
{
}

bool Creature::TackDamage(int damage)
{
    if (_isInvincible)
        return false;

    _hp -= damage;

    if (_hp < 0)
    {
        _hp = 0;
        SetState(ObjectState::DEAD);
    }
    else
    	SetState(ObjectState::HIT);

    return true;
}

bool Creature::TackHeal(int heal)
{
    _hp += heal;
    if(_hp > _maxHP)
		_hp = _maxHP;

    // 나중에 상태이상같은 거 확인
    return true;
}

bool Creature::SetState(ObjectState state, bool isSend)
{
    if (!GameObject::SetState(state, isSend))
        return false;

    return true;
}