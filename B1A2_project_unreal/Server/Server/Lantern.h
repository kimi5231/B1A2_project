#pragma once
#include "Tool.h"

class Room;

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
    void SetOwnerRoom(Room* room) { _ownerRoom = room; }

private:
    bool _isOn = false;
    unsigned char _battery ;
    unsigned char _currnetBattery ;
    unsigned char _range;
    float _angle;
    float _sumTime;

    Room* _ownerRoom;
};