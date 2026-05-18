#include "pch.h"
#include "Player.h"
#include "Cutlass.h"
#include "Inventory.h"
#include "Room.h"

Player::Player()
{
	_maxHP = 100;
	_hp = _maxHP;
	_pos = { 0, 0, 25 };
	_currentCubeID = 0;
	_rotation = {0, 0, 0};
	_type = ObjectType::Player;
	_currentEmotion = Emotion::Neutral;
	_box.SetBounds(_pos, {60, 30, 180}, Front);
	_inventory = new Inventory();
}

Player::~Player()
{
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
			}
		}
	}
}