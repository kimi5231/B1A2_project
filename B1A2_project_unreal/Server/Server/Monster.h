#pragma once
#include "GameObject.h"

class Monster : public GameObject
{
public:
	Monster();
	~Monster();

public:
	void Update(std::unordered_map<std::pair<int, int>, short, PairHash>& map);
};