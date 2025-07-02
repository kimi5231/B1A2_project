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
		_sound->release();	// FMOD ���ҽ� ����
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
        mode = FMOD_LOOP_NORMAL | FMOD_2D; // ��������� �ݺ� ���
        break;

    case SoundType::Normal:
        mode = FMOD_LOOP_OFF | FMOD_2D; // �Ϲ� ����� 1ȸ ���
        break;

    default:
        ::MessageBox(NULL, L"�� �� ���� ���� Ÿ��", L"", MB_OK);
        return false;
    }

    // FMOD �ý��ۿ��� ���� �ε�
    FMOD_RESULT result = system->createSound(fullPath.string().c_str(), mode, nullptr, &_sound);
    if (result != FMOD_OK)
    {
        ::MessageBox(NULL, L"���� ���� �ε� ����", L"", MB_OK);
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

