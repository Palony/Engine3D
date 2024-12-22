#ifndef LIGHTING_H
#define LIGHTING_H

#include <GL/glut.h>

struct PhongModel {
    GLfloat ambient[4];  // Sk³adowa œwiat³a otoczenia (RGBA)
    GLfloat diffuse[4];  // Sk³adowa œwiat³a rozproszonego (RGBA)
    GLfloat specular[4]; // Sk³adowa œwiat³a odbitego (RGBA)
    GLfloat shininess;   // Wspó³czynnik po³ysku
};

class Light {
public:
    GLfloat position[4];     // Pozycja œwiat³a (wspó³rzêdne 3D + typ œwiat³a: kierunkowe/punktowe)
    GLfloat attenuation[3];  // T³umienie œwiat³a: sta³e, liniowe, kwadratowe

    PhongModel phong;        // Parametry Phonga

    Light();
    void enableLight(GLenum lightID); // W³¹czenie œwiat³a OpenGL
};

#endif // LIGHTING_H
