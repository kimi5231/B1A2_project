#include "pch.h"
#include "Inventory.h"
#include "ValueManager.h";
#include "ResourceManager.h"
#include "Texture.h"
#include "Player.h"
#include "Item.h"

Inventory::Inventory()
{
	// Flipbook
	_flipbookKey = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_keyInInventory");
	_flipbookPencil = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_pencilInInventory");
	_flipbookMatch = GET_SINGLE(ResourceManager)->GetFlipbook(L"1003_matchInMap");
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

	// _acquiredItems���� ���� �����ͼ� ���(�κ��丮 ��, ���� / ���콺 ��� - �κ��丮 �� �ø��� ����, ����, ����)
		
}

void Inventory::SaveAcquireItems()
{
	if (!_owner)
		return;

	// Player�� ����� _acquiredItems ������
	_acquiredItems = _owner->GetAquireItems();
}

