#include "pch.h"
#include "Creature.h"
#include "Cube.h"
#include "Global.h"
#include "Room.h"

Creature::Creature()
{
    _currentCubeID = 0;
    _hp = 50;
}

bool Creature::GetDamage(int damage)
{
    _hp -= damage;

    // 나중에 무적같은 거 확인
    return true;
}

void Creature::SetPos(Vector pos)
{
	GameObject::SetPos(pos);
    if(g_framework != nullptr)
        SetCurrentCubeID(g_framework->GetRoom()->GetCubes());
}

void Creature::SetCurrentCubeID(const std::vector<CubeRef>& cubes)
{
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

    // 
    for (const auto& cube : cubes[_currentCubeID]->GetConnectedCubes())
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