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
#include "LockedDoorAndKey.h"
#include "BreakingWall.h"
#include "DestructibleObject.h"
#include "Window.h"
#include "FootHold.h"
#include "Blanket.h"
#include "Projectile.h"
#include "Crystal.h"

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
	_flipbookPlayerHit[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerHitRight");
	_flipbookPlayerHit[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerHitLeft");
	_flipbookPlayerSkillReady[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerSkillReadyRight");
	_flipbookPlayerSkillReady[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerSkillReadyLeft");	
	_flipbookPlayerSkillWaiting[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerSkillWaitingRight");
	_flipbookPlayerSkillWaiting[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerSkillWaitingLeft");
	_flipbookPlayerSkillEnd[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerSkillEndRight");
	_flipbookPlayerSkillEnd[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerSkillEndLeft");

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

				// ��� ���� ������ ���� ȹ��� �� �������� ����
				if (_collideItem->GetID() == 300100)
					_isKeyAcquire = true;

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
	if (_state != ObjectState::SkillWaiting && _state != ObjectState::SkillEnd)
	{
		if (_skillCollider)
		{
			GET_SINGLE(CollisionManager)->RemoveCollider(_skillCollider);
			RemoveComponent(_skillCollider);
			_skillCollider = nullptr;
		}

		// Detect Collider ����
		if (!_detectCollider)
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
	if (_state == ObjectState::SkillWaiting || _state == ObjectState::SkillEnd)
	{
		if (_detectCollider)
		{
			GET_SINGLE(CollisionManager)->RemoveCollider(_detectCollider);
			RemoveComponent(_detectCollider);
			_detectCollider = nullptr;
		}
	}

	// Window
	if (_window && _isInWindow)
	{
		if (_window->GetState() == ObjectState::On)
		{
			if (!_damagedByWindow)
			{
				// ü�� ���� �Լ� ȣ��
				SubtractHealthPoint(20);

				// ü���� �� ������ ���
				if (_playerStat->commonStat.hp == 0)
				{
					SetState(ObjectState::Dead);
					return;
				}

				_damagedByWindow = true;
			}
		}
	}
	else
	{
		_damagedByWindow = false;
	}

	// FootHoldAndZipLineButton
	if (_footHoldAndZipLineButton)
	{
		switch (_footHoldAndZipLineButton->GetState())
		{
		case ObjectState::Off:
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_1))
				_footHoldAndZipLineButton->SetState(ObjectState::On);
			break;
		case ObjectState::On:
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_2))
				_footHoldAndZipLineButton->SetState(ObjectState::On2);
			break;
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
		AddSkillPoint(3);

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
		if (GetSkillPoint() >= 3)
		{
			SubtractSkillPoint(3);

			_skillTimer = 0.f;

			_leftInputCount = 0;
			_rightInputCount = 0;

			SetState(ObjectState::SkillReady);
		}
	}
	else
	{
		_keyPressed = false;

		if (_state == ObjectState::Idle)
			UpdateAnimation();
	}
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
		SetState(ObjectState::SkillReady);
	}
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

	if (sumTime <= 0.7f)
	{
		if (_dir == DIR_RIGHT)
		{
			_pos.x += 114 * deltaTime;
		}
		else 
			_pos.x -= 114 * deltaTime;
	}

	if (this->GetIdx() == 6)
	{
		sumTime = 0.0f;

		SetState(ObjectState::Idle);
	}
}

void Player::TickSkillReady()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_skillTimer += deltaTime;

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::A) && _leftInputCount < 5)
	{
		_leftInputCount++;
	}
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::D) && _rightInputCount < 5)
	{
		_rightInputCount++;
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::RightMouse))
	{
		if (_leftInputCount > 0 || _rightInputCount > 0)
		{
			_skillTimer = 0.f;

			if (_leftInputCount == _rightInputCount)
				SetState(ObjectState::Idle);
			else
			{
				if (_leftInputCount < _rightInputCount)
					SetDir(DIR_RIGHT);
				else
					SetDir(DIR_LEFT);

				SetState(ObjectState::SkillWaiting);
			}
		}
	}
	if (_skillTimer >= 2.0f)
	{
		_skillTimer = 0.f;

		if (_leftInputCount > 0 || _rightInputCount > 0)
		{
			if (_leftInputCount == _rightInputCount)
				SetState(ObjectState::Idle);
			else
			{
				if (_leftInputCount < _rightInputCount)
					SetDir(DIR_RIGHT);
				else
					SetDir(DIR_LEFT);

				SetState(ObjectState::SkillWaiting);
			}
		}
		else // A, D ���Է�
		{
			SetState(ObjectState::Idle);
		}
	}	
}

