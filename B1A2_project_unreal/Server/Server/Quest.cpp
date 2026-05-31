#include "pch.h"
#include "Quest.h"

Quest::Quest()
{
	_id = 0;
	_currentCollectCount = 0;
}

Quest::~Quest()
{
}

bool Quest::IsNeed(ItemType itemType)
{
	if(_collectItemType != itemType)
		return false;

	if (_currentCollectCount == _goalCollectCount)
		return false;

	return true;
}