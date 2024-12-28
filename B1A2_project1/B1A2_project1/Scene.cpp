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

	// * panel ���� �ڵ� �ۼ� �ʿ�
}

void Scene::Init()
{
	if (_panel)
		_panel->BeginPlay();

	for (const std::vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			actor->BeginPlay();
}

void Scene::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// �Ÿ� = �ð� * �ӵ�
	for (const std::vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			actor->Tick();

	if (_panel)
		_panel->Tick();
}

void Scene::Render(HDC hdc)
{
	for (const std::vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			actor->Render(hdc);

	if (_panel)
		_panel->Render(hdc);
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
