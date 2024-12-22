#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glut.h>

class Material {
public:
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;

    Material();
    void applyMaterial();
};

#endif // MATERIAL_H
