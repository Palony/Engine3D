#include "Engine.h"
#include <iostream>
#include "Camera.h"
#include "Cube.h"
#include "Lighting.h"
//#include "Material.h"
#include "BitmapHandler.h"


Engine* Engine::instance = nullptr;
//zmienne globalne dla dema
float rocketY = 0.0f; // Pozycja pionowa rakiety
float rocketSpeed = 0.0; // Prêdkoœæ lotu rakiety
float rotationAngle = 0.0f; // K¹t obrotu wokó³ œrodka rakiety
float cubeRotationAngle = 0.0f; // K¹t obrotu szeœcianu
float cubeScaleFactor = 0.5f;   // Wspó³czynnik skalowania szeœcianu
float scaleDirection = 0.001f;   // Kierunek skalowania (rosn¹cy/malej¹cy)
Light light;
//Material material;

const float base_vert[] = {
-1.0f, -3.0f,  1.0f,   1.0f, -3.0f,  1.0f,  -1.0f,  1.0f,  1.0f,   1.0f,  1.0f,  1.0f,
-1.0f, -3.0f, -1.0f,  -1.0f,  1.0f, -1.0f,   1.0f, -3.0f, -1.0f,   1.0f,  1.0f, -1.0f,
-1.0f,  1.0f, -1.0f,  -1.0f,  1.0f,  1.0f,   1.0f,  1.0f, -1.0f,   1.0f,  1.0f,  1.0f,
-1.0f, -3.0f, -1.0f,   1.0f, -3.0f, -1.0f,  -1.0f, -3.0f,  1.0f,   1.0f, -3.0f,  1.0f,
 1.0f, -3.0f, -1.0f,   1.0f,  1.0f, -1.0f,   1.0f, -3.0f,  1.0f,   1.0f,  1.0f,  1.0f,
-1.0f, -3.0f, -1.0f,  -1.0f, -3.0f,  1.0f,  -1.0f,  1.0f, -1.0f,  -1.0f,  1.0f,  1.0f,
};

const float top_vert[] = {
    // Podstawa ostros³upa (rozszerzona do wymiarów base)
    -1.0f, 1.0f, -1.0f,  // Wierzcho³ek 0
     1.0f, 1.0f, -1.0f,  // Wierzcho³ek 1
     1.0f, 1.0f,  1.0f,  // Wierzcho³ek 2
    -1.0f, 1.0f,  1.0f,  // Wierzcho³ek 3

    // Wierzcho³ek szczytowy (pozostaje bez zmian)
     0.0f, 3.0f,  0.0f   // Wierzcho³ek 4
};
const float base_colors[] = {
    // Kolory dla dolnej podstawy
    0.5f, 0.5f, 0.5f,  // Wierzcho³ek 0 (czerwony)
    0.5f, 0.5f, 0.5f,  // Wierzcho³ek 1 (zielony)
    0.5f, 0.5f, 0.5f,  // Wierzcho³ek 2 (niebieski)
    0.5f, 0.5f, 0.5f,  // Wierzcho³ek 3 (¿ó³ty)

    // Kolory dla górnej podstawy
    0.5f, 0.5f, 0.5f,  // Wierzcho³ek 4 (fioletowy)
    0.5f, 0.5f, 0.5f,  // Wierzcho³ek 5 (turkusowy)
    0.5f, 0.5f, 0.5f,  // Wierzcho³ek 6 (szary)
    0.5f, 0.5f, 0.5f   // Wierzcho³ek 7 (bia³y)
};

