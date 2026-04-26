#pragma once

class Timer
{
public:
    Timer();
    ~Timer();

    void Update();

public:
    float GetDeltaTime() const { return _deltaTime; }

private:
    std::chrono::steady_clock::time_point _previousTime;
    float _deltaTime;
};