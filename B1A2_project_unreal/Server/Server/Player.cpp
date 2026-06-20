#include "pch.h"
#include "Player.h"
#include "Cutlass.h"
#include "Inventory.h"
#include "Room.h"
#include "Global.h"

Player::Player()
{
	const PlayerStat& stat = g_dataManager->GetPlayerStat();

	// 최초 생성 시에만 초기화하면 되는 것들
	_maxHP = stat.hp;
	_lookRange = 1500;
	_lookHeight = 200;
	_lookAngle = 90.f;
	_isInvincible = false;
	_size = stat.size;
	_type = ObjectType::Player;
	_box.SetBounds({ 0, 0, 25 }, _size, Front);
	_inventory = new Inventory();
}

Player::~Player()
{
	delete _inventory;
}

void Player::Init()
{
	// 재사용시 초기화해야 하는 것들
	_hp = _maxHP;
	_fearCount = 0;
	_isCanMove = true;

	SetPos({ 0, 0, 25 });
	SetRotation({ 0, 0, 0 });

	_currentEmotion = Emotion::Neutral;
	_objectPoolState = ObjectPoolState::InWorld;

	_inventory->Init();
}

void Player::Update()
{

}

bool Player::AddItemToInventory(bool isTool, int id)
{
	return _inventory->AddItem(isTool, id);
}

bool Player::RemoveItemFromInventory(bool isTool, int id)
{
	return _inventory->RemoveItem(isTool, id);
}

bool Player::ExistItem(bool isTool, int id)
{
	return _inventory->ExistItem(isTool, id);
}

void Player::Attack(Room* room)
{
	Tool* currentTool = dynamic_cast<Tool*>(room->GetGameObject(ObjectType::Item, _currentTool));

	if (currentTool->GetItemType() == ItemType::CUTLASS)
	{
		Cutlass* cutlass = dynamic_cast<Cutlass*>(currentTool);
		const std::array<Monster*, MAX_MONSTER>& monsters = room->GetMonsters();
		for (auto& monster : monsters)
		{
			if (monster->GetObjectPoolState() == ObjectPoolState::Reusable)
				continue;

			// 공격 범위 내에 있는지 확인
			if (CheckInclude(monster->GetPos(), cutlass->GetRange(), cutlass->GetAngle(), cutlass->GetHeight()))
			{
				// 공격 범위 내에 있다면 데미지 주기
				monster->TackDamage(cutlass->GetDamage());
				std::cout << "Monster " << monster->GetID() << " HP: " << monster->GetHP() << "\n";
			
				// 맞은 몬스터는 플레이어를 타겟으로 지정
				monster->SetTarget(this);
			}
		}
	}
}

void Player::Respawn()
{
	_hp = _maxHP;
	_fearCount = 0;
	_isCanMove = true;

	SetPos({ 0, 0, 25 });
	SetRotation({ 0, 0, 0 });
	SetState(ObjectState::IDLE, true);

	g_network->SendUpdateHpPacket(_id, _hp, _client);
}