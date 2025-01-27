#include "Engine.h"
#include <iostream>
#include "Camera.h"
#include "Cube.h"
#include "Lighting.h"

#include "BitmapHandler.h"


Engine* Engine::instance = nullptr;
//zmienne globalne dla dema
float rocketY = 0.0f; // Pozycja pionowa rakiety
float rocketSpeed = 0.0; // Pr�dko�� lotu rakiety
float rotationAngle = 0.0f; // K�t obrotu wok� �rodka rakiety
float cubeRotationAngle = 4.0f; // K�t obrotu sze�cianu
float cubeScaleFactor = 1.0f;   // Wsp�czynnik skalowania sze�cianu
float scaleDirection = 0.001f;   // Kierunek skalowania (rosn�cy/malej�cy)
Light light;


const float base_vert[] = {
-1.0f, -3.0f,  1.0f,   1.0f, -3.0f,  1.0f,  -1.0f,  1.0f,  1.0f,   1.0f,  1.0f,  1.0f,
-1.0f, -3.0f, -1.0f,  -1.0f,  1.0f, -1.0f,   1.0f, -3.0f, -1.0f,   1.0f,  1.0f, -1.0f,
-1.0f,  1.0f, -1.0f,  -1.0f,  1.0f,  1.0f,   1.0f,  1.0f, -1.0f,   1.0f,  1.0f,  1.0f,
-1.0f, -3.0f, -1.0f,   1.0f, -3.0f, -1.0f,  -1.0f, -3.0f,  1.0f,   1.0f, -3.0f,  1.0f,
 1.0f, -3.0f, -1.0f,   1.0f,  1.0f, -1.0f,   1.0f, -3.0f,  1.0f,   1.0f,  1.0f,  1.0f,
-1.0f, -3.0f, -1.0f,  -1.0f, -3.0f,  1.0f,  -1.0f,  1.0f, -1.0f,  -1.0f,  1.0f,  1.0f,
};

const float top_vert[] = {
    // Podstawa ostros�upa (rozszerzona do wymiar�w base)
    -1.0f, 1.0f, -1.0f,  // Wierzcho�ek 0
     1.0f, 1.0f, -1.0f,  // Wierzcho�ek 1
     1.0f, 1.0f,  1.0f,  // Wierzcho�ek 2
    -1.0f, 1.0f,  1.0f,  // Wierzcho�ek 3

    // Wierzcho�ek szczytowy (pozostaje bez zmian)
     0.0f, 3.0f,  0.0f   // Wierzcho�ek 4
};
const float base_colors[] = {
    // Kolory dla dolnej podstawy
    0.5f, 0.5f, 0.5f,  // Wierzcho�ek 0 (czerwony)
    0.5f, 0.5f, 0.5f,  // Wierzcho�ek 1 (zielony)
    0.5f, 0.5f, 0.5f,  // Wierzcho�ek 2 (niebieski)
    0.5f, 0.5f, 0.5f,  // Wierzcho�ek 3 (��ty)

    // Kolory dla g�rnej podstawy
    0.5f, 0.5f, 0.5f,  // Wierzcho�ek 4 (fioletowy)
    0.5f, 0.5f, 0.5f,  // Wierzcho�ek 5 (turkusowy)
    0.5f, 0.5f, 0.5f,  // Wierzcho�ek 6 (szary)
    0.5f, 0.5f, 0.5f   // Wierzcho�ek 7 (bia�y)
};

const float top_colors[] = {
    // Kolory dla podstawy
    1.0f, 0.0f, 0.0f,  // Wierzcho�ek 0 (pomara�czowy)
    1.0f, 0.5f, 1.0f,  // Wierzcho�ek 1 (niebieskozielony)
    1.0f, 0.0f, 0.0f,  // Wierzcho�ek 2 (��ty)
    1.5f, 0.0f, 0.0f,  // Wierzcho�ek 3 (fioletowy)

    // Kolor dla wierzcho�ka szczytowego
    1.0f, 0.0f, 0.0f   // Wierzcho�ek 4 (czerwony)
};


const float base_normals[] = {
0.0,  0.0, -1.0,  // Front face normals
0.0,  0.0, -1.0,
0.0,  0.0, -1.0,
0.0,  0.0, -1.0,
0.0,  0.0,  1.0,  //Back face normals
0.0,  0.0,  1.0,
0.0,  0.0,  1.0,
0.0,  0.0,  1.0
};

