#include "Camera.h"

// Konstruktor domyœlny: ustawia kamerê na pozycjê pocz¹tkow¹
Camera::Camera() {
    setPosition(0.0f, 0.0f, 5.0f);  // Domyœlna pozycja kamery
    setTarget(0.0f, 0.0f, 0.0f);    // Domyœlny cel
    setUp(0.0f, 1.0f, 0.0f);        // Domyœlny kierunek "góry"
}

// Ustawia pozycjê kamery
void Camera::setPosition(float x, float y, float z) {
    position[0] = x;
    position[1] = y;
    position[2] = z;
}

// Ustawia punkt, na który kamera patrzy
void Camera::setTarget(float x, float y, float z) {
    target[0] = x;
    target[1] = y;
    target[2] = z;
}

// Ustawia kierunek "góry"
void Camera::setUp(float x, float y, float z) {
    up[0] = x;
    up[1] = y;
    up[2] = z;
}

// Zastosowanie ustawieñ kamery w OpenGL
void Camera::apply() const {
    glLoadIdentity();
    gluLookAt(
        position[0], position[1], position[2], // Pozycja kamery
        target[0], target[1], target[2],       // Punkt, na który patrzy
        up[0], up[1], up[2]                    // Kierunek "góry"
    );
}

// Gettery
const float* Camera::getPosition() const { return position; }
const float* Camera::getTarget() const { return target; }
const float* Camera::getUp() const { return up; }
