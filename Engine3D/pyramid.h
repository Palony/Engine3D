#pragma once
#include "ShapeObject.h"
class Pyramid :public ShapeObject
{
public:
	Pyramid();
	void draw(const float pryamid_vert[], const float pryamid_norm[], const float pyramid_cols[], const unsigned char pyramid_ind[]);
	void translate();
	void rotate();
	void scale();

private:
	glm::mat4 transformationMatrix;
};