const float top_colors[] = {
    // Kolory dla podstawy
    1.0f, 0.0f, 0.0f,  // Wierzcho³ek 0 (pomarañczowy)
    1.0f, 0.5f, 1.0f,  // Wierzcho³ek 1 (niebieskozielony)
    1.0f, 0.0f, 0.0f,  // Wierzcho³ek 2 (¿ó³ty)
    1.5f, 0.0f, 0.0f,  // Wierzcho³ek 3 (fioletowy)

    // Kolor dla wierzcho³ka szczytowego
    1.0f, 0.0f, 0.0f   // Wierzcho³ek 4 (czerwony)
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
    0.0f, -1.0f,  0.0f,  // Wierzcho³ek 0
    0.0f, -1.0f,  0.0f,  // Wierzcho³ek 1
    0.0f, -1.0f,  0.0f,  // Wierzcho³ek 2
    0.0f, -1.0f,  0.0f,  // Wierzcho³ek 3

    // Normalne dla œcian bocznych
    0.0f,  0.447f,  0.894f,  // Œciana 1
   -0.894f,  0.447f,  0.0f,  // Œciana 2
    0.0f,  0.447f, -0.894f,  // Œciana 3
    0.894f,  0.447f,  0.0f   // Œciana 4
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
    // Podstawa (2 trójk¹ty)
    0, 1, 2,
    0, 2, 3,

    // Œciany boczne (4 œciany, 1 trójk¹t ka¿da)
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

// Wspó³rzêdne tekstury (dla ka¿dego wierzcho³ka):
const float cube2_texc[] = {
    1.0f, 0.0f,		0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f,
    0.0f, 0.0f,		0.0f, 1.0f,		1.0f, 0.0f,		1.0f, 1.0f,
    0.0f, 0.0f,		0.0f, 1.0f,		1.0f, 0.0f,		1.0f, 1.0f,
    1.0f, 0.0f,		0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f,
    0.0f, 0.0f,		0.0f, 1.0f,		1.0f, 0.0f,		1.0f, 1.0f,
    1.0f, 0.0f,		0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f
};

//normalne szeœcianu
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
        std::cerr << "Wiele instancji Engine nie jest obs³ugiwane." << std::endl;
        exit(EXIT_FAILURE);
    }
}


