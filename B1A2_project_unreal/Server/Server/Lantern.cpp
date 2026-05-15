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
	_sumTime = 0.f;
}

Lantern::~Lantern()
{
}

void Lantern::Update()
{
	if(_isOn)
	{
		_sumTime += g_timer->GetDeltaTime();
		if (_sumTime >= 1.f)
		{
			_sumTime = 0.f;
			_currnetBattery--;
			
			if (_currnetBattery == 0)
				TurnOff();
		}
	}
}

void Lantern::TurnOn()
{
	_isOn = true;
	_sumTime = 0.f;
	//g_framework->SendTurnOnLanternPacket(dynamic_pointer_cast<Lantern>(shared_from_this()), _ownerID, true);
}

void Lantern::TurnOff()
{
	_isOn = false;
	_sumTime = 0.f;
	//g_framework->SendTurnOffLanternPacket(dynamic_pointer_cast<Lantern>(shared_from_this()), _ownerID, true);
}