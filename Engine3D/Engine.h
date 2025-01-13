#ifndef ENGINE_H
#define ENGINE_H

#include <GL/freeglut.h>
#include <string>
#include "Geometric_Objects.h"
#include "Camera.h"
#include "Cube.h"
#include "Pyramid.h"

class Engine {
public:
    Engine(int width, int height, const std::string& title, bool fullscreen = false);
    ~Engine();


    void setGraphicsMode(bool fullscreen, int width, int height);
    void setFrameRate(int fps);
    void enableMouseInput(bool enable);
    void enableKeyboardInput(bool enable);
    void enableDepthBuffer(bool enable);
    void setClearColor(float r, float g, float b, float a);
    void toggleLighting(); // Funkcja prze��czania o�wietlenia
    void start();
    void stop();

    void mouseMotionCallback(int x, int y); // Obs�uga ruchu myszki


    Geometric_Objects geometric_Objects;
    // Wywo�ania funkcji kamery
    Camera& getCamera(); // Zwraca referencj� do kamery
    Cube cube;
    Pyramid pyramid;




private:
    Camera camera;
    int windowWidth, windowHeight;
    std::string windowTitle;
    bool isFullscreen;
    int frameRate;
    bool mouseEnabled;
    bool keyboardEnabled;
    bool depthBufferEnabled;
    float clearColor[4];
    bool isRunning;
    bool lightingEnabled; // Flaga w��czaj�ca/wy��czaj�ca o�wietlenie

    GLuint textureID;
    GLuint TexID[3];
    


    //enum dla tryb�w rzutowania
    enum class ProjectionMode { PERSPECTIVE, ORTHOGRAPHIC };
    ProjectionMode currentProjectionMode;

    static void displayCallback();
    static void reshapeCallback(int width, int height);
    static void keyboardCallback(unsigned char key, int x, int y);
    static void mouseCallback(int button, int state, int x, int y);
    static void timerCallback(int value);

    void initGraphics();
    void deinitGraphics();

    static Engine* instance;

   


};

#endif
