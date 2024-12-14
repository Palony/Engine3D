#include "Cube.h"

void Cube::draw(const float cube_vert[], const float cube_norm[], const float cube_cols[], const unsigned char cube_ind[])
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, cube_vert);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, cube_norm);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, cube_cols);



    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, cube_ind);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Cube::update() 
{
}

void Cube::translate()
{
}

void Cube::rotate()
{
}

void Cube::scale()
{
}
