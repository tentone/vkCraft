#pragma once

#include "Object3D.h"

Object3D::Object3D()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Object3D::updateMatrix()
{
	matrix = glm::translate(glm::mat4(), position);
	matrix = glm::rotate(matrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	matrix = glm::rotate(matrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::rotate(matrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::scale(matrix, scale);
}
