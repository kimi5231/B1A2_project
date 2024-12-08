#include "pch.h"
#include "DialogueManager.h"
#include "InputManager.h"
#include "Dialogue.h"
#include "Actor.h"
#include "Player.h"
#include "DialogueComponent.h"

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

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		if (_currentComponent->GetState() == DialogueState::Wait)
		{
			_eventCount++;

			if (_eventCount == _event.size())
				EndDialogue();
			else
				ChangeSpeech();
		}
		else if (_currentComponent->GetState() == DialogueState::Running)
		{
			const std::wstring& speech = _currentComponent->GetSpeech();
			_currentComponent->SetCurrentSpeech(speech);
		}
	}
}

void DialogueManager::StartDialogue(const std::wstring& eventName, const std::vector<Actor*>& actors)
{
	_event = _dialogue->GetEvent(eventName);
	_actors = actors;

	_isDialogue = true;

	ChangeSpeech();
}

void DialogueManager::EndDialogue()
{
	for (Actor* actor : _actors)
	{
		DialogueComponent* component = actor->GetDialogue();
		component->SetState(DialogueState::Hidden);
	}

	_eventCount = 0;

	_isDialogue = false;
}

void DialogueManager::ChangeSpeech()
{
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
				_currentComponent = player->GetDialogue();
				_currentComponent->SetState(DialogueState::Running);
				_currentComponent->SetSpeech(_event[_eventCount].speech);
			}

			continue;
		}

		// ��翡 �´� ��ü�� �ƴ� ��
		DialogueComponent* component = actor->GetDialogue();
		component->SetState(DialogueState::Hidden);
	}
}