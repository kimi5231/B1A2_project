#include "pch.h"
#include "Player.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "ValueManager.h"
#include "DialogueManager.h"
#include "CameraComponent.h"
#include "DialogueComponent.h"
#include "Dialogue.h"
#include "BoxCollider.h"
#include "ItemActor.h"
#include "Item.h"
#include "DevScene.h"
#include "ZipLine.h"
#include "SceneManager.h"
#include "Flipbook.h"

Player::Player()
{
	// PlayerStat
	PlayerStat* playerStat = new PlayerStat();
	playerStat = GET_SINGLE(ResourceManager)->LoadPlayerStat(L"DataBase\\playerStat.csv");
	_playerStat = playerStat;
	CalPixelPerSecond();
	
	// Flipbook Sprite
	_flipbookPlayerIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerIdleRight");
	_flipbookPlayerIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerIdleLeft");
	_flipbookPlayerMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerMoveRight");
	_flipbookPlayerMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerMoveLeft");
	_flipbookPlayerJump[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerJumpRight");
	_flipbookPlayerJump[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerJumpLeft");
	_flipbookPlayerDuckDown[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerDuckDownRight");
	_flipbookPlayerDuckDown[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerDuckDownLeft");
	_flipbookPlayerDuckDownMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerDuckDownMoveRight");
	_flipbookPlayerDuckDownMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerDuckDownMoveLeft");
	_flipbookPlayerHang[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerHangRight");
	_flipbookPlayerHang[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerHangLeft");
	_flipbookPlayerRelease[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerReleaseRight");
	_flipbookPlayerRelease[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerReleaseLeft");
	_flipbookPlayerSlash[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerSlashRight");
	_flipbookPlayerSlash[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerSlashLeft");

	// Camera Component
	CameraComponent* camera = new CameraComponent();
	AddComponent(camera);

	// Dialogue Component
	DialogueComponent* dialogueComponent = new DialogueComponent();
	AddComponent(dialogueComponent);

	// Collider
	{
		{
			BoxCollider* collider = new BoxCollider();
			// ���� �� �ϸ� ��� �浹��
			collider->ResetCollisionFlag();

			// �� �ڽ��� ����
			collider->SetCollisionLayer(CLT_PLAYER);

			// �浹�ϰ� ���� ��ü ����
			collider->AddCollisionFlagLayer(CLT_MONSTER_ATTACK);
			collider->AddCollisionFlagLayer(CLT_PROJECTILE);
			collider->AddCollisionFlagLayer(CLT_ITEM);
			collider->AddCollisionFlagLayer(CLT_GROUND);
			collider->AddCollisionFlagLayer(CLT_WALL);
			collider->AddCollisionFlagLayer(CLT_SAVE_POINT);
			collider->AddCollisionFlagLayer(CLT_DETECT);
			collider->AddCollisionFlagLayer(CLT_STRUCTURE);
			collider->AddCollisionFlagLayer(CLT_STRUCTURE_DETECT);

			collider->SetSize({ 23, 75 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
			SetPlayerCollider(collider);
		}

		// Monster Detect
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_DETECT);

			collider->AddCollisionFlagLayer(CLT_MONSTER);

			collider->SetSize({ 80, 80 });

			_detectCollider = collider;

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}
}

Player::~Player()
{
}

void Player::BeginPlay()
{	
	Super::BeginPlay();
}

void Player::Tick()
{
	Super::Tick();

	// ��ȭ �߿��� ������ �� ������ ���� ��ȭ ��ŵ
	// �� �ڵ��� ��ġ�� ���� ������ �� ����
	if (GET_SINGLE(DialogueManager)->GetIsDialouge())
		return;
	/*if (GetDialogue()->GetState() == DialogueState::Running || GetDialogue()->GetState() == DialogueState::Wait)
		return;*/

		// F key�� Ȱ��ȭ�Ǹ� ȹ���� �� ����
		// ȹ�� �� F key�� Item�� ȭ�鿡�� ����
	if (_collideItem)
	{
		if (_collideItem->GetFKeyState() == FKeyState::Show)
		{
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::F))
			{
				_acquiredItems[_collideItem->GetItemID()]++;

				Collider* collider = _collideItem->GetCollider();
				if (collider)
				{
					collider->SetCollisionLayer(CLT_NONE);
				}

				// Scene�� ������ ȹ�� ȿ�� �׸���
				// ���� GameScene�� ������ ����
				DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
				scene->SetItemAcquireState(_collideItem);

				// ������ �����
				_collideItem->SetFKeyState(FKeyState::Hidden);
				_collideItem->SetItemState(ItemState::Hidden);
			}
		}
	}

	if (_state != ObjectState::CloseAttack && _state != ObjectState::LongAttack)
	{
		if (_attackCollider)
		{
			GET_SINGLE(CollisionManager)->RemoveCollider(_attackCollider);
			RemoveComponent(_attackCollider);
			_attackCollider = nullptr;
		}
	}	

	TickGravity();

	// �÷��̾ ȭ�� ������ �Ѿ�� �ʵ���
	Vec2Int mapSize = GET_SINGLE(ValueManager)->GetMapSize();
	_pos.x = std::clamp(_pos.x, (float)(67 / 2), (float)mapSize.x);		// 67�� DevScene���� ������ Player collider ũ��
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Player::TickIdle()
{
	if (GetDialogue()->GetState() == DialogueState::Running || GetDialogue()->GetState() == DialogueState::Wait)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	static float sumTime = 0.0f;

	sumTime += deltaTime;

	_keyPressed = true;

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		SetDir(DIR_LEFT);
		SetState(ObjectState::Move);
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		SetDir(DIR_RIGHT);
		SetState(ObjectState::Move);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		// �̹� ���� ���̸� ����
		if (!_isGround && _isAir)
			return;

		SubtractHealthPoint(3);		// ü�¹� test

		_isGround = false;
		_isAir = true;

		SetState(ObjectState::Jump);

		_ySpeed = -_playerStat->jumpSpeed;
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		SetState(ObjectState::DuckDown);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		if (_isCloseAtk)
			SetState(ObjectState::CloseAttack);
		else
			SetState(ObjectState::LongAttack);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::RightMouse))
	{
		SetState(ObjectState::Skill);
	}
	else
	{
		_keyPressed = false;

		if (_state == ObjectState::Idle)
			UpdateAnimation();
	}
	
	//if (���� ����)
	//{
	//	SubtractHealthPoint(����hp);
	//	SetState(ObjectState::Hit);
	//}
}

void Player::TickMove()
{
	if (GetDialogue()->GetState() == DialogueState::Running || GetDialogue()->GetState() == DialogueState::Wait)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	static float sumTime = 0.0f;

	sumTime += deltaTime;

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		SetDir(DIR_LEFT);
		_pos.x -= _playerStat->runSpeed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		SetDir(DIR_RIGHT);
		_pos.x += _playerStat->runSpeed * deltaTime;
	}
	else
	{
		SetState(ObjectState::Idle); // �̵� Ű�� ���� �� Idle ���·� ����
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		// �̹� ���� ���̸� ����
		if (!_isGround && _isAir)
			return;

		_isGround = false;
		_isAir = true;

		SetState(ObjectState::Jump);

		_ySpeed = -_playerStat->jumpSpeed;
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		SetState(ObjectState::DuckDownMove);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))	// Normal Attack
	{
		if (_isCloseAtk)
			SetState(ObjectState::CloseAttack);
		else
			SetState(ObjectState::LongAttack);

	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::RightMouse))	// Skill
	{
		SetState(ObjectState::Skill);
	}

	//if (���� ����)
	//{
	//	SubtractHealthPoint(����hp);
	//	SetState(ObjectState::Hit);
	//}
}

void Player::TickDuckDown()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::A))
	{
		SetDir(DIR_LEFT);
		SetState(ObjectState::DuckDownMove);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::D))
	{
		SetDir(DIR_RIGHT);
		SetState(ObjectState::DuckDownMove);
	}
	else if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::S))	// ��ư�� ���� ��
	{
		SetState(ObjectState::Idle);
	}

	//if (���� ����)
	//{
	//	SubtractHealthPoint(����hp);
	//	SetState(ObjectState::Hit);
	//}

}

