#pragma once
#include "ShapeObject.h"

class Cube:public ShapeObject {
public:
    void draw(const float cube_vert[], const float cube_norm[], const float cube_cols[], const unsigned char cube_ind[]);
    void update() override;
    void translate() override;
    void rotate() override;
    void scale() override;
};


