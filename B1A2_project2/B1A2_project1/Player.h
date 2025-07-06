#pragma once
#include "Creature.h"
#include "FlipbookActor.h"

class Flipbook;
class BoxCollider;
class ItemActor;
class ZipLine;
class LockedDoorAndKey;
class Window;
class FootHoldAndZipLineButton;
class GameScene;
class Projectile;

struct PlayerStat
{
	int32 hp = 0; // A
	float runSpeed = 0;	// B
	float crouchSpeed = 0;	// C
	float jumpSpeed = 0;	// D
	int32 skillPoint = 0;	// E
	int32 nAtkRange = 0;	// F
	int32 nLongAtkDistance = 0;	// G
	int32 knockBackDistance = 0;	// H
	float strongAtkMultiplier = 0.f;	// I
	int32 nAtkDamage = 0;	// J
	int32 skillDamage = 0;	// K
	int32 skillRange = 0;	// L
	float skillDuration = 0;	// M
	int32 skillStepDistance = 0;	// N
};

class Player : public Creature
{
	using Super = Creature;
public:
	Player();
	virtual ~Player() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	// Player State
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickDuckDown() override;
	virtual void TickDuckDownMove() override;
	virtual void TickJump() override;
	virtual void TickCloseAttack() override;
	virtual void TickLongAttack() override;
	virtual void TickSkillReady() override;
	virtual void TickSkillWaiting() override;
	virtual void TickSkillEnd() override;
	virtual void TickHang() override;
	virtual void TickRelease() override;
	virtual void TickHit() override;
	virtual void TickDead() override;
	virtual void UpdateAnimation() override;

	void TickColliderCreationAndRemove();
	void TickCollideItem();
	void TickWindow();
	void TickFootHold();

public:
	virtual int32 GetAttack() override;
	virtual float GetSpeed() override;

	virtual void OnDamaged(Creature* other);
	void OnDamagedByProjectile(Projectile* projectile);

	// Hp 
	using HealthObserver = void(*)(int);	// hp 변화시 호출될 콜백 함수 타입
	void SetHealthObserver(std::function<void(int)> observer) { _healthObserver = observer; }

	void SetHealthPoint(int hp);
	void AddHealthPoint(int hp);
	void SubtractHealthPoint(int hp);

	int32& GetHp() { return _playerStat->hp; }
	void SetHp(int32 hp) { _playerStat->hp = hp; }

	// SkillPoint
	using SkillPointObserver = void(*)(int);
	void SetSkillPointObserver(std::function<void(int)> observer) { _skillPointObserver = observer; }

	int32 GetSkillPoint() { return _playerStat->skillPoint; }
	void SetSkillPoint(int32 skillPoint) { _playerStat->skillPoint = skillPoint; }
	void AddSkillPoint(int32 skillPoint);
	void SubtractSkillPoint(int32 skillPoint);

	void SetPlayerStat(const Protocol::PlayerStat& stat);

public:
	void SetCurrentScene(GameScene* gameScene) { _gameScene = gameScene; }		// GameScene으로 수정 필요
	void SetCurStageNum(int32 stage) { _curStageNum = stage; }

public:
	void CalPixelPerSecond();

	// Collider
	void SetPlayerCollider(BoxCollider* collider) { _playerCollider = collider; }

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);
	virtual void OnComponentOverlapping(Collider* collider, Collider* other);

	void AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2);	// 튕기기
	void AdjustCollisionPosGround(BoxCollider* b1, BoxCollider* b2);

public:
	// Item
	void RemoveItem(int32 id, int32 count);
	std::unordered_map<int32, int32>& GetAquireItems() { return _acquiredItems; }
	void SetAcquireItems(const std::unordered_map<int32, int32>& items) { _acquiredItems = items; }		// 저장 데이터 불러올 때 사용
	void ClearAcquireItems() { _acquiredItems.clear(); }

public:
	int32 GetAtkRange() { return _playerStat->nAtkRange; }

	void SetIsCloseAtk(bool isCloseAtk) { _isCloseAtk = isCloseAtk; }

	bool isSkillActive() const { return _info.state() == SKILL_READY || _info.state() == SKILL_WAITING || _info.state() == SKILL_END; }
private:
	// Flipbook
	Flipbook* _flipbookPlayerIdle[2] = {};
	Flipbook* _flipbookPlayerMove[2] = {};
	Flipbook* _flipbookPlayerJump[2] = {};
	Flipbook* _flipbookPlayerDuckDown[2] = {};
	Flipbook* _flipbookPlayerDuckDownMove[2] = {};
	Flipbook* _flipbookPlayerHang[2] = {};
	Flipbook* _flipbookPlayerSlash[2] = {};		// CloseAtk
	Flipbook* _flipbookPlayerThrust[2] = {};
	Flipbook* _flipbookPlayerSkillReady[2] = {};
	Flipbook* _flipbookPlayerSkillWaiting[2] = {};
	Flipbook* _flipbookPlayerSkillEnd[2] = {};
	Flipbook* _flipbookPlayerRelease[2] = {};
	Flipbook* _flipbookPlayerHit[2] = {};
	Flipbook* _flipbookPlayerDead[2] = {};

protected:
	bool _keyPressed = false;

	PlayerStat* _playerStat = {};

	std::function<void(int)> _healthObserver;	// 체력 변화 알림 받을 함수 포인터
	std::function<void(int)> _skillPointObserver;

	bool _isOnStair = false;

	// 획득한 아이템
	ItemActor* _collideItem = {};	// unordered map에 저장하기 위해, 충돌한 아이템을 담을 변수
	std::unordered_map<int32, int32> _acquiredItems;		// [아이템 ID, 개수]

	GameScene* _gameScene = nullptr;	// 현재 씬 데이터 정보 저장을 위해 필요, 다른 게임 Scene 추가시 수정 필요

	ZipLine* _currentZipLine = nullptr;
	ZipLine* _nearZipLine = nullptr;
	Window* _window = nullptr;
	FootHoldAndZipLineButton* _footHoldAndZipLineButton = nullptr;

	BoxCollider* _playerCollider = nullptr;
	Collider* _attackCollider = nullptr;
	Collider* _detectCollider = nullptr;	// 근거리, 원거리 공격 결정 
	Collider* _skillCollider = nullptr;

	bool _isCloseAtk = false;
	bool _isKeyAcquire = false;
	bool _isInWindow = false;
	bool _damagedByWindow = false;
	bool _isReleaseInMid = false;
	bool _isMoving = false;

	// Skill
	float _skillTimer = 0.f;
	float _hangTimer = 0.f;
	int32 _leftInputCount = 0;
	int32 _rightInputCount = 0;

	// CurSceneNum
	int32 _curStageNum = 0;
};