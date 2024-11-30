#include "Engine.h"
#include <iostream>

Engine* Engine::instance = nullptr;

Engine::Engine(int width, int height, const std::string& title, bool fullscreen)
    : windowWidth(width), windowHeight(height), windowTitle(title), isFullscreen(fullscreen),
    frameRate(60), mouseEnabled(false), keyboardEnabled(false), depthBufferEnabled(false), isRunning(false),
    currentProjectionMode(ProjectionMode::PERSPECTIVE) // Inicjalizacja trybu rzutowania
{
    clearColor[0] = 0.0f; // Red
    clearColor[1] = 0.0f; // Green
    clearColor[2] = 0.0f; // Blue
    clearColor[3] = 1.0f; // Alpha

    if (instance == nullptr) {
        instance = this;
    }
    else {
        std::cerr << "Wiele instancji Engine nie jest obs³ugiwane." << std::endl;
        exit(EXIT_FAILURE);
    }
}

Engine::~Engine() {
    stop();
    instance = nullptr;
}

void Engine::setGraphicsMode(bool fullscreen, int width, int height) {
    isFullscreen = fullscreen;
    windowWidth = width;
    windowHeight = height;
}

void Engine::setFrameRate(int fps) {
    frameRate = fps;
}

void Engine::enableMouseInput(bool enable) {
    mouseEnabled = enable;
}

void Engine::enableKeyboardInput(bool enable) {
    keyboardEnabled = enable;
}

void Engine::enableDepthBuffer(bool enable) {
    depthBufferEnabled = enable;
}

void Engine::setClearColor(float r, float g, float b, float a) {
    clearColor[0] = r;
    clearColor[1] = g;
    clearColor[2] = b;
    clearColor[3] = a;
}

void Engine::start() {
    isRunning = true;

    // Inicjalizacja GLUT
    int argc = 1;
    char* argv[1] = { (char*)"Engine" };
    glutInit(&argc, argv);

    int displayMode = GLUT_DOUBLE | GLUT_RGBA;
    if (depthBufferEnabled) {
        displayMode |= GLUT_DEPTH;
    }
    glutInitDisplayMode(displayMode);

    // Ustawienie okna
    if (isFullscreen) {
        glutGameModeString("1920x1080:32");
        glutEnterGameMode();
    }
    else {
        glutInitWindowSize(windowWidth, windowHeight);
        glutCreateWindow(windowTitle.c_str());
    }

    initGraphics();

    // Ustawienie callbacków
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    if (keyboardEnabled) {
        glutKeyboardFunc(keyboardCallback);
    }
    if (mouseEnabled) {
        glutMouseFunc(mouseCallback);
    }

    // Uruchomienie g³ównej pêtli
    glutTimerFunc(1000 / frameRate, timerCallback, 0);
    glutMainLoop();
}

void Engine::stop() {
    if (isRunning) {
        deinitGraphics();
        glutLeaveMainLoop();
        isRunning = false;
    }
}

void Engine::initGraphics() {
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    if (depthBufferEnabled) {
        glEnable(GL_DEPTH_TEST);
    }
}

void Engine::deinitGraphics() {
    if (depthBufferEnabled) {
        glDisable(GL_DEPTH_TEST);
    }
}

// Zaktualizowany displayCallback do rysowania osi
void Engine::displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT | (instance->depthBufferEnabled ? GL_DEPTH_BUFFER_BIT : 0));

    glLoadIdentity();

    // Dla rzutowania perspektywicznego przesuwamy scenê do ty³u
    if (instance->currentProjectionMode == ProjectionMode::PERSPECTIVE) {
        glTranslatef(0.0f, 0.0f, -5.0f);
    }

    // Rysowanie osi wspó³rzêdnych
    glBegin(GL_LINES);
    // Oœ X (czerwona)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-2.0f, 0.0f, 0.0f);
    glVertex3f(2.0f, 0.0f, 0.0f);
    // Oœ Y (zielona)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -2.0f, 0.0f);
    glVertex3f(0.0f, 2.0f, 0.0f);
    // Oœ Z (niebieska)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -2.0f);
    glVertex3f(0.0f, 0.0f, 2.0f);
    glEnd();

    glutSwapBuffers();
}

// Zaktualizowany reshapeCallback do dostosowania macierzy rzutowania
void Engine::reshapeCallback(int width, int height) {
    instance->windowWidth = width;
    instance->windowHeight = height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (instance->currentProjectionMode == ProjectionMode::PERSPECTIVE) {
        // Ustawienie rzutowania perspektywicznego
        gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
    }
    else if (instance->currentProjectionMode == ProjectionMode::ORTHOGRAPHIC) {
        // Ustawienie rzutowania ortograficznego
        float aspect = (float)width / (float)height;
        glOrtho(-2.0f * aspect, 2.0f * aspect, -2.0f, 2.0f, -10.0f, 10.0f);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Zaktualizowany keyboardCallback do prze³¹czania trybów rzutowania
void Engine::keyboardCallback(unsigned char key, int x, int y) {
    if (key == 27) { // Klawisz ESC
        instance->stop();
    }
    else if (key == 'P' || key == 'p') {
        instance->currentProjectionMode = ProjectionMode::PERSPECTIVE;
        instance->reshapeCallback(instance->windowWidth, instance->windowHeight);
    }
    else if (key == 'O' || key == 'o') {
        instance->currentProjectionMode = ProjectionMode::ORTHOGRAPHIC;
        instance->reshapeCallback(instance->windowWidth, instance->windowHeight);
    }
}

void Engine::mouseCallback(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        std::cout << "Przycisk myszy " << button << " klikniêty w (" << x << ", " << y << ")." << std::endl;
    }
}

void Engine::timerCallback(int value) {
    if (instance->isRunning) {
        glutPostRedisplay();
        glutTimerFunc(1000 / instance->frameRate, timerCallback, value);
    }
}
