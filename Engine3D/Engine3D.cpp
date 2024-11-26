//#include <gl\gl.h>
#include "Engine.h"

Engine engine;

// Drawing function:
void OnDraw() {
    // Background colour (R, G, B, Alpha):
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    // Clearing the colour buffer:
    glClear(GL_COLOR_BUFFER_BIT);
    // Flushing the rendering queue:
    glFinish();	// or glFlush();
}

int main(int argc, char* argv[]) {
       
    engine.createWindow();


    // Drawing callback function:
    glutDisplayFunc(engine.render);

    glutMainLoop();
    return 0;
}