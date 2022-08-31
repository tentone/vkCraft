#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

/**
 * Object 3D represents a drawable object that has a pose in the world.
 */
class Object3D
{
public:
	glm::mat4 matrix;

	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	Object3D();

	void updateMatrix();
};
