#pragma once
#include <GL/freeglut.h>

class Geometric_Objects
{
public:

	void draw_line(const float LineVerts[], const float LineColours[]);
	void draw_triangle(const float LineVerts[], const float LineColours[]);
	void draw_rectangle(const float LineVerts[], const float LineColours[]);
	void draw_sphere(double dRadius, GLint slices, GLint stacks); //Rysuje kule
	void draw_Cube(double dSize); // Rysuje szeœcian
	void draw_Torus(double dInnerRadius, double dOuterRadius, GLint nSides, GLint nRings); //Rysuje pierœcieñ
	void draw_Cylinder(double base, double height, GLint slices, GLint stacks); //Rysuje cylinder
	void draw_Cone(double base, double height, GLint slices, GLint stacks); // Rysuje sto¿ek

};