const float top_normals[] = {
    // Normalne dla podstawy
    0.0f, -1.0f,  0.0f,  // Wierzcho�ek 0
    0.0f, -1.0f,  0.0f,  // Wierzcho�ek 1
    0.0f, -1.0f,  0.0f,  // Wierzcho�ek 2
    0.0f, -1.0f,  0.0f,  // Wierzcho�ek 3

    // Normalne dla �cian bocznych
    0.0f,  0.447f,  0.894f,  // �ciana 1
   -0.894f,  0.447f,  0.0f,  // �ciana 2
    0.0f,  0.447f, -0.894f,  // �ciana 3
    0.894f,  0.447f,  0.0f   // �ciana 4
};

const unsigned char base_indices[] = {
    0, 1, 2,    // strona 1
    2, 1, 3,
    4, 5, 6,    // strona 2
    6, 5, 7,
    8, 9, 10,    // strona 3
    10, 9, 11,
    12, 13, 14,    // strona 4
    14, 13, 15,
    16, 17, 18,    // strona 5
    18, 17, 19,
    20, 21, 22,    // strona 6
    22, 21, 23,
};

const float base_texc[] = {
    1.0f, 0.0f,		0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f,
    0.0f, 0.0f,		0.0f, 1.0f,		1.0f, 0.0f,		1.0f, 1.0f,
    0.0f, 0.0f,		0.0f, 1.0f,		1.0f, 0.0f,		1.0f, 1.0f,
    1.0f, 0.0f,		0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f,
    0.0f, 0.0f,		0.0f, 1.0f,		1.0f, 0.0f,		1.0f, 1.0f,
    1.0f, 0.0f,		0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f
};

const unsigned char top_indices[] = {
    // Podstawa (2 tr�jk�ty)
    0, 1, 2,
    0, 2, 3,

    // �ciany boczne (4 �ciany, 1 tr�jk�t ka�da)
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};



const float cube2_vert[] = {
-1.0f, -1.0f,  1.0f,	 1.0f, -1.0f,  1.0f,	-1.0f,  1.0f,  1.0f,	 1.0f,  1.0f,  1.0f,
-1.0f, -1.0f, -1.0f,	-1.0f,  1.0f, -1.0f,	 1.0f, -1.0f, -1.0f,	 1.0f,  1.0f, -1.0f,
-1.0f,  1.0f, -1.0f,	-1.0f,  1.0f,  1.0f,	 1.0f,  1.0f, -1.0f,	 1.0f,  1.0f,  1.0f,
-1.0f, -1.0f, -1.0f,	 1.0f, -1.0f, -1.0f,	-1.0f, -1.0f,  1.0f,	 1.0f, -1.0f,  1.0f,
 1.0f, -1.0f, -1.0f,	 1.0f,  1.0f, -1.0f,	 1.0f, -1.0f,  1.0f,	 1.0f,  1.0f,  1.0f,
-1.0f, -1.0f, -1.0f,	-1.0f, -1.0f,  1.0f,	-1.0f,  1.0f, -1.0f,	-1.0f,  1.0f,  1.0f,
};




const unsigned char cube2_ind[] = {
    0, 1, 2,    // strona 1
    2, 1, 3,
    4, 5, 6,    // strona 2
    6, 5, 7,
    8, 9, 10,    // strona 3
    10, 9, 11,
    12, 13, 14,    // strona 4
    14, 13, 15,
    16, 17, 18,    // strona 5
    18, 17, 19,
    20, 21, 22,    // strona 6
    22, 21, 23,
};

// Wsp�rz�dne tekstury (dla ka�dego wierzcho�ka):
const float cube2_texc[] = {
    1.0f, 0.0f,		0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f,
    0.0f, 0.0f,		0.0f, 1.0f,		1.0f, 0.0f,		1.0f, 1.0f,
    0.0f, 0.0f,		0.0f, 1.0f,		1.0f, 0.0f,		1.0f, 1.0f,
    1.0f, 0.0f,		0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f,
    0.0f, 0.0f,		0.0f, 1.0f,		1.0f, 0.0f,		1.0f, 1.0f,
    1.0f, 0.0f,		0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f
};

