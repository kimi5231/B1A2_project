#include "pch.h"
#include "Creature.h"
#include "Cube.h"
#include "Global.h"
#include "Room.h"

Creature::Creature()
{
}

bool Creature::TackDamage(int damage)
{
    _hp -= damage;

    if(_hp <= 0)
		SetState(ObjectState::DEAD);
    else
    	SetState(ObjectState::HIT);

    // 나중에 무적같은 거 확인
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

void Creature::SetPos(Vector pos)
{
	GameObject::SetPos(pos);
    SetCurrentCubeID();
}

void Creature::SetCurrentCubeID()
{
    const std::vector<CubeRef>& cubes = _ownerRoom->GetCubes();
    if (cubes.empty())
        return;

    // 최초로 지정하는 것이라면 전부 확인
    if (_currentCubeID == -1)
    {
        for (const auto& cube : cubes)
        {
            if (cube->GetBoundingBox().CheckInclude(_pos))
            {
                _currentCubeID = cube->GetID();
                return;
            }
        }
    }

    //for (const auto& cube : cubes[_currentCubeID]->GetConnectedCubes())
    for (const auto& cube : cubes)
    {
        if (cube->GetBoundingBox().CheckInclude(_pos))
        {
            _currentCubeID = cube->GetID();
            return;
        }
    }
}

bool Creature::SetState(ObjectState state, bool isSend)
{
    // 나중에 GameObject에 있는 내용 옮겨오기
    if (!GameObject::SetState(state, isSend))
        return false;

    return true;
}