void Engine::toggleLighting() {
    if (lightingEnabled) {
        glDisable(GL_LIGHTING); // Wy³¹cz oœwietlenie
    }
    else {
        glEnable(GL_LIGHTING); // W³¹cz oœwietlenie
    }
    lightingEnabled = !lightingEnabled; // Prze³¹cz stan
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
    // Tabela z punktami:
    glVertexPointer(3, GL_FLOAT, 0, cube2_vert);
    // Tabela ze wspó³rzêdnymi tekstur (2 wspó³rzêdne):
    glTexCoordPointer(2, GL_FLOAT, 0, cube2_texc);


    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    if (depthBufferEnabled) {
        glEnable(GL_DEPTH_TEST);
    }

    //Wlaczenie teksturowania
   
    
    // Inicjalizacja oœwietlenia
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

    // W³¹czenie GL_COLOR_MATERIAL, aby u¿ywaæ naturalnych kolorów obiektów
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    BitmapHandler bitmapHandler;
    GLuint textureID = bitmapHandler.loadTexture("woda.jpg");
    if (textureID != 0) {
        instance->textureID = textureID; // Zapisuje id tekstury 
    }
    else {
        std::cerr << "Nie uda³o siê za³adowaæ tekstury!" << std::endl;
    }

    textureID = bitmapHandler.loadTexture("tex0.png");
    if (textureID != 0) {
        instance->TexID[0] = textureID; // Zapisuje id tekstury 
    }
    else {
        std::cerr << "Nie uda³o siê za³adowaæ tekstury!" << std::endl;
    }

    textureID = bitmapHandler.loadTexture("tex1.png");
    if (textureID != 0) {
        instance->TexID[1] = textureID; // Zapisuje id tekstury 
    }
    else {
        std::cerr << "Nie uda³o siê za³adowaæ tekstury!" << std::endl;
    }

    textureID = bitmapHandler.loadTexture("tex2.png");
    if (textureID != 0) {
        instance->TexID[2] = textureID; // Zapisuje id tekstury 
    }
    else {
        std::cerr << "Nie uda³o siê za³adowaæ tekstury!" << std::endl;
    }
    textureID = bitmapHandler.loadTexture("rocket_tex.png");
    if (textureID != 0) {
        instance->Rocket_tex = textureID; // Zapisuje id tekstury 
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

    instance->camera.apply(); // Zastosowanie ustawieñ kamery 
   
    
    // Kontrola oœwietlenia na podstawie flagi
    if (instance->lightingEnabled) {
        glEnable(GL_LIGHTING);
    }
    else {
        glDisable(GL_LIGHTING);
    }
    


    // Dla rzutowania perspektywicznego przesuwamy scenê do ty³u
    if (instance->currentProjectionMode == ProjectionMode::PERSPECTIVE) {
        glTranslatef(0.0f, 0.0f, -5.0f);
    }

    //// Rysowanie osi wspó³rzêdnych
    //glBegin(GL_LINES);
    //// Oœ X (czerwona)
    //glColor3f(1.0f, 0.0f, 0.0f);
    //glVertex3f(-2.0f, 0.0f, 0.0f);
    //glVertex3f(2.0f, 0.0f, 0.0f);
    //// Oœ Y (zielona)
    //glColor3f(0.0f, 1.0f, 0.0f);
    //glVertex3f(0.0f, -2.0f, 0.0f);
    //glVertex3f(0.0f, 2.0f, 0.0f);
    //// Oœ Z (niebieska)
    //glColor3f(0.0f, 0.0f, 1.0f);
    //glVertex3f(0.0f, 0.0f, -2.0f);
    //glVertex3f(0.0f, 0.0f, 2.0f);



    //glEnd();

    //instance->geometric_Objects.draw_rectangle(-1.0f, 1.0f, 0.0f, 
    //    1.0f, 1.0f, 0.0f,   
    //    1.0f, -1.0f, 0.0f,   
    //    -1.0f, -1.0f, 0.0f); 

    // Wywo³anie funkcji rysuj¹cej kulê


    //rysuje kule
   //instance->geometric_Objects.draw_sphere(1.0, 16, 16);


    //rysuje szeœcian
    //instance->geometric_Objects.draw_Cube(2);

    // Wektor Wierzcholkow dla punktów
    const float PointVerts[] = {
        0.2f, 0.1f, 0.2f, // Punkt 1
        0.5f, 0.5f, 0.2f, // Punkt 2
       -0.5f, -0.5f, 0.2f // Punkt 3
    };

    // Wektor kolorow dla punktów
    const float PointColours[] = {
        1.0f, 0.0f, 0.0f, // Kolor punktu 1
        0.0f, 1.0f, 0.0f, // Kolor punktu 2
        0.0f, 0.0f, 1.0f  // Kolor punktu 3
    };

    // Wywo³anie metody rysuj¹cej punkty
    //instance->geometric_Objects.draw_points(PointVerts, PointColours, 3); 

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

    //instance->geometric_Objects.draw_line(LineVerts, LineColours);
    
    /*
    // rysowanie ³amanych
    // Wektor Wierzcholkow dla linii ³amanej
    const float PolylineVerts[] = {
        -1.0f, -1.0f, 0.2f, // Punkt 1
        -0.5f,  0.5f, 0.2f, // Punkt 2
         0.0f, -0.5f, 0.2f, // Punkt 3
         0.5f,  0.5f, 0.2f  // Punkt 4
    };

    // Wektor kolorow dla linii ³amanej
    const float PolylineColours[] = {
        1.0f, 0.0f, 0.0f, // Czerwony dla Punktu 1
        0.0f, 1.0f, 0.0f, // Zielony dla Punktu 2
        0.0f, 0.0f, 1.0f, // Niebieski dla Punktu 3
        1.0f, 1.0f, 0.0f  // ¯ó³ty dla Punktu 4
    };

    // Wywo³anie rysowania linii ³amanej
    instance->geometric_Objects.draw_polyline(PolylineVerts, PolylineColours, 4);
    */
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
        1.0f, 1.0f, 0.0f  // ¯ó³ty
    };

    instance->geometric_Objects.draw_triangle_strip(TriangleStripVerts, TriangleStripColours, 4);
    */
    //rysowanie wachlarzy trojkata
    /*
    const float TriangleFanVerts[] = {
    0.0f,  0.0f, 0.0f, // Punkt 1 (wspólny)
    -1.0f, -1.0f, 0.0f, // Punkt 2
     1.0f, -1.0f, 0.0f, // Punkt 3
     1.0f,  1.0f, 0.0f, // Punkt 4
    -1.0f,  1.0f, 0.0f  // Punkt 5
    };

    const float TriangleFanColours[] = {
        1.0f, 1.0f, 1.0f, // Bia³y (dla Punktu 1)
        1.0f, 0.0f, 0.0f, // Czerwony
        0.0f, 1.0f, 0.0f, // Zielony
        0.0f, 0.0f, 1.0f, // Niebieski
        1.0f, 1.0f, 0.0f  // ¯ó³ty
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
instance->cube.translate(5, 0, 0); // Przesuniêcie szeœcianu o (x,y,z)
instance->cube.rotate(45, 1.0f, 1.0f, 0); // Obrót o X stopni wokó³ osi X i Y
instance->cube.scale(0.5, 0.5, 0.5); // Zmniejszenie rozmiaru szeœcianu
   */


    //rysowanie szeœcianu
    const float cube_vert[] = {
        //wierzcho³ki szeœcianu
        -1.0f, -1.0f, -1.0f, // 0
        -1.0f, -1.0f,  1.0f, // 1
        -1.0f,  1.0f,  1.0f, // 2
        -1.0f,  1.0f, -1.0f, // 3
         1.0f,  1.0f,  1.0f, // 4
         1.0f,  1.0f, -1.0f, // 5
         1.0f, -1.0f,  1.0f, // 6
         1.0f, -1.0f, -1.0f  // 7
    };

    //normalne szeœcianu
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
    //kolory wierzcho³ków
    const float cube_cols[] = {
      0.0f, 1.0f, 0.0f, // Wierzcho³ek 1 - czerwony
      0.0f, 1.0f, 0.0f, // Wierzcho³ek 2 - czerwony
      0.0f, 1.0f, 0.0f, // Wierzcho³ek 3 - czerwony
      0.0f, 1.0f, 0.0f, // Wierzcho³ek 4 - czerwony
      0.0f, 1.0f, 0.0f, // Wierzcho³ek 5 - czerwony
      0.0f, 1.0f, 0.0f, // Wierzcho³ek 6 - czerwony
      0.0f, 1.0f, 0.0f, // Wierzcho³ek 7 - czerwony
      0.0f, 1.0f, 0.0f  // Wierzcho³ek 8 - czerwony
    };

  
    const unsigned char cube_ind[] = {
        // przednia œciana, wierzcho³ki 1,2,4,6
        1,2,4,  1,4,6,
        // tylna œciana: wierzcho³ki 0,3,5,7
        0,3,5,  0,5,7,
        // lewa œciana wierzcho³ki 0,1,2,3
        0,1,2,  0,2,3,
        // prawa œciana wierzcho³ki 7,6,4,5
        7,6,4,  7,4,5,
        // górna œciana wierzcho³ki 3,2,4,5
        3,2,4,  3,4,5,
        // dolna œciana wierzcho³ki 0,7,6,1
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








    
    //instance->cube.draw(cube_vert, cube_norm, cube_cols, cube_ind); // Rysowanie szeœcianu
    

	//instance->cube2.TexID[0] = instance->TexID[0];
	//instance->cube2.draw_w_texture(cube2_vert, cube2_norm, cube2_ind, cube2_texc); // Rysowanie szeœcianu z tekstur¹




    
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

    // Wspó³rzêdne tekstury (dla ka¿dego wierzcho³ka):
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
	// Przygotowanie szeœcianu:
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	// Tabela z punktami:
	glVertexPointer(3, GL_FLOAT, 0, cube_vert);
	// Tabela ze wspó³rzêdnymi tekstur (2 wspó³rzêdne):
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



    // Ustawienie materia³u
  //  material.applyMaterial();
 //demo

//ruszajacy sie kwadracik
glPushMatrix();
instance->cube.resetTransform();

// Aktualizacja k¹ta obrotu
cubeRotationAngle += 0.5f; // Zwiêksz k¹t obrotu
if (cubeRotationAngle >= 360.0f) {
    cubeRotationAngle -= 360.0f;
}

// Aktualizacja skalowania
cubeScaleFactor += scaleDirection;
if (cubeScaleFactor >= 1.2f || cubeScaleFactor <= 0.3f) {
    scaleDirection = -scaleDirection; // Odwróæ kierunek skalowania
}

// Zastosowanie transformacji
instance->cube.translate(0, 5, 0);                      // Przesuniêcie
instance->cube.rotate(cubeRotationAngle, 1.0f, 1.0f, 0); // Obrót
instance->cube.scale(cubeScaleFactor, cubeScaleFactor, cubeScaleFactor); // Skalowanie

// Rysowanie szeœcianu
instance->cube.draw(cube_vert, cube_norm, cube_cols, cube_ind);
glPopMatrix();

//kula
glPushMatrix();
glColor3f(0.0f, 0.58f, 0.94f); // Kolor kuli (np. niebieski)
instance->geometric_Objects.draw_sphere(0, -7.5, -5, 5, 18, 18);
glPopMatrix();

//torus
glPushMatrix();
glColor3f(0.0f, 0.58f, 0.94f); // Kolor kuli (np. niebieski)
instance->geometric_Objects.draw_Torus(-5, 10.5, -9, 1, 3, 32,32);
glPopMatrix();

//cone
glPushMatrix();
glColor3f(0.0f, 0.58f, 0.94f); // Kolor kuli (np. niebieski)
instance->geometric_Objects.draw_Cone(5, 25, -9,2, 5, 32,16);
glPopMatrix();

// Przywracanie domyœlnego koloru i materia³u
glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru na bia³y (neutralny)


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
if (rocketY > 40.0f) { // Gdy rakieta przekroczy pewn¹ wysokoœæ, wraca na dó³
    rocketY = 0.0f;
    rocketSpeed = 0.f;
}
//demo_end

    // W³¹czenie œwiat³a
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
        glOrtho(-2.0f * aspect, 2.0f * aspect, -2.0f, 2.0f, -200.0f, 200.0f);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//funkcja do prze³¹czania trybów rzutowania
void Engine::keyboardCallback(unsigned char key, int x, int y) {
    const float cameraSpeed = 0.1f;     // Prêdkoœæ ruchu kamery
    const float rotationAngle = 5.0f;  // K¹t obrotu w stopniach

    // Konwersja z const float* na glm::vec3
    glm::vec3 position(instance->camera.getPosition()[0],
        instance->camera.getPosition()[1],
        instance->camera.getPosition()[2]);

    glm::vec3 target(instance->camera.getTarget()[0],
        instance->camera.getTarget()[1],
        instance->camera.getTarget()[2]);

    glm::vec3 direction = glm::normalize(target - position); // Kierunek patrzenia
    glm::vec3 up(0.0f, 1.0f, 0.0f);             // Wektor "góra"
    glm::vec3 right = glm::normalize(glm::cross(direction, up)); // Wektor w prawo

    switch (key) {
    case 27: // ESC - zakoñcz program
        instance->stop();
        break;

    case 'w': // Przybli¿anie (ruch do przodu)
        position += direction * cameraSpeed;
        instance->camera.setPosition(position.x, position.y, position.z);
        instance->camera.setTarget(position.x + direction.x, position.y + direction.y, position.z + direction.z);
        break;

    case 's': // Oddalanie (ruch do ty³u)
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

    case 'q': // Obrót w lewo (wokó³ osi Y)
    {
        float yaw = glm::radians(-rotationAngle); // Obrót w lewo
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), yaw, up);
        glm::vec3 newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));
        instance->camera.setTarget(position.x + newDirection.x, position.y + newDirection.y, position.z + newDirection.z);
        break;
    }

    case 'e': // Obrót w prawo (wokó³ osi Y)
    {
        float yaw = glm::radians(rotationAngle); // Obrót w prawo
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), yaw, up);
        glm::vec3 newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));
        instance->camera.setTarget(position.x + newDirection.x, position.y + newDirection.y, position.z + newDirection.z);
        break;
    }

    case 'z': // Patrzenie w górê (wokó³ osi X)
    {
        float pitch = glm::radians(rotationAngle);
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), pitch, right);
        glm::vec3 newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));
        instance->camera.setTarget(position.x + newDirection.x, position.y + newDirection.y, position.z + newDirection.z);
        break;
    }

    case 'x': // Patrzenie w dó³ (wokó³ osi X)
    {
        float pitch = glm::radians(-rotationAngle);
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), pitch, right);
        glm::vec3 newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));
        instance->camera.setTarget(position.x + newDirection.x, position.y + newDirection.y, position.z + newDirection.z);
        break;
    }
    case 'l':
        if (instance->lightingEnabled) {
            glDisable(GL_LIGHTING); // Wy³¹czenie oœwietlenia
            std::cout << "Oswietlenie wylaczone" << std::endl;
        }
        else {
            glEnable(GL_LIGHTING); // W³¹czenie oœwietlenia
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
    case 'r': // Resetuj rakietê
        rocketY = 0.0f;
        break;
    case '=': // Zwiêksz prêdkoœæ
        rocketSpeed += 0.01f;
        break;
    case '-': // Zmniejsz prêdkoœæ
        rocketSpeed -= 0.01f;
        break;
    case ']': // Pauza/wznów
        rocketSpeed = (rocketSpeed == 0.0f) ? 0.05f : 0.0f;
        break;
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






