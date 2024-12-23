#include "pch.h"
#include "Inventory.h"
#include "ValueManager.h";
#include "ResourceManager.h"
#include "Texture.h"
#include "Player.h"
#include "Item.h"
#include "FlipbookActor.h"
#include "Flipbook.h"

Inventory::Inventory()
{
	// Flipbook
	_flipbookKey = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_keyInInventory");
	_flipbookPencil = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_pencilInInventory");
	_flipbookMatch = GET_SINGLE(ResourceManager)->GetFlipbook(L"1003_matchInInventory");

	// csv ���Ϸ� ������ Item ���� ������
	_itemList = GET_SINGLE(ResourceManager)->GetItem(L"Item");
	_itemInfo = _itemList->GetItems();
}

Inventory::~Inventory()
{
}

void Inventory::BeginPlay()
{
}

void Inventory::TickComponent()
{
}

void Inventory::Render(HDC hdc)
{
	if (_inventoryState == InventoryState::Hidden)
		return;

	// ���� ���� ��������
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();
	Vec2 cameraPosAdjustmemt = GET_SINGLE(ValueManager)->GetCameraPosAdjustment();

	// �κ��丮 ��
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Inventory");
		::TransparentBlt(hdc,
			0,
			0,
			texture->GetSize().x,
			texture->GetSize().y,
			texture->GetDC(),
			0,
			0,
			texture->GetSize().x,
			texture->GetSize().y,
			texture->GetTransparent());
	}

	// _acquiredItems���� ���� �����ͼ� ���(�κ��丮 ��, ���� / ���콺 ��� - �κ��丮 �� �ø��� ����, ����, ����)
	if (_acquiredItems.empty())	// ȹ���� �������� ������ �� �׸�
		return;

	// Item
	{
		int32 i = 0;	// ��ġ ���� Count
		for (auto it = _acquiredItems.begin(); it != _acquiredItems.end(); ++it, ++i)
		{
			int32 itemID = it->first;
			int32 itemCount = it->second;

			// �������� ���� ��������
			auto itemInfoIt = _itemInfo.find(itemID);
			if (itemInfoIt != _itemInfo.end())
				const ItemInfo* itemInfo = itemInfoIt->second;

			// ����� ���ҽ� ���ϱ�
			Texture* texture = nullptr;

			switch (itemID)
			{
			case 1001:
				texture = GET_SINGLE(ResourceManager)->GetTexture(L"1001_keyInInventory"); break;
				break;
			case 1002:
				texture = GET_SINGLE(ResourceManager)->GetTexture(L"1002_pencilInInventory"); break;
			case 1003:
				texture = GET_SINGLE(ResourceManager)->GetTexture(L"1003_matchInInventory"); break;
			}

			::TransparentBlt(hdc,
				ITEM_STARTX + (i % 5) * ITEM_SIZEX,
				ITEM_STARTY + (i / 5) * ITEM_SIZEY,
				ITEM_SIZEX,
				ITEM_SIZEY,
				texture->GetDC(),
				0,
				0,
				ITEM_SIZEX,
				ITEM_SIZEY,
				texture->GetTransparent());
		}	
	}
	
}

void Inventory::SaveAcquireItems()
{
	if (!_owner)
		return;

	// Player�� ����� _acquiredItems ������
	_acquiredItems = _owner->GetAquireItems();
}

