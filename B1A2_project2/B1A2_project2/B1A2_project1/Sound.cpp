#include "pch.h"
#include "Sound.h"
#include "SoundManager.h"

Sound::Sound() : _sound(nullptr), _channel(nullptr) 
{

}

Sound::~Sound()
{
	if (_sound)
	{
		_sound->release();	// FMOD 리소스 해제
		_sound = nullptr;
	}
}

bool Sound::Load(const std::filesystem::path& fullPath, FMOD::System* system, SoundType type)
{
    if (!system || fullPath.extension() != L".wav")
    {
        ::MessageBox(NULL, L"Invalid system or file extension", L"", MB_OK);
        return false;
    }

    FMOD_MODE mode = FMOD_DEFAULT;

    switch (type)
    {
    case SoundType::BGM:
        mode = FMOD_LOOP_NORMAL | FMOD_2D; // 배경음악은 반복 재생
        break;

    case SoundType::Normal:
        mode = FMOD_LOOP_OFF | FMOD_2D; // 일반 사운드는 1회 재생
        break;

    default:
        ::MessageBox(NULL, L"알 수 없는 사운드 타입", L"", MB_OK);
        return false;
    }

    // FMOD 시스템에서 사운드 로드
    FMOD_RESULT result = system->createSound(fullPath.string().c_str(), mode, nullptr, &_sound);
    if (result != FMOD_OK)
    {
        ::MessageBox(NULL, L"사운드 파일 로드 실패", L"", MB_OK);
        return false;
    }

    return true;
}

void Sound::Play(bool loop)
{
    if (_sound)
    {
        if (loop)
            _sound->setMode(FMOD_LOOP_NORMAL);
        else
            _sound->setMode(FMOD_LOOP_OFF);

        FMOD::System* system = nullptr;
        _sound->getSystemObject(&system);

        FMOD_RESULT result = system->playSound(_sound, nullptr, false, &_channel);
        if (result != FMOD_OK)
        {
            ::MessageBox(NULL, L"FMOD play failed", L"", MB_OK);
        }
    }
}

void Sound::Stop()
{
    if (_channel)
    {
        _channel->stop();
    }
}

