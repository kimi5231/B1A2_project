#pragma once

class SoundManager
{
	DECLARE_SINGLE(SoundManager);

	~SoundManager();

public:
	void Init(HWND hwnd);

	void Play(const std::wstring& key, bool loop = false);

	LPDIRECTSOUND GetSoundDevice() { return _soundDevice; }

private:
	LPDIRECTSOUND _soundDevice = nullptr; // ���� ī��
};

