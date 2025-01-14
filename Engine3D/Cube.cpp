#include "Cube.h"
#include <iostream>

Cube::Cube() {
  
    transformationMatrix = glm::mat4(1.0f);
}

void Cube::draw(const float cube_vert[], const float cube_norm[], const float cube_cols[], const unsigned char cube_ind[])
{



    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(transformationMatrix));



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



    glPopMatrix();
    glutSwapBuffers();
}

void Cube::draw_w_texture(const float obj_vert[], const float obj_norm[], const unsigned char obj_ind[], const float obj_texc[])
{




    //// Szeœcian z lewej tekstura #0:
    glBindTexture(GL_TEXTURE_2D, TexID[0]);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, obj_ind);





    glutSwapBuffers();

}



void Cube::translate(float tx, float ty, float tz) {
   
    transformationMatrix = glm::translate(glm::vec3(tx, ty, tz)) * transformationMatrix;
    
}

void Cube::rotate(float angle, float x, float y, float z) {
    
    transformationMatrix = glm::rotate(glm::radians(angle), glm::vec3(x, y, z)) * transformationMatrix;
    
}

void Cube::scale(float sx, float sy, float sz) {
    
    transformationMatrix = glm::scale(glm::vec3(sx, sy, sz)) * transformationMatrix;
  
}

void Cube::resetTransform() {
    
    transformationMatrix = glm::mat4(1.0f);
    
}
