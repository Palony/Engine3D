#pragma once
#include "TextureObject.h"

class Cube:public TextureObject {
public:
    Cube();
    void draw(const float cube_vert[], const float cube_norm[], const float cube_cols[], const unsigned char cube_ind[]);
    void draw_w_texture(const float cube_vert[], const float cube_norm[], const unsigned char cube_ind[],const float cube_texc[]);
    void translate(float tx, float ty, float tz);
    void rotate(float angle, float x, float y, float z);
    void scale(float sx, float sy, float sz);
    void resetTransform();

    BitmapHandler bt;
    GLuint TexID[3];

private:
    glm::mat4 transformationMatrix;
};


