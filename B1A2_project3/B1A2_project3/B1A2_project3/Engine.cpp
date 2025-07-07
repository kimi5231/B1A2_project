#include "pch.h"
#include "Engine.h"
// Manager
#include "InputManager.h"	
#include "TimeManager.h"
// API

void Engine::Init(const WindowInfo& info)
{
	_window = info;

	// 그려질 화면 크기를 설정
	_viewport = { 0, 0, static_cast<FLOAT>(info.width), static_cast<FLOAT>(info.height), 0.0f, 1.0f };
	_scissorRect = CD3DX12_RECT(0, 0, info.width, info.height);

	ResizeWindow(info.width, info.height);

	GET_SINGLE(InputManager)->Init(info.hwnd);
	GET_SINGLE(TimeManager)->Init();
}

void Engine::Update()
{
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(TimeManager)->Update();

	Render();
}

void Engine::Render()
{
	RenderBegin();

	RenderEnd();
}

void Engine::RenderBegin()
{
}

void Engine::RenderEnd()
{
}

void Engine::ResizeWindow(int32 width, int32 height)
{
	_window.width = width;
	_window.height = height;

	RECT rect = { 0, 0, width, height };
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	::SetWindowPos(_window.hwnd, 0, 100, 100, width, height, 0);
}
