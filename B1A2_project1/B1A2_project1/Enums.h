#pragma once

enum class SceneType
{
	None,
	TitleScene,	// Ÿ��Ʋ ��
	SettingScene, // ���� ��
	GameScene,	// �ΰ��� ��
	DevScene,	// ���� ��
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

// �浹
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

	CLT_STRUCTURE,	// 14 - ��. ¤���� ��ư
	CLT_STRUCTURE_DETECT, // 15 - ��. ¤����

	CLT_NONE,		
};

// �÷��̾� ����
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
	Idle,	// ���
	Move,	// �޸���
	DuckDown,	// ���̱�
	DuckDownMove,	// ���̸鼭 �޸���
	Jump,	// ����
	CloseAttack,	// �⺻ ����
	LongAttack,
	LongAttackLength,
	LongAttackWidth,
	Thrust,		// ���
	BackStep,	// �齺��
	SlashWave,	// �˱� ������
	SkillReady,	// ��ų
	SkillWaiting,
	SkillEnd, 
	Hang,	// �Ŵ޸���
	Release,	// ����
	Hit,	// �ǰ�
	Dead,	// ���
	Chase,	// ����
	Roaming,	// ��ȸ
	Dash,	// �뽬
	Return,		// ����
	ReturnIdle,		// ���� ���(�����ϱ� �� ����ϴ� ����)
	ProjectileFall,
	CrystalCreation,
	MonsterCreation,
	Teleport,
	CutSeverely,
	On,		// ������
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
	None,	// �밢�� - �׸��� ����
	Line,	// ���� - �׸�
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