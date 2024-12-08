#include "Engine.h"

int main() {
    // Konfiguracja silnika
    Engine engine(800, 600, "Silnik3D", false);

    // Parametryzacja
    engine.setGraphicsMode(false, 800, 600); // Tryb okienkowy 800x600
    engine.setFrameRate(60);                 // 60 klatek na sekund�
    engine.enableMouseInput(true);           // W��cz obs�ug� myszy
    engine.enableKeyboardInput(true);        // W��cz obs�ug� klawiatury
    engine.enableDepthBuffer(true);          // W��cz bufor g��bi
    engine.setClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Kolor t�a: czarny



    // Uruchomienie silnika
    engine.start();



    return 0;
}
