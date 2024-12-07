#include "pch.h"
#include "DialogueComponent.h"
#include "Dialogue.h"
#include "Actor.h"
#include "FlipbookActor.h"
#include "Flipbook.h"
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
}

void DialogueComponent::Render(HDC hdc)
{
	if (!_owner)
		return;
	
	// owner ������ ��������
	FlipbookActor* owner = dynamic_cast<FlipbookActor*>(_owner);
	Flipbook* flipbook = owner->GetFlipbook();
	const FlipbookInfo& info = flipbook->GetInfo();
	Vec2Int size = info.size;

	// �̺�Ʈ ��������
	std::vector<LineInfo>& event = _dialogue->GetEvent(L"test1");

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
	Vec2Int rectSize = GetDialogueRectSize(hdc, event.begin()->speech);

	// Dialogue ��ġ ����
	Vec2 ownerPos = _owner->GetPos();
	Vec2 pos = { ownerPos.x - (float)rectSize.x / 2, ownerPos.y - (float)size.y / 2 - rectSize.y };
	RECT rect = { pos.x, pos.y, pos.x + rectSize.x, pos.y + rectSize.y };

	Utils::DrawString(hdc, event.begin()->speech, rect);

	::SelectObject(hdc, oldFont);
	::DeleteObject(hfont);
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