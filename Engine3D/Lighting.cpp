#include "Lighting.h"

Light::Light() {
    // Domyœlna pozycja œwiat³a
    position[0] = 0.0f; position[1] = 1.0f; position[2] = 1.0f; position[3] = 1.0f;

    // Domyœlne t³umienie
    attenuation[0] = 1.0f; // Sta³e
    attenuation[1] = 0.1f; // Liniowe
    attenuation[2] = 0.01f; // Kwadratowe

    // Domyœlne parametry Phonga
    phong.ambient[0] = 0.2f; phong.ambient[1] = 0.2f; phong.ambient[2] = 0.2f; phong.ambient[3] = 1.0f;
    phong.diffuse[0] = 0.8f; phong.diffuse[1] = 0.8f; phong.diffuse[2] = 0.8f; phong.diffuse[3] = 1.0f;
    phong.specular[0] = 1.0f; phong.specular[1] = 1.0f; phong.specular[2] = 1.0f; phong.specular[3] = 1.0f;
    phong.shininess = 32.0f;
}

void Light::enableLight(GLenum lightID) {
    glEnable(GL_LIGHTING);       // W³¹czenie systemu oœwietlenia OpenGL
    glEnable(lightID);           // W³¹czenie konkretnego Ÿród³a œwiat³a

    glLightfv(lightID, GL_POSITION, position);
    glLightfv(lightID, GL_AMBIENT, phong.ambient);
    glLightfv(lightID, GL_DIFFUSE, phong.diffuse);
    glLightfv(lightID, GL_SPECULAR, phong.specular);

    glLightf(lightID, GL_CONSTANT_ATTENUATION, attenuation[0]);
    glLightf(lightID, GL_LINEAR_ATTENUATION, attenuation[1]);
    glLightf(lightID, GL_QUADRATIC_ATTENUATION, attenuation[2]);
}
