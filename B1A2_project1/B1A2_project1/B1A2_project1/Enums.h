#pragma once

enum class SceneType
{
	None,
	TitleScene,	// 타이틀 씬
	SettingScene, // 설정 씬
	GameScene,	// 인게임 씬
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
	CLT_PLAYER,		
	CLT_MONSTER,	
	CLT_PROJECTILE, 

	CLT_ITEM,		
	
	CLT_GROUND,		
	CLT_WALL,		
	CLT_STAIR,		
	CLT_SAVE_POINT,	
	CLT_GAME_OVER,	
	CLT_NEXT,

	CLT_DETECT,		
	CLT_MONSTER_ATTACK,
	CLT_FINAL_BOSS_SLASH,
	CLT_PLAYER_ATTACK,	
	CLT_PLAYER_SKILL,

	CLT_STRUCTURE,	//  예. 짚라인 버튼
	CLT_STRUCTURE_DETECT, // 예. 짚라인
	CLT_STRUCTURE_COLLISION,	// 충돌 처리 필요

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
	// Title Scene
	Title,
	SelectStart,

	// Game Scene
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

enum class ZipLineRenderType
{
	None,	// 대각선 - 그리지 않음
	Line,	// 직선 - 그림
};

enum class SlashWaveType
{
	W,
	H,
};

enum class BreakingWallType
{
	Normal,
	Short,
	Long,
};