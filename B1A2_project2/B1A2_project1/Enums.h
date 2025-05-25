#pragma once

enum class SceneType
{
	None,
	TitleScene,	// 타이틀 씬
	SettingScene, // 설정 씬
	GameScene,	// 인게임 씬
	DevScene,	// 개발 씬
	TilemapScene,
};

enum LAYER_TYPE
{
	LAYER_BACKGROUND,
	LAYER_TILEMAP,
	LAYER_ITEM,
	LAYER_STRUCTURE,
	LAYER_PROJECTILE,
	LAYER_MONSTER,
	LAYER_PLAYER,

	LAYER_UI,

	LAYER_MAXCOUNT
};

// 충돌
enum class ColliderType
{
	Box,
	Sphere,
};

enum COLLISION_LAYER_TYPE : uint8
{
	CLT_PLAYER,		// 0
	CLT_MONSTER,	// 1
	CLT_PROJECTILE, // 2

	CLT_ITEM,		// 3
	
	CLT_GROUND,		// 4
	CLT_WALL,		// 5
	CLT_STAIR,		// 6
	CLT_SAVE_POINT,	// 7
	CLT_GAME_OVER,	// 8

	CLT_DETECT,		// 9
	CLT_MONSTER_ATTACK,	// 10
	CLT_FINAL_BOSS_SLASH, // 12
	CLT_PLAYER_ATTACK,	// 13
	CLT_PLAYER_SKILL,

	CLT_STRUCTURE,	// 14 - 예. 짚라인 버튼
	CLT_STRUCTURE_DETECT, // 15 - 예. 짚라인

	CLT_NONE,		
};

// 플레이어 방향
enum Dir
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN,
};

// Sound
enum class SoundType
{
	BGM,
	Normal,
};

// Dialogue
enum class DialogueState
{
	Running,
	Wait,
	Hidden,
};

enum class DialogueType
{
	Bubble,
	CutScene,
};

// F_key 
enum class FKeyState
{
	Hidden,
	Show,
};

enum class ItemState
{
	Hidden,
	Show,
};

// Inventory
enum class InventoryState
{
	Hidden,
	Show,
};

// Scene
enum class SceneState
{
	Play,
	Menu,
	ItemAcquire,
	Inventory,
};

// Object
enum class ObjectState
{
	Idle,	// 대기
	Move,	// 달리기
	DuckDown,	// 숙이기
	DuckDownMove,	// 숙이면서 달리기
	Jump,	// 점프
	CloseAttack,	// 기본 공격
	LongAttack,
	LongAttackLength,
	LongAttackWidth,
	Thrust,		// 찌르기
	BackStep,	// 백스텝
	SlashWave,	// 검기 날리기
	SkillReady,	// 스킬
	SkillWaiting,
	SkillEnd, 
	Hang,	// 매달리기
	Release,	// 놓기
	Hit,	// 피격
	Dead,	// 사망
	Chase,	// 추적
	Roaming,	// 배회
	Dash,	// 대쉬
	Return,		// 복귀
	ReturnIdle,		// 복귀 대기(복귀하기 전 대기하는 상태)
	ProjectileFall,
	CrystalCreation,
	MonsterCreation,
	Teleport,
	CutSeverely,
	On,		// 구조물
	On2,
	Ready,
	Off,
};

enum class ZipLineType
{
	ZipLine,
	ZipLineWithButton,
};

enum class SlashWaveType
{
	W,
	H,
};