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
	CLT_SAVE_POINT,	// 6
	CLT_GAME_OVER,	// 7

	CLT_DETECT,		// 8
	CLT_MONSTER_ATTACK,	// 9
	CLT_PLAYER_ATTACK,	// 10 

	CLT_STRUCTURE,	// 11 - ��. ¤���� ��ư
	CLT_STRUCTURE_DETECT, // 12 - ��. ¤����

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
	Thrust,		// ���
	BackStep,	// �齺��
	SlashWave,	// �˱� ������
	Skill,	// ��ų
	Hang,	// �Ŵ޸���
	Release,	// ����
	Hit,	// �ǰ�
	Dead,	// ���
	Chase,	// ����
	Roaming,	// ��ȸ
	Dash,	// �뽬
	Return,		// ����
	ReturnIdle,		// ���� ���(�����ϱ� �� ����ϴ� ����)
	On,		// ¤����
	Off,
};

enum class ZipLineType
{
	ZipLine,
	ZipLineWithButton,
};