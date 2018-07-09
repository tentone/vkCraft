#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Object3D.cpp"

class Camera : public Object3D
{
public:
	glm::mat4 projection;
	float aspect;
	float near, far, fov;

	Camera(float _fov = 60.0f, float _near = 0.1f, float _far = 1000.0f)
	{
		fov = _fov;
		near = _near;
		far = _far;
	}

	void updateMatrix()
	{
		matrix = glm::translate(glm::mat4(), position);
		matrix = glm::rotate(matrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		matrix = glm::rotate(matrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		matrix = glm::rotate(matrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		matrix = glm::scale(matrix, scale);
		matrix = glm::inverse(matrix);
	}

	void updateProjectionMatrix(float width, float height)
	{
		aspect = width / height;
		projection = glm::perspective(glm::radians(fov), aspect, near, far);

		//Fix Y direction from OpenGL to Vulkan
		projection[1][1] *= -1;
	}
};
