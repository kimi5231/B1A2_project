#pragma once
// InputManager : 키보드, 마우스 입력을 처리하는 매니저

enum class KeyType	// 키 버튼 
{
	LeftMouse = VK_LBUTTON,
	RightMouse = VK_RBUTTON,

	Up = VK_UP,
	DOWN = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,
	SpaceBar = VK_SPACE,
	Esc = VK_ESCAPE,
	Tab = VK_TAB,
	LeftAlt = VK_LMENU,
	LeftCtrl = VK_LCONTROL,
	LeftShift = VK_LSHIFT,

	KEY_1 = '1',
	KEY_2 = '2',

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	Q = 'Q',
	E = 'E',
	F = 'F'
};

enum class KeyState		// 키 상태
{
	None,
	Press,
	Down,
	Up,

	End		// KeyState의 개수
};

enum    // 개수 깔끔하게 정리
{
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<int32>(KeyState::End)
};

class InputManager
{
	DECLARE_SINGLE(InputManager);

public:
	void Init(HWND hwnd);
	void Update();

	// 누르고 있을 때
	bool GetButton(KeyType key) { return GetState(key) == KeyState::Press; }

	// 맨 처음 눌렀을 때
	bool GetButtonDown(KeyType key) { return GetState(key) == KeyState::Down; }

	// 맨 처음 눌렀다가 땔 때
	bool GetButtonUp(KeyType key) { return GetState(key) == KeyState::Up; }

	POINT GetMousePos() { return _mousePos; }

private:
	KeyState GetState(KeyType key) { return _states[static_cast<uint8>(key)]; }

private:
	HWND _hwnd = 0;
	std::vector<KeyState> _states;
	POINT _mousePos;
};