void Player::TickSkillWaiting()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	static float sumTime = 0.f;
	sumTime += deltaTime;

	int32 distance = std::abs(_rightInputCount - _leftInputCount) * 80;

	if (!_skillCollider)
	{
		BoxCollider* collider = new BoxCollider();
		collider->ResetCollisionFlag();
		collider->SetCollisionLayer(CLT_PLAYER_SKILL);

		collider->AddCollisionFlagLayer(CLT_MONSTER);

		collider->SetSize({ 140, 85 });

		GET_SINGLE(CollisionManager)->AddCollider(collider);
		AddComponent(collider);
		
		_skillCollider = collider;
	}

	if (_dir == DIR_RIGHT)
		_pos.x += (distance / 0.7) * deltaTime;		// �� = �� / ��
	else
		_pos.x -= (distance / 0.7) * deltaTime;

	if (sumTime > 0.7f)
	{
		sumTime = 0.f;
		SetState(ObjectState::SkillEnd);
	}
}

void Player::TickSkillEnd()
{
	if (GetIdx() == _flipbookPlayerSkillEnd[_dir]->GetFlipbookEndNum())
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

	if (_zipLine->GetMidPos().x != 0 && _zipLine->GetMidPos().y != 0)	// �߰� ž��
		beginPos = _zipLine->GetMidPos();


	// �Ŵ޸��� ���� - ¤���� ���� ��ġ�� �̵�
	if (!isMoving)
	{
		_pos = beginPos;

		_isGround = true;
		_isAir = false;

		sumTime += GET_SINGLE(TimeManager)->GetDeltaTime();

		if (sumTime >= 1.0f)	// 1�� ��� �� �̵� ����
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
		//_zipLine->GetPlayerDetectCollider()->SetPos({ _pos });

		// �̵� �� SpaceBar �Է� �� ����
		if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
		{
			isMoving = false;

			sumTime = 0.0f;

			_isGround = false;
			_isAir = true;

			_zipLine->SetMidPos(_pos);

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

			_zipLine->SetMidPos({ 0, 0 });	// �߰� ���� X

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
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	static float sumTime = 0.f;
	sumTime += deltaTime;

	// knockback
	if (_dir == DIR_RIGHT)
		_pos.x -= (_playerStat->knockBackDistance * 2) * deltaTime;		// �� = �� / ��
	else
		_pos.x += (_playerStat->knockBackDistance * 2) * deltaTime;

	if (sumTime >= 0.5f)
	{
		sumTime = 0.f;
		SetState(ObjectState::Idle);
	}
}

void Player::TickDead()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	static float sumTime = 0.f;
	sumTime += deltaTime;

	if (sumTime >= 2.f)
	{
		sumTime = 0.f;

		// �ʱ�ȭ - ü��, ��ġ?
		SetHealthPoint(100);
		SetState(ObjectState::Idle);
	}
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
	case ObjectState::SkillReady:
		_playerCollider->SetSize({140, 85});
		SetFlipbook(_flipbookPlayerSkillReady[_dir]);
		break;
	case ObjectState::SkillWaiting:
		_playerCollider->SetSize({ 140, 85 });
		SetFlipbook(_flipbookPlayerSkillWaiting[_dir]);
		break;
	case ObjectState::SkillEnd:
		_playerCollider->SetSize({ 140, 85 });
		SetFlipbook(_flipbookPlayerSkillEnd[_dir]);
		break;
	case ObjectState::CloseAttack:
		//_playerCollider->SetSize({ 75, 90 });
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
}

int32 Player::GetAttack()
{
	// damage ���� ����
	switch (_state)
	{
	case ObjectState::CloseAttack:
		if (GetSkillPoint() >= 5)
		{
			SubtractSkillPoint(3);
			return _playerStat->nAtkDamage * _playerStat->strongAtkMultiplier;
		}
		else
		{
			return _playerStat->nAtkDamage;
		}
		break;
	case ObjectState::LongAttack:
		if (GetSkillPoint() >= 5)
		{
			SubtractSkillPoint(3);
			return _playerStat->nAtkDamage * _playerStat->strongAtkMultiplier;
		}
		else
		{
			return _playerStat->nAtkDamage;
		}
		break;
	case ObjectState::SkillWaiting:
	case ObjectState::SkillEnd:
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

void Player::OnDamagedByProjectile(Projectile* projectile)
{
	int damage = projectile->GetAttack();

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

void Player::SetHealthPoint(int hp)
{
	_playerStat->commonStat.hp = 100;

	_healthObserver(_playerStat->commonStat.hp);
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

	// Structure Detect
	if (b2->GetCollisionLayer() == CLT_STRUCTURE_DETECT)
	{
		Structure* structure = dynamic_cast<Structure*>(b2->GetOwner());
		if (!structure)
			return;

		// ZipLine
		{
			ZipLine* zipLine = dynamic_cast<ZipLine*>(structure);

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
				return;
			}
		}

		// LockedDoorAndKey - �÷��̾ ���踦 ȹ���� ���¶�� �� ����
		{
			LockedDoorAndKey* lockedDoorAndKey = dynamic_cast<LockedDoorAndKey*>(structure);

			if (lockedDoorAndKey)
			{
				if (_isKeyAcquire)
				{
					lockedDoorAndKey->_isKeyAcquired = true;
					return;
				}
			}
		}
	}

	// Structure
	if (b2->GetCollisionLayer() == CLT_STRUCTURE)
	{
		Structure* structure = dynamic_cast<Structure*>(b2->GetOwner());
		if (!structure)
			return;

		// LcokedDoorAndKey
		{
			LockedDoorAndKey* lockedDoorAndKey = dynamic_cast<LockedDoorAndKey*>(structure);

			if (lockedDoorAndKey)
			{
				if (!lockedDoorAndKey->_isKeyAcquired)
				{
					AdjustCollisionPos(b1, b2);
					return;
				}
				return;
			}
		}

		// BreakingWall
		{
			BreakingWall* breakingWall = dynamic_cast<BreakingWall*>(structure);

			if (breakingWall)
			{
				_isCloseAtk = true;
				AdjustCollisionPos(b1, b2);
				return;
			}
		}

		// DestructibleObject
		{
			DestructibleObject* destructibleObject = dynamic_cast<DestructibleObject*>(structure);

			if (destructibleObject)
			{
				_isCloseAtk = true;
				AdjustCollisionPos(b1, b2);
			}
		}

		// Window
		{
			Window* window = dynamic_cast<Window*>(structure);

			if (window)
			{
				_isInWindow = true;
				_window = window;
				return;
			}
		}

		// FootHoldAndZipLineButton
		{
			FootHoldAndZipLineButton* button = dynamic_cast<FootHoldAndZipLineButton*>(structure);

			if (button)
			{
				_footHoldAndZipLineButton = button;
				return;
			}
		}

		// Crystal
		{
			Crystal* crystal = dynamic_cast<Crystal*>(structure);

			if (crystal)
			{
				AdjustCollisionPos(b1, b2);
				return;
			}
		}
	}

	// Monster Atk - ���Ͱ� ��Ÿ� �� ������, �ٰŸ� ����
	if (b1->GetCollisionLayer() == CLT_DETECT && b2->GetCollisionLayer() == CLT_MONSTER)
	{
		_isCloseAtk = true;
		return;
	}

	// Projectile
	if (b2->GetCollisionLayer() == CLT_PROJECTILE)
	{
		Projectile* projectile = dynamic_cast<Projectile*>(b2->GetOwner());
		if (!projectile)
			return;

		// Blanket
		{
			Blanket* blanket = dynamic_cast<Blanket*>(projectile);
			if (blanket)
			{
				Projectile* projectile = dynamic_cast<Projectile*>(b2->GetOwner());
				OnDamagedByProjectile(projectile);

				return;
			}
		}
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

	// Structure
	if (b2->GetCollisionLayer() == CLT_STRUCTURE)
	{
		Structure* structure = dynamic_cast<Structure*>(b2->GetOwner());
	
		// Window
		{
			Window* window = dynamic_cast<Window*>(structure);

			if (window)
			{
				_isInWindow = false;
				_window = nullptr;

				return;
			}
		}

		// FootHoldAndZipLineButton
		{
			FootHoldAndZipLineButton* button = dynamic_cast<FootHoldAndZipLineButton*>(structure);
			if (button)
			{
				_footHoldAndZipLineButton = nullptr;

				return;
			}
		}
	}

	// ���� �Ÿ��� ���� �ٰŸ� or ���Ÿ� ����
	if (b1->GetCollisionLayer() == CLT_DETECT && b2->GetCollisionLayer() == CLT_MONSTER)
	{
		_isCloseAtk = false;

		return;
	}

	if (b1->GetCollisionLayer() == CLT_PLAYER_ATTACK && b2->GetCollisionLayer() == CLT_MONSTER)
	{
		AddSkillPoint(1);
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