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
#include "GameScene.h"
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
	// Set Stat
	Stat* stat = GET_SINGLE(ResourceManager)->GetStat();
	_playerStat = stat->GetPlayerStat();
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
	_flipbookPlayerThrust[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerThrustRight");
	_flipbookPlayerThrust[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerThrustLeft");
	_flipbookPlayerHit[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerHitRight");
	_flipbookPlayerHit[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerHitLeft");
	_flipbookPlayerSkillReady[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerSkillReadyRight");
	_flipbookPlayerSkillReady[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerSkillReadyLeft");	
	_flipbookPlayerSkillWaiting[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerSkillWaitingRight");
	_flipbookPlayerSkillWaiting[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerSkillWaitingLeft");
	_flipbookPlayerSkillEnd[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerSkillEndRight");
	_flipbookPlayerSkillEnd[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerSkillEndLeft");

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
			collider->AddCollisionFlagLayer(CLT_GAME_OVER);
			collider->AddCollisionFlagLayer(CLT_NEXT);
			collider->AddCollisionFlagLayer(CLT_DETECT);
			collider->AddCollisionFlagLayer(CLT_STRUCTURE);
			collider->AddCollisionFlagLayer(CLT_STRUCTURE_DETECT);
			collider->AddCollisionFlagLayer(CLT_STRUCTURE_COLLISION);

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


	TickCollideItem();

	TickColliderCreationAndRemove();

	TickWindow();

	TickFootHold();

	TickGravity();

	// 플레이어가 화면 밖으로 넘어가지 않도록
	Vec2Int mapSize = GET_SINGLE(ValueManager)->GetMapSize();
	_pos.x = std::clamp(_pos.x, (float)(67 / 2), (float)mapSize.x);

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

				if (collider->GetCollisionLayer() == CLT_GROUND || collider->GetCollisionLayer() == CLT_STAIR || collider->GetCollisionLayer() == CLT_GAME_OVER)
				{
					Vec2 pos = _playerCollider->GetPos();
					float posX1 = pos.x - _playerCollider->GetSize().x / 2;
					float posX2 = pos.x + _playerCollider->GetSize().x / 2;
					float posY = pos.y + _playerCollider->GetSize().y / 2;

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

		if (_info.state() != HANG)
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
		SetState(MOVE);
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		SetDir(DIR_RIGHT);
		SetState(MOVE);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		// 이미 점프 중이면 리턴
		if (!_isGround && _isAir)
			return;

		_isGround = false;
		_isAir = true;

		SetState(JUMP);

		_ySpeed = -_playerStat->jumpSpeed;
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		SetState(DUCK_DOWN);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		if (_isCloseAtk)
			SetState(CLOSE_ATTACK);
		else
			SetState(LONG_ATTACK);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::RightMouse))
	{
		if (GetSkillPoint() >= 3)
		{
			SubtractSkillPoint(3);

			_skillTimer = 0.f;

			_leftInputCount = 0;
			_rightInputCount = 0;

			SetState(SKILL_READY);
		}
	}
	else
	{
		_keyPressed = false;

		if (_info.state() == IDLE)
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
		SetState(IDLE); // 이동 키를 뗐을 때 Idle 상태로 변경
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		// 이미 점프 중이면 리턴
		if (!_isGround && _isAir)
			return;

		_isGround = false;
		_isAir = true;

		SetState(JUMP);

		_ySpeed = -_playerStat->jumpSpeed;
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		SetState(DUCK_DOWN_MOVE);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))	// Normal Attack
	{
		if (_isCloseAtk)
			SetState(CLOSE_ATTACK);
		else
			SetState(LONG_ATTACK);

	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::RightMouse))	// Skill
	{
		SetState(SKILL_READY);
	}
}

void Player::TickDuckDown()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::A))
	{
		SetDir(DIR_LEFT);
		SetState(DUCK_DOWN_MOVE);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::D))
	{
		SetDir(DIR_RIGHT);
		SetState(DUCK_DOWN_MOVE);
	}
	else if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::S))	// 버튼을 뗐을 때
	{
		SetState(IDLE);
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
		SetState(DUCK_DOWN);
	}

	if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::S))
	{
		SetState(MOVE);
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
			SetState(MOVE);
		}
		else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
		{
			SetDir(DIR_RIGHT);
			SetState(MOVE);
		}
		else
			SetState(IDLE);
	}
	else
	{
		// ZipLine 
		if (_nearZipLine)
		{
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
			{
				// 바라보는 방향 설정
				SetDir(DIR_RIGHT);

				_currentZipLine = _nearZipLine;
				SetState(HANG);
			}
		}
	}
 }

