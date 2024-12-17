#pragma once
#include "ShapeObject.h"

class Cube:public ShapeObject {
public:
    Cube();
    void draw(const float cube_vert[], const float cube_norm[], const float cube_cols[], const unsigned char cube_ind[]);
    void translate(float tx, float ty, float tz);
    void rotate(float angle, float x, float y, float z);
    void scale(float sx, float sy, float sz);
    void resetTransform();

private:
    glm::mat4 transformationMatrix;
};


