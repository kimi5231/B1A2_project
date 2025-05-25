#include "pch.h"
#include "Player.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "ValueManager.h"
#include "DialogueManager.h"
#include "SceneManager.h"
#include "CameraComponent.h"
#include "DialogueComponent.h"
#include "Dialogue.h"
#include "BoxCollider.h"
#include "ItemActor.h"
#include "Item.h"
#include "DevScene.h"
#include "ZipLine.h"
#include "Flipbook.h"
#include "LockedDoorAndKey.h"
#include "BreakingWall.h"
#include "DestructibleObject.h"
#include "Window.h"
#include "FootHold.h"
#include "Blanket.h"
#include "Projectile.h"
#include "Crystal.h"
#include "TilemapActor.h"

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
		// Player Collider
		{
			BoxCollider* collider = new BoxCollider();
			// 리셋 안 하면 모두 충돌함
			collider->ResetCollisionFlag();

			// 나 자신을 설정
			collider->SetCollisionLayer(CLT_PLAYER);

			// 충돌하고 싶은 객체 설정
			collider->AddCollisionFlagLayer(CLT_MONSTER_ATTACK);
			collider->AddCollisionFlagLayer(CLT_FINAL_BOSS_SLASH);
			collider->AddCollisionFlagLayer(CLT_PROJECTILE);
			collider->AddCollisionFlagLayer(CLT_ITEM);
			collider->AddCollisionFlagLayer(CLT_GROUND);
			collider->AddCollisionFlagLayer(CLT_STAIR);
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

	// 대화 중에는 조작할 수 없도록 상태 변화 스킵
	// 이 코드의 위치는 추후 수정될 수 있음
	if (GET_SINGLE(DialogueManager)->GetIsDialouge())
		return;
	/*if (GetDialogue()->GetState() == DialogueState::Running || GetDialogue()->GetState() == DialogueState::Wait)
		return;*/

		// F key가 활성화되면 획득할 수 있음
		// 획득 후 F key와 Item을 화면에서 지움
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

				// Scene에 아이템 획득 효과 그리기
				// 추후 GameScene로 변경할 예정
				DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
				scene->SetItemAcquireState(_collideItem);

				// 잠긴 문과 열쇠의 열쇠 획득시 문 열리도록 설정
				if (_collideItem->GetItemID() == 310100)
					_isKeyAcquire = true;

				// 아이템 숨기기
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

		// Detect Collider 생성
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
				// 체력 감소 함수 호출
				SubtractHealthPoint(20);

				// 체력이 다 닳으면 사망
				if (_playerStat->hp == 0)
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

	// 플레이어가 화면 밖으로 넘어가지 않도록
	Vec2Int mapSize = GET_SINGLE(ValueManager)->GetMapSize();
	_pos.x = std::clamp(_pos.x, (float)(67 / 2), (float)mapSize.x);		// 67은 DevScene에서 설정한 Player collider 크기

	// Ground or Air 판단 코드(추후 코드 정리 필요)
	{
		Scene* scene = GET_SINGLE(SceneManager)->GetCurrentScene();

		TilemapActor* actor = dynamic_cast<TilemapActor*>(scene->GetActor(-2));

		const std::vector<Component*>& components = actor->GetComponents();

		for (Component* component : components)
		{
			if (dynamic_cast<BoxCollider*>(component))
			{
				BoxCollider* collider = dynamic_cast<BoxCollider*>(component);

				if (collider->GetCollisionLayer() == CLT_GROUND || collider->GetCollisionLayer() == CLT_STAIR)
				{
					Vec2 pos = _playerCollider->GetPos();
					float posX1 = pos.x - _playerCollider->GetSize().x / 2;
					float posX2 = pos.x + _playerCollider->GetSize().x / 2;
					float posY = pos.y +  _playerCollider->GetSize().y / 2;
					
					if (collider->GetPos().x - 20 < posX1 && posX1 < collider->GetPos().x + 20)
					{
						if (collider->GetPos().y - 20 < posY && posY < collider->GetPos().y + 20)
						{
							_isAir = false;
							_isGround = true;

							if (collider->GetCollisionLayer() == CLT_STAIR)
								_isOnStair = true;
							else
								_isOnStair = false;

							return;
						}
					}

					if (collider->GetPos().x - 20 < posX2 && posX2 < collider->GetPos().x + 20)
					{
						if (collider->GetPos().y - 20 < posY && posY < collider->GetPos().y + 20)
						{
							_isAir = false;
							_isGround = true;

							if (collider->GetCollisionLayer() == CLT_STAIR)
								_isOnStair = true;
							else
								_isOnStair = false;

							return;
						}
					}
				}
			}
		}

		if (_state != ObjectState::Hang)
		{
			_isAir = true;
			_isGround = false;
		}
	}
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
		// 이미 점프 중이면 리턴
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
		SetState(ObjectState::Idle); // 이동 키를 뗐을 때 Idle 상태로 변경
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		// 이미 점프 중이면 리턴
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
	else if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::S))	// 버튼을 뗐을 때
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

	// 좌우 이동도 가능하도록 추가
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

	if (_isGround && !_isAir)	// 땅에 닿았을 때
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
		if (_nearZipLine)
		{
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
			{
				// 바라보는 방향 설정
				_dir = DIR_RIGHT;

				_currentZipLine = _nearZipLine;
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
		else // A, D 미입력
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
		_pos.x += (distance / 0.7) * deltaTime;		// 속 = 거 / 시
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
	static bool isMoving = false;	// 이동 하는지
	static float sumTime = 0.0f;

	if (!_currentZipLine)
		return;

	Vec2 beginPos = _currentZipLine->GetBeginPos();
	Vec2 endPos = _currentZipLine->GetEndPos();
	Vec2 direction = (endPos - beginPos).Normalize();

	if (_currentZipLine->GetMidPos().x != 0 && _currentZipLine->GetMidPos().y != 0)	// 중간 탑승
		beginPos = _currentZipLine->GetMidPos();


	// 매달리기 시작 - 짚라인 시작 위치로 이동
	if (!isMoving)
	{
		_pos = beginPos;

		_isGround = true;
		_isAir = false;

		sumTime += GET_SINGLE(TimeManager)->GetDeltaTime();

		if (sumTime >= 1.0f)	// 1초 대기 후 이동 시작
		{
			isMoving = true;
			sumTime = 0.0f;
		}
	}
	// 이동 시작
	else
	{
		float speed = 300.0f;
		float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
		
		_pos += direction * speed * deltaTime;
		//_zipLine->GetPlayerDetectCollider()->SetPos({ _pos });

		// 이동 중 SpaceBar 입력 시 놓기
		if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
		{
			isMoving = false;

			sumTime = 0.0f;

			_isGround = false;
			_isAir = true;

			_currentZipLine->SetMidPos(_pos);

			SetState(ObjectState::Release);

			return;
		}

		// endPos에 도착하면 놓기
		Vec2 toEnd = endPos - _pos;
		if (toEnd.Dot(direction) <= 0.f)
		{
			isMoving = false;
			sumTime = 0.0f;

			_isGround = false;
			_isAir = true;

			_currentZipLine->SetMidPos({ 0, 0 });	// 중간 하차 X

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
		_pos.x -= (_playerStat->knockBackDistance * 2) * deltaTime;		// 속 = 거 / 시
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

		// 초기화 - 체력, 위치?
		SetHealthPoint(100);
		SetState(ObjectState::Idle);
	}
}

void Player::UpdateAnimation()
{
	Vec2 colliderSize = _playerCollider->GetSize();

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

	if (colliderSize.y > _playerCollider->GetSize().y)
	{
		_isGround = false;
		_isAir = true;
	}
}

int32 Player::GetAttack()
{
	// damage 수정 예정
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

	// 체력 감소 함수 호출
	SubtractHealthPoint(damage);

	// 체력이 다 닳으면 사망
	if (_playerStat->hp == 0)
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

	// 체력 감소 함수 호출
	SubtractHealthPoint(damage);

	// 체력이 다 닳으면 사망
	if (_playerStat->hp == 0)
	{
		SetState(ObjectState::Dead);
		return;
	}

	SetState(ObjectState::Hit);
}

void Player::SetHealthPoint(int hp)
{
	_playerStat->hp = 100;

	_healthObserver(_playerStat->hp);
}

void Player::AddHealthPoint(int hp)
{
	if (_playerStat->hp >= 100)
		return;

	if (_playerStat->hp += hp >= 100)
	{
		_playerStat->hp = 100;
	}
	else
		_playerStat->hp += hp;

	// 관찰자에게 알림
	_healthObserver(_playerStat->hp);
}

void Player::SubtractHealthPoint(int hp)
{
	if (_playerStat->hp <= 0)
		return;

	_playerStat->hp -= hp;

	// 관찰자에게 알림
	_healthObserver(_playerStat->hp);
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

void Player::RemoveItem(int32 id, int32 count)
{
	if (_acquiredItems.find(id) != _acquiredItems.end() && _acquiredItems[id] >= count)
	{
		_acquiredItems[id] -= count;
		if (_acquiredItems[id] == 0)	// 아이템 개수가 0이면 삭제
			_acquiredItems.erase(id);	
	}
}

void Player::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	// Item과 충돌하면 F key 활성화(밀어내기 X)
	if (b2->GetCollisionLayer() == CLT_ITEM)
	{
		ItemActor* item = reinterpret_cast<ItemActor*>(b2->GetOwner());

		if (item->GetItemID() != 300100)
			item->SetFKeyState(FKeyState::Show);
		else
		{
			AddHealthPoint(20);	// 숫자 수정 필요
			item->SetItemState(ItemState::Hidden);
		}

		_collideItem = item;

		return;
	}

	// Save Point에 충돌하면 저장하기(밀어내기 X)
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
					_nearZipLine = zipLine;
				}
				else if (zipLine->GetZipLineType() == ZipLineType::ZipLineWithButton)
				{
					ZipLineButtonAndDisplay* BD = zipLine->GetZipLineButtonAndDisplay();
					if (BD->GetState() == ObjectState::On)
					{
						_nearZipLine = zipLine;
					}
				}
				return;
			}
		}

		// LockedDoorAndKey - 플레이어가 열쇠를 획득한 상태라면 문 열기
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

	// Monster Atk - 몬스터가 사거리 내 있으면, 근거리 공격
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

		OnDamagedByProjectile(projectile);
	}

	// 벽 충돌하면 밀어내기
	if (b2->GetCollisionLayer() == CLT_WALL)
	{
		AdjustCollisionPos(b1, b2);
		return;
	}

	// 땅과 충돌 - 상하좌우 확인
	if (b2->GetCollisionLayer() == CLT_GROUND)
	{
		_isGround = true;
		_isAir = false;
	}

	// 계단
	if (b2->GetCollisionLayer() == CLT_STAIR)
	{
		// Jump State일때만 충돌
		if (_state == ObjectState::Jump)
		{
			_isGround = true;
			_isAir = false;
			//_isOnStair = true;
		}
	}

	if (b1->GetCollisionLayer() == CLT_PLAYER && (b2->GetCollisionLayer() == CLT_MONSTER_ATTACK || b2->GetCollisionLayer() == CLT_FINAL_BOSS_SLASH))
	{
		Creature* otherOwner = dynamic_cast<Creature*>(b2->GetOwner());
		OnDamaged(otherOwner);

		return;
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
		_nearZipLine = nullptr;

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

	// 몬스터 거리에 따라 근거리 or 원거리 공격
	if (b1->GetCollisionLayer() == CLT_DETECT && b2->GetCollisionLayer() == CLT_MONSTER)
	{
		_isCloseAtk = false;

		return;
	}
}