void Player::TickCloseAttack()
{
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
		SetState(IDLE);
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
		if (_info.dir() == DIR_RIGHT)
		{
			_pos.x += 114 * deltaTime;
		}
		else
			_pos.x -= 114 * deltaTime;
	}

	if (this->GetIdx() == 14)
	{
		sumTime = 0.0f;

		SetState(IDLE);
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
				SetState(IDLE);
			else
			{
				if (_leftInputCount < _rightInputCount)
					SetDir(DIR_RIGHT);
				else
					SetDir(DIR_LEFT);

				SetState(SKILL_WAITING);
			}
		}
	}
	if (_skillTimer >= 2.0f)
	{
		_skillTimer = 0.f;

		if (_leftInputCount > 0 || _rightInputCount > 0)
		{
			if (_leftInputCount == _rightInputCount)
				SetState(IDLE);
			else
			{
				if (_leftInputCount < _rightInputCount)
					SetDir(DIR_RIGHT);
				else
					SetDir(DIR_LEFT);

				SetState(SKILL_WAITING);
			}
		}
		else // A, D 미입력
		{
			SetState(IDLE);
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

	if (_info.dir() == DIR_RIGHT)
		_pos.x += (distance / 0.7) * deltaTime;		// 속 = 거 / 시
	else
		_pos.x -= (distance / 0.7) * deltaTime;

	if (sumTime > 0.7f)
	{
		sumTime = 0.f;
		SetState(SKILL_END);
	}
}

void Player::TickSkillEnd()
{
	if (GetIdx() == _flipbookPlayerSkillEnd[_info.dir()]->GetFlipbookEndNum())
		SetState(IDLE);
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
		_pos.x = beginPos.x;
		_pos.y = beginPos.y + 50;	// 위치 보정

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

			_pos.y -= 50;	// 위치 보정

			_isGround = false;
			_isAir = true;

			_currentZipLine->SetMidPos(_pos);

			SetState(RELEASE);

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

			SetState(RELEASE);
		}
	}
}

void Player::TickRelease()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	static float sumTime = 0.0f;

	sumTime += deltaTime;

	if (_info.dir() == DIR_RIGHT)
		_pos.x += _playerStat->runSpeed * deltaTime;
	else
		_pos.x -= _playerStat->runSpeed * deltaTime;

	if (sumTime >= 0.3f)
	{
		sumTime = 0.f;
		SetState(IDLE);
	}
}

void Player::TickHit()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	static bool knockBackApplied = false;
	static float sumTime = 0.f;

	// knockback
	if (!knockBackApplied)
	{
		if (_info.dir() == DIR_RIGHT)
			_pos.x -= _playerStat->knockBackDistance;
		else
			_pos.x += _playerStat->knockBackDistance;

		knockBackApplied = true;
	}

	sumTime += deltaTime;

	if (sumTime >= 0.5f)
	{
		SetState(IDLE);
		knockBackApplied = false;
		sumTime = 0.f;
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

		// 보스 스테이지
		if (_curStageNum == 4)
		{
			SetPos({ 200, 520 });
			AddHealthPoint(100);
			SubtractSkillPoint(5);

			SetState(IDLE);
			return;
		}

		// 나머지 스테이지
		GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		if (scene->isSaveFile())
		{
			scene->LoadGameData();
			LoadData data = scene->GetLoadData();

			SetPos(data.playerPos);
			AddHealthPoint(100);
			SubtractSkillPoint(5);
			SetAcquireItems(data.playerItems);
		}
		else
		{
			SetPos({ 400, 200 });
			AddHealthPoint(100);
			SubtractSkillPoint(5);
		}

		SetState(IDLE);
	}
}

