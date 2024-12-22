#ifndef LIGHTING_H
#define LIGHTING_H

#include <GL/glut.h>

struct PhongModel {
    GLfloat ambient[4];  // Sk�adowa �wiat�a otoczenia (RGBA)
    GLfloat diffuse[4];  // Sk�adowa �wiat�a rozproszonego (RGBA)
    GLfloat specular[4]; // Sk�adowa �wiat�a odbitego (RGBA)
    GLfloat shininess;   // Wsp�czynnik po�ysku
};

class Light {
public:
    GLfloat position[4];     // Pozycja �wiat�a (wsp�rz�dne 3D + typ �wiat�a: kierunkowe/punktowe)
    GLfloat attenuation[3];  // T�umienie �wiat�a: sta�e, liniowe, kwadratowe

    PhongModel phong;        // Parametry Phonga

    Light();
    void enableLight(GLenum lightID); // W��czenie �wiat�a OpenGL
};

#endif // LIGHTING_H