void Player::OnComponentOverlapping(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayer() == CLT_WALL)
	{
		AdjustCollisionPos(b1, b2);
		return;
	}

	if (b2->GetCollisionLayer() == CLT_GROUND)
	{
		AdjustCollisionPosGround(b1, b2);
		return;
	}

	if (b2->GetCollisionLayer() == CLT_STAIR && _isOnStair)
	{
		AdjustCollisionPosGround(b1, b2);
		return;
	}
}

void Player::AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2)
{
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();

	Vec2 pos = GetPos();
	RECT intersect = {};	// 충돌된 범위

	if (::IntersectRect(&intersect, &r1, &r2))
	{
		int32 w = intersect.right - intersect.left;
		int32 h = intersect.bottom - intersect.top;
		
		if (w > h)
		{
			if (intersect.top == r2.top)
			{
				// 위로 올려 보내기
				pos.y -= h;
			}
			else
			{
				// 아래로 내려 보내기
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

void Player::AdjustCollisionPosGround(BoxCollider* b1, BoxCollider* b2)
{
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();

	Vec2 pos = GetPos();
	Vec2 colliderPos = _playerCollider->GetPos();

	// 충돌 범위
	RECT intersect = {};

	if (::IntersectRect(&intersect, &r1, &r2))
	{
		int32 h = intersect.bottom - intersect.top;

		// 위로 올려 보내기
		pos.y -= h;	
		colliderPos.y -= h;
	}

	SetPos(pos);
	_playerCollider->SetPos(colliderPos);
}