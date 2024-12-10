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
        std::cerr << "Wiele instancji Engine nie jest obs�ugiwane." << std::endl;
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

    // Ustawienie callback�w
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    if (keyboardEnabled) {
        glutKeyboardFunc(keyboardCallback);
    }
    if (mouseEnabled) {
        glutMouseFunc(mouseCallback);
    }

    // Uruchomienie g��wnej p�tli
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

    // Dla rzutowania perspektywicznego przesuwamy scen� do ty�u
    if (instance->currentProjectionMode == ProjectionMode::PERSPECTIVE) {
        glTranslatef(0.0f, 0.0f, -5.0f);
    }

    // Rysowanie osi wsp�rz�dnych
    glBegin(GL_LINES);
    // O� X (czerwona)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-2.0f, 0.0f, 0.0f);
    glVertex3f(2.0f, 0.0f, 0.0f);
    // O� Y (zielona)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -2.0f, 0.0f);
    glVertex3f(0.0f, 2.0f, 0.0f);
    // O� Z (niebieska)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -2.0f);
    glVertex3f(0.0f, 0.0f, 2.0f);



    glEnd();

    //instance->geometric_Objects.draw_rectangle(-1.0f, 1.0f, 0.0f, 
    //    1.0f, 1.0f, 0.0f,   
    //    1.0f, -1.0f, 0.0f,   
    //    -1.0f, -1.0f, 0.0f); 

    // Wywo�anie funkcji rysuj�cej kul�
    

    //rysuje kule
    //instance->geometric_Objects.draw_sphere(1.0, 16, 16);


    //rysuje sze�cian
   // instance->geometric_Objects.draw_Cube(2);

    // Wektor Wierzcholkow dla punkt�w
    const float PointVerts[] = {
        0.2f, 0.1f, 0.2f, // Punkt 1
        0.5f, 0.5f, 0.2f, // Punkt 2
       -0.5f, -0.5f, 0.2f // Punkt 3
    };

    // Wektor kolorow dla punkt�w
    const float PointColours[] = {
        1.0f, 0.0f, 0.0f, // Kolor punktu 1
        0.0f, 1.0f, 0.0f, // Kolor punktu 2
        0.0f, 0.0f, 1.0f  // Kolor punktu 3
    };

    // Wywo�anie metody rysuj�cej punkty
    instance->geometric_Objects.draw_points(PointVerts, PointColours, 3); 
