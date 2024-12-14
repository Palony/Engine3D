#pragma once
#include "UpdatableObject.h"

class TransformableObject :public UpdatableObject
{
	virtual void translate() = 0;
	virtual void rotate() = 0;
	virtual void scale() = 0;

};
