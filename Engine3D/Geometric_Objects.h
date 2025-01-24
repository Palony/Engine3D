#pragma once
#include <GL/freeglut.h>

class Geometric_Objects
{
public:

	void draw_points(const float PointVerts[], const float PointColours[], int numPoints);
	void draw_polyline(const float PolylineVerts[], const float PolylineColours[], int numPoints);  
	void draw_line(const float LineVerts[], const float LineColours[]);
	void draw_triangle(const float LineVerts[], const float LineColours[]);
	void draw_triangle_strip(const float Verts[], const float Colours[], int numPoints);
	void draw_triangle_fan(const float Verts[], const float Colours[], int numPoints);
	void draw_rectangle(const float LineVerts[], const float LineColours[]);
	void draw_sphere(double x, double y, double z, double dRadius, GLint slices, GLint stacks); //Rysuje kule
	void draw_Cube(double dSize); // Rysuje szeœcian
	void draw_Torus(double x, double y, double z, double dInnerRadius, double dOuterRadius, GLint nSides, GLint nRings); //Rysuje pierœcieñ
	void draw_Cylinder(double x, double y, double z, double base, double height, GLint slices, GLint stacks); //Rysuje cylinder
	void draw_Cone(double x, double y, double z, double base, double height, GLint slices, GLint stacks); // Rysuje sto¿ek
	void draw_Box(const float cube_vert[], const float cube_norm[],const float cube_cols[], const unsigned char cube_ind[]);
	void draw_sphere_with_texture(double x, double y, double z, double dRadius, GLint slices, GLint stacks, GLuint textureID);

};

