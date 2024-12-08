#include "pch.h"
#include "DialogueComponent.h"
#include "Dialogue.h"
#include "Actor.h"
#include "FlipbookActor.h"
#include "Flipbook.h"
#include "TimeManager.h"
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
	_fontSize = 20;
}

void DialogueComponent::TickComponent()
{
	if (_state == DialogueState::Hidden || _state == DialogueState::Wait)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_currentSpeech == _speech)
	{
		_speechCount = 0;
		_state = DialogueState::Wait;
	}

	if (_sumTime >= 0.5f)
	{
		_currentSpeech += _speech[_speechCount++];
		_sumTime = 0.f;
	}
}

void DialogueComponent::Render(HDC hdc)
{
	if (_state == DialogueState::Hidden)
		return;
	
	// owner ������ ��������
	FlipbookActor* owner = dynamic_cast<FlipbookActor*>(_owner);
	Flipbook* flipbook = owner->GetFlipbook();
	const FlipbookInfo& info = flipbook->GetInfo();
	Vec2Int size = info.size;

	// ��Ʈ ����
	HFONT hfont = CreateFont(
		-_fontSize,
		0, 
		0, 
		0, 
		FW_NORMAL, 
		FALSE, 
		FALSE, 
		FALSE, 
		DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, 
		DEFAULT_PITCH | FF_SWISS, 
		L"�ձٸ��");

	// ��Ʈ ����
	HFONT oldFont = (HFONT)SelectObject(hdc, hfont);

	// ���� ����ȭ
	SetBkMode(hdc, TRANSPARENT);

	// �ؽ�Ʈ ��� ���� ������ ������
	Vec2Int rectSize = GetDialogueRectSize(hdc, _speech);

	// DialogueComponent ��ġ ����
	Vec2 ownerPos = _owner->GetPos();
	Vec2 pos = { ownerPos.x - (float)rectSize.x / 2, ownerPos.y - (float)size.y / 2 - rectSize.y };
	RECT rect = { pos.x, pos.y, pos.x + rectSize.x, pos.y + rectSize.y };

	Utils::DrawString(hdc, _currentSpeech, rect);

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
	// ���ڿ� ��Ʈ�� ����
	std::wistringstream wiss(str);

	std::wstring text;
	std::vector<std::wstring> texts;

	// ���๮�ڸ� �������� ���ڿ� �и�
	while (std::getline(wiss, text, L'\n'))
		texts.push_back(text);

	SIZE textSize;
	int32 max = 0;

	// ���� ���̰� �� ���ڿ� ���� �����ϱ�
	for (const std::wstring& text : texts)
	{
		::GetTextExtentPoint32(hdc, text.c_str(), text.length(), &textSize);
		if (max < textSize.cx)
			max = textSize.cx;
	}

	return Vec2Int{ max, (int32)texts.size() * _fontSize };
}