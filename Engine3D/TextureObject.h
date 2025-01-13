#pragma once
#include "ShapeObject.h"
#include "BitmapHandler.h"

class TextureObject:public ShapeObject
{
    void draw();
    virtual void draw_w_texture(const float cube_vert[], const float cube_norm[], const unsigned char cube_ind[],const float cube_texc[]) = 0;
    void update() override;
    void translate() override;
    void rotate() override;
    void scale() override;


};

