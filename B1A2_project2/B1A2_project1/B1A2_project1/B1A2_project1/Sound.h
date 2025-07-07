#pragma once
#include "ResourceBase.h"
#include <fmod.hpp>
#include <filesystem>
#include <string>

class Sound : public ResourceBase
{
public:
	Sound();
	virtual ~Sound();

	bool Load(const std::filesystem::path& fullPath, FMOD::System* system, SoundType type);
	void Play(bool loop = false);
	void Stop();

private:
	virtual void LoadFile(const std::wstring& path) override {}
	virtual void SaveFile(const std::wstring& path) override {}

private:
	FMOD::Sound* _sound = nullptr;  // FMOD »ç¿îµå °´Ã¼
	FMOD::Channel* _channel = nullptr;  // FMOD Ã¤³Î °´Ã¼
};

