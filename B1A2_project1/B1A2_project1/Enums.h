#pragma once

enum class SceneType
{
	None,
	TitleScene,	// Ÿ��Ʋ ��
	SettingScene, // ���� ��
	GameScene,	// �ΰ��� ��
	DevScene,	// ���� ��
	TestScene,
};

enum LAYER_TYPE
{
	LAYER_BACKGROUND,
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