#pragma once
#include "ShapeObject.h"
class Pyramid :public ShapeObject
{
public:
	Pyramid();
	void draw(const float pryamid_vert[], const float pryamid_norm[], const float pyramid_cols[], const unsigned char pyramid_ind[]);
	void translate(float tx, float ty, float tz);
	void rotate(float angle, float x, float y, float z);
	void scale(float sx, float sy, float sz);

private:
	glm::mat4 transformationMatrix;
};