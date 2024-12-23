#include "pch.h"
#include "Inventory.h"
#include "ValueManager.h";
#include "ResourceManager.h"
#include "Texture.h"
#include "Player.h"
#include "Item.h"
#include "FlipbookActor.h"
#include "Flipbook.h"
#include "InputManager.h"

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
	if (_inventoryState == InventoryState::Show)
	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

		//if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
			// MouseClick(mousePos);	// ������ �߻��Ѵ�..
	}
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

			int32 boxX = ITEM_STARTX + (i % 5) * ITEM_SIZEX;
			int32 boxY = ITEM_STARTY + (i / 5) * ITEM_SIZEY;

			::TransparentBlt(hdc,
				boxX,
				boxY,
				ITEM_SIZEX,
				ITEM_SIZEY,
				texture->GetDC(),
				0,
				0,
				ITEM_SIZEX,
				ITEM_SIZEY,
				texture->GetTransparent());

			_itemBoxes.push_back({ boxX, boxY, boxX + ITEM_SIZEX, boxY + ITEM_SIZEY });

			// ������ ���� ���
			std::wstring itemCountStr = std::to_wstring(itemCount);

			// ����� ��ġ
			RECT rect = { boxX + 108, boxY, boxX + ITEM_SIZEX, boxY + 20 };

			HFONT hfont = CreateFont(
				-20.f * winSizeAdjustmemt.y,
				0,
				0,
				0,
				FW_NORMAL,
				FALSE,
				FALSE,
				FALSE,
				DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_SWISS,
				L"�ձٸ��");

			// ��Ʈ ����
			HFONT oldFont = (HFONT)::SelectObject(hdc, hfont);

			// �ؽ�Ʈ ���� ����
			::SetTextColor(hdc, RGB(0, 0, 0));

			// �ؽ�Ʈ ��� ����ȭ
			::SetBkMode(hdc, TRANSPARENT);

			Utils::DrawString(hdc, itemCountStr, rect);

			::SetTextColor(hdc, RGB(0, 0, 0));
			::SelectObject(hdc, oldFont);
			::DeleteObject(hfont);
		}	
	}

	// Photo
	{
		if (_clickedItemID != 0)
		{
			Texture* texture = nullptr;

			switch (_clickedItemID)
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
				81,
				165,
				426,
				323,
				texture->GetDC(),
				0,
				0,
				128,
				128,
				texture->GetTransparent());
		}
	}

	// explain
	{
		if (_clickedItemID != 0)
		{
			// ����� ����
			std::wstring explain;
			auto it = _itemInfo.find(_clickedItemID);
			if (it != _itemInfo.end())
				explain = it->second->explain;

			// ����� ��ġ
			RECT rect = { 81, 488, 507, 677 };

			HFONT hfont = CreateFont(
				-20.f * winSizeAdjustmemt.y,
				0,
				0,
				0,
				FW_NORMAL,
				FALSE,
				FALSE,
				FALSE,
				DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_SWISS,
				L"�ձٸ��");

			// ��Ʈ ����
			HFONT oldFont = (HFONT)::SelectObject(hdc, hfont);

			// �ؽ�Ʈ ���� ����
			::SetTextColor(hdc, RGB(0, 0, 0));

			// �ؽ�Ʈ ��� ����ȭ
			::SetBkMode(hdc, TRANSPARENT);

			Utils::DrawString(hdc, explain, rect);

			::SetTextColor(hdc, RGB(0, 0, 0));
			::SelectObject(hdc, oldFont);
			::DeleteObject(hfont);
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

void Inventory::MouseClick(POINT mousePos)
{
	int32 i = 0;
	for (const RECT& box : _itemBoxes)
	{
		if (mousePos.x >= box.left && mousePos.x <= box.right &&
			mousePos.y >= box.top && mousePos.y <= box.bottom)
		{
			// Ŭ���� �������� ID ��������
			auto it = std::next(_acquiredItems.begin(), i);
			_clickedItemID = it->first;
		}
		++i;
	}
}
