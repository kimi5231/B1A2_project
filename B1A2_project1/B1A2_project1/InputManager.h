#pragma once
// InputManager : Ű����, ���콺 �Է��� ó���ϴ� �Ŵ���

enum class KeyType	// Ű ��ư 
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

enum class KeyState		// Ű ����
{
	None,
	Press,
	Down,
	Up,

	End		// KeyState�� ����
};

enum    // ���� ����ϰ� ����
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

	// ������ ���� ��
	bool GetButton(KeyType key) { return GetState(key) == KeyState::Press; }

	// �� ó�� ������ ��
	bool GetButtonDown(KeyType key) { return GetState(key) == KeyState::Down; }

	// �� ó�� �����ٰ� �� ��
	bool GetButtonUp(KeyType key) { return GetState(key) == KeyState::Up; }

	POINT GetMousePos() { return _mousePos; }

private:
	KeyState GetState(KeyType key) { return _states[static_cast<uint8>(key)]; }

private:
	HWND _hwnd = 0;
	std::vector<KeyState> _states;
	POINT _mousePos;
};

