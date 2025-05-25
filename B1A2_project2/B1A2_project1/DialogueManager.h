#pragma once
#include "Dialogue.h"

class Actor;
class GameObject;
class DialogueComponent;

// Actor들의 대화를 관리하는 클래스
class DialogueManager
{
public:
	DECLARE_SINGLE(DialogueManager);

	~DialogueManager();

public:
	void Init();
	void Update();

public:
	void SetDialogue(Dialogue* dialogue) { _dialogue = dialogue; }
	bool GetIsDialouge() { return _isDialogue; }

public:
	void StartDialogue(const std::wstring& eventName, const std::vector<Actor*>& actors);
	void EndDialogue();

	void SetSpeech();

	void StartMove(GameObject* object);
	void EndMove();
	void Move();

private:
	Dialogue* _dialogue{};

	std::vector<Line> _event;
	int32 _LineCount = 0;
	std::vector<Actor*> _actors;
	DialogueComponent* _currentComponent;
	
	bool _isDialogue = false;

	bool _isMove = false;
	GameObject* _movingObject;

	float _sumTime = 0.f;
};

