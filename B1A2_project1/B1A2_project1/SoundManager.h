#pragma once
#include <fmod.hpp>
#include "Sound.h"	// SoundType ������ ��¿ �� ���� include ��

class SoundManager
{
	DECLARE_SINGLE(SoundManager);

	~SoundManager();

public:
	void Init(HWND hwnd);
	void Play(const std::wstring& key, SoundType type, bool loop = false);
	void Stop(const std::wstring& key);
	void StopAll();

	FMOD::System* GetSystem() const { return _system; }

private:
	FMOD::System* _system = nullptr; // FMOD �ý��� ��ü
	std::unordered_map<std::wstring, Sound*> _sounds; // �ε�� ���� �����
};

