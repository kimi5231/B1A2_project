#pragma once
#include "MonoBehaviour.h"

class Actor : public MonoBehaviour
{
public:
	Actor();
	virtual ~Actor();

	virtual void LateUpdate() override;
};

