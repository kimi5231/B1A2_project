#include "pch.h"
#include "DialogueComponent.h"
#include "Dialogue.h"
#include "Actor.h"
#include "FlipbookActor.h"
#include "Flipbook.h"
#include "Sprite.h"
#include "Texture.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "ValueManager.h"
#include <fstream>
#include <iostream>
#include <string>

DialogueComponent::DialogueComponent()
{
}

DialogueComponent::~DialogueComponent()
{
}

void DialogueComponent::BeginPlay()
{
	_fontSize = 20.f;
}

void DialogueComponent::TickComponent()
{
	if (_speech == L"")
		_state = DialogueState::Hidden;

	if (_state == DialogueState::Hidden || _state == DialogueState::Wait)
		return;

	if (_currentSpeech == _speech)
	{
		_speechCount = 0;
		_state = DialogueState::Wait;
		return;
	}

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= 0.1f)
	{
		_currentSpeech += _speech[_speechCount++];
		_sumTime = 0.f;
	}
}

void DialogueComponent::Render(HDC hdc)
{
	if (_state == DialogueState::Hidden)
		return;

	// 보정 변수 가져오기
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	// 폰트 생성
	HFONT hfont = Utils::MakeFont(_fontSize * winSizeAdjustmemt.y, L"DungGeunMo");

	// 폰트 선택
	HFONT oldFont = (HFONT)::SelectObject(hdc, hfont);

	// 텍스트 색깔 설정
	::SetTextColor(hdc, RGB(255, 255, 255));

	// 텍스트 배경 투명화
	::SetBkMode(hdc, TRANSPARENT);

	if(_type == DialogueType::Bubble)
		PrintBubble(hdc);
	else if(_type == DialogueType::CutScene)
		PrintCutScene(hdc);

	::SetTextColor(hdc, RGB(0, 0, 0));
	::SelectObject(hdc, oldFont);
	::DeleteObject(hfont);
}

void DialogueComponent::SetSpeech(const std::wstring& speech)
{
	_speech = speech;
	SetCurrentSpeech(L"");
}

Vec2Int DialogueComponent::GetDialogueRectSize(HDC hdc, const std::wstring& str)
{
	// 문자열 스트림 생성
	std::wistringstream wiss(str);

	std::wstring text;
	std::vector<std::wstring> texts;

	// 개행문자를 기준으로 문자열 분리
	while (std::getline(wiss, text, L'\n'))
		texts.push_back(text);

	SIZE textSize;
	int32 max = 0;

	// 가장 길이가 긴 문자열 길이 저장하기
	for (const std::wstring& text : texts)
	{
		::GetTextExtentPoint32(hdc, text.c_str(), text.length(), &textSize);
		if (max < textSize.cx)
			max = textSize.cx;
	}

	Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();

	return Vec2Int{ max, (int32)texts.size() * (int32)(_fontSize * ((float)winSize.y / (float)DefaultWinSizeY)) };
}

