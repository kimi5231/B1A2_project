#include "pch.h"
#include "Tool.h"

Tool::Tool(ItemType itemType)
	:Item(itemType)
{

}

Tool::~Tool()
{
}

void Tool::Update()
{

}

void Tool::UseTool()
{
	switch (_itemType)
	{
	case Cutlass:
		// 몬스터와 충돌처리할 바운딩 박스 생성
		break;
	case Blaster:
		// 몬스터와 충돌처리할 총알 생성
		break;
	case Key:
		break;
	case Lantern:
		break;
	}
}