#include "pch.h"
#include "Cutlass.h"

Cutlass::Cutlass(ItemType itemType)
	:Tool(itemType)
{
	_angle = 120.f;
	_range = 150.f;
	_damage = 15;
}