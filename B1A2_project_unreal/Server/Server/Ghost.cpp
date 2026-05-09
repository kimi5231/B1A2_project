#include "pch.h"
#include "Ghost.h"

Ghost::Ghost(MonsterType monsterType, Room* ownerRoom)
	: Monster(monsterType, ownerRoom)
{
}

Ghost::~Ghost()
{
}

void Ghost::Update(Room* room)
{
}

bool Ghost::IsReadyNextState()
{
	return false;
}

bool Ghost::SetState(ObjectState state, bool isSend)
{
	return false;
}