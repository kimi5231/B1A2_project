#include "pch.h"
#include "DialogueComponent.h"
#include "Dialogue.h"
#include "Actor.h"
#include "FlipbookActor.h"
#include "Flipbook.h"

DialogueComponent::DialogueComponent()
{
}

DialogueComponent::~DialogueComponent()
{
}

void DialogueComponent::BeginPlay()
{
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

	// �ؽ�Ʈ ���� ���� ������
	SIZE textSize;
	::GetTextExtentPoint32(hdc, event.begin()->speech.c_str(), (event.begin()->speech).length(), &textSize);

	// Dialogue ��ġ ����
	Vec2 ownerPos = _owner->GetPos();
	Vec2 pos = { ownerPos.x - (float)textSize.cx / 2, ownerPos.y - (float)size.y / 2 - textSize.cy };

	// ��Ʈ ����
	HFONT hfont = CreateFont(
		-20,
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

	Utils::DrawString(hdc, pos, event.begin()->speech);

	::SelectObject(hdc, oldFont);
	::DeleteObject(hfont);
}