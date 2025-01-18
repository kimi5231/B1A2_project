#include "pch.h"
#include "Scene.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Panel.h"
#include "Actor.h"
#include "CollisionManager.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	GET_SINGLE(CollisionManager)->ClearColliders();

	for (const std::vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			SAFE_DELETE(actor);

	_actors->clear();

	// ���� ����Ʈ �����Ͱ� �ƴ϶� ���� ����
	// => Panel�� �ִ� Button�� ��� �߿� Panel�� ���� ����
	/*for (Panel* panel : _panels)
		SAFE_DELETE(panel);

	_panels.clear();*/
}

void Scene::Init()
{
	for (const std::vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			actor->BeginPlay();

	for (Panel* panel : _panels)
		panel->BeginPlay();
}

void Scene::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// �Ÿ� = �ð� * �ӵ�
	for (const std::vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			actor->Tick();

	for (Panel* panel : _panels)
		panel->Tick();
}

void Scene::Render(HDC hdc)
{
	for (const std::vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			actor->Render(hdc);

	for (Panel* panel : _panels)
		panel->Render(hdc);
}

void Scene::AddActor(Actor* actor)
{
	if (!actor)
		return;

	_actors[actor->GetLayer()].push_back(actor);
}

void Scene::RemoveActor(Actor* actor)
{
	if (!actor)
		return;

	std::vector<Actor*>& v = _actors[actor->GetLayer()];
	v.erase(std::remove(v.begin(), v.end(), actor), v.end());
}

void Scene::AddPanel(Panel* panel)
{
	if (!panel)
		return;

	_panels.push_back(panel);
}

void Scene::RemovePanel(Panel* panel)
{
	if (!panel)
		return;
	
	_panels.erase(std::remove(_panels.begin(), _panels.end(), panel), _panels.end());
}