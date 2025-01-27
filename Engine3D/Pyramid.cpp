#include "pyramid.h"

Pyramid::Pyramid()
{
    transformationMatrix = glm::mat4(1.0f);
}

void Pyramid::draw(const float pryamid_vert[], const float pryamid_norm[], const float pyramid_cols[], const unsigned char pyramid_ind[])
{
    glMatrixMode(GL_MODELVIEW);
 
    glMultMatrixf(glm::value_ptr(transformationMatrix));


    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, pryamid_vert);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, pryamid_norm);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, pyramid_cols);



    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_BYTE, pyramid_ind);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

  
}

void Pyramid::translate(float tx, float ty, float tz)
{
    transformationMatrix = glm::translate(glm::vec3(tx, ty, tz)) * transformationMatrix;
}

void Pyramid::rotate(float angle, float x, float y, float z)
{
    transformationMatrix = glm::rotate(glm::radians(angle), glm::vec3(x, y, z)) * transformationMatrix;

}

void Pyramid::scale(float sx, float sy, float sz)
{
    transformationMatrix = glm::scale(glm::vec3(sx, sy, sz)) * transformationMatrix;
}
void Pyramid::resetTransform() {

    transformationMatrix = glm::mat4(1.0f);

}