/*
    //Rysowanie lini


    //Wektor Wierzcholkow
    const float LineVerts[] = {
        -1.0f,-1.f,0.2f,
        -1.0f,1.0f,0.2f
    };


    //Wektor kolorow
    const float LineColours[] = {
        1.0f, 1.0f, 0.3f,
        1.0f, 0.9f, 0.0f,
    };

    instance->geometric_Objects.draw_line(LineVerts, LineColours);
    */
    // rysowanie �amanych
    // Wektor Wierzcholkow dla linii �amanej
    const float PolylineVerts[] = {
        -1.0f, -1.0f, 0.2f, // Punkt 1
        -0.5f,  0.5f, 0.2f, // Punkt 2
         0.0f, -0.5f, 0.2f, // Punkt 3
         0.5f,  0.5f, 0.2f  // Punkt 4
    };

    // Wektor kolorow dla linii �amanej
    const float PolylineColours[] = {
        1.0f, 0.0f, 0.0f, // Czerwony dla Punktu 1
        0.0f, 1.0f, 0.0f, // Zielony dla Punktu 2
        0.0f, 0.0f, 1.0f, // Niebieski dla Punktu 3
        1.0f, 1.0f, 0.0f  // ��ty dla Punktu 4
    };

    // Wywo�anie rysowania linii �amanej
    instance->geometric_Objects.draw_polyline(PolylineVerts, PolylineColours, 4);

    //Rysowanie trojkata


    /*
    const float LineVerts_triangle[] = {
        0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 
        -1.0f, -1.0f, 0.0f
    };

    const float LineColours_triangle[] = {
        1.0f, 1.0f, 0.3f,
        1.0f, 0.9f, 0.0f,
        1.0f, 1.0f, 1.0f
    };

    instance->geometric_Objects.draw_triangle(LineVerts_triangle, LineColours_triangle);

    */
    /*
    //rysowanie pasow trojkata
    const float TriangleStripVerts[] = {
    -1.0f, -1.0f, 0.0f, // Punkt 1
     0.0f,  1.0f, 0.0f, // Punkt 2
     1.0f, -1.0f, 0.0f, // Punkt 3
     2.0f,  1.0f, 0.0f  // Punkt 4
    };

    const float TriangleStripColours[] = {
        1.0f, 0.0f, 0.0f, // Czerwony
        0.0f, 1.0f, 0.0f, // Zielony
        0.0f, 0.0f, 1.0f, // Niebieski
        1.0f, 1.0f, 0.0f  // ��ty
    };

    instance->geometric_Objects.draw_triangle_strip(TriangleStripVerts, TriangleStripColours, 4);
    */
    //rysowanie wachlarzy trojkata
    /*
    const float TriangleFanVerts[] = {
    0.0f,  0.0f, 0.0f, // Punkt 1 (wsp�lny)
    -1.0f, -1.0f, 0.0f, // Punkt 2
     1.0f, -1.0f, 0.0f, // Punkt 3
     1.0f,  1.0f, 0.0f, // Punkt 4
    -1.0f,  1.0f, 0.0f  // Punkt 5
    };

    const float TriangleFanColours[] = {
        1.0f, 1.0f, 1.0f, // Bia�y (dla Punktu 1)
        1.0f, 0.0f, 0.0f, // Czerwony
        0.0f, 1.0f, 0.0f, // Zielony
        0.0f, 0.0f, 1.0f, // Niebieski
        1.0f, 1.0f, 0.0f  // ��ty
    };

    instance->geometric_Objects.draw_triangle_fan(TriangleFanVerts, TriangleFanColours, 5);
    */
    //Rysowanie Czworokata
    /*

    const float LineVerts_rectangle[] = {
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,   
        1.0f, -1.0f, 0.0f,   
        -1.0f, -1.0f, 0.0f
    };

    const float LineColours_rectangle[] = {
        0.2f, 1.0f, 0.3f,
        1.0f, 0.9f, 0.0f,
        1.0f, 1.5f, 1.0f,
        1.0f, 1.0f, 0.5f
    };



    instance->geometric_Objects.draw_rectangle(LineVerts_rectangle, LineColours_rectangle);
   
    */
   
    //rysowanie sze�cianu
    const float cube_vert[] = {
        //wierzcho�k�w sze�cianu
        -1.0f, -1.0f, -1.0f, // 0
        -1.0f, -1.0f,  1.0f, // 1
        -1.0f,  1.0f,  1.0f, // 2
        -1.0f,  1.0f, -1.0f, // 3
         1.0f,  1.0f,  1.0f, // 4
         1.0f,  1.0f, -1.0f, // 5
         1.0f, -1.0f,  1.0f, // 6
         1.0f, -1.0f, -1.0f  // 7
    };

    //normalne sze�cianu
    const float cube_norm[] = {
        0.0f, 0.0f, 1.0f,  
        0.0f, 0.0f, 1.0f,  
        0.0f, 0.0f, 1.0f,  
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };
    //kolory wierzcho�k�w
    const float cube_cols[] = {
        1.0f, 0.0f, 0.0f, 
        0.0f, 1.0f, 0.0f, 
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 
        0.0f, 1.0f, 1.0f,
        0.5f, 0.0f, 0.5f  
    };

  
    const unsigned char cube_ind[] = {
        // przednia �ciana, wierzcho�ki 1,2,4,6
        1,2,4,  1,4,6,
        // tylna �ciana: wierzcho�ki 0,3,5,7
        0,3,5,  0,5,7,
        // lewa �ciana wierzcho�ki 0,1,2,3
        0,1,2,  0,2,3,
        // prawa �ciana wierzcho�ki 7,6,4,5
        7,6,4,  7,4,5,
        // g�rna �ciana wierzcho�ki 3,2,4,5
        3,2,4,  3,4,5,
        // dolna �ciana wierzcho�ki 0,7,6,1
        0,7,6,  0,6,1
    };

    instance->geometric_Objects.draw_Box(cube_vert, cube_norm, cube_cols, cube_ind);
    
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

// Zaktualizowany keyboardCallback do prze��czania tryb�w rzutowania
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
        std::cout << "Przycisk myszy " << button << " klikni�ty w (" << x << ", " << y << ")." << std::endl;
    }
}

void Engine::timerCallback(int value) {
    if (instance->isRunning) {
        glutPostRedisplay();
        glutTimerFunc(1000 / instance->frameRate, timerCallback, value);
    }
}
