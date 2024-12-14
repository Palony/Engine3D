#pragma once
#include "GameObject.h"
class UpdatableObject :public GameObject
{
private:

public:
	virtual void update() = 0;
};