void Player::UpdateAnimation()
{
	Vec2 colliderSize = _playerCollider->GetSize();

	switch (_info.state())
	{
	case IDLE:
		_playerCollider->SetSize({ 23, 85 });
		SetFlipbook(_flipbookPlayerIdle[_info.dir()]);		
		break;
	case MOVE:
		_playerCollider->SetSize({67, 70 });
		SetFlipbook(_flipbookPlayerMove[_info.dir()]);
		break;
	case DUCK_DOWN:
		_playerCollider->SetSize({35, 45});
		SetFlipbook(_flipbookPlayerDuckDown[_info.dir()]);
		break;
	case DUCK_DOWN_MOVE:
		_playerCollider->SetSize({ 34, 50 });
		SetFlipbook(_flipbookPlayerDuckDownMove[_info.dir()]);
		break;
	case JUMP:
		_playerCollider->SetSize({ 34, 55 });
		SetFlipbook(_flipbookPlayerJump[_info.dir()]);
		break;
	case HANG:
		_playerCollider->SetSize({ 30, 80 });
		SetFlipbook(_flipbookPlayerHang[_info.dir()]);
		break;
	case RELEASE:
		_playerCollider->SetSize({ 34, 88 });
		SetFlipbook(_flipbookPlayerRelease[_info.dir()]);
		break;
	case SKILL_READY:
		_playerCollider->SetSize({140, 85});
		SetFlipbook(_flipbookPlayerSkillReady[_info.dir()]);
		break;
	case SKILL_WAITING:
		_playerCollider->SetSize({ 140, 85 });
		SetFlipbook(_flipbookPlayerSkillWaiting[_info.dir()]);
		break;
	case SKILL_END:
		_playerCollider->SetSize({ 140, 85 });
		SetFlipbook(_flipbookPlayerSkillEnd[_info.dir()]);
		break;
	case CLOSE_ATTACK:
		_playerCollider->SetSize({ 75, 90 });
		SetFlipbook(_flipbookPlayerSlash[_info.dir()]);
		break;
	case LONG_ATTACK:
		_playerCollider->SetSize({ 125, 85 });
		SetFlipbook(_flipbookPlayerThrust[_info.dir()]);		
		break;
	case HIT:
		_playerCollider->SetSize({ 41, 80 });
		SetFlipbook(_flipbookPlayerHit[_info.dir()]);
	break;
	case DEAD:
		SetFlipbook(_flipbookPlayerDead[_info.dir()]);
	break;
	}

	if (colliderSize.y > _playerCollider->GetSize().y)
	{
		_isGround = false;
		_isAir = true;
	}
}

void Player::TickColliderCreationAndRemove()
{
	if (_info.state() != CLOSE_ATTACK && _info.state() != LONG_ATTACK)
	{
		if (_attackCollider)
		{
			GET_SINGLE(CollisionManager)->RemoveCollider(_attackCollider);
			RemoveComponent(_attackCollider);
			_attackCollider = nullptr;
		}
	}
	if (_info.state() != SKILL_WAITING && _info.state() != SKILL_END)
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
	if (_info.state() == SKILL_WAITING || _info.state() == SKILL_END)
	{
		if (_detectCollider)
		{
			GET_SINGLE(CollisionManager)->RemoveCollider(_detectCollider);
			RemoveComponent(_detectCollider);
			_detectCollider = nullptr;
		}
	}
}

void Player::TickCollideItem()
{
	// F key가 활성화되면 획득할 수 있음
	// 획득 후 F key와 Item을 화면에서 지움

	if (!_collideItem)
		return;

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

			GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
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

void Player::TickWindow()
{
	if (_window && _isInWindow)
	{
		if (_window->GetState() == ON)
		{
			if (!_damagedByWindow)
			{
				// 체력 감소 함수 호출
				SubtractHealthPoint(20);

				// 체력이 다 닳으면 사망
				if (_playerStat->hp == 0)
				{
					SetState(DEAD);
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
}

void Player::TickFootHold()
{
	// FootHoldAndZipLineButton
	if (_footHoldAndZipLineButton)
	{
		switch (_footHoldAndZipLineButton->GetState())
		{
		case OFF:
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_1))
				_footHoldAndZipLineButton->SetState(ON);
			break;
		case ON:
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_2))
				_footHoldAndZipLineButton->SetState(ON2);
			break;
		}
	}
}


int32 Player::GetAttack()
{
	// damage 수정 예정
	switch (_info.state())
	{
	case CLOSE_ATTACK:
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
	case LONG_ATTACK:
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
	case SKILL_WAITING:
	case SKILL_END:
		return _playerStat->skillDamage;
		break;
	}

	return 50;
}

float Player::GetSpeed()
{
	switch (_info.state())
	{
	case MOVE:
		return _playerStat->runSpeed;
		break;
	case DUCK_DOWN_MOVE:
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
		SetState(DEAD);
		return;
	}

	SetState(HIT);
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
		SetState(DEAD);
		return;
	}

	SetState(HIT);
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
	_playerStat->hp = max(0, _playerStat->hp - hp);

	// 관찰자에게 알림
	_healthObserver(_playerStat->hp);
}

void Player::AddSkillPoint(int32 skillPoint)
{
	_playerStat->skillPoint = min(5, _playerStat->skillPoint + skillPoint);

	// 관찰자에게 알림
	_skillPointObserver(_playerStat->skillPoint);
}

