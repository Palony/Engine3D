#pragma once
#include "UpdatableObject.h"
class DrawableObject :public UpdatableObject
{
	virtual void draw() = 0;
};