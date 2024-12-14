#pragma once
#include "DrawableObject.h"
#include "TransformableObject.h"


class ShapeObject :public DrawableObject, public TransformableObject
{
    void draw();
    void update() override;
    void translate() override;
    void rotate() override;
    void scale() override;
};