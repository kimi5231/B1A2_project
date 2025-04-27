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
class DevScene;
class Projectile;

struct PlayerStat
{
	CommonStat commonStat{}; // A, B
	float runSpeed = 0;	// C
	float crouchSpeed = 0;	// D
	float jumpSpeed = 0;	// E
	int32 skillPoint = 0;	// F
	int32 nAtkRange = 0;	// G
	int32 nLongAtkDistance = 0;	// H
	int32 knockBackDistance = 0;	// I
	float strongAtkMultiplier = 0.f;	// J	
	int32 nAtkDamage = 0;	// K
	int32 skillDamage = 0;	// L
	int32 skillRange = 0;	// M
	float skillDuration = 0;	// N
	int32 skillStepDistance = 0;	// O

	void LoadFile(const std::wstring& path)
	{
		std::ifstream ifs;
		ifs.open(path);

		std::string line;

		if (std::getline(ifs, line))
		{
			std::istringstream lineStream(line);
			std::string cell;
			int column = 0;

			while (std::getline(lineStream, cell, ','))
			{
				switch (column)
				{
				case 0:this->commonStat.id = std::stoi(cell); break;	// A
				case 1: this->commonStat.hp = std::stoi(cell); break;	// B
				case 2: this->runSpeed = std::stof(cell); break;	// C
				case 3: this->crouchSpeed = std::stof(cell); break;	// D
				case 4: this->jumpSpeed = std::stof(cell); break;	// E
				case 5: this->skillPoint = std::stoi(cell); break;	// F
				case 6: this->nAtkRange = std::stoi(cell); break;	// G
				case 7: this->nLongAtkDistance = std::stoi(cell); break;	// H
				case 8: this->knockBackDistance = std::stoi(cell); break;	// I
				case 9: this->strongAtkMultiplier = std::stof(cell); break;	// J
				case 10: this->nAtkDamage = std::stoi(cell); break;	// K
				case 11: this->skillDamage = std::stoi(cell); break;	// L
				case 12: this->skillRange = std::stoi(cell); break;	// M
				case 13: this->skillDamage = std::stof(cell); break;	// N
				case 14: this->skillStepDistance = std::stoi(cell); break;	// O
				}
				++column;
			}
		}
		ifs.close();
	}
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

private:
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

public:
	virtual int32 GetAttack() override;
	virtual float GetSpeed() override;

	virtual void OnDamaged(Creature* other);
	void OnDamagedByProjectile(Projectile* projectile);

	// Hp �ٲ� ��
	using HealthObserver = void(*)(int);	// hp ��ȭ�� ȣ��� �ݹ� �Լ� Ÿ��
	void SetHealthObserver(std::function<void(int)> observer) { _healthObserver = observer; }
	
	void SetHealthPoint(int hp);
	void AddHealthPoint(int hp);
	void SubtractHealthPoint(int hp);

	int32& GetHp() { return _playerStat->commonStat.hp; }
	void SetHp(int32 hp) { _playerStat->commonStat.hp = hp; }

	int32 GetSkillPoint() { return _playerStat->skillPoint; }
	void SetSkillPoint(int32 skillPoint) { _playerStat->skillPoint = skillPoint; }
	void AddSkillPoint(int32 skillPoint) { _playerStat->skillPoint = min(5, _playerStat->skillPoint + skillPoint); }
	void SubtractSkillPoint(int32 skillPoint) { _playerStat->skillPoint = max(0, _playerStat->skillPoint - skillPoint); }

public:
	// Player�� Save Point�� �浹���� �� �������� ���� ������ ���� �� ������ �ʿ���, �ٸ� �� �߰� �� ���� �ʿ�
	void SetCurrentScene(DevScene* devScene) { _devScene = devScene; }

public: 
	// ���ǿ����� ������ �ȼ� ������ �ٲ�
	void CalPixelPerSecond();

	// Collider
	void SetPlayerCollider(BoxCollider* collider) { _playerCollider = collider; }

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);
	
	void AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2);	// ƨ���
	void TickGravity();

public:
	// Item
	void RemoveItem(int32 id, int32 count);
	std::unordered_map<int32, int32>& GetAquireItems() { return _acquiredItems; }
	void SetAcquireItems(const std::unordered_map<int32, int32>& items) { _acquiredItems = items; }		// ���� ������ �ҷ��� �� ���
	void ClearAcquireItems() { _acquiredItems.clear(); }

public:
	int32 GetAtkRange() { return _playerStat->nAtkRange; }

	void SetIsCloseAtk(bool isCloseAtk) { _isCloseAtk = isCloseAtk; }

private:
	// Flipbook
	Flipbook* _flipbookPlayerIdle[2] = {};
	Flipbook* _flipbookPlayerMove[2] = {};
	Flipbook* _flipbookPlayerJump[2] = {};
	Flipbook* _flipbookPlayerDuckDown[2] = {};
	Flipbook* _flipbookPlayerDuckDownMove[2] = {};
	Flipbook* _flipbookPlayerHang[2] = {};
	Flipbook* _flipbookPlayerSlash[2] = {};		// CloseAtk

	Flipbook* _flipbookPlayerSkill[2] = {};
	//Flipbook* _flipbookPlayerCloseAttack[2] = {};
	//Flipbook* _flipbookPlayerLongAttack[2] = {};
	Flipbook* _flipbookPlayerRelease[2] = {};
	Flipbook* _flipbookPlayerHit[2] = {};
	Flipbook* _flipbookPlayerDead[2] = {};

private:
	bool _keyPressed = false;

	PlayerStat* _playerStat = {};

	std::function<void(int)> _healthObserver;	// ü�� ��ȭ �˸� ���� �Լ� ������

	// Jump
	int32 _groundCollisionCount = 0;	// �浹���� Ÿ�ϸ� ���� (0���� �� _Ground = true)
	int32 _gravity = 1000;
	float _ySpeed = {};

	bool _isGround = false;
	bool _isAir = false;

	// ȹ���� ������
	ItemActor* _collideItem = {};	// unordered map�� �����ϱ� ����, �浹�� �������� ���� ����
	std::unordered_map<int32, int32> _acquiredItems;		// [������ ID, ����]

	DevScene* _devScene = nullptr;	// ���� �� ������ ���� ������ ���� �ʿ�, �ٸ� ���� Scene �߰��� ���� �ʿ�

	ZipLine* _zipLine = nullptr;	// �浹 ���� ¤������ ������ �����ͼ� �Ŵ޸���
	Window* _window = nullptr;
	FootHoldAndZipLineButton* _footHoldAndZipLineButton = nullptr;

	BoxCollider* _playerCollider = nullptr;
	Collider* _attackCollider = nullptr;
	Collider* _detectCollider = nullptr;	// �ٰŸ�, ���Ÿ� ���� ���� 

	bool _isCloseAtk = false;
	bool _isKeyAcquire = false;
	bool _isInWindow = false;
	bool _damagedByWindow = false;	
	bool _isReleaseInMid = false;

	// Skill
	float _skillTimer = 0.f;
	int32 _leftInputCount = 0;
	int32 _rightInputCount = 0;
};

