#include "Geometric_Objects.h"

void Geometric_Objects::draw_points(const float PointVerts[], const float PointColours[], int numPoints)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, PointVerts);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, PointColours);

    glDrawArrays(GL_POINTS, 0, numPoints);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}


void Geometric_Objects::draw_line(const float LineVerts[], const float LineColours[])
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, LineVerts);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, LineColours);

    glDrawArrays(GL_LINES,0,2);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Geometric_Objects::draw_polyline(const float Verts[], const float Colours[], int numPoints)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, Verts);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, Colours);

    glDrawArrays(GL_LINE_STRIP, 0, numPoints);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Geometric_Objects::draw_triangle(const float LineVerts[], const float LineColours[])
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, LineVerts);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, LineColours);

    glDrawArrays(GL_TRIANGLES,0,6);


    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Geometric_Objects::draw_triangle_strip(const float Verts[], const float Colours[], int numPoints)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, Verts);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, Colours);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, numPoints);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
void Geometric_Objects::draw_triangle_fan(const float Verts[], const float Colours[], int numPoints)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, Verts);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, Colours);

    glDrawArrays(GL_TRIANGLE_FAN, 0, numPoints);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}


void Geometric_Objects::draw_rectangle(const float LineVerts[], const float LineColours[])
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, LineVerts);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, LineColours);

    glDrawArrays(GL_QUADS, 0, 6);


    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
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





