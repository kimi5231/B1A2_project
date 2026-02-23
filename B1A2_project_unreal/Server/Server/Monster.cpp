#include "pch.h"
#include "Monster.h"
#include "Global.h"
#include "Room.h"

Monster::Monster()
{
	_pos = {0, 200, 10};
	_rotation = { 0, 0, 0 };
	_type = ObjectType::Monster;
	_box.SetRanges({ _pos.x - 40,  _pos.y - 40,  _pos.z }, { _pos.x + 40,  _pos.y + 40,  _pos.z + 80 });
} 

Monster::~Monster()
{
}

void Monster::Update(std::unordered_map<std::pair<int, int>, short, PairHash>& map)
{
	// 일단은 랜덤한 방향으로 이동하도록, 추후 수정
	std::uniform_int_distribution<int> selectDir(static_cast<int>(Front), static_cast<int>(Left));
	Dir dir = static_cast<Dir>(selectDir(gen));

	Vector pos = _pos;
	// map 타일 한칸씩 이동
	switch (dir)
	{
	case Front:
		pos.y -= 100;
		break;
	case Right:
		pos.x += 100;
		break;
	case Back:
		pos.y += 100;
		break;
	case Left:
		pos.x -= 100;
		break;
	}

	// 해당 타일로 이동이 가능한지 확인
	std::pair<int, int> index{ pos.x / 10, pos.y / 10 };
	int x = pos.x / 10;
	int y = pos.y / 10;
	 
}