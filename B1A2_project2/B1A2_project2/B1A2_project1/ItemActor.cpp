#include "pch.h"
#include "ItemActor.h"
#include "ResourceManager.h"
#include "ValueManager.h"
#include "Flipbook.h"
#include "FlipbookActor.h"
#include "SceneManager.h"
#include "Texture.h"
#include "BoxCollider.h"
#include "Item.h"
#include "InputManager.h"
#include "CollisionManager.h"

ItemActor::ItemActor(int32 itemID, const std::unordered_map<int32, ItemInfo*>& items)
{
	SetFKeyState(FKeyState::Show);

	// items에서 item 정보 찾기
	auto it = items.find(itemID);
	if (it != items.end())
	{
		_itemInfo = it->second;
		//_itemInfo->ID = itemID;

		// 플립북 설정
		switch (itemID)
		{
		case 300100:
			_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_map_Heal");
			SetFKeyState(FKeyState::Hidden);
			break;
		case 310100:
			_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_map_Key");
			break;
		case 310200:
			_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_map_Multipletap");
			break;
		case 320100:
			_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_map_Gem");
			break;
		case 320001:
			_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_map_Nametag");
			break;
		case 320002:
			_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_map_Sword");
			break;
		case 320003:
			_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_map_Medal1gold");
			break;
		case 320004:
			_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_map_Medal2gold");
			break;
		case 320005:
			_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_map_Photo1");
			break;
		case 320006:
			_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_map_Medal3silver");
			break;
		case 320007:
			_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_map_Photo2");
			break;
		case 320008:
			_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_map_Photo3");
			break;
		case 320009:
			_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_map_Box");
			break;
		case 320010:
			_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_map_Photo4");
			break;
		case 320011:
			_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_map_Poster");
			break;
		}
	}

	// F_key
	_flipbookFKey = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Fkey");

	// Collider
	{
		BoxCollider* collider = new BoxCollider();
		collider->ResetCollisionFlag();

		collider->SetCollisionLayer(CLT_ITEM);
		collider->AddCollisionFlagLayer(CLT_PLAYER);

		if (itemID == 300100)
			collider->SetSize({ 10, 55 });
		else
			collider->SetSize({ 120, 55 });

		GET_SINGLE(CollisionManager)->AddCollider(collider);
		AddComponent(collider);
	}

	SetFlipbook(_flipbookItemInMap);
	SetFKeyState(FKeyState::Hidden);
}

ItemActor::~ItemActor()
{
}

void ItemActor::BeginPlay()
{
	Super::BeginPlay();
}

void ItemActor::Tick()
{
	Super::Tick();
}

void ItemActor::Render(HDC hdc)
{
	// Item 그리기
	if (_itemState == ItemState::Show)
		Super::Render(hdc);

	// F key
	if (_FkeyState == FKeyState::Hidden)
		return;

	// 보정 변수 가져오기
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();
	Vec2 cameraPosAdjustmemt = GET_SINGLE(ValueManager)->GetCameraPosAdjustment();

	// F key 위치 지정
	Vec2 ItemPos = _pos;
	ItemPos.y -= 50;

	Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"F_key");
	::TransparentBlt(hdc,
		((int32)ItemPos.x - texture->GetSize().x / 2) * winSizeAdjustmemt.x - cameraPosAdjustmemt.x,
		((int32)ItemPos.y - texture->GetSize().y / 2) * winSizeAdjustmemt.y - cameraPosAdjustmemt.y,
		texture->GetSize().x * winSizeAdjustmemt.x,
		texture->GetSize().y * winSizeAdjustmemt.y,
		texture->GetDC(),
		0,
		0,
		texture->GetSize().x,
		texture->GetSize().y,
		texture->GetTransparent());
}

Collider* ItemActor::GetCollider() const
{
	for (auto* component : _components)
	{
		if (auto* collider = dynamic_cast<Collider*>(component))
			return collider;
	}
	return nullptr;
}
