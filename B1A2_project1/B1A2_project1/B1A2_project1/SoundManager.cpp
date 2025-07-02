#include "pch.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "Sound.h"

SoundManager::~SoundManager()
{
	StopAll();

	for (auto& pair : _sounds)
	{
		delete pair.second;
	}
	_sounds.clear();

	if (_system)
	{
		_system->release(); // FMOD 시스템 해제
		_system = nullptr;
	}
}

void SoundManager::Init(HWND hwnd)
{
	FMOD_RESULT result = FMOD::System_Create(&_system);
	if (result != FMOD_OK)
	{
		::MessageBox(NULL, L"FMOD system creation failed", L"", MB_OK);
		return;
	}

	result = _system->init(512, FMOD_INIT_NORMAL, nullptr);
	if (result != FMOD_OK)
	{
		::MessageBox(NULL, L"FMOD system initialization failed", L"", MB_OK);
		return;
	}
}

void SoundManager::Play(const std::wstring& key, SoundType type, bool loop)
{
	//auto iter = _sounds.find(key);
	//if (iter == _sounds.end())
	//{
	//	// 사운드가 없는 경우 에러 출력 후 종료
	//	::MessageBox(NULL, L"Sound not found", L"", MB_OK);
	//	return;
	//}

	_sounds[key]->Play(loop);
}

void SoundManager::Stop(const std::wstring& key)
{
	auto iter = _sounds.find(key);
	if (iter != _sounds.end())
	{
		iter->second->Stop();
	}
}

void SoundManager::StopAll()
{
	for (auto& pair : _sounds)
	{
		pair.second->Stop();
	}
}
