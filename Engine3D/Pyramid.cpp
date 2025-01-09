#include "pyramid.h"

Pyramid::Pyramid()
{
    transformationMatrix = glm::mat4(1.0f);
}

void Pyramid::draw(const float pryamid_vert[], const float pryamid_norm[], const float pyramid_cols[], const unsigned char pyramid_ind[])
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(transformationMatrix));


    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, pryamid_vert);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, pryamid_norm);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, pyramid_cols);



    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, pyramid_ind);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glPopMatrix();
}

void Pyramid::translate()
{
}

void Pyramid::rotate()
{
}

void Pyramid::scale()
{
}