//normalne sze�cianu
const float cube2_norm[] = {
0.0,  0.0, -1.0,  // Front face normals
0.0,  0.0, -1.0,
0.0,  0.0, -1.0,
0.0,  0.0, -1.0,
0.0,  0.0,  1.0,  //Back face normals
0.0,  0.0,  1.0,
0.0,  0.0,  1.0,
0.0,  0.0,  1.0
};


Engine::Engine(int width, int height, const std::string& title, bool fullscreen)
    : windowWidth(width), windowHeight(height), windowTitle(title), isFullscreen(fullscreen),
    frameRate(60), mouseEnabled(false), keyboardEnabled(false), depthBufferEnabled(false),
    isRunning(false), lightingEnabled(true), currentProjectionMode(ProjectionMode::PERSPECTIVE) {
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


void Engine::toggleLighting() {
    if (lightingEnabled) {
        glDisable(GL_LIGHTING); // Wy��cz o�wietlenie
    }
    else {
        glEnable(GL_LIGHTING); // W��cz o�wietlenie
    }
    lightingEnabled = !lightingEnabled; // Prze��cz stan
}

Camera& Engine::getCamera() {
    return camera;
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
    // Tabela z punktami:
    glVertexPointer(3, GL_FLOAT, 0, cube2_vert);
    // Tabela ze wsp�rz�dnymi tekstur (2 wsp�rz�dne):
    glTexCoordPointer(2, GL_FLOAT, 0, cube2_texc);


    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    if (depthBufferEnabled) {
        glEnable(GL_DEPTH_TEST);
    }

    //Wlaczenie teksturowania
   
    
    // Inicjalizacja o�wietlenia
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);



    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 1.0f, 7.0f, 7.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // W��czenie GL_COLOR_MATERIAL, aby u�ywa� naturalnych kolor�w obiekt�w
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    BitmapHandler bitmapHandler;
    GLuint textureID = bitmapHandler.loadTexture("woda.jpg");
    if (textureID != 0) {
        instance->textureID = textureID; // Zapisuje id tekstury 
    }
    else {
        std::cerr << "Nie uda�o si� za�adowa� tekstury!" << std::endl;
    }

    textureID = bitmapHandler.loadTexture("tex0.png");
    if (textureID != 0) {
        instance->TexID[0] = textureID; // Zapisuje id tekstury 
    }
    else {
        std::cerr << "Nie uda�o si� za�adowa� tekstury!" << std::endl;
    }

    textureID = bitmapHandler.loadTexture("tex1.png");
    if (textureID != 0) {
        instance->TexID[1] = textureID; // Zapisuje id tekstury 
    }
    else {
        std::cerr << "Nie uda�o si� za�adowa� tekstury!" << std::endl;
    }

    textureID = bitmapHandler.loadTexture("tex2.png");
    if (textureID != 0) {
        instance->TexID[2] = textureID; // Zapisuje id tekstury 
    }
    else {
        std::cerr << "Nie uda�o si� za�adowa� tekstury!" << std::endl;
    }
    textureID = bitmapHandler.loadTexture("rocket_tex.png");
    if (textureID != 0) {
        instance->Rocket_tex = textureID; // Zapisuje id tekstury 
    }
    else {
        std::cerr << "Nie udalo sie zaladowac tekstury!" << std::endl;
    } GLuint sphereTextureID = bitmapHandler.loadTexture("tex0.png"); 
    if (sphereTextureID != 0) {
        instance->Sphere_tex = sphereTextureID; 
    }
    else {
        std::cerr << "Nie udalo sie zaladowac tekstury!" << std::endl;
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

    instance->camera.apply(); // Zastosowanie ustawie� kamery 
   
    
    // Kontrola o�wietlenia na podstawie flagi
    if (instance->lightingEnabled) {
        glEnable(GL_LIGHTING);
    }
    else {
        glDisable(GL_LIGHTING);
    }
    


    // Dla rzutowania perspektywicznego przesuwamy scen� do ty�u
    if (instance->currentProjectionMode == ProjectionMode::PERSPECTIVE) {
        glTranslatef(0.0f, 0.0f, -5.0f);
    }
   
    //niepotrzebne
    //// Rysowanie osi wsp�rz�dnych
    //glBegin(GL_LINES);
    //// O� X (czerwona)
    //glColor3f(1.0f, 0.0f, 0.0f);
    //glVertex3f(-2.0f, 0.0f, 0.0f);
    //glVertex3f(2.0f, 0.0f, 0.0f);
    //// O� Y (zielona)
    //glColor3f(0.0f, 1.0f, 0.0f);
    //glVertex3f(0.0f, -2.0f, 0.0f);
    //glVertex3f(0.0f, 2.0f, 0.0f);
    //// O� Z (niebieska)
    //glColor3f(0.0f, 0.0f, 1.0f);
    //glVertex3f(0.0f, 0.0f, -2.0f);
    //glVertex3f(0.0f, 0.0f, 2.0f);



    //glEnd();
    //niepotrzebne
    //instance->geometric_Objects.draw_rectangle(-1.0f, 1.0f, 0.0f, 
    //    1.0f, 1.0f, 0.0f,   
    //    1.0f, -1.0f, 0.0f,   
    //    -1.0f, -1.0f, 0.0f); 
    //niepotrzebne
    // Wywo�anie funkcji rysuj�cej kul�


    //rysuje kule
   //instance->geometric_Objects.draw_sphere(1.0, 16, 16);


    //rysuje sze�cian
    //instance->geometric_Objects.draw_Cube(2);
    //niepotrzebne
    // Wektor Wierzcholkow dla punkt�w
    /*const float PointVerts[] = {
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
    //instance->geometric_Objects.draw_points(PointVerts, PointColours, 3); 
    */
    //Rysowanie lini

    /*
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
    */

    //instance->geometric_Objects.draw_line(LineVerts, LineColours);
    
    
    // rysowanie �amanych-- w demie
    
    
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



/*instance->cube.resetTransform();  // Resetuje wszystkie transformacje
instance->cube.translate(5, 0, 0); // Przesuni�cie sze�cianu o (x,y,z)
instance->cube.rotate(45, 1.0f, 1.0f, 0); // Obr�t o X stopni wok� osi X i Y
instance->cube.scale(0.5, 0.5, 0.5); // Zmniejszenie rozmiaru sze�cianu
   */


    //rysowanie sze�cianu
    const float cube_vert[] = {
        //wierzcho�ki sze�cianu
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
    0.0,  0.0, -1.0,  // Front face normals
    0.0,  0.0, -1.0,
    0.0,  0.0, -1.0,
    0.0,  0.0, -1.0,
    0.0,  0.0,  1.0,  //Back face normals
    0.0,  0.0,  1.0,
    0.0,  0.0,  1.0,
    0.0,  0.0,  1.0
    };
    //kolory wierzcho�k�w
    const float cube_cols[] = {
      0.0f, 1.0f, 0.0f, // Wierzcho�ek 1 - czerwony
      0.0f, 1.0f, 0.0f, // Wierzcho�ek 2 - czerwony
      0.0f, 1.0f, 0.0f, // Wierzcho�ek 3 - czerwony
      0.0f, 1.0f, 0.0f, // Wierzcho�ek 4 - czerwony
      0.0f, 1.0f, 0.0f, // Wierzcho�ek 5 - czerwony
      0.0f, 1.0f, 0.0f, // Wierzcho�ek 6 - czerwony
      0.0f, 1.0f, 0.0f, // Wierzcho�ek 7 - czerwony
      0.0f, 1.0f, 0.0f  // Wierzcho�ek 8 - czerwony
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

    const float cube_texc[] = {
        0.0, 0.0,  // 0 - Front bottom - left
        1.0, 0.0,  // 1 - Front bottom - right
        1.0, 1.0,  // 2 - Front top - right
        0.0, 1.0,  // 3 - Front top - left
        0.0, 0.0,  // 4 - Back bottom - left
        1.0, 0.0,  // 5 - Back bottom - right
        1.0, 1.0,  // 6 - Back top - right
        0.0, 1.0   // 7 - Back top - left
    };








    
    //instance->cube.draw(cube_vert, cube_norm, cube_cols, cube_ind); // Rysowanie sze�cianu
    

	//instance->cube2.TexID[0] = instance->TexID[0];
	//instance->cube2.draw_w_texture(cube2_vert, cube2_norm, cube2_ind, cube2_texc); // Rysowanie sze�cianu z tekstur�




    
    /*

    const float cube2_vert[] = {
    -1.0f, -1.0f,  1.0f,	 1.0f, -1.0f,  1.0f,	-1.0f,  1.0f,  1.0f,	 1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,	-1.0f,  1.0f, -1.0f,	 1.0f, -1.0f, -1.0f,	 1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,	-1.0f,  1.0f,  1.0f,	 1.0f,  1.0f, -1.0f,	 1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,	 1.0f, -1.0f, -1.0f,	-1.0f, -1.0f,  1.0f,	 1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,	 1.0f,  1.0f, -1.0f,	 1.0f, -1.0f,  1.0f,	 1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,	-1.0f, -1.0f,  1.0f,	-1.0f,  1.0f, -1.0f,	-1.0f,  1.0f,  1.0f,
    };



    const unsigned char cube2_ind[] = {
	    0, 1, 2,    // strona 1
	    2, 1, 3,
	    4, 5, 6,    // strona 2
	    6, 5, 7,
	    8, 9, 10,    // strona 3
	    10, 9, 11,
	    12, 13, 14,    // strona 4
	    14, 13, 15,
	    16, 17, 18,    // strona 5
	    18, 17, 19,
	    20, 21, 22,    // strona 6
	    22, 21, 23,
    };

    // Wsp�rz�dne tekstury (dla ka�dego wierzcho�ka):
    const float cube2_texc[] = {
        1.0f, 0.0f,		0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f,
        0.0f, 0.0f,		0.0f, 1.0f,		1.0f, 0.0f,		1.0f, 1.0f,
        0.0f, 0.0f,		0.0f, 1.0f,		1.0f, 0.0f,		1.0f, 1.0f,
        1.0f, 0.0f,		0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f,
        0.0f, 0.0f,		0.0f, 1.0f,		1.0f, 0.0f,		1.0f, 1.0f,
        1.0f, 0.0f,		0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f
    };
    */



    /*
	// Przygotowanie sze�cianu:
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	// Tabela z punktami:
	glVertexPointer(3, GL_FLOAT, 0, cube_vert);
	// Tabela ze wsp�rz�dnymi tekstur (2 wsp�rz�dne):
	glTexCoordPointer(2, GL_FLOAT, 0, cube_texc);

    glBindTexture(GL_TEXTURE_2D, TexID[0]);
    //glDrawElements(GL_TRIANGLES, sizeof(cube_ind), GL_UNSIGNED_BYTE, cube_ind);

    glBindTexture(GL_TEXTURE_2D, TexID[1]);
    //glDrawElements(GL_TRIANGLES, sizeof(cube_ind), GL_UNSIGNED_BYTE, cube_ind);

    glBindTexture(GL_TEXTURE_2D, TexID[2]);
    //glDrawElements(GL_TRIANGLES, sizeof(cube_ind), GL_UNSIGNED_BYTE, cube_ind);




    glGenTextures(3, TexID);
    BitmapHandler bt;

    bt.bindTexture(TexID[0]);
    bt.loadTexture("tex0.png");
    bt.bindTexture(TexID[1]);
    bt.loadTexture("tex1.png");
    bt.bindTexture(TexID[2]);
    bt.loadTexture("tex2.png");
    */





    
        //instance->cube.draw_w_texture(cube_vert, cube_norm, cube_ind, cube_texc);
    




    //Rysowanie Piramidy
    /*
    const float pyramid_vert[] = {
        -1.0f, -1.0f, 0.5f,
        0.0f, -1.0f, -1,
        1.0f, -1.0f, 0.5f,
        0.0f, 1.0f, 0.0f
    };

    const float pryamid_colors[] = {
        1.0f, 1.0f, 0.6f,
        1.0f, 0.5f, 0.0f,
        0.0f, 1.0f, 1.0f,
        1.0f,1.0f,1.0f
    };

    const float pyramid_norm[] = {
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    };

    const unsigned char pyramid_ind[] = {
        0,3,1, // przednia sciana
        1,3,2, // prawa sciana
        2,3,0, // lewa sciana
        0,1,2 // podstawa
    };

    instance->pyramid.draw(pyramid_vert, pyramid_norm, pryamid_colors, pyramid_ind);
    */



    // Ustawienie materia�u
  //  material.applyMaterial();
   
  


 //demo

//transformowany szescian
glPushMatrix();
instance->cube.resetTransform();


cubeRotationAngle += 0.5f; 
if (cubeRotationAngle >= 360.0f) {
    cubeRotationAngle -= 360.0f;
}

// Aktualizacja skalowania
cubeScaleFactor += scaleDirection;
if (cubeScaleFactor >= 2 || cubeScaleFactor <= 0.5f) {
    scaleDirection = -scaleDirection; // Odwr�� kierunek skalowania
}

// Zastosowanie transformacji
instance->cube.translate(0, 10, 0);                      
instance->cube.rotate(cubeRotationAngle, 1.0f, 1.0f, 0); 
instance->cube.scale(cubeScaleFactor, cubeScaleFactor, cubeScaleFactor); 

// Rysowanie sze�cianu
instance->cube.draw(cube_vert, cube_norm, cube_cols, cube_ind);
glPopMatrix();



//kula (glowna planeta)
glPushMatrix();
glColor3f(0.0f, 0.58f, 0.94f); 
instance->geometric_Objects.draw_sphere_with_texture(0, -7.7, -5, 5, 18, 18, instance->Sphere_tex);
glPopMatrix();


//planeta1
glPushMatrix();
glColor3f(0.4f, 0.98f, 0.314f);
instance->geometric_Objects.draw_sphere_with_texture(12, -7.7, 102, 3, 14, 14, instance->Sphere_tex);
//instance->geometric_Objects.draw_sphere(12, -7.7, 102, 3, 14, 14);
glPopMatrix();


//planeta2
glPushMatrix();
glColor3f(1.0f, 0.0f, 0.5f);
//instance->geometric_Objects.draw_sphere(-14, -1.7, -50, 2.5, 18, 18);
instance->geometric_Objects.draw_sphere_with_texture(-14, -1.7, -50, 2.5, 18, 18, instance->Sphere_tex);
glPopMatrix();

//planeta3
glPushMatrix();
glColor3f(0.75f, 0.58f, 0.14f);
//instance->geometric_Objects.draw_sphere(5.0f, 14.0f, -20.0f, 2.0f, 18, 18);
instance->geometric_Objects.draw_sphere_with_texture(5.0f, 14.0f, -20.0f, 2.0f, 18, 18, instance->Sphere_tex);
glPopMatrix();

//torus (pierscien)
glPushMatrix();
glColor3f(1.0f,1.0f, 0.0f);
instance->geometric_Objects.draw_Torus(5.0, 14.0, -20.0, 0.6, 3.7, 32, 32);
glPopMatrix();

//torus
glPushMatrix();
glColor3f(0.4f, 1.0f, 0.2f);
instance->geometric_Objects.draw_Torus(-5, 15.5, -49, 1, 3, 32,32);
glPopMatrix();



//stozek
glPushMatrix();
glColor3f(0.3f, 0.3f, 0.7f);
instance->geometric_Objects.draw_Cone(1, 17, -9,2, 5, 32,16);
glPopMatrix();

//cylinder
glPushMatrix();
glColor3f(0.1f, 0.1f, 0.7f);
instance->geometric_Objects.draw_Cylinder(-17, 25, -28, 4, 4, 18, 16);
glPopMatrix();


    

    //Punkty (gwiazdy)
    const float PointVerts[] = {
    44.0f, 16.5f, -34.6f,
    -25.5f, -4.6f, -13.2f,
    11.6f, 6.0f, 22.3f,
    42.2f, -10.3f, 19.4f,
    35.9f, -26.8f, 15.6f,
    -15.7f, 23.2f, -29.5f,
    -31.4f, -39.9f, -42.3f,
    27.7f, 48.1f, -3.6f,
    -8.1f, -7.3f, 16.9f,
    4.6f, -49.5f, 14.2f,
    18.4f, -8.9f, -24.6f,
    -48.5f, 12.7f, 36.8f,
    -22.3f, -35.7f, 43.2f,
    19.2f, 7.5f, -49.7f,
    -39.4f, -15.6f, 31.8f,
    2.3f, 37.5f, 23.4f,
    9.7f, -19.6f, 27.1f,
    -17.8f, -28.5f, -7.4f,
    21.3f, 45.2f, -2.8f,
    -12.4f, 18.7f, -43.6f,
    36.2f, 9.3f, -22.5f,
    -49.7f, 27.4f, 4.9f,
    24.8f, -40.6f, 32.5f,
    -8.2f, 10.7f, 12.3f,
    15.6f, -35.9f, -30.4f,
    -27.5f, -13.9f, 26.8f,
    30.9f, 21.2f, 14.3f,
    -42.8f, 37.1f, -10.6f,
    17.5f, -45.2f, 48.3f,
    -7.4f, 25.5f, -22.7f,
    49.6f, -23.7f, 8.2f,
    -33.8f, 18.9f, -41.6f,
    12.4f, 39.8f, -2.1f,
    -46.1f, -25.7f, 11.7f,
    41.5f, 15.9f, 43.2f,
    -10.2f, -20.3f, -19.5f,
    34.7f, 2.8f, -6.7f,
    -21.6f, -41.8f, 7.4f,
    16.9f, -8.5f, 13.7f,
    -47.5f, 33.6f, -12.4f,
    8.6f, 42.3f, -5.8f,
    -6.3f, -31.4f, 40.5f,
    14.8f, 6.2f, 27.5f,
    -39.6f, -18.3f, -49.4f,
    25.4f, -39.7f, -21.9f,
    -15.3f, 11.7f, 29.6f,
    20.5f, 48.6f, -37.2f,
    -44.8f, -14.2f, 45.8f,
    38.2f, 5.4f, -46.1f
    };
    const float PointColours[] = {
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f
    };
       
     instance->geometric_Objects.draw_points(PointVerts, PointColours, 50); 

   
     //�amane linie (gwiazdozbior)
     // Wektor Wierzcholkow dla linii �amanej
     const float PolylineVerts[] = {
        15.0f, 22.0f, -14.8f,  
    15.4f, 19.6f, -14.8f,  
    16.0f, 19.2f, -14.8f, 
    16.1f, 18.6f, -14.8f,  
    14.0f, 18.0f, -14.8f,  
    14.7f, 16.4f, -14.8f,  
    16.6f, 16.6f, -14.8f,  
    16.1f, 18.6f, -14.8f
    
     };


     // Wektor kolorow dla linii �amanej
     const float PolylineColours[] = {
     1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f
     };

     
     instance->geometric_Objects.draw_polyline(PolylineVerts, PolylineColours, 8);


// Przywracanie domy�lnego koloru
glColor3f(1.0f, 1.0f, 1.0f); 

// Rysowanie rakiety
glPushMatrix();
instance->cube.resetTransform();
instance->pyramid.resetTransform();
instance->cube.TexID[0] = instance->Rocket_tex;

instance->cube.translate(0.0f, rocketY, -5.0f);
instance->pyramid.translate(0.0f, rocketY, -5.0f);
instance->cube.rotate(rocketY, 1, 0, 0);
instance->pyramid.rotate(rocketY, 1, 0, 0);

instance->cube.draw_w_texture(base_vert, base_normals, base_indices, base_texc);
instance->pyramid.draw(top_vert, top_normals, top_colors, top_indices);
glPopMatrix();

rocketY += rocketSpeed;
if (rocketY > 40.0f) { 
    rocketY = 0.0f;
    rocketSpeed = 0.f;
}
//demo_end

    // W��czenie �wiat�a
    light.enableLight(GL_LIGHT0);
    
    glutSwapBuffers();

    
}





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
        glOrtho(-30.0f * aspect, 30.0f * aspect, -30.0f, 30.0f, -200.0f, 200.0f);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//funkcja do prze��czania tryb�w rzutowania
void Engine::keyboardCallback(unsigned char key, int x, int y) {
    const float cameraSpeed = 0.2f;     // Pr�dko�� ruchu kamery
    const float rotationAngle = 5.0f;  // K�t obrotu w stopniach

    // Konwersja z const float* na glm::vec3
    glm::vec3 position(instance->camera.getPosition()[0],
        instance->camera.getPosition()[1],
        instance->camera.getPosition()[2]);

    glm::vec3 target(instance->camera.getTarget()[0],
        instance->camera.getTarget()[1],
        instance->camera.getTarget()[2]);

    glm::vec3 direction = glm::normalize(target - position); // Kierunek patrzenia
    glm::vec3 up(0.0f, 1.0f, 0.0f);             // Wektor "g�ra"
    glm::vec3 right = glm::normalize(glm::cross(direction, up)); // Wektor w prawo

    switch (key) {
    case 27: // ESC - zako�cz program
        instance->stop();
        break;

    case 'w': // Przybli�anie (ruch do przodu)
        position += direction * cameraSpeed;
        instance->camera.setPosition(position.x, position.y, position.z);
        instance->camera.setTarget(position.x + direction.x, position.y + direction.y, position.z + direction.z);
        break;

    case 's': // Oddalanie (ruch do ty�u)
        position -= direction * cameraSpeed;
        instance->camera.setPosition(position.x, position.y, position.z);
        instance->camera.setTarget(position.x + direction.x, position.y + direction.y, position.z + direction.z);
        break;

    case 'a': // Ruch w lewo po osi X
        position -= right * cameraSpeed;
        instance->camera.setPosition(position.x, position.y, position.z);
        instance->camera.setTarget(position.x + direction.x, position.y + direction.y, position.z + direction.z);
        break;

    case 'd': // Ruch w prawo po osi X
        position += right * cameraSpeed;
        instance->camera.setPosition(position.x, position.y, position.z);
        instance->camera.setTarget(position.x + direction.x, position.y + direction.y, position.z + direction.z);
        break;

    case 'q': // Obr�t w lewo (wok� osi Y)
    {
        float yaw = glm::radians(-rotationAngle); // Obr�t w lewo
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), yaw, up);
        glm::vec3 newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));
        instance->camera.setTarget(position.x + newDirection.x, position.y + newDirection.y, position.z + newDirection.z);
        break;
    }

    case 'e': // Obr�t w prawo (wok� osi Y)
    {
        float yaw = glm::radians(rotationAngle); // Obr�t w prawo
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), yaw, up);
        glm::vec3 newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));
        instance->camera.setTarget(position.x + newDirection.x, position.y + newDirection.y, position.z + newDirection.z);
        break;
    }

    case 'z': // Patrzenie w g�r� (wok� osi X)
    {
        float pitch = glm::radians(rotationAngle);
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), pitch, right);
        glm::vec3 newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));
        instance->camera.setTarget(position.x + newDirection.x, position.y + newDirection.y, position.z + newDirection.z);
        break;
    }

    case 'x': // Patrzenie w d� (wok� osi X)
    {
        float pitch = glm::radians(-rotationAngle);
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), pitch, right);
        glm::vec3 newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));
        instance->camera.setTarget(position.x + newDirection.x, position.y + newDirection.y, position.z + newDirection.z);
        break;
    }
    case 'l':
        if (instance->lightingEnabled) {
            glDisable(GL_LIGHTING); // Wy��czenie o�wietlenia
            std::cout << "Oswietlenie wylaczone" << std::endl;
        }
        else {
            glEnable(GL_LIGHTING); // W��czenie o�wietlenia
            std::cout << "Oswietlenie wlaczone" << std::endl;
        }
        instance->lightingEnabled = !instance->lightingEnabled;
        break;
    case 'p': {
            instance->currentProjectionMode = ProjectionMode::PERSPECTIVE;
            instance->reshapeCallback(instance->windowWidth, instance->windowHeight);
            break;
    }
    case 'o': {
        instance->currentProjectionMode = ProjectionMode::ORTHOGRAPHIC;
        instance->reshapeCallback(instance->windowWidth, instance->windowHeight);
        break;
        }

    case '1': {
        glShadeModel(GL_FLAT);
        std::cout << "GL_FLAT" << std::endl;
        break;
    }
    case '2': {
        glShadeModel(GL_SMOOTH);
        std::cout << "GL_SMOOTH" << std::endl;
        break;
    }
    case 'r': // Resetuj rakiet�
        rocketY = 0.0f;
        break;
    case '=': // Zwi�ksz pr�dko��
        rocketSpeed += 0.01f;
        break;
    case '-': // Zmniejsz pr�dko��
        rocketSpeed -= 0.01f;
        break;
    case ']': // Pauza/wzn�w
        rocketSpeed = (rocketSpeed == 0.0f) ? 0.05f : 0.0f;
        break;
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






