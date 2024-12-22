#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>

class Camera {
private:
    float position[3];  // Pozycja kamery (x, y, z)
    float target[3];    // Punkt, na który kamera patrzy (x, y, z)
    float up[3];        // Kierunek "góry" kamery (x, y, z)

public:
    // Konstruktor domyœlny
    Camera();

    // Funkcje ustawiaj¹ce parametry kamery
    void setPosition(float x, float y, float z);
    void setTarget(float x, float y, float z);
    void setUp(float x, float y, float z);

    // Funkcja do zastosowania kamery
    void apply() const;

    // Gettery
    const float* getPosition() const;
    const float* getTarget() const;
    const float* getUp() const;
};

#endif // CAMERA_H
