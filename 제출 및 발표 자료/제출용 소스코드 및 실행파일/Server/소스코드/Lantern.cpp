#include "pch.h"
#include "Lantern.h"
#include "Global.h"
#include "Session.h"
#include "Room.h"

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
		_sumTime += _ownerRoom->GetUpdateRoomTime();
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

	// Broadcast
	for (auto& p : _ownerRoom->GetPlayers())
	{
		if (!p->GetClient())
			continue;

		g_network->SendTurnOnLanternPacket(dynamic_cast<Lantern*>(this), _ownerID, p->GetClient());
	}
}

void Lantern::TurnOff()
{
	_isOn = false;
	_sumTime = 0.f;

	// Broadcast
	for (auto& p : _ownerRoom->GetPlayers())
	{
		if (!p->GetClient())
			continue;

		g_network->SendTurnOffLanternPacket(dynamic_cast<Lantern*>(this), _ownerID, p->GetClient());
	}
}