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

		if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
			 MouseClick(mousePos);	
	}
}

void Inventory::Render(HDC hdc)
{
	if (_inventoryState == InventoryState::Hidden)
		return;

	// ���� ���� ��������
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	// �κ��丮 ��
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Inventory");
		::TransparentBlt(hdc,
			0,
			0,
			(texture->GetSize().x) * winSizeAdjustmemt.x,
			(texture->GetSize().y) * winSizeAdjustmemt.y,
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
			case 1002:
				texture = GET_SINGLE(ResourceManager)->GetTexture(L"1002_pencilInInventory"); break;
			case 1003:
				texture = GET_SINGLE(ResourceManager)->GetTexture(L"1003_matchInInventory"); break;
			}

			int32 boxX = ITEM_STARTX + (i % 5) * ITEM_SIZEX;
			int32 boxY = ITEM_STARTY + (i / 5) * ITEM_SIZEY;

			// ���õ� �������� ������ ǥ�� - �ؽ�ó�� ������ ����
			int32 textureStartY = 0;
			
			if (_clickedItemID == 0)
			{
				textureStartY = 0;
			}
			else
			{
				textureStartY = ITEM_SIZEX;
			}
				

			::TransparentBlt(hdc,
				boxX * winSizeAdjustmemt.x,
				boxY * winSizeAdjustmemt.y,
				ITEM_SIZEX * winSizeAdjustmemt.x,
				ITEM_SIZEY * winSizeAdjustmemt.y,
				texture->GetDC(),
				0,
				textureStartY,
				ITEM_SIZEX,
				ITEM_SIZEY,
				texture->GetTransparent());

			_itemBoxes.push_back({ boxX, boxY, boxX + ITEM_SIZEX, boxY + ITEM_SIZEY });

			// ������ ���� ���
			std::wstring itemCountStr = std::to_wstring(itemCount);

			// ����� ��ġ
			RECT rect = { (boxX + 108) * winSizeAdjustmemt.x, boxY * winSizeAdjustmemt.y, (boxX + ITEM_SIZEX) * winSizeAdjustmemt.x, (boxY + 20) * winSizeAdjustmemt.y };

			// ��Ʈ ����
			HFONT hfont = Utils::MakeFont(20.f * winSizeAdjustmemt.y * winSizeAdjustmemt.y, L"DungGeunMo");

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
				81 * winSizeAdjustmemt.x,
				165 * winSizeAdjustmemt.y,
				426 * winSizeAdjustmemt.x,
				323 * winSizeAdjustmemt.y,
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
			RECT rect = { 81 * winSizeAdjustmemt.x, 488 * winSizeAdjustmemt.y, 507 * winSizeAdjustmemt.x, 677 * winSizeAdjustmemt.y };

			// ��Ʈ ����
			HFONT hfont = Utils::MakeFont(20.f * winSizeAdjustmemt.y, L"DungGeunMo");

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

	// ���� ���� ��������
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	for (const RECT& box : _itemBoxes)
	{
		if (mousePos.x >= box.left * winSizeAdjustmemt.x && mousePos.x <= box.right * winSizeAdjustmemt.x &&
			mousePos.y >= box.top * winSizeAdjustmemt.y && mousePos.y <= box.bottom * winSizeAdjustmemt.y)
		{
			if (i < _acquiredItems.size())
			{
				// Ŭ���� �������� ID ��������
				auto it = std::next(_acquiredItems.begin(), i);
				_clickedItemID = it->first;
			}
			return;
		}
		++i;
	}
}
