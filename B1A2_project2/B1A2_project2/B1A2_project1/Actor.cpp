#include "pch.h"
#include "Actor.h"
#include "Component.h"
#include "Collider.h"
#include "DialogueComponent.h"
#include "CollisionManager.h"

Actor::Actor()
{
}

Actor::~Actor()
{
	for (Component* component : _components)
	{
		if (dynamic_cast<Collider*>(component))
		{
			Collider* collider = dynamic_cast<Collider*>(component);
			GET_SINGLE(CollisionManager)->RemoveCollider(collider);
		}
		SAFE_DELETE(component);
	}
}

void Actor::BeginPlay()
{
	for (Component* component : _components)
	{
		component->BeginPlay();
	}
}

void Actor::Tick()
{
	for (Component* component : _components)
	{
		component->TickComponent();
	}
}

void Actor::Render(HDC hdc)
{
	for (Component* component : _components)
	{
		component->Render(hdc);
	}
}

void Actor::AddComponent(Component* component)
{
	if (!component)
		return;

	component->SetOwner(this);
	_components.push_back(component);
}

void Actor::RemoveComponent(Component* component)
{
	auto findIt = std::find(_components.begin(), _components.end(), component);
	if (findIt == _components.end())
		return;
	
	_components.erase(findIt);
}

Component* Actor::GetCollider()
{
	for (Component* component : _components)
	{
		if (dynamic_cast<Collider*>(component))
			return component;
	}

	return nullptr;
}

void Actor::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
}

void Actor::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}

DialogueComponent* Actor::GetDialogue()
{
	for (Component* component : _components)
	{
		if (dynamic_cast<DialogueComponent*>(component))
			return dynamic_cast<DialogueComponent*>(component);
	}

	return nullptr;
}
