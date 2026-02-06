#include "pch.h"
#include "Monster.h"

Monster::Monster()
{
	_pos = { Width / 2 * 10 + 100, Height / 2 * 10, 100 };
	_rotation = { 0, 0, 0 };
}

Monster::~Monster()
{
}

void Monster::Update()
{

}
