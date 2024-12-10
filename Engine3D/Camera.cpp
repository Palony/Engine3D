#include "Camera.h"

// Konstruktor domy�lny: ustawia kamer� na pozycj� pocz�tkow�
Camera::Camera() {
    setPosition(0.0f, 0.0f, 5.0f);  // Domy�lna pozycja kamery
    setTarget(0.0f, 0.0f, 0.0f);    // Domy�lny cel
    setUp(0.0f, 1.0f, 0.0f);        // Domy�lny kierunek "g�ry"
}

// Ustawia pozycj� kamery
void Camera::setPosition(float x, float y, float z) {
    position[0] = x;
    position[1] = y;
    position[2] = z;
}

// Ustawia punkt, na kt�ry kamera patrzy
void Camera::setTarget(float x, float y, float z) {
    target[0] = x;
    target[1] = y;
    target[2] = z;
}

// Ustawia kierunek "g�ry"
void Camera::setUp(float x, float y, float z) {
    up[0] = x;
    up[1] = y;
    up[2] = z;
}

// Zastosowanie ustawie� kamery w OpenGL
void Camera::apply() const {
    glLoadIdentity();
    gluLookAt(
        position[0], position[1], position[2], // Pozycja kamery
        target[0], target[1], target[2],       // Punkt, na kt�ry patrzy
        up[0], up[1], up[2]                    // Kierunek "g�ry"
    );
}

// Gettery
const float* Camera::getPosition() const { return position; }
const float* Camera::getTarget() const { return target; }
const float* Camera::getUp() const { return up; }
