#include "pch.h"
#include "Creature.h"

Creature::Creature()
{
    _hp = 50;
}

bool Creature::GetDamage(int damage)
{
    _hp -= damage;

    // 나중에 무적같은 거 확인
    return true;
}

bool Creature::SetState(ObjectState state)
{
    // 나중에 GameObject에 있는 내용 옮겨오기
    if (!GameObject::SetState(state))
        return false;

    return false;
}