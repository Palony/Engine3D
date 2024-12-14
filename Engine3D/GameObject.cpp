#include "GameObject.h"

void GameObject::setPoistion(const glm::vec3& Pos)
{
	position = Pos;
}

glm::vec3 GameObject::getPoistion()
{
	return position;
}

void GameObject::setScale(const glm::vec3& sc)
{
	scale = sc;
}

glm::vec3 GameObject::getScale()
{
	return scale;
}
