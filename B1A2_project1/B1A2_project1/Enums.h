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
	LAYER_OBJECT,
	LAYER_UI,

	LAYER_MAXCOUNT
};

// ������ â ũ��
enum class WinSize
{
	HD,		// 1280*720(Default)
	FullScreen,
};

// �浹
enum class ColliderType
{
	Box,
	Sphere,
};

enum COLLISION_LAYER_TYPE : uint8
{
	CLT_OBJECT,		// 0
	CLT_GROUND,		// 1
	CLT_WALL,		// 2
};

// �÷��̾� ����
enum Dir
{
	DIR_LEFT,
	DIR_RIGHT,
};