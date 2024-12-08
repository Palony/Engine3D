#include "Engine.h"

int main() {
    // Konfiguracja silnika
    Engine engine(800, 600, "Silnik3D", false);

    // Parametryzacja
    engine.setGraphicsMode(false, 800, 600); // Tryb okienkowy 800x600
    engine.setFrameRate(60);                 // 60 klatek na sekundê
    engine.enableMouseInput(true);           // W³¹cz obs³ugê myszy
    engine.enableKeyboardInput(true);        // W³¹cz obs³ugê klawiatury
    engine.enableDepthBuffer(true);          // W³¹cz bufor g³êbi
    engine.setClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Kolor t³a: czarny



    // Uruchomienie silnika
    engine.start();



    return 0;
}