void Player::TickDuckDownMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		SetDir(DIR_LEFT);
		_pos.x -= _playerStat->runSpeed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		SetDir(DIR_RIGHT);
		_pos.x += _playerStat->runSpeed * deltaTime;
	}
	
	if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::A) || GET_SINGLE(InputManager)->GetButtonUp(KeyType::D))
	{
		SetState(ObjectState::DuckDown);
	}

	if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::S))
	{
		SetState(ObjectState::Move);
	}

	//if (���� ����)
	//{
	//	SubtractHealthPoint(����hp);
	//	SetState(ObjectState::Hit);
	//}

}

void Player::TickJump()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// �¿� �̵��� �����ϵ��� �߰�
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		SetDir(DIR_LEFT);
		_pos.x -= _playerStat->runSpeed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		SetDir(DIR_RIGHT);
		_pos.x += _playerStat->runSpeed * deltaTime;
	}

	if (_isGround && !_isAir)	// ���� ����� ��
	{
		if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
		{
			SetDir(DIR_LEFT);
			SetState(ObjectState::Move);
		}
		else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
		{
			SetDir(DIR_RIGHT);
			SetState(ObjectState::Move);
		}
		else
			SetState(ObjectState::Idle);
	}
	else
	{
		// ZipLine 
		if (_zipLine)
		{
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
			{
				// �ٶ󺸴� ���� ����
				_dir = DIR_RIGHT;

				SetState(ObjectState::Hang);
			}
		}
	}

	//if (���� ����)
	//{
	//	SubtractHealthPoint(����hp);
	//	SetState(ObjectState::Hit);
	//}

 }


