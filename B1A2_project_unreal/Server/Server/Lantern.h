#pragma once
#include "Tool.h"

class Lantern : public Tool
{
public:
    Lantern(ItemType itemType);
    virtual ~Lantern();

public:
    virtual void Update();

public:
    void TurnOn();
    void TurnOff();

public:
	bool IsOn() { return _isOn; }
	unsigned char GetCurrentBattery() { return _currnetBattery; }
	unsigned char GetRange() { return _range; }
	float GetAngle() { return _angle; }

private:
    bool _isOn = false;
    unsigned char _battery ;
    unsigned char _currnetBattery ;
    unsigned char _range;
    float _angle;
};