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
	CLT_ITEM,		// 1
	CLT_GROUND,		// 2
	CLT_WALL,		// 3
};


// �÷��̾� ����
enum Dir
{
	DIR_LEFT,
	DIR_RIGHT,
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

// Item ����
enum class ItemType
{
	Pencil,
	Match,
	Key,
};

// F_key 
enum class FKeyState
{
	Hidden,
	Show,
};