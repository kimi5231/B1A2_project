#include "pch.h"
#include "Game.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "ValueManager.h"
#include "CollisionManager.h"
#include "DialogueManager.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_hdc = ::GetDC(hwnd);	// hwnd로 hdc 알 수 있는 함수

	// 상대 경로 path 알아내는 코드
	_resourcePath = std::filesystem::current_path().relative_path();
	std::filesystem::path _resourcePath = std::filesystem::current_path().parent_path().parent_path() / "B1A2_project2\\Resources";

	// 폰트 경로
	std::filesystem::path fullPath = _resourcePath / L"Font\\DungGeunMo.ttf";
	// 폰트 추가
	::AddFontResourceEx(fullPath.c_str(), FR_PRIVATE, NULL);

	// 더블 버퍼링 코드
	::GetClientRect(hwnd, &_rect);

	_hdcBack = ::CreateCompatibleDC(_hdc);	// hdc와 호환되는 DC 생성
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);	// hdc와 호환되는 비트맵 생성
	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack);	// DC와 BMP 연결
	::DeleteObject(prev);

	// 각 매니저들 Init
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(ResourceManager)->Init(hwnd, _resourcePath);
	GET_SINGLE(SoundManager)->Init(hwnd);
	GET_SINGLE(ValueManager)->Init(hwnd);
	GET_SINGLE(CollisionManager)->Init();
	GET_SINGLE(DialogueManager)->Init();

	GET_SINGLE(SceneManager)->ChangeScene(SceneType::DevScene);
}

void Game::Update()
{
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(SceneManager)->Update();
	GET_SINGLE(CollisionManager)->Update();
	GET_SINGLE(DialogueManager)->Update();
}

void Game::Render()
{
	uint32 fps = GET_SINGLE(TimeManager)->GetFps();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 윈도우 창 사이즈 얻어오기
	Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();

	// 창 사이즈가 변경됐는지 확인
	if ((_rect.right != winSize.x) || (_rect.bottom != winSize.y))
	{
		// 변경된 사이즈 저장
		_rect.right = winSize.x;
		_rect.bottom = winSize.y;
		// 기존 비트맵 해제
		HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, NULL);
		::DeleteObject(prev);
		// 변경된 사이즈에 맞춰 비트맵 재생성
		_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);
		// DC와 비트맵 연결
		(HBITMAP)::SelectObject(_hdcBack, _bmpBack);
	}

	GET_SINGLE(SceneManager)->Render(_hdcBack);

	//{
	//	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	//	std::wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
	//	Utils::DrawString(_hdcBack, str, Vec2Int{ 20, 10 });
	//}

	{
		std::wstring str = std::format(L"FPS({0}), DT({1})", fps, deltaTime);
		Utils::DrawString(_hdcBack, str, Vec2Int{ 550, 10 });
	}

	// Double Buffering
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY); // 비트 블릿 : 고속 복사
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}