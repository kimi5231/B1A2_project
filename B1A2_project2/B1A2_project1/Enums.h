#pragma once

#include "Enum.pb.h"

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
	CLT_STRUCTURE_COLLISION,

	CLT_NONE,		
};

// Player Direction
using Dir = Protocol::DIR_TYPE;

#define DIR_LEFT	Dir::DIR_TYPE_LEFT
#define DIR_RIGHT	Dir::DIR_TYPE_RIGHT
#define DIR_UP		Dir::DIR_TYPE_UP
#define DIR_DOWN	Dir::DIR_TYPE_DOWN

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

// Object State
using ObjectState = Protocol::OBJECT_STATE_TYPE;

#define IDLE				ObjectState::OBJECT_STATE_TYPE_IDLE
#define MOVE				ObjectState::OBJECT_STATE_TYPE_MOVE
#define DUCK_DOWN			ObjectState::OBJECT_STATE_TYPE_DUCK_DOWN
#define DUCK_DOWN_MOVE		ObjectState::OBJECT_STATE_TYPE_DUCK_DOWN_MOVE
#define JUMP				ObjectState::OBJECT_STATE_TYPE_JUMP
#define CLOSE_ATTACK		ObjectState::OBJECT_STATE_TYPE_CLOSE_ATTACK
#define LONG_ATTACK			ObjectState::OBJECT_STATE_TYPE_LONG_ATTACK
#define LONG_ATTACK_LENGTH	ObjectState::OBJECT_STATE_TYPE_LONG_ATTACK_LENGTH
#define LONG_ATTACK_WIDTH	ObjectState::OBJECT_STATE_TYPE_LONG_ATTACK_WIDTH
#define THRUST				ObjectState::OBJECT_STATE_TYPE_THRUST
#define BACK_STEP			ObjectState::OBJECT_STATE_TYPE_BACK_STEP
#define SLASH_WAVE			ObjectState::OBJECT_STATE_TYPE_SLASH_WAVE
#define SKILL_READY			ObjectState::OBJECT_STATE_TYPE_SKILL_READY
#define SKILL_WAITING		ObjectState::OBJECT_STATE_TYPE_SKILL_WAITING
#define SKILL_END			ObjectState::OBJECT_STATE_TYPE_SKILL_END
#define HANG				ObjectState::OBJECT_STATE_TYPE_HANG
#define RELEASE				ObjectState::OBJECT_STATE_TYPE_RELEASE
#define HIT					ObjectState::OBJECT_STATE_TYPE_HIT
#define DEAD				ObjectState::OBJECT_STATE_TYPE_DEAD
#define CHASE				ObjectState::OBJECT_STATE_TYPE_CHASE
#define ROAMING				ObjectState::OBJECT_STATE_TYPE_ROAMING
#define DASH				ObjectState::OBJECT_STATE_TYPE_DASH
#define RETURN				ObjectState::OBJECT_STATE_TYPE_RETURN
#define RETURN_IDLE			ObjectState::OBJECT_STATE_TYPE_RETURN_IDLE
#define PROJECTILE_FALL		ObjectState::OBJECT_STATE_TYPE_PROJECTILE_FALL
#define CRYSTAL_CREATION	ObjectState::OBJECT_STATE_TYPE_CRYSTAL_CREATION
#define MONSTER_CREATION	ObjectState::OBJECT_STATE_TYPE_MONSTER_CREATION
#define TELEPORT			ObjectState::OBJECT_STATE_TYPE_TELEPORT
#define CUT_SEVERELY		ObjectState::OBJECT_STATE_TYPE_CUT_SEVERELY
#define ON					ObjectState::OBJECT_STATE_TYPE_ON
#define ON2					ObjectState::OBJECT_STATE_TYPE_ON2
#define READY				ObjectState::OBJECT_STATE_TYPE_READY
#define OFF					ObjectState::OBJECT_STATE_TYPE_OFF

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