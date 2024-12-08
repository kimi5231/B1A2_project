#include "pch.h"
#include "DialogueManager.h"
#include "Dialogue.h"
#include "Actor.h"
#include "Player.h"
#include "DialogueComponent.h"
#include "TimeManager.h"

DialogueManager::~DialogueManager()
{
	SAFE_DELETE(_dialogue);

	for (Actor* actor : _actors)
		SAFE_DELETE(actor);
	_actors.clear();

	_event.clear();
}

void DialogueManager::Init()
{
	_isDialogue = false;
}

void DialogueManager::Update()
{
	if (!_isDialogue)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	for (Actor* actor : _actors)
	{
		// ��翡 �´� ��ü ã��
		if (_event[_eventCount].speakerID == actor->GetID())
		{
			// Actor Type�� ���� ���� �߰� ����
			if (dynamic_cast<Player*>(actor))
			{
				// Actor Setting
				Player* player = dynamic_cast<Player*>(actor);
				player->SetState(static_cast<PlayerState>(_event[_eventCount].state));
				player->SetDir(static_cast<Dir>(_event[_eventCount].dir));
				// DialogueComponent Setting
				DialogueComponent* component = player->GetDialogue();
				component->SetShowDialogue(true);
				component->SetSpeech(_event[_eventCount].speech);
			}


			// ���� ���� �̵�
			if (_sumTime >= 2.0)
			{
				_eventCount++;
				_sumTime = 0.f;
			}
			
			// ��ȭ ����
			if (_eventCount == _event.size())
				EndDialogue();

			break;
		}
	}
	
}

void DialogueManager::StartDialogue(const std::wstring& eventName, const std::vector<Actor*>& actors)
{
	_event = _dialogue->GetEvent(eventName);
	_actors = actors;

	_isDialogue = true;
}

void DialogueManager::EndDialogue()
{
	for (Actor* actor : _actors)
	{
		DialogueComponent* component = actor->GetDialogue();
		component->SetShowDialogue(false);
	}

	_isDialogue = false;
}