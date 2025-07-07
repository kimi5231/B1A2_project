#include "pch.h"
#include "Window.h"
#include "ResourceManager.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "TimeManager.h"

Window::Window()
{
	// Flipbook
	_flipbookOff = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_WindowOff");
	_flipbookOn = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_WindowOn");

	// Collider
	{
		// Structure
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_STRUCTURE);

			collider->AddCollisionFlagLayer(CLT_PLAYER);
			
			collider->SetSize({ 280, 120 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}
}

Window::~Window()
{
}

void Window::BeginPlay()
{
	Super::BeginPlay();

	SetState(OFF);
}

void Window::Tick()
{
	Super::Tick();
}

void Window::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Window::TickOn()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	static float sumTime = 0.f;
	sumTime += deltaTime;

	if (sumTime >= _flickeringDuration)
	{
		SetState(OFF);

		sumTime = 0.f;
	}
}

void Window::TickOff()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	static float sumTime = 0.f;
	sumTime += deltaTime;

	if (sumTime >= _flickeringCycle)
	{
		SetState(ON);

		sumTime = 0.f;
	}
}

void Window::UpdateAnimation()
{
	switch (_info.state())
	{
	case ON:
		SetFlipbook(_flipbookOn);
		break;
	case OFF:
		SetFlipbook(_flipbookOff);
		break;
	}
}

void Window::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
}

void Window::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