void Player::SubtractSkillPoint(int32 skillPoint)
{
	_playerStat->skillPoint = max(0, _playerStat->skillPoint - skillPoint);

	// 관찰자에게 알림
	_skillPointObserver(_playerStat->skillPoint);
}

void Player::SetPlayerStat(const Protocol::PlayerStat& stat)
{
	PlayerStat* playerStat = new PlayerStat();

	playerStat->hp = stat.hp();
	playerStat->runSpeed = stat.runspeed();
	playerStat->crouchSpeed = stat.crouchspeed();
	playerStat->jumpSpeed = stat.jumpspeed();
	playerStat->skillPoint = stat.skillpoint();
	playerStat->nLongAtkDistance = stat.nlongatkdistance();
	playerStat->knockBackDistance = stat.knockbackdistance();
	playerStat->strongAtkMultiplier = stat.strongatkmultiplier();
	playerStat->nAtkDamage = stat.natkdamage();
	playerStat->skillDamage = stat.skilldamage();
	playerStat->skillRange = stat.skillrange();
	playerStat->skillDuration = stat.skillduration();
	playerStat->skillStepDistance = stat.skillstepdistance();

	_playerStat = playerStat;

	CalPixelPerSecond();
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
			AddHealthPoint(20);
			item->SetItemState(ItemState::Hidden);
		}

		_collideItem = item;

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
					if (BD->GetState() == ON)
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

		// DestructibleObject
		{
			DestructibleObject* destructibleObject = dynamic_cast<DestructibleObject*>(structure);

			if (destructibleObject)
			{
				_isCloseAtk = true;
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
	}
	// Structure Collision
	if (b2->GetCollisionLayer() == CLT_STRUCTURE_COLLISION)
	{
		Structure* structure = dynamic_cast<Structure*>(b2->GetOwner());
		if (!structure)
			return;

		// BreakingWall
		{
			BreakingWall* breakingWall = dynamic_cast<BreakingWall*>(structure);

			if (breakingWall)
			{
				_isCloseAtk = true;
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
		// 스킬 중엔 Projectile 안 맞도록
		if (_info.state() == SKILL_READY || _info.state() == SKILL_END || _info.state() == SKILL_WAITING)
			return;

		Projectile* projectile = dynamic_cast<Projectile*>(b2->GetOwner());
		if (!projectile)
			return;

		OnDamagedByProjectile(projectile);
	}

	// 낙사
	if (b2->GetCollisionLayer() == CLT_GAME_OVER)
	{
		SetState(DEAD);
		return;
	}

	// Save Point에 충돌하면 저장하기(밀어내기 X)
	if (b2->GetCollisionLayer() == CLT_SAVE_POINT)
	{
		_gameScene->SaveCurData();

		return;
	}

	// Next - 다음 스테이지로
	if (b2->GetCollisionLayer() == CLT_NEXT)
	{
		GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

		switch (_curStageNum)
		{
		case 1:
			scene->RequestStageChange(2); break;
		case 2:
			scene->RequestStageChange(3); break;
		case 3:
			scene->RequestStageChange(4);	break;
		}

		return;
	}

	// 계단
	if (b2->GetCollisionLayer() == CLT_STAIR)
	{
		// Jump State일때만 충돌
		if (_info.state() == JUMP)
		{
			_isGround = true;
			_isAir = false;
			//_isOnStair = true;
		}
	}

	if (b1->GetCollisionLayer() == CLT_PLAYER && (b2->GetCollisionLayer() == CLT_MONSTER_ATTACK || b2->GetCollisionLayer() == CLT_FINAL_BOSS_SLASH))
	{
		if (_info.state() == HIT)
			return;

		Creature* otherOwner = dynamic_cast<Creature*>(b2->GetOwner());
		OnDamaged(otherOwner);

		return;
	}

	if (b1->GetCollisionLayer() == CLT_PLAYER_ATTACK && b2->GetCollisionLayer() == CLT_MONSTER)
	{
		AddSkillPoint(1);
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

	if (b2->GetCollisionLayer() == CLT_GAME_OVER)
	{
		AdjustCollisionPos(b1, b2);
		return;
	}

	if (b2->GetCollisionLayer() == CLT_STRUCTURE_COLLISION)
	{
		Structure* structure = dynamic_cast<Structure*>(b2->GetOwner());

		// LcokedDoorAndKey - 잠겼을 때만 위치 조정
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

		AdjustCollisionPos(b1, b2);
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