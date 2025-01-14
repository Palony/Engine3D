#pragma once
#include "ShapeObject.h"
#include "BitmapHandler.h"

class TextureObject:public ShapeObject
{
    void draw();
    virtual void draw_w_texture(const float obj_vert[], const float obj_norm[], const unsigned char obj_ind[],const float obj_texc[]) = 0;
    void update() override;
    void translate() override;
    void rotate() override;
    void scale() override;


};

