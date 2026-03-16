#include "pch.h"
#include "Tool.h"

Tool::Tool(ItemType itemType)
	:Item(itemType)
{
	_type = ObjectType::Tool;
}

Tool::~Tool()
{
}

void Tool::Update()
{

}