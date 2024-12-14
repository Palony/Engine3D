#pragma once
#include <GL/freeglut.h>
#include <glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/transform.hpp>>
#include <gtc/type_ptr.hpp>


class GameObject
{
private:
	glm::vec3 position;
	glm::vec3 scale;
	
public:

	void setPoistion(const glm::vec3& Pos);
	glm::vec3 getPoistion();
	void setScale(const glm::vec3& sc);
	glm::vec3 getScale();
};
