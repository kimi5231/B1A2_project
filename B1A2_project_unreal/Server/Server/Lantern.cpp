#include "pch.h"
#include "Lantern.h"
#include "Global.h"

Lantern::Lantern(ItemType itemType)
	: Tool(itemType)
{
	_battery = 180;
	_currnetBattery = _battery;
	_range = 300;
	_angle = 35.f;
}

Lantern::~Lantern()
{
}

void Lantern::Update()
{
	/*if(_isOn)
	{
		_currnetBattery--;

		if (_currnetBattery == 0)
			TurnOff();
	}*/
}

void Lantern::TurnOn()
{
	_isOn = true;
	g_framework->SendTurnOnLanternPacket(dynamic_pointer_cast<Lantern>(shared_from_this()), _ownerID, true);
}

void Lantern::TurnOff()
{
	_isOn = false;
	g_framework->SendTurnOffLanternPacket(dynamic_pointer_cast<Lantern>(shared_from_this()), _ownerID, true);
}