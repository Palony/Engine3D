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



void Geometric_Objects::draw_sphere(double x, double y, double z, double dRadius, GLint slices, GLint stacks)
{
    glPushMatrix();               // Zapisuje bie¿¹c¹ macierz
    glTranslatef(x, y, z);        // Przesuniêcie obiektu na (x, y, z)
   // glColor3f(0, 150, 240);  // Ustaw kolor kuli (np. ¿ó³ty)
    glutSolidSphere(dRadius, slices, stacks);
    glPopMatrix();                // Przywraca poprzedni stan macierzy
}

void Geometric_Objects::draw_Cube(double dSize)
{
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidCube(dSize);
}

void Geometric_Objects::draw_Torus(double x, double y, double z, double dInnerRadius, double dOuterRadius, GLint nSides, GLint nRings)
{
    glPushMatrix();               // Zapisuje bie¿¹c¹ macierz
    glTranslatef(x, y, z);
    glColor3f(124.0f, 1.0f, 0.0f);
    glutSolidTorus(dInnerRadius, dOuterRadius, nSides, nRings);
    glPopMatrix();
}

void Geometric_Objects::draw_Cylinder(double x, double y, double z, double base, double height, GLint slices, GLint stacks)
{
    glPushMatrix();               // Zapisuje bie¿¹c¹ macierz
    glTranslatef(x, y, z);
    glColor3f(240.0f, 50.0f, 0.0f);
    glutSolidCylinder(base,  height,  slices,  stacks);
    glPopMatrix();
}

void Geometric_Objects::draw_Cone(double x, double y, double z, double base, double height, GLint slices, GLint stacks)
{
    glPushMatrix();               // Zapisuje bie¿¹c¹ macierz
    glTranslatef(x, y, z);
    glColor3f(47, 79, 79);
    glutSolidCone(base, height, slices, stacks);
    glPopMatrix();
}

void Geometric_Objects::draw_Box(const float cube_vert[], const float cube_norm[], const float cube_cols[], const unsigned char cube_ind[])
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, cube_vert);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, cube_norm);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, cube_cols);
    
        

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, cube_ind);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Geometric_Objects::draw_sphere_with_texture(double x, double y, double z, double dRadius, GLint slices, GLint stacks, GLuint textureID)
{
    glPushMatrix();
    glTranslatef(x, y, z);

    // Enable texturing and bind the texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Generate texture coordinates for the sphere
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE); // Enable texture generation
    gluQuadricNormals(quadric, GLU_SMOOTH); // Smooth normals for lighting

    // Draw the sphere
    gluSphere(quadric, dRadius, slices, stacks);

    // Cleanup
    gluDeleteQuadric(quadric);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}