void Player::TickCloseAttack()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (!_attackCollider)
	{
		BoxCollider* collider = new BoxCollider();
		collider->ResetCollisionFlag();
		collider->SetCollisionLayer(CLT_PLAYER_ATTACK);

		collider->AddCollisionFlagLayer(CLT_MONSTER);

		collider->SetSize({ 55, 55 });

		_attackCollider = collider;

		GET_SINGLE(CollisionManager)->AddCollider(collider);
		AddComponent(collider);
	}

	if (this->GetIdx() == 6)
	{
		SetState(ObjectState::Idle);
	}

	//if (���� ����)
	//{
	//	SubtractHealthPoint(����hp);
	//	SetState(ObjectState::Hit);
	//}
}

void Player::TickLongAttack()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	static float sumTime = 0.0f;

	sumTime += deltaTime;

	if (!_attackCollider)
	{
		BoxCollider* collider = new BoxCollider();
		collider->ResetCollisionFlag();
		collider->SetCollisionLayer(CLT_PLAYER_ATTACK);

		collider->AddCollisionFlagLayer(CLT_MONSTER);

		collider->SetSize({ 55, 55 });

		_attackCollider = collider;

		GET_SINGLE(CollisionManager)->AddCollider(collider);
		AddComponent(collider);
	}

	if (sumTime <= 1.0)
	{
		if (_dir == DIR_RIGHT)
		{
			_pos.x += 80 * deltaTime;
		}
		else 
			_pos.x -= 80 * deltaTime;
	}

	if (this->GetIdx() == 6)
	{
		sumTime = 0.0f;

		SetState(ObjectState::Idle);
	}

	//if (���� ����)
	//{
	//	SubtractHealthPoint(����hp);
	//	SetState(ObjectState::Hit);
	//}
}

void Player::TickSkill()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// �¿� �̵��� �����ϵ��� �߰�
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		SetDir(DIR_LEFT);
		_pos.x -= _playerStat->runSpeed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		SetDir(DIR_RIGHT);
		_pos.x += _playerStat->runSpeed * deltaTime;
	}

	//if (���� ����)
	//{
	//	SubtractHealthPoint(����hp);
	//	SetState(ObjectState::Hit);
	//}

	// ��ų �ڵ� �ۼ�
	// ...

	SetState(ObjectState::Idle);
}

