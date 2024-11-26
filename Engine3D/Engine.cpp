#include "Engine.h"

void Engine::createWindow()
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Hello OpenGL");

}

void Engine::render()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glFinish();	// or glFlush();
}