void DialogueComponent::PrintBubble(HDC hdc)
{
	// 보정 변수 가져오기
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();
	Vec2 cameraPosAdjustmemt = GET_SINGLE(ValueManager)->GetCameraPosAdjustment();

	// owner 사이즈 가져오기
	Vec2Int size;

	if (dynamic_cast<FlipbookActor*>(_owner))
	{
		FlipbookActor* owner = dynamic_cast<FlipbookActor*>(_owner);
		Flipbook* flipbook = owner->GetFlipbook();
		
		const FlipbookInfo& info = flipbook->GetInfo();
		size = info.size;
	}
	else
	{
		// flipbook이 없는 경우
		size = { 0, 0 };
	}

	// 텍스트 출력 범위 사이즈 얻어오기
	Vec2Int rectSize = GetDialogueRectSize(hdc, _speech);

	// DialogueComponent 위치 지정
	Vec2 ownerPos = _owner->GetPos() * winSizeAdjustmemt - cameraPosAdjustmemt;
	Vec2 pos = { (ownerPos.x - (float)rectSize.x / 2), (ownerPos.y - (((float)size.y / 2 + 21.f) * winSizeAdjustmemt.y) - (float)rectSize.y) };
	RECT rect = { pos.x, pos.y, pos.x + rectSize.x, pos.y + rectSize.y };

	// 말풍선 출력
	{
		// LeftTop
		{
			Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"DialogueCornerLeftTop");
			BubbleTile tile{ sprite, {pos.x - (CORNER_SIZEX * winSizeAdjustmemt.x),
				pos.y - (CORNER_SIZEY * winSizeAdjustmemt.y)},
				{CORNER_SIZEX + 1, CORNER_SIZEY + 1} };

			_cornerTiles.push_back(tile);
		}
		// RightTop
		{
			Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"DialogueCornerRightTop");
			BubbleTile tile{ sprite, {pos.x + rectSize.x,
				pos.y - (CORNER_SIZEY * winSizeAdjustmemt.y)},
				{CORNER_SIZEX, CORNER_SIZEY + 1} };

			_cornerTiles.push_back(tile);
		}
		// LeftBottom
		{
			Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"DialogueCornerLeftBottom");
			BubbleTile tile{ sprite, {pos.x - (CORNER_SIZEX * winSizeAdjustmemt.x),
				pos.y + rectSize.y},
				{CORNER_SIZEX + 1, CORNER_SIZEY} };

			_cornerTiles.push_back(tile);
		}
		// RightBottom
		{
			Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"DialogueCornerRightBottom");
			BubbleTile tile{ sprite, {pos.x + rectSize.x, pos.y + rectSize.y}, {CORNER_SIZEX, CORNER_SIZEY} };

			_cornerTiles.push_back(tile);
		}

		// WidthTop
		{
			Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"DialogueWidthTop");

			for (int32 i = 0; i < rectSize.x; ++i)
			{
				BubbleTile tile{ sprite, {pos.x + i * WIDTH_SIZEX,
					pos.y - (WIDTH_SIZEY * winSizeAdjustmemt.y)},
					{WIDTH_SIZEX, WIDTH_SIZEY + 1} };

				_widthTiles.push_back(tile);
			}
		}
		// WidthBottom
		{
			Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"DialogueWidthBottom");

			for (int32 i = 0; i < rectSize.x; ++i)
			{
				BubbleTile tile{ sprite, {pos.x + i * WIDTH_SIZEX,
					pos.y + rectSize.y},
					{WIDTH_SIZEX, WIDTH_SIZEY} };

				_widthTiles.push_back(tile);
			}
		}

		// HeightLeft
		{
			Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"DialogueHeightLeft");

			for (int32 i = 0; i < rectSize.y; ++i)
			{
				BubbleTile tile{ sprite, {pos.x - (HEIGHT_SIZEX * winSizeAdjustmemt.x),
					pos.y + i * HEIGHT_SIZEY},
					{HEIGHT_SIZEX + 1, HEIGHT_SIZEY} };

				_heightTiles.push_back(tile);
			}
		}
		// HeightRight
		{
			Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"DialogueHeightRight");

			for (int32 i = 0; i < rectSize.y; ++i)
			{
				BubbleTile tile{ sprite, {pos.x + rectSize.x,
					pos.y + i * HEIGHT_SIZEY},
					{HEIGHT_SIZEX, HEIGHT_SIZEY} };

				_heightTiles.push_back(tile);
			}
		}

		// Background
		Texture* background = GET_SINGLE(ResourceManager)->GetTexture(L"DialogueBackground");
		::TransparentBlt(hdc,
			pos.x,
			pos.y,
			rectSize.x,
			rectSize.y,
			background->GetDC(),
			0,
			0,
			background->GetSize().x,
			background->GetSize().y,
			background->GetTransparent());

		// Corner
		for (BubbleTile& tile : _cornerTiles)
		{
			::TransparentBlt(hdc,
				tile.pos.x,
				tile.pos.y,
				tile.size.x * winSizeAdjustmemt.x,
				tile.size.y * winSizeAdjustmemt.y,
				tile.sprite->GetDC(),
				tile.sprite->GetPos().x,
				tile.sprite->GetPos().y,
				tile.sprite->GetSize().x,
				tile.sprite->GetSize().y,
				tile.sprite->GetTransparent());
		}

		// Width
		for (BubbleTile& tile : _widthTiles)
		{
			::TransparentBlt(hdc,
				tile.pos.x,
				tile.pos.y,
				tile.size.x,
				tile.size.y * winSizeAdjustmemt.y,
				tile.sprite->GetDC(),
				tile.sprite->GetPos().x,
				tile.sprite->GetPos().y,
				tile.sprite->GetSize().x,
				tile.sprite->GetSize().y,
				tile.sprite->GetTransparent());
		}

		// Height
		for (BubbleTile& tile : _heightTiles)
		{
			::TransparentBlt(hdc,
				tile.pos.x,
				tile.pos.y,
				tile.size.x * winSizeAdjustmemt.x,
				tile.size.y,
				tile.sprite->GetDC(),
				tile.sprite->GetPos().x,
				tile.sprite->GetPos().y,
				tile.sprite->GetSize().x,
				tile.sprite->GetSize().y,
				tile.sprite->GetTransparent());
		}

		// Tail
		Texture* tail = GET_SINGLE(ResourceManager)->GetTexture(L"DialogueTail");
		::TransparentBlt(hdc,
			pos.x + (rectSize.x / 2) - ((WIDTH_SIZEX / 2) * winSizeAdjustmemt.x),
			pos.y + rectSize.y + ((WIDTH_SIZEY - 2) * winSizeAdjustmemt.y),
			TAIL_SIZEX * winSizeAdjustmemt.x,
			TAIL_SIZEY * winSizeAdjustmemt.y,
			tail->GetDC(),
			0,
			0,
			TAIL_SIZEX,
			TAIL_SIZEY,
			tail->GetTransparent());

		_cornerTiles.clear();
		_widthTiles.clear();
		_heightTiles.clear();
	}

	// 대사가 끝났음을 알리는 삼각형 출력
	if (_state == DialogueState::Wait)
	{
		Texture* triangle = GET_SINGLE(ResourceManager)->GetTexture(L"DialogueTriangle");
		::TransparentBlt(hdc,
			pos.x + rectSize.x + ((HEIGHT_SIZEX + 1) * winSizeAdjustmemt.x),
			pos.y + rectSize.y + ((WIDTH_SIZEY - TRIANGLE_SIZEY) * winSizeAdjustmemt.y),
			TRIANGLE_SIZEX * winSizeAdjustmemt.x,
			TRIANGLE_SIZEY * winSizeAdjustmemt.y,
			triangle->GetDC(),
			0,
			0,
			TRIANGLE_SIZEX,
			TRIANGLE_SIZEY,
			triangle->GetTransparent());
	}

	// 텍스트 출력
	Utils::DrawString(hdc, _currentSpeech, rect);
}

void DialogueComponent::PrintCutScene(HDC hdc)
{
	// 보정 변수 가져오기
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();

	// CutScene 출력
	{
		Texture* cutScene = GET_SINGLE(ResourceManager)->GetTexture(_currentCutScene);
		::TransparentBlt(hdc,
			0,
			0,
			cutScene->GetSize().x * winSizeAdjustmemt.x,
			cutScene->GetSize().y * winSizeAdjustmemt.y,
			cutScene->GetDC(),
			0,
			0,
			cutScene->GetSize().x,
			cutScene->GetSize().y,
			cutScene->GetTransparent());
	}

	// 텍스트 배경 출력
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, hBrush);

		Utils::DrawRect(hdc, { float(winSize.x / 2), float(560 * winSizeAdjustmemt.y) }, { winSize.x, static_cast<int32>(winSize.y / 4) });
	
		DeleteObject(hBrush);
	}

	// 텍스트 출력
	Vec2Int pos{ static_cast<int32>(100 * winSizeAdjustmemt.x), static_cast<int32>(560 * winSizeAdjustmemt.y) };
	Utils::DrawString(hdc, _currentSpeech, pos);
}