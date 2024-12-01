#include "Geometric_Objects.h"


void Geometric_Objects::draw_traingle(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    // Rysowanie trójk¹ta
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru trójk¹ta
    glVertex3f(x1, y1, z1);  // Wierzcho³ek górny
    glVertex3f(x2, y2, z2); // Wierzcho³ek dolny prawy
    glVertex3f(x3, y3, z3); // Wierzcho³ek dolny lewy
    glEnd();
}

void Geometric_Objects::draw_rectangle(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3, GLfloat x4, GLfloat y4, GLfloat z4)
{
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru trójk¹ta
    glVertex3f(x1, y1, z1);  // Wierzcho³ek lewy górny
    glVertex3f(x2, y2, z2); // Wierzcho³ek prawny górny
    glVertex3f(x3, y3, z3); // Wierzcho³ek dolny lewy
    glVertex3f(x4, y4, z4); // Wierzcho³ek prawy lewy
    glEnd();
}

void Geometric_Objects::draw_sphere(double dRadius, GLint slices, GLint stacks)
{
    glColor3f(1.0f, 1.0f, 0.0f);  // Ustawienie koloru kuli na ¿ó³ty
    glutSolidSphere(dRadius,slices,stacks); // Rysowanie pe³nej kuli 
}

void Geometric_Objects::draw_Cube(double dSize)
{
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidCube(dSize);
}

void Geometric_Objects::draw_Torus(double dInnerRadius, double dOuterRadius, GLint nSides, GLint nRings)
{
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidTorus(dInnerRadius, dOuterRadius, nSides, nRings);
}

void Geometric_Objects::draw_Cylinder(double base, double height, GLint slices, GLint stacks)
{
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidCylinder(base,  height,  slices,  stacks);
}

void Geometric_Objects::draw_Cone(double base, double height, GLint slices, GLint stacks)
{
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidCone(base, height, slices, stacks);
}





