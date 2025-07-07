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
	// csv 파일로 저장한 Item 정보 가져옴
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

	InventoryBackgroundRender(hdc);

	// _acquiredItems에서 정보 꺼내와서 출력(인벤토리 안, 숫자 / 마우스 대면 - 인벤토리 안 플립북 변경, 사진, 설명)
	if (_acquiredItems.empty())	// 획득한 아이템이 없으면 안 그림
		return;

	// Item
	InventoryItemRender(hdc);

	// Photo & Explain
	if (_clickedItemID != 0)
	{
		ClickedItemPhotoRender(hdc);
		ClickedItemExplainRender(hdc);
	}
}

void Inventory::SaveAcquireItems()
{
	if (!_owner)
		return;

	// Player에 저장된 _acquiredItems 가져옴
	_acquiredItems = _owner->GetAquireItems();
}

void Inventory::InventoryBackgroundRender(HDC hdc)
{
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

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
}

void Inventory::InventoryItemRender(HDC hdc)
{
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	int32 i = 0;	// 위치 조정 Count

	for (auto it = _acquiredItems.begin(); it != _acquiredItems.end(); ++it, ++i)
	{
		int32 itemID = it->first;
		int32 itemCount = it->second;

		// 아이템의 정보 가져오기
		auto itemInfoIt = _itemInfo.find(itemID);
		if (itemInfoIt != _itemInfo.end())
			const ItemInfo* itemInfo = itemInfoIt->second;

		// 출력할 리소스 정하기
		Texture* texture = nullptr;

		switch (itemID)
		{
		case 300100:
			texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Heal"); break;
		case 310100:
			texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Key"); break;
		case 310200:
			texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Multipletap"); break;
		case 320100:
			texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Gem"); break;
		case 320001:
			texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Nametag"); break;
		case 320002:
			texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Sword"); break;
		case 320003:
			texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Medal1gold"); break;
		case 320004:
			texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Medal2gold"); break;
		case 320005:
			texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Photo1"); break;
		case 320006:
			texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Medal3silver"); break;
		case 320007:
			texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Photo2"); break;
		case 320008:
			texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Photo3"); break;
		case 320009:
			texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Box"); break;
		case 320010:
			texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Photo4"); break;
		case 320011:
			texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Poster"); break;
		}

		int32 boxX = ITEM_STARTX + (i % 5) * ITEM_SIZEX;
		int32 boxY = ITEM_STARTY + (i / 5) * ITEM_SIZEY;

		// 선택된 아이템이 있으면 표시 - 텍스처의 시작점 지정
		int32 textureStartY = 0;

		if (_clickedItemID == itemID)
		{
			textureStartY = ITEM_SIZEX;
		}
		else
		{
			textureStartY = 0;
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

		// 아이템 개수 출력
		{
			std::wstring itemCountStr = std::to_wstring(itemCount);

			// 출력할 위치
			RECT rect = { (boxX + 108) * winSizeAdjustmemt.x, (boxY - 10) *winSizeAdjustmemt.y, (boxX + ITEM_SIZEX) * winSizeAdjustmemt.x, (boxY + 30) * winSizeAdjustmemt.y };

			// 폰트 생성
			HFONT hfont = Utils::MakeFont(30.f * winSizeAdjustmemt.y, L"DungGeunMo");

			// 폰트 선택
			HFONT oldFont = (HFONT)::SelectObject(hdc, hfont);

			// 텍스트 색깔 설정
			::SetTextColor(hdc, RGB(0, 0, 0));

			// 텍스트 배경 투명화
			::SetBkMode(hdc, TRANSPARENT);

			Utils::DrawString(hdc, itemCountStr, rect);

			::SetTextColor(hdc, RGB(0, 0, 0));
			::SelectObject(hdc, oldFont);
			::DeleteObject(hfont);
		}
	}
}

void Inventory::ClickedItemPhotoRender(HDC hdc)
{
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	Texture* texture = nullptr;

	switch (_clickedItemID)
	{
	case 300100:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Heal"); break;
	case 310100:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Key"); break;
	case 310200:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Multipletap"); break;
	case 320100:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Gem"); break;
	case 320001:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Nametag"); break;
	case 320002:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Sword"); break;
	case 320003:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Medal1gold"); break;
	case 320004:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Medal2gold"); break;
	case 320005:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Photo1"); break;
	case 320006:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Medal3silver"); break;
	case 320007:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Photo2"); break;
	case 320008:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Photo3"); break;
	case 320009:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Box"); break;
	case 320010:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Photo4"); break;
	case 320011:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"inventory_Poster"); break;
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

void Inventory::ClickedItemExplainRender(HDC hdc)
{
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	// 출력할 설명
	std::wstring explain;
	auto it = _itemInfo.find(_clickedItemID);
	if (it != _itemInfo.end())
		explain = it->second->explain;

	// 출력할 위치
	RECT rect = { 81 * winSizeAdjustmemt.x, 488 * winSizeAdjustmemt.y, 507 * winSizeAdjustmemt.x, 677 * winSizeAdjustmemt.y };

	// 폰트 생성
	HFONT hfont = Utils::MakeFont(17.f * winSizeAdjustmemt.y, L"DungGeunMo");

	// 폰트 선택
	HFONT oldFont = (HFONT)::SelectObject(hdc, hfont);

	// 텍스트 색깔 설정
	::SetTextColor(hdc, RGB(0, 0, 0));

	// 텍스트 배경 투명화
	::SetBkMode(hdc, TRANSPARENT);

	Utils::DrawString(hdc, explain, rect);

	::SelectObject(hdc, oldFont);
	::DeleteObject(hfont);
}

void Inventory::MouseClick(POINT mousePos)
{
	int32 i = 0;

	// 보정 변수 가져오기
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	for (const RECT& box : _itemBoxes)
	{
		if (mousePos.x >= box.left * winSizeAdjustmemt.x && mousePos.x <= box.right * winSizeAdjustmemt.x &&
			mousePos.y >= box.top * winSizeAdjustmemt.y && mousePos.y <= box.bottom * winSizeAdjustmemt.y)
		{
			if (i < _acquiredItems.size())
			{
				// 클릭된 아이템의 ID 가져오기
				auto it = std::next(_acquiredItems.begin(), i);
				_clickedItemID = it->first;
			}
			return;
		}
		++i;
	}
}
