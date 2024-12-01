#pragma once
#include <GL/freeglut.h>

class Geometric_Objects
{
public:

	void draw_traingle(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3);  //Rysuje tr�jk�t
	void draw_rectangle(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3, GLfloat x4, GLfloat y4, GLfloat z4); //Rysuje prostok�t
	void draw_sphere(double dRadius, GLint slices, GLint stacks); //Rysuje kule
	void draw_Cube(double dSize); // Rysuje sze�cian
	void draw_Torus(double dInnerRadius, double dOuterRadius, GLint nSides, GLint nRings); //Rysuje pier�cie�
	void draw_Cylinder(double base, double height, GLint slices, GLint stacks); //Rysuje cylinder
	void draw_Cone(double base, double height, GLint slices, GLint stacks); // Rysuje sto�ek

};

