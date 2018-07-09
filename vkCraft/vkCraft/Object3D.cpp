#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

class Object3D
{
public:
	glm::mat4 matrix;
	
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	Object3D()
	{
		position = glm::vec3(0.0f, 0.0f, 0.0f);
		scale = glm::vec3(1.0f, 1.0f, 1.0f);
		rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	void updateMatrix()
	{
		matrix = glm::translate(glm::mat4(), position);
		matrix = glm::rotate(matrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		matrix = glm::rotate(matrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		matrix = glm::rotate(matrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		matrix = glm::scale(matrix, scale);
	}
};
