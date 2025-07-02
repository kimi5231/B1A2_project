#pragma once
#include "Component.h"

class Dialogue;
class Sprite;

enum BUBBLE_TILE_SIZE
{
	CORNER_SIZEX = 7,
	CORNER_SIZEY = 6,
	WIDTH_SIZEX = 1,
	WIDTH_SIZEY = 6,
	HEIGHT_SIZEX = 7,
	HEIGHT_SIZEY = 1,
	TAIL_SIZEX = 14,
	TAIL_SIZEY = 15,
	TRIANGLE_SIZEX = 9,
	TRIANGLE_SIZEY = 13,
};

struct BubbleTile
{
	Sprite* sprite;
	Vec2 pos;
	Vec2Int size;
};

class DialogueComponent : public Component
{
	using Super = Component;
public:
	DialogueComponent();
	virtual ~DialogueComponent() override;

	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

public:
	void SetSpeech(const std::wstring& speech);
	const std::wstring& GetSpeech() { return _speech; }

	void SetCurrentSpeech(const std::wstring& speech) { _currentSpeech = speech; }

	void SetCurrentCutScene(const std::wstring& cutScene) { _currentCutScene = cutScene; }

	void SetState(DialogueState state) { _state = state; }
	DialogueState GetState() { return _state; }

	void SetType(DialogueType type) { _type = type; }
	DialogueType GetType() { return _type; }

	Vec2Int GetDialogueRectSize(HDC hdc, const std::wstring& str);

private:
	void PrintBubble(HDC hdc);
	void PrintCutScene(HDC hdc);

private:
	std::wstring _speech;
	std::wstring _currentSpeech;
	int32 _speechCount = 0;
	DialogueState _state = DialogueState::Hidden;
	DialogueType _type = DialogueType::Bubble;
	float _fontSize{};

	std::vector<BubbleTile> _cornerTiles;
	std::vector<BubbleTile> _widthTiles;
	std::vector<BubbleTile> _heightTiles;

	std::wstring _currentCutScene;

	float _sumTime = 0.f;
};

