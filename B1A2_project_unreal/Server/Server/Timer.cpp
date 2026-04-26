#include "pch.h"
#include "Timer.h"

Timer::Timer()
{
    _previousTime = std::chrono::steady_clock::now();
}

Timer::~Timer()
{
}

void Timer::Update()
{
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> frameTime = currentTime - _previousTime;
    _deltaTime = frameTime.count();
    _previousTime = currentTime;
}