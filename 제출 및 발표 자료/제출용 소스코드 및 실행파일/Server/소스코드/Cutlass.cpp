#include "pch.h"
#include "Cutlass.h"

Cutlass::Cutlass(ItemType itemType)
	:Tool(itemType)
{
	_angle = 180.f;
	_range = 150.f;
	_height = 200.f;
	_damage = 15;
}