void Player::TickHang()
{
	static bool isMoving = false;	// �̵� �ϴ���
	static float sumTime = 0.0f;

	if (!_zipLine)
		return;

	Vec2 beginPos = _zipLine->GetBeginPos();
	Vec2 endPos = _zipLine->GetEndPos();

	// �Ŵ޸��� ���� - ¤���� ���� ��ġ�� �̵�
	if (!isMoving)
	{
		_pos = _zipLine->GetBeginPos();

		_isGround = true;
		_isAir = false;

		sumTime += GET_SINGLE(TimeManager)->GetDeltaTime();

		if (sumTime >= 1.0f)	// 2�� ��� �� �̵� ����
		{
			isMoving = true;
			sumTime = 0.0f;
		}
	}
	// �̵� ����
	else
	{
		float speed = 300.0f;
		float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

		Vec2 direction = (endPos - beginPos).Normalize();
		_pos += direction * speed * deltaTime;

		// �̵� �� SpaceBar �Է� �� ����
		if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
		{
			isMoving = false;
			sumTime = 0.0f;

			_isGround = false;
			_isAir = true;

			SetState(ObjectState::Release);

			return;
		}

		// endPos�� �����ϸ� ����
		if ((_pos - endPos).Length() <= 5.0f) // ���� ���� ���
		{
			isMoving = false;
			sumTime = 0.0f;

			_isGround = false;
			_isAir = true;

			SetState(ObjectState::Release);
		}
	}
}

void Player::TickRelease()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	static float sumTime = 0.0f;

	sumTime += deltaTime;

	if (_dir == DIR_RIGHT)
		_pos.x += _playerStat->runSpeed * deltaTime;
	else
		_pos.x -= _playerStat->runSpeed * deltaTime;

	if (sumTime >= 0.3f)
	{
		sumTime = 0.f;
		SetState(ObjectState::Idle);
	}
}

void Player::TickHit()
{
	// knockback
	if (_dir == DIR_RIGHT)
		_pos.x -= _playerStat->knockBackDistance;
	else
		_pos.x += _playerStat->knockBackDistance;

	SetState(ObjectState::Idle);

}

void Player::TickDead()
{
	// ��ü ����
	// ���� GameScene�� ������ ����
	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	scene->RemoveActor(this);
}

void Player::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Idle:
		_playerCollider->SetSize({ 23, 85 });
		SetFlipbook(_flipbookPlayerIdle[_dir]);		
		break;
	case ObjectState::Move:
		_playerCollider->SetSize({67, 70 });
		SetFlipbook(_flipbookPlayerMove[_dir]);
		break;
	case ObjectState::DuckDown:
		_playerCollider->SetSize({35, 45});
		SetFlipbook(_flipbookPlayerDuckDown[_dir]);
		break;
	case ObjectState::DuckDownMove:
		_playerCollider->SetSize({ 34, 50 });
		SetFlipbook(_flipbookPlayerDuckDownMove[_dir]);
		break;
	case ObjectState::Jump:
		_playerCollider->SetSize({ 34, 55 });
		SetFlipbook(_flipbookPlayerJump[_dir]);
		break;
	case ObjectState::Hang:
		_playerCollider->SetSize({ 30, 80 });
		SetFlipbook(_flipbookPlayerHang[_dir]);
		break;
	case ObjectState::Release:
		_playerCollider->SetSize({ 34, 88 });
		SetFlipbook(_flipbookPlayerRelease[_dir]);
		break;
	case ObjectState::Skill:
		//playerCollider->SetSize({})
		//SetFlipbook(_flipbookPlayerSkill[_dir]);
		break;
	case ObjectState::CloseAttack:
		_playerCollider->SetSize({ 75, 90 });
		SetFlipbook(_flipbookPlayerSlash[_dir]);
		break;
	case ObjectState::LongAttack:
		_playerCollider->SetSize({ 75, 90 });
		SetFlipbook(_flipbookPlayerSlash[_dir]);		
		break;
	case ObjectState::Hit:
		_playerCollider->SetSize({ 41, 80 });
		SetFlipbook(_flipbookPlayerHit[_dir]);
	break;
	case ObjectState::Dead:
	//	SetFlipbook(_flipbookPlayerDead[_dir]);
	break;
	}

	// CheckCollisionAfterResize();	// Collider ũ�� ���� �� �浹 �˻��ϱ�
}

int32 Player::GetAttack()
{
	// damage ���� ����
	switch (_state)
	{
	case ObjectState::CloseAttack:
		return _playerStat->nAtkDamage;
		break;
	case ObjectState::LongAttack:
		return _playerStat->nAtkDamage;
		break;
	case ObjectState::Skill:
		return _playerStat->skillDamage;
		break;
	}

	return 50;
}

float Player::GetSpeed()
{
	switch (_state)
	{
	case ObjectState::Move:
		return _playerStat->runSpeed;
		break;
	case ObjectState::DuckDownMove:
		return _playerStat->crouchSpeed;
		break;
	}
}

void Player::OnDamaged(Creature* other)
{
	int32 damage = other->GetAttack();

	if (damage <= 0)
		return;

	// ü�� ���� �Լ� ȣ��
	SubtractHealthPoint(damage);

	// ü���� �� ������ ���
	if (_playerStat->commonStat.hp == 0)
	{
		SetState(ObjectState::Dead);
		return;
	}

	SetState(ObjectState::Hit);
}

void Player::AddHealthPoint(int hp)
{
	if (_playerStat->commonStat.hp >= 100)
		return;

	if (_playerStat->commonStat.hp += hp >= 100)
	{
		_playerStat->commonStat.hp = 100;
	}
	else
		_playerStat->commonStat.hp += hp;

	// �����ڿ��� �˸�
	_healthObserver(_playerStat->commonStat.hp);
}

void Player::SubtractHealthPoint(int hp)
{
	if (_playerStat->commonStat.hp <= 0)
		return;

	_playerStat->commonStat.hp -= hp;

	// �����ڿ��� �˸�
	_healthObserver(_playerStat->commonStat.hp);
}

void Player::CalPixelPerSecond()
{
	float PIXEL_PER_METER = (10.0 / 0.2);

	// run
	{
		float RUN_SPEED_KMPH = _playerStat->runSpeed;
		float RUN_SPEED_MPM = (RUN_SPEED_KMPH * 1000.0 / 60.0);
		float RUN_SPEED_MPS = (RUN_SPEED_MPM / 60.0);
		float RUN_SPEED_PPS = (RUN_SPEED_MPS * PIXEL_PER_METER);

		_playerStat->runSpeed = RUN_SPEED_PPS;
	}

	// crouch
	{
		float CROUCH_SPEED_KMPH = _playerStat->crouchSpeed;
		float CROUCH_SPEED_MPM = (CROUCH_SPEED_KMPH * 1000.0 / 60.0);
		float CROUCH_SPEED_MPS = (CROUCH_SPEED_MPM / 60.0);
		float CROUCH_SPEED_PPS = (CROUCH_SPEED_MPS * PIXEL_PER_METER);

		_playerStat->crouchSpeed = CROUCH_SPEED_PPS;
	}

	// jump
	{
		float JUMP_SPEED_KMPH = _playerStat->jumpSpeed;
		float JUMP_SPEED_MPM = (JUMP_SPEED_KMPH * 1000.0 / 60.0);
		float JUMP_SPEED_MPS = (JUMP_SPEED_MPM / 60.0);
		float JUMP_SPEED_PPS = (JUMP_SPEED_MPS * PIXEL_PER_METER);

		_playerStat->jumpSpeed = JUMP_SPEED_PPS;
	}

}

void Player::TickGravity()
{
	// ���� ��������� �߷� ���� X
	if (_isGround)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	if (deltaTime > 0.1f)
		return;

	// v = at
	// s = vt

	_ySpeed += _gravity * deltaTime;
	_pos.y += _ySpeed * deltaTime;
}

void Player::RemoveItem(int32 id, int32 count)
{
	if (_acquiredItems.find(id) != _acquiredItems.end() && _acquiredItems[id] >= count)
	{
		_acquiredItems[id] -= count;
		if (_acquiredItems[id] == 0)	// ������ ������ 0�̸� ����
			_acquiredItems.erase(id);	
	}
}

void Player::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	// Item�� �浹�ϸ� F key Ȱ��ȭ(�о�� X)
	if (b2->GetCollisionLayer() == CLT_ITEM)
	{
		ItemActor* item = reinterpret_cast<ItemActor*>(b2->GetOwner());
		
		if (item->GetItemID() != 300100)
			item->SetFKeyState(FKeyState::Show);
		else
		{
			AddHealthPoint(20);	// ���� ���� �ʿ�
			item->SetItemState(ItemState::Hidden);
		}

		_collideItem = item;

		return;
	}

	// Save Point�� �浹�ϸ� �����ϱ�(�о�� X)
	if (b2->GetCollisionLayer() == CLT_SAVE_POINT)
	{
		_devScene->SaveCurData();

		return;
	}

	// ZipLine
	if (b2->GetCollisionLayer() == CLT_STRUCTURE_DETECT)
	{
		ZipLine* zipLine = dynamic_cast<ZipLine*>(b2->GetOwner()); 
		
		if (zipLine)
		{
			if (zipLine->GetZipLineType() == ZipLineType::ZipLine)
			{
				_zipLine = zipLine;
			}
			else if (zipLine->GetZipLineType() == ZipLineType::ZipLineWithButton)
			{
				ZipLineButtonAndDisplay* BD = zipLine->GetZipLineButtonAndDisplay();
				if (BD->GetState() == ObjectState::On)
				{
					_zipLine = zipLine;
				}
			}
		}

		 return;
	}

	// Monster Atk - ���Ͱ� ��Ÿ� �� ������, �ٰŸ� ����
	if (b1->GetCollisionLayer() == CLT_DETECT && b2->GetCollisionLayer() == CLT_MONSTER)
	{
		_isCloseAtk = true;
		return;
	}

	// �� �浹�ϸ� �о��
	if (b2->GetCollisionLayer() == CLT_WALL)
	{
		AdjustCollisionPos(b1, b2);
		return;
	}

	// ���� �浹 - �����¿� Ȯ��
	if (b2->GetCollisionLayer() == CLT_GROUND)
	{
		_groundCollisionCount++;
		_isGround = true;
		_isAir = false;
	}
}

void Player::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayer() == CLT_ITEM)
	{
		ItemActor* Item = reinterpret_cast<ItemActor*>(b2->GetOwner());
		Item->SetFKeyState(FKeyState::Hidden);

		_collideItem = nullptr;

		return;
	}

	// ZipLine
	if (b2->GetCollisionLayer() == CLT_STRUCTURE_DETECT)
	{
		_zipLine = nullptr;

		return;
	}

	// ���� �Ÿ��� ���� �ٰŸ� or ���Ÿ� ����
	if (b1->GetCollisionLayer() == CLT_DETECT && b2->GetCollisionLayer() == CLT_MONSTER)
	{
		_isCloseAtk = false;

		return;
	}

	if (b1->GetCollisionLayer() == CLT_PLAYER && b2->GetCollisionLayer() == CLT_MONSTER_ATTACK)
	{
		Creature* otherOwner = dynamic_cast<Creature*>(b2->GetOwner());
		OnDamaged(otherOwner);

		return;
	}

	if (b2->GetCollisionLayer() == CLT_GROUND)
	{
		_groundCollisionCount--;

		if (_groundCollisionCount <= 0)		// Ÿ�ϰ� ������ �������� �� �߷� �����ϱ�
		{
			_isGround = false;
			_isAir = true;
			_groundCollisionCount = 0;
		}
	}
}

void Player::AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2)
{
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();

	Vec2 pos = GetPos();
	RECT intersect = {};	// �浹�� ����

	if (::IntersectRect(&intersect, &r1, &r2))
	{
		int32 w = intersect.right - intersect.left;
		int32 h = intersect.bottom - intersect.top;
		
		if (w > h)
		{
			if (intersect.top == r2.top)
			{
				// ���� �÷� ������
				pos.y -= h;
			}
			else
			{
				// �Ʒ��� ���� ������
				pos.x += h;
			}
		}
		else
		{
			if (intersect.left == r2.left)
			{
				pos.x -= w;
			}
			else
			{
				pos.x += w;
			}
		}
	}
	
	SetPos